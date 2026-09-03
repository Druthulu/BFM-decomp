#!/usr/bin/env python3
"""verbatim_target_s.py — regenerate a splat-format target `.s` for a function that is no longer a stub.

WHY THIS EXISTS (P31 S75). `tools/asm_in_c.py` found 147 GAME functions that are §265 verbatim
`__asm__` bodies — assembly pasted into a C string literal, byte-identical by construction and
completely undecompiled. They are real remaining work, and NONE of them can be worked on, because:

    splat emits `asm/nonmatchings/<subseg>/<fn>.s` only for functions that are still INCLUDE_ASM
    stubs. A verbatim body is not a stub, so splat stops emitting its `.s` — and `match_one` and
    `rtu_match` BOTH consume a `.s`. Measured: 1 of 147 had a target on disk.

So the entire class was unworkable, not because the information is missing but because it is in the
wrong FORM. This tool puts it back.

WHERE THE BYTES COME FROM, AND WHY IT MATTERS (R34). From the **extracted ROM image**, never from
the `__asm__` block in our own source. The block is the thing under test: regenerating a target from
it would produce an oracle that agrees with the candidate by construction, and a decompile verified
against it would prove only that we transcribed our own transcription. The image is independent.

Output is byte-compatible with what splat emits, so `match_one --asm-subdir` and `rtu_match` consume
it unchanged:

    /* <fileoff> <vaddr> <LEHEX> */  <mnemonic operands>

The mnemonic column comes from a real `objdump` disassembly (so `detect_o0`'s prologue sniffing and
any human reader get true text); the word column is the ground truth used for comparison.

Usage:
    tools/verbatim_target_s.py --binary main --fn SaveLoadRoutine
    tools/verbatim_target_s.py --all                 # every verbatim body asm_in_c.py finds
    tools/verbatim_target_s.py --all      # default: .run/verbatim_targets/<binary>/<fn>.s
                                      # (NEVER under asm/ — the Makefile globs that tree)
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))

OBJDUMP = 'mipsel-linux-gnu-objdump'


def _fr():
    import family_remap
    return family_remap


def func_extent(binary, fn):
    """(vaddr, nins) for a function, from the binary's sig registry."""
    addr = None
    m = re.match(r'(?:func_|D_)([0-9A-Fa-f]{8})$', fn)
    if m:
        addr = int(m.group(1), 16)
    sig = os.path.join(REPO, '.run', f'sig.{binary}.jsonl')
    if not os.path.exists(sig):
        return None, None
    rows = {}
    for ln in open(sig):
        try:
            r = json.loads(ln)
        except Exception:
            continue
        rows[int(r['addr'], 16)] = r.get('nins')
    if addr is not None and addr in rows:
        return addr, rows[addr]
    # A NAMED function (SaveLoadRoutine, VectorNormal…) has no address in its name. Resolve it
    # through the symbol map rather than guessing — a wrong address silently produces a target for
    # the WRONG FUNCTION, which is the worst possible failure for a matching oracle (R43).
    for f in ('config/symbols.us.txt', f'config/symbols.{binary}.txt'):
        p = os.path.join(REPO, f)
        if not os.path.exists(p):
            continue
        for ln in open(p):
            mm = re.match(rf'\s*{re.escape(fn)}\s*=\s*(0x[0-9A-Fa-f]+)', ln)
            if mm:
                a = int(mm.group(1), 16)
                return a, rows.get(a)
    return None, None


def disassemble(data, vaddr):
    """[(word, text)] for a byte blob at `vaddr`, via a real objdump disassembly."""
    with tempfile.NamedTemporaryFile(suffix='.bin', delete=False) as fh:
        fh.write(data)
        tmp = fh.name
    try:
        # `-z` (--disassemble-zeroes) IS LOAD-BEARING. By default objdump ELIDES runs of zero bytes
        # as `...`, and a MIPS `nop` IS 0x00000000 — so every nop, and every nop-padded tail,
        # silently vanished from the disassembly. Measured across the verbatim class: func_80049610
        # (three nops) produced ZERO instructions, func_80047D3C 31 of 36, func_80049440 5 of 7.
        # The length assertion below caught all of them, which is the only reason this was not
        # shipped as ~30 quietly-truncated targets (R32 — the check is what makes the tool usable).
        r = subprocess.run([OBJDUMP, '-D', '-z', '-b', 'binary', '-m', 'mips:3000', '-EL',
                            f'--adjust-vma={vaddr:#x}', tmp],
                           capture_output=True, text=True, timeout=120)
        out = r.stdout
    except (OSError, subprocess.SubprocessError) as e:
        sys.exit(f'verbatim_target_s: {OBJDUMP} failed: {e}')
    finally:
        os.unlink(tmp)
    insns = []
    for ln in out.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$', ln)
        if m:
            insns.append((int(m.group(2), 16), m.group(3).strip()))
    return insns


def emit(binary, fn, outdir, quiet=False):
    fr = _fr()
    vaddr, nins = func_extent(binary, fn)
    if vaddr is None:
        return None, f'{binary}:{fn}: no address (not in sig registry or symbols) — REFUSING to guess'
    if not nins:
        return None, f'{binary}:{fn}: address 0x{vaddr:08X} known but no nins in the sig registry'
    try:
        img = open(fr.img_path(binary), 'rb').read()
        base = fr.vram_of(binary)
    except Exception as e:
        return None, f'{binary}: cannot read image/vram ({e})'
    off = vaddr - base
    if off < 0 or off + nins * 4 > len(img):
        return None, (f'{binary}:{fn}: extent 0x{vaddr:08X}+{nins} lies outside the image '
                      f'(base 0x{base:08X}, {len(img)} bytes) — REFUSING')
    data = img[off:off + nins * 4]
    insns = disassemble(data, vaddr)
    if len(insns) != nins:
        return None, (f'{binary}:{fn}: objdump produced {len(insns)} instruction(s), sig says '
                      f'{nins} — REFUSING to emit a target that disagrees with the registry')
    os.makedirs(os.path.join(outdir, binary), exist_ok=True)
    path = os.path.join(outdir, binary, f'{fn}.s')
    with open(path, 'w') as fh:
        fh.write(f'.include "macro.inc"\n\n')
        fh.write(f'/* Regenerated target for a §265 verbatim body by tools/verbatim_target_s.py.\n')
        fh.write(f' * Source of truth: the EXTRACTED ROM IMAGE, not the __asm__ block in src/ —\n')
        fh.write(f' * the block is the thing under test. {nins} instructions at 0x{vaddr:08X}. */\n\n')
        fh.write('.section .text\n\n')
        fh.write(f'glabel {fn}\n')
        for k, (word, text) in enumerate(insns):
            va = vaddr + 4 * k
            # BYTE-ORDER hex, not value-order. splat writes the four bytes as they sit in the
            # image (`C8FFBD27` for the instruction 0x27BDFFC8) and masked_diff.insns_from_s reads
            # the column with `struct.unpack("<I", bytes.fromhex(...))`. objdump prints the VALUE,
            # so reversing here double-swaps and every word comes out wrong: measured 91 of 1139
            # words agreeing with splat's own .s for the same function, which is what a
            # known-true cross-check is for (the length matched perfectly, so nothing else caught it).
            le = struct.pack('<I', word).hex().upper()
            fh.write(f'/* {off + 4*k:06X} {va:08X} {le} */  {text}\n')
    if not quiet:
        print(f'  {binary:14s} {fn:26s} {nins:5d} ins @ 0x{vaddr:08X} -> {os.path.relpath(path, REPO)}')
    return path, None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary')
    ap.add_argument('--fn')
    ap.add_argument('--all', action='store_true', help='every verbatim body tools/asm_in_c.py finds')
    ap.add_argument('--game-only', action='store_true', default=True)
    # NOT under asm/ — `build/asm/%.o: asm/%.s` globs that tree, so targets written there are
    # picked up as BUILD OBJECTS and the binary goes red (I did exactly that, P31 S75).
    ap.add_argument('--out', default=os.path.join(REPO, '.run/verbatim_targets'))
    a = ap.parse_args()

    targets = []
    if a.all:
        import asm_in_c
        rows, _ = [], None
        for path, b in asm_in_c.sources(None):
            r, _d = asm_in_c.scan_file(path, b)
            rows += r
        for r in rows:
            if r['cls'] != 'A-FILE-SCOPE-VERBATIM':
                continue
            if a.game_only and r['fn'] in asm_in_c.SDK_NAMES:
                continue
            targets.append((r['binary'], r['fn']))
    elif a.binary and a.fn:
        targets = [(a.binary, a.fn)]
    else:
        ap.error('give --binary and --fn, or --all')

    ok, refused = 0, []
    for b, fn in sorted(set(targets)):
        p, err = emit(b, fn, a.out)
        if p:
            ok += 1
        else:
            refused.append(err)
    print(f'\nemitted {ok} target(s) -> {os.path.relpath(a.out, REPO)}/<binary>/<fn>.s')
    if refused:
        # R32/R43: a refusal is REPORTED, never a silent skip — a missing target is why this whole
        # class was unworkable in the first place.
        print(f'REFUSED {len(refused)} (reported, not skipped):')
        for e in refused[:15]:
            print(f'   {e}')


if __name__ == '__main__':
    main()
