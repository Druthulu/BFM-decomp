#!/usr/bin/env python3
"""sig_image.py — Ghidra-FREE per-function signer for a flat PS1 image (Phase 11).

Signs a flat binary (an extracted overlay payload `0.4.dec`, or the resident `1.1`) at a known
vram base, emitting JSONL field-identical to tools/ghidra_scripts/DumpFunctionSignatures.java so a
function appearing in both an imported binary and a flat image hashes the SAME. This lets all ~134
overlays be signed WITHOUT importing each into Ghidra — the input to the cross-binary dedup report.

`h_exact` is the workhorse: it is SHA1 of the function's raw instruction bytes — format-independent,
so it needs only correct boundaries + a byte slice (no normalization). All overlays load at the same
vram (0x80128158), so a shared function at the same offset is byte-identical (h_exact) across overlays.

`h_norm`/`h_seq` (structural / mnemonic tiers) require replicating Ghidra's normToken + mnemonic
rendering exactly — that calibration + its resident acceptance gate is T5. UNTIL T5, this tool emits
h_norm = h_seq = h_exact (a CONSERVATIVE placeholder: it produces zero false structural matches; it
never claims two different-byte functions are structurally equal). Overlays are not signed until T6
(after T5 calibrates), so the cross-report only ever consumes the calibrated tiers.

Disassembly (rabbitizer — the same engine splat uses) is needed ONLY for boundary detection
(`jr $ra` ends, `jal` call targets) and (in T5) normalization.

Usage:
  sig_image.py --image PATH --vram-base HEX [--name NAME] [--out PATH]
               [--seeds PATH] [--text-lo HEX] [--text-hi HEX] [--bootstrap]
  --seeds  : known function entry addresses — a sig .jsonl (reads 'addr'+'name') or a plain
             list of 0xADDR lines. Without --seeds, --bootstrap discovers entries by jal-closure.
  --text-lo/--text-hi : restrict the code sweep (exclude data/rodata). Default: derived from seeds.
"""
import argparse, hashlib, json, pathlib, struct, sys
import rabbitizer as R


def make_insn(word, vram):
    """Decode one 32-bit word at vram. cop2/GTE words (opcode 0x12) need the GTE category."""
    if (word >> 26) == 0x12:
        try:
            return R.Instruction(word, vram, category=R.InstrCategory.R3000GTE)
        except Exception:
            pass
    return R.Instruction(word, vram)


def read_seeds(path):
    """Return {addr: name}. Accepts a sig .jsonl (uses 'addr'/'name') or plain 0xADDR lines."""
    seeds = {}
    for line in pathlib.Path(path).read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("{"):
            r = json.loads(line)
            seeds[int(r["addr"], 16)] = r.get("name", "")
        else:
            seeds[int(line, 0)] = ""
    return seeds


def bootstrap_seeds(data, vram_base, lo, hi):
    """Discover entries with no Ghidra: every in-range jal target + the region start (jal-closure,
    the match_protos anchor model). Misses functions reached ONLY via jump tables — a documented
    coverage gap, acceptable for the dedup scan (h_exact still collapses what IS reached)."""
    seeds = {lo}
    for off in range(lo - vram_base, hi - vram_base, 4):
        word = struct.unpack_from("<I", data, off)[0]
        ins = make_insn(word, vram_base + off)
        if ins.isFunctionCall():
            t = ins.getInstrIndexAsVram()
            if lo <= t < hi:
                seeds.add(t)
    return seeds


def func_end(data, vram_base, start, hard_end):
    """End = the first `jr $ra`(+delay slot) that lies at/after EVERY forward branch/jump target seen
    so far. This (a) does not mistake an early-return `jr` for the end (a later branch jumps past it),
    and (b) ignores a trailing orphan `jr;nop` after the real epilogue (the double-epilogue case). No
    qualifying return (tail-call / data) -> hard_end (the next seed)."""
    max_target = start
    o = start - vram_base
    end_off = hard_end - vram_base
    while o + 4 <= end_off:
        vram = vram_base + o
        ins = make_insn(struct.unpack_from("<I", data, o)[0], vram)
        if ins.isReturn() and vram >= max_target:
            return min(hard_end, vram + 8)  # jr + its delay slot
        tgt = None
        if ins.isBranch():
            try: tgt = ins.getBranchVramGeneric()
            except Exception: tgt = None
        elif ins.isJump() and not ins.isFunctionCall():
            try: tgt = ins.getInstrIndexAsVram()
            except Exception: tgt = None
        if tgt is not None and start <= tgt < hard_end:
            max_target = max(max_target, tgt)
        o += 4
    return hard_end


# I-type opcodes whose 16-bit immediate is an ADDRESS low-half when the base/source register (rs)
# currently holds a lui-loaded address high (hi/lo pairing): loads, stores, addiu/ori/etc.
_ITYPE_ADDR = frozenset((0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,   # lb lh lwl lw lbu lhu lwr
                         0x28, 0x29, 0x2A, 0x2B, 0x2E,               # sb sh swl sw swr
                         0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E))  # addi addiu slti sltiu andi ori xori


def norm_stream(raw):
    """Self-consistent normalized byte stream: mask the address-sensitive fields so two
    structurally-identical functions at DIFFERENT addresses normalize to the same bytes —
      * j / jal       : 26-bit target -> 0
      * lui           : 16-bit high   -> 0  (and the dest register is flagged 'holds an addr-hi')
      * lw/sw/addiu/… : 16-bit imm    -> 0  ONLY when rs holds a lui-loaded addr-hi (hi/lo pair)
    while KEEPING registers (regalloc matters), true constants, and PC-relative branch offsets
    (already position-independent in the encoding). NOT byte-identical to Ghidra's normToken
    (a deliberately different, simpler model — the scope-guard path); self-consistent WITHIN
    sig_image so the overlay fleet's structural dups group. h_exact stays the format-independent
    cross-tool tier. The hi/lo tracker is consistent (depends only on the instruction stream, not
    absolute addresses), so any imprecision is conservative: it can miss a match, never forge one."""
    pending_hi = set()   # registers currently holding a lui address-high
    out = bytearray()
    for k in range(0, len(raw) - (len(raw) % 4), 4):
        w = struct.unpack_from("<I", raw, k)[0]
        op = w >> 26
        rs = (w >> 21) & 0x1F
        rt = (w >> 16) & 0x1F
        nw = w
        if op in (2, 3):                       # j / jal -> mask absolute target
            nw = w & 0xFC000000
        elif op == 0x0F:                       # lui -> mask high; rt now holds an addr-hi
            nw = w & 0xFFFF0000
            pending_hi.add(rt)
            out += struct.pack("<I", nw)
            continue
        elif op in _ITYPE_ADDR:
            if rs in pending_hi:               # hi/lo pair -> the lo immediate is address-derived
                nw = w & 0xFFFF0000
            pending_hi.discard(rt)             # rt is overwritten (no longer a stale hi)
        elif op == 0:                          # R-type: dest rd overwritten
            pending_hi.discard((w >> 11) & 0x1F)
        out += struct.pack("<I", nw)
    return bytes(out)


def sign_function(data, vram_base, start, end, name):
    off = start - vram_base
    n = end - start
    raw = data[off:off + n]
    h_exact = hashlib.sha1(raw).hexdigest()
    mnem = []
    calls = []
    for k in range(0, n, 4):
        word = struct.unpack_from("<I", raw, k)[0]
        ins = make_insn(word, start + k)
        mnem.append(ins.getOpcodeName())
        if ins.isFunctionCall():
            try:
                calls.append(f"{ins.getInstrIndexAsVram():08x}")  # 8-hex, NO 0x — matches the Ghidra dumper
            except RuntimeError:
                pass  # jalr (register-indirect call): no static target, as in the reference-based dumper
    h_norm = hashlib.sha1(norm_stream(raw)).hexdigest()       # self-consistent (see norm_stream)
    h_seq = hashlib.sha1((" ".join(mnem) + " ").encode()).hexdigest() if mnem else h_exact
    return {
        "addr": f"0x{start:08x}", "name": name or f"func_{start:08x}", "src": "IMAGE",
        "nins": n // 4, "nbytes": n, "ncalls": len(calls),
        "h_exact": h_exact, "h_norm": h_norm, "h_seq": h_seq, "calls": calls,
    }


def sign_image(data, vram_base, seeds_map, lo, hi):
    """seeds_map: {addr: name}. Functions are [seed, next_seed) trimmed to the real return end."""
    seeds = sorted(a for a in seeds_map if lo <= a < hi)
    rows = []
    for i, s in enumerate(seeds):
        hard = seeds[i + 1] if i + 1 < len(seeds) else hi
        end = func_end(data, vram_base, s, hard)
        rows.append(sign_function(data, vram_base, s, end, seeds_map.get(s, "")))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--image", required=True, help="flat payload (0.4.dec / 1.1)")
    ap.add_argument("--vram-base", required=True, help="fileoff->vram delta (resident 0x800CEDF8, overlay 0x80128158)")
    ap.add_argument("--name", default=None, help="output stem -> .run/sig.<name>.jsonl")
    ap.add_argument("--out", default=None, help="explicit output path (overrides --name)")
    ap.add_argument("--seeds", default=None, help="known entry addrs: a sig .jsonl or 0xADDR-per-line")
    ap.add_argument("--text-lo", default=None, help="code region start vram (default: min seed)")
    ap.add_argument("--text-hi", default=None, help="code region end vram (default: image end)")
    ap.add_argument("--bootstrap", action="store_true", help="discover entries by jal-closure (no --seeds)")
    a = ap.parse_args()

    data = pathlib.Path(a.image).read_bytes()
    vram_base = int(a.vram_base, 0)
    img_end = vram_base + len(data)

    if a.seeds:
        seeds_map = read_seeds(a.seeds)
    elif a.bootstrap:
        seeds_map = {}
    else:
        sys.exit("sig_image: need --seeds or --bootstrap")

    # lo defaults to vram_base (never below it): a sig .jsonl may carry out-of-range IMPORTED
    # entries (e.g. 0x2000xxxx GTE-macro thunks) — excluded by the [lo,hi) seed filter.
    lo = int(a.text_lo, 0) if a.text_lo else vram_base
    hi = min(int(a.text_hi, 0), img_end) if a.text_hi else img_end
    if a.bootstrap and not seeds_map:
        seeds_map = {s: "" for s in bootstrap_seeds(data, vram_base, lo, hi)}

    rows = sign_image(data, vram_base, seeds_map, lo, hi)

    name = a.name or pathlib.Path(a.image).stem
    out = pathlib.Path(a.out) if a.out else pathlib.Path(".run") / f"sig.{name}.jsonl"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("".join(json.dumps(r, separators=(",", ":")) + "\n" for r in rows))
    print(f"sig_image: {len(rows)} functions [{lo:#010x}..{hi:#010x}) -> {out}")


if __name__ == "__main__":
    main()
