#!/usr/bin/env python3
"""xsig — relocation-masked per-function signatures for CROSS-PROJECT code identification (MIPS, PlayStation-era).

Two projects that compile the SAME source with the SAME compiler emit byte-identical machine code EXCEPT in the
relocated operand fields — `j`/`jal` 26-bit targets and `%hi`/`%lo` 16-bit immediates — which differ by link address.
xsig hashes a signature that MASKS exactly those fields and keeps everything else (opcodes, registers, true constants,
PC-relative branch offsets) verbatim, so a shared signature means "the same function, linked somewhere else".

    sig = sha1( little-endian masked word stream, trailing all-zero (nop) words stripped )

Masking, driven by EXPLICIT relocation information on both sides:
  * j / jal (opcode 2/3): keep the 6-bit opcode, mask the 26-bit target — by opcode, no reloc record needed;
  * an instruction carrying a HI16/LO16 relocation: keep opcode+rs+rt, mask the low 16 bits. The relocation is read
    from the input: a splat-style `.s` line whose operands contain `%hi(` / `%lo(`, or an `objdump -dr` listing whose
    next line names R_MIPS_HI16 / R_MIPS_LO16;
  * everything else is kept — registers are NEVER masked (that is too loose), a constant `lui` stays a constant.
Trailing nops are inter-function alignment padding; stripping them on both sides removes a boundary-dependent length
ambiguity and cannot forge a match. Symmetric and tighter than a heuristic that tracks `lui` pairs, which over-masks.

Library:  signature(pairs) · parse_splat_s(path) · parse_objdump_dr(text) · compare(pairs_a, pairs_b)
CLI:
    xsig.py sign-s      PATH... [--project P] [--dedup] [-o out.jsonl]     one function per splat-style .s file
    xsig.py sign-objdump FILE... [--project P] [-o out.jsonl]              every function in `objdump -dr` texts
    xsig.py cross A.jsonl B.jsonl [--min-ins N]                            join two signature sets on `sig`
    xsig.py verify A B [--name-a F] [--name-b G]                           compare two functions instruction by instruction
    xsig.py selftest                                                        the built-in property checks (no files)
Input files may be splat-style `.s` (one function) or `objdump -dr` text (many functions, --name to pick one).

Written for the Brave Fencer Musashi decompilation (github.com/Druthulu/BFM-decomp), where it compared the unmatched
functions against three sibling decompilations built with the same compiler; see README.md. MIT license.
"""
import argparse
import glob
import hashlib
import json
import os
import re
import struct
import sys

__version__ = "1.0.0"
J_OPS = (2, 3)  # j, jal


# ----------------------------------------------------------------------------- the signature
def mask_word(word, is_addr_imm):
    op = word >> 26
    if op in J_OPS:
        return word & 0xFC000000          # keep opcode, mask the 26-bit target
    if is_addr_imm:
        return word & 0xFFFF0000          # keep opcode + rs + rt, mask the 16-bit immediate
    return word & 0xFFFFFFFF              # keep everything (registers, constants, branch offsets)


def _strip_trailing_nops(masked):
    n = len(masked)
    while n > 0 and masked[n - 1] == 0:
        n -= 1
    return masked[:n]


def signature(pairs):
    """pairs: [(raw_word, is_addr_imm)] → {sig, nins, nins_raw, masked}; `masked` is the trailing-nop-stripped
    masked word list, kept for diffing near-misses."""
    masked = [mask_word(w, a) for (w, a) in pairs]
    core = _strip_trailing_nops(masked)
    buf = b"".join(struct.pack("<I", w) for w in core)
    return {"sig": hashlib.sha1(buf).hexdigest(), "nins": len(core), "nins_raw": len(pairs), "masked": core}


# ----------------------------------------------------------------------------- front-end: splat-style .s
# line form:  /* <offset> <vaddr> <LE-HEX-WORD> */  <mnemonic> <operands>
_SLINE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s+(\S.*)")


def parse_splat_s(path):
    """One function per file (splat's `nonmatchings/*.s`). Returns (pairs, mnemonics)."""
    pairs, mnem = [], []
    with open(path, "r", errors="replace") as fh:
        for line in fh:
            m = _SLINE.search(line)
            if not m:
                continue
            word = struct.unpack("<I", bytes.fromhex(m.group(1)))[0]
            ops = m.group(2)
            pairs.append((word, ("%hi(" in ops) or ("%lo(" in ops)))
            mnem.append(ops.split()[0] if ops.split() else "")
    return pairs, mnem


# ----------------------------------------------------------------------------- front-end: objdump -dr text
_HDR = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
_INS = re.compile(r"^\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(.*)")     # an object file indents the address, a linked ELF does not


def parse_objdump_dr(text):
    """Every function in an `objdump -dr` listing → [(name, pairs, mnemonics)]. HI16/LO16 relocation lines flip the
    preceding instruction's is_addr flag; R_MIPS_26 is handled by opcode; R_MIPS_PC16 (branches) is kept."""
    out, cur, pairs, mnem = [], None, [], []

    def flush():
        if cur is not None and pairs:
            out.append((cur, [(w, bool(a)) for (w, a) in pairs], list(mnem)))

    for line in text.splitlines():
        h = _HDR.match(line)
        if h:
            flush()
            cur, pairs, mnem = h.group(1), [], []
            continue
        mi = _INS.match(line)
        if mi:
            pairs.append([int(mi.group(1), 16), False])
            mnem.append(mi.group(2).split()[0] if mi.group(2).split() else "")
            continue
        if "R_MIPS" in line and pairs and (("_HI16" in line) or ("_LO16" in line)):
            pairs[-1][1] = True
    flush()
    return out


def load_functions(path, name=None):
    """A .s file (one function, named after the file) or an objdump text (many). Returns [(name, pairs, mnem)]."""
    if path.endswith(".s"):
        pairs, mnem = parse_splat_s(path)
        return [(os.path.splitext(os.path.basename(path))[0], pairs, mnem)]
    fns = parse_objdump_dr(open(path, errors="replace").read())
    if name is not None:
        fns = [f for f in fns if f[0] == name]
        if not fns:
            sys.exit(f"xsig: no function named {name!r} in {path}")
    return fns


# ----------------------------------------------------------------------------- compare (the diff a score cannot replace)
def compare(pairs_a, pairs_b):
    """Instruction-by-instruction comparison of two functions' masked streams. Returns a dict:
    same (bool), nins_a/nins_b, relocated (fields masked on the A side), diffs = [(index, word_a, word_b, kind)]
    with kind ∈ {'opcode', 'register', 'immediate', 'length'} — read it before believing any score."""
    sa, sb = signature(pairs_a), signature(pairs_b)
    diffs = []
    n = max(len(sa["masked"]), len(sb["masked"]))
    for i in range(n):
        if i >= len(sa["masked"]) or i >= len(sb["masked"]):
            diffs.append((i, sa["masked"][i] if i < len(sa["masked"]) else None,
                          sb["masked"][i] if i < len(sb["masked"]) else None, "length"))
            continue
        wa, wb = sa["masked"][i], sb["masked"][i]
        if wa == wb:
            continue
        if (wa >> 26) != (wb >> 26) or ((wa >> 26) == 0 and (wa & 0x3F) != (wb & 0x3F)):
            kind = "opcode"
        elif (wa & 0x03E00000) != (wb & 0x03E00000) or (wa & 0x001F0000) != (wb & 0x001F0000) \
                or ((wa >> 26) == 0 and (wa & 0x0000F800) != (wb & 0x0000F800)):
            kind = "register"
        else:
            kind = "immediate"
        diffs.append((i, wa, wb, kind))
    relocated = sum(1 for (w, a) in pairs_a if a or (w >> 26) in J_OPS)
    return {"same": sa["sig"] == sb["sig"], "sig_a": sa["sig"], "sig_b": sb["sig"], "nins_a": sa["nins"],
            "nins_b": sb["nins"], "relocated": relocated, "diffs": diffs}


# ----------------------------------------------------------------------------- CLI
def _record(project, tu, name, pairs, mnem, path=""):
    s = signature(pairs)
    return {"project": project, "tu": tu, "name": name, "kind": "c_function", "sig": s["sig"], "nins": s["nins"],
            "nins_raw": s["nins_raw"], "mnem_head": " ".join(mnem[:6]), "path": path}


def _write(records, out):
    fh = open(out, "w") if out else sys.stdout
    for r in records:
        fh.write(json.dumps(r, separators=(",", ":")) + "\n")
    if out:
        fh.close()


def cmd_sign_s(a):
    paths = []
    for p in a.paths:
        paths += sorted(glob.glob(os.path.join(p, "**", "*.s"), recursive=True)) if os.path.isdir(p) else [p]
    recs, by_sig, empty = [], {}, 0
    for p in paths:
        pairs, mnem = parse_splat_s(p)
        if not pairs:
            empty += 1
            continue
        r = _record(a.project, os.path.dirname(p), os.path.splitext(os.path.basename(p))[0], pairs, mnem, p)
        if a.dedup:
            e = by_sig.get(r["sig"])
            if e is None:
                r["n_loc"], r["locs"] = 1, [{"tu": r["tu"], "name": r["name"]}]
                by_sig[r["sig"]] = r
            else:
                e["n_loc"] += 1
                if len(e["locs"]) < 40:
                    e["locs"].append({"tu": r["tu"], "name": r["name"]})
        else:
            recs.append(r)
    recs = list(by_sig.values()) if a.dedup else recs
    _write(recs, a.out)
    print(f"xsig sign-s: {len(paths)} files ({empty} without instructions) -> {len(recs)} records"
          + (f" ({len(by_sig)} unique signatures)" if a.dedup else "") + (f" -> {a.out}" if a.out else ""), file=sys.stderr)
    return 0 if paths else 2


def cmd_sign_objdump(a):
    recs = []
    for f in a.files:
        tu = os.path.splitext(os.path.basename(f))[0]
        for name, pairs, mnem in parse_objdump_dr(open(f, errors="replace").read()):
            recs.append(_record(a.project, tu, name, pairs, mnem, f))
    _write(recs, a.out)
    print(f"xsig sign-objdump: {len(a.files)} listings -> {len(recs)} functions" + (f" -> {a.out}" if a.out else ""),
          file=sys.stderr)
    return 0 if recs else 2


def _load_jsonl(path):
    return [json.loads(l) for l in open(path) if l.strip()]


def cmd_cross(a):
    A, B = _load_jsonl(a.a), _load_jsonl(a.b)
    by_sig = {}
    for r in B:
        by_sig.setdefault(r["sig"], []).append(r)
    hits = [(ra, rb) for ra in A for rb in by_sig.get(ra["sig"], []) if ra["nins"] >= a.min_ins]
    hits.sort(key=lambda h: -h[0]["nins"])
    print(f"# xsig cross: {len(A)} records ({len(set(r['sig'] for r in A))} unique sigs) x {len(B)} records "
          f"({len(by_sig)} unique sigs), min-ins {a.min_ins} -> {len(hits)} hits")
    print("nins\tsig\tproject_a\tname_a\ttu_a\tproject_b\tname_b\ttu_b")
    for ra, rb in hits:
        print(f"{ra['nins']}\t{ra['sig'][:12]}\t{ra.get('project','')}\t{ra['name']}\t{ra.get('tu','')}\t"
              f"{rb.get('project','')}\t{rb['name']}\t{rb.get('tu','')}")
    return 0


def cmd_verify(a):
    fa = load_functions(a.a, a.name_a)
    fb = load_functions(a.b, a.name_b)
    if len(fa) != 1 or len(fb) != 1:
        sys.exit(f"xsig verify: pick one function per side (--name-a / --name-b): A has {len(fa)}, B has {len(fb)}")
    (na, pa, ma), (nb, pb, mb) = fa[0], fb[0]
    c = compare(pa, pb)
    print(f"xsig verify: {na} ({c['nins_a']} ins) vs {nb} ({c['nins_b']} ins) — {c['relocated']} relocated fields masked on A")
    for i, wa, wb, kind in c["diffs"]:
        fa_ = f"{wa:08x}" if wa is not None else "--------"
        fb_ = f"{wb:08x}" if wb is not None else "--------"
        print(f"  #{i:<4} {fa_}  {fb_}  {kind:9s} {ma[i] if i < len(ma) else ''}")
    kinds = {}
    for _, _, _, k in c["diffs"]:
        kinds[k] = kinds.get(k, 0) + 1
    print("xsig verify: " + ("IDENTICAL up to relocation" if c["same"] else
                             "DIFFERENT — " + ", ".join(f"{v} {k}" for k, v in sorted(kinds.items()))))
    return 0 if c["same"] else 1


def selftest():
    """Property checks on a synthetic stream (no files, no game bytes): self-match, relocation invariance,
    register sensitivity, discrimination, trailing-nop stripping, and the two front-ends agreeing on one function."""
    import random
    rng = random.Random(1)
    # a synthetic 12-instruction function: lui/addiu %hi/%lo pair, a jal, a branch, ALU, loads, a nop tail
    words = [(0x27BDFFE8, False), (0xAFBF0014, False), (0x3C028001, True), (0x24422A40, True), (0x8C430000, False),
             (0x0C004A10, False), (0x00000000, False), (0x10400003, False), (0x24630001, False), (0x8FBF0014, False),
             (0x03E00008, False), (0x27BD0018, False), (0x00000000, False), (0x00000000, False)]
    base = signature(words)
    assert signature(words)["sig"] == base["sig"], "self-match"
    assert base["nins"] == 12 and base["nins_raw"] == 14, "trailing nops stripped, the delay-slot nop kept"
    pert = []
    for w, a in words:
        if (w >> 26) in J_OPS:
            pert.append(((w & 0xFC000000) | rng.randint(1, 0x3FFFFFF), a))
        elif a:
            pert.append(((w & 0xFFFF0000) | rng.randint(1, 0xFFFF), a))
        else:
            pert.append((w, a))
    assert signature(pert)["sig"] == base["sig"], "relocation invariance"
    reg = list(words); w, a = reg[4]; reg[4] = (w ^ (1 << 16), a)              # flip rt of the lw
    assert signature(reg)["sig"] != base["sig"], "register sensitivity"
    other = [(0x00851021, False), (0x03E00008, False), (0x00000000, False)]
    assert signature(other)["sig"] != base["sig"], "discrimination"
    c = compare(words, reg)
    assert not c["same"] and c["diffs"] and c["diffs"][0][3] == "register", "compare classifies a register flip"
    # the two front-ends on the same function
    s_lines, od_lines = [], ["00000000 <fn>:"]
    for i, (w, a) in enumerate(words):
        le = struct.pack("<I", w).hex().upper()
        s_lines.append(f"/* {i*4:X} {0x80010000 + i*4:X} {le} */  ins {'%hi(sym)' if a else 'x'}")
        od_lines.append(f"    {i*4:x}:\t{w:08x} \tins\tx")
        if a:
            od_lines.append(f"\t\t\t{i*4:x}: R_MIPS_{'HI16' if i == 2 else 'LO16'}\tsym")
    import tempfile
    with tempfile.NamedTemporaryFile("w", suffix=".s", delete=False) as t:
        t.write("\n".join(s_lines) + "\n"); sp = t.name
    try:
        pa, _ = parse_splat_s(sp)
    finally:
        os.unlink(sp)
    fb = parse_objdump_dr("\n".join(od_lines))
    assert len(fb) == 1 and signature(pa)["sig"] == signature(fb[0][1])["sig"] == base["sig"], "front-ends agree"
    print("xsig selftest: 7 checks passed (self-match, nop stripping, relocation invariance, register sensitivity, "
          "discrimination, compare classification, front-ends agree)")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(prog="xsig", description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--version", action="version", version=f"xsig {__version__}")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("sign-s", help="sign splat-style .s files (one function each)")
    p.add_argument("paths", nargs="+"); p.add_argument("--project", default="a"); p.add_argument("--dedup", action="store_true")
    p.add_argument("-o", "--out"); p.set_defaults(fn=cmd_sign_s)
    p = sub.add_parser("sign-objdump", help="sign every function in objdump -dr listings")
    p.add_argument("files", nargs="+"); p.add_argument("--project", default="b"); p.add_argument("-o", "--out")
    p.set_defaults(fn=cmd_sign_objdump)
    p = sub.add_parser("cross", help="join two signature sets on sig")
    p.add_argument("a"); p.add_argument("b"); p.add_argument("--min-ins", type=int, default=1); p.set_defaults(fn=cmd_cross)
    p = sub.add_parser("verify", help="compare two functions instruction by instruction")
    p.add_argument("a"); p.add_argument("b"); p.add_argument("--name-a"); p.add_argument("--name-b"); p.set_defaults(fn=cmd_verify)
    p = sub.add_parser("selftest", help="the built-in property checks"); p.set_defaults(fn=lambda a: selftest())
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
