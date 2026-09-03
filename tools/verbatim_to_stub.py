#!/usr/bin/env python3
"""verbatim_to_stub.py — turn a §265 verbatim `__asm__` body back into an `INCLUDE_ASM` stub.

WHY (P31 S75). `tools/asm_in_c.py` found 147 GAME functions carried as verbatim `__asm__` bodies:
the target assembly pasted into a C string literal, byte-identical by construction and completely
undecompiled. They are real remaining work and they are UNREACHABLE by the toolchain, because every
gate in this project substitutes a draft in place of an `INCLUDE_ASM` line and these have none:

    gate_main.substitute()  -> resolves each entry through the STUB map; a verbatim function is
                               reported `resolved to NO stub` and dropped.
    gate_stage/harvest_verify -> same splice, same gap.
    splat                   -> stops emitting `<fn>.s` once a function is not a stub.

The fix is NOT a parallel gate (R33 — one implementation). It is to put the function back into the
form every existing tool already understands. Converting a verbatim body to `INCLUDE_ASM` is also the
HONEST representation: `INCLUDE_ASM` pastes the very same original assembly, so the bytes are
identical either way, but a stub counts as OUTSTANDING WORK in `progress.py` while a verbatim body
counted as banked. The conversion moves the function from "silently done" to "visibly to do".

BYTE-NEUTRALITY IS ASSERTED, NEVER ASSUMED. `INCLUDE_ASM` includes the same `.s` the block
transcribes, so the emitted bytes must not change — but "must" is a claim, and this tool's whole
purpose is to enable a byte gate, so it refuses to be the one link that goes unchecked. Use
`--gate` to rebuild the binary and compare its SHA before keeping the change.

    tools/verbatim_to_stub.py --binary main --fn func_80047E58            # dry run: show the edit
    tools/verbatim_to_stub.py --binary main --fn func_80047E58 --apply
    tools/verbatim_to_stub.py --binary main --fn func_80047E58 --apply --gate
    tools/verbatim_to_stub.py --restore <path.bak>                        # undo
"""
import argparse
import os
import re
import shutil
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))


def find_block(text, fn):
    """(start, end, asm_subdir_hint) char offsets of the file-scope __asm__ block defining `fn`.

    Brace/paren matched, not regex-sliced: a block contains string literals full of braces and
    parens, and an approximate cut here would corrupt a source file that currently builds."""
    import verbatim_check as VC
    for (ln0, ln1, blk, file_scope) in VC.asm_blocks(text):
        if not file_scope:
            continue
        names = set()
        names |= VC.defined_in(blk)
        if fn in names:
            lines = text.split('\n')
            start = sum(len(l) + 1 for l in lines[:ln0 - 1])
            end = sum(len(l) + 1 for l in lines[:ln1])
            return start, end, blk
    return None, None, None


def asm_subdir_for(binary, fn):
    """The `asm/...` path INCLUDE_ASM must name, derived from how the binary's OTHER stubs spell it."""
    import glob
    pat = (os.path.join(REPO, 'src', '*.c') if binary == 'main'
           else os.path.join(REPO, 'src', binary, '*.c'))
    seen = {}
    for p in glob.glob(pat):
        for m in re.finditer(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\)', open(p, errors='ignore').read()):
            seen.setdefault(os.path.basename(p), m.group(1))
    return seen


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--binary')
    ap.add_argument('--fn')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--gate', action='store_true', help='rebuild the binary and assert the SHA is unchanged')
    ap.add_argument('--restore', help='restore a .bak written by --apply')
    a = ap.parse_args()

    if a.restore:
        orig = a.restore[:-4] if a.restore.endswith('.bak') else None
        if not orig or not os.path.exists(a.restore):
            sys.exit('--restore wants the .bak path written by --apply')
        shutil.copyfile(a.restore, orig)
        os.unlink(a.restore)
        print(f'restored {orig}')
        return

    if not (a.binary and a.fn):
        ap.error('--binary and --fn are required')

    import verbatim_check as VC
    # CASE-NORMALISE THE ADDRESS (P31 S75). splat's convention is `func_%08X` (UPPERCASE hex), but
    # analysis artifacts routinely carry `func_8005ed4c` lowercase — the triage taxonomy did, and
    # asking for the lowercase form found 0 of 24 blocks that were all sitting right there. An
    # address is a NUMBER; matching it as a case-sensitive string is the R48 hazard in its
    # case-sensitivity form. Resolve to whatever spelling the source actually uses, and say so.
    want = a.fn
    m = re.match(r'(func_|D_)([0-9A-Fa-f]{8})$', want)
    hit = None
    for path, b in VC.sources(a.binary):
        text = open(path, errors='ignore').read()
        cands = [want]
        if m:
            cands += [m.group(1) + m.group(2).upper(), m.group(1) + m.group(2).lower()]
        for cand in dict.fromkeys(cands):
            if cand not in text:
                continue
            s, e, blk = find_block(text, cand)
            if s is not None:
                if cand != want:
                    print(f'note: {want} resolved to {cand} (address matched case-insensitively)')
                a.fn = cand
                hit = (path, text, s, e, blk)
                break
        if hit:
            break
    if not hit:
        sys.exit(f'verbatim_to_stub: no file-scope __asm__ block defining {a.fn} in {a.binary} '
                 f'— is it already a stub, or a class-B asm-bodied C function? (R43: refusing to guess)')
    path, text, s, e, blk = hit

    # The asm subdir INCLUDE_ASM must name: take it from a sibling stub in the SAME FILE, because
    # that is the only spelling guaranteed to resolve for this TU (subsegs are per-file, and a
    # neighbouring file's spelling is a different subseg — using it would produce a stub that
    # compiles and includes the WRONG function's asm).
    sib = re.search(r'INCLUDE_ASM\("([^"]+)",\s*\w+\)', text)
    if not sib:
        sys.exit(f'verbatim_to_stub: {os.path.relpath(path, REPO)} has no sibling INCLUDE_ASM to copy '
                 f'the asm subdir spelling from — REFUSING to guess it (a wrong subdir silently '
                 f'includes another function\'s assembly)')
    subdir = sib.group(1)
    stub = f'INCLUDE_ASM("{subdir}", {a.fn});\n'

    print(f'file      : {os.path.relpath(path, REPO)}')
    print(f'block     : chars {s}..{e}  ({blk.count(chr(10)) + 1} lines)')
    print(f'replace with: {stub.strip()}')
    if not a.apply:
        print('\n(dry run — pass --apply)')
        return

    shutil.copyfile(path, path + '.bak')
    open(path, 'w').write(text[:s] + stub + text[e:])
    print(f'applied; backup at {os.path.relpath(path, REPO)}.bak')

    if a.gate:
        print('re-extracting (splat must now emit the .s again) and rebuilding...')
        subprocess.run(['make', 'extract', f'BINARY={a.binary}'], cwd=REPO,
                       capture_output=True, text=True, timeout=3600)
        r = subprocess.run(['make', 'build', f'BINARY={a.binary}', '-j'], cwd=REPO,
                           capture_output=True, text=True, timeout=3600)
        ok = '[ OK ]' in r.stdout or 'BYTE-IDENTICAL' in r.stdout
        print(r.stdout.strip().splitlines()[-2:] and '\n'.join(r.stdout.strip().splitlines()[-2:]))
        if ok:
            print('BYTE-IDENTICAL — the conversion is byte-neutral, as expected.')
        else:
            print('*** NOT byte-identical — restoring the file. The conversion is NOT neutral here '
                  'and the reason must be understood before proceeding.')
            shutil.copyfile(path + '.bak', path)
            os.unlink(path + '.bak')
            sys.exit(1)


if __name__ == '__main__':
    main()
