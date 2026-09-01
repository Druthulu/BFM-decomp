#!/usr/bin/env python3
"""asm_verbatim.py — emit the cookbook §265 FILE-SCOPE VERBATIM-ASM bank form from a splat `.s`.
(P31 S69, Fable-3 tooling agent.)

WHY. Two functions banked this session by an agent hand-transcribing the target `.s` into a
file-scope `__asm__(...)` block (`main/func_80026514`, `ov_SC05_005/func_80181828`, cookbook §265
+ §383). The transcription is MECHANICAL and every rule it obeys was learned at the cost of a
failed compile somewhere:
  * maspsx parses immediates with `int(x)` (decimal only) on several paths — every hex immediate
    AND every hex memory-operand offset must be rewritten decimal (§265, §383 #1);
  * the block must open `.set noreorder` and close `.set reorder` so maspsx does not pad delay
    slots (it force-emits noreorder after `.ent` anyway, but the explicit pair is what both banked
    forms carry);
  * `.L` local labels, `%hi()/%lo()`, `jal <sym>` and `j .L…` pass through untouched;
  * `.frame/.mask/.fmask` are derived from the prologue the way cc1 would write them (they emit
    no bytes; they are what `.ent`-aware tooling expects to see).

WHAT IT IS NOT. This banks BYTES, not understanding: the output is the INCLUDE_ASM stub's own text
inlined into the TU (INCLUDE_ASM expands to `.include "<fn>.s"` under `.set noreorder`, see
include/include_asm.h), so it is byte-equivalent to the stub BY CONSTRUCTION and the function
stays undecompiled. §265's ACCOUNTING paragraph applies: `corpus.stubs()` stops counting it as a
stub. Use it only for (a) the §332/§188 toolchain walls (`oracle_reorder`-proven C exists and the
pinned triple cannot emit it), and (b) genuinely handwritten asm — never for an ordinary -O2
function that merely resists.

REFUSALS (R43 — loud, never silent). The tool refuses a `.s` that:
  * carries a non-`.text` section (`.section .rodata` — a migrated jump table / string pool; the
    §265 form has no data-emission story and a jtbl function must go through the carve chain);
  * has a `dlabel`, `.word`, `.asciz` or `jtbl_` reference in its text stream;
  * has an instruction the tool does not recognise as safe to rewrite (unknown directive).

VERIFICATION. `--check` compiles the emitted C standalone through the pinned triple via
`tools/match_one.py --c` against the same `.s` and reports MATCH/DIFF: a MATCH proves the block
assembles to the target bytes under maspsx. A negative control is built in: `--check` on a `.s`
this tool refuses must exit non-zero BEFORE any compile.

    tools/asm_verbatim.py asm/nonmatchings/800c3/func_8005FA94.s            # print the C block
    tools/asm_verbatim.py <fn.s> --out draft.c [--check]                     # write + byte-check
    tools/asm_verbatim.py --sweep .run/S68_walls.txt --outdir D --check      # many, with a ledger
"""
import argparse
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

INSN_RE = re.compile(r"^\s*/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*?)\s*$")
LABEL_RE = re.compile(r"^\s*(\.L[0-9A-Fa-f]{8}):\s*$")
GLABEL_RE = re.compile(r"^\s*glabel\s+(\w+)\s*$")
ENDLABEL_RE = re.compile(r"^\s*endlabel\s+(\w+)\s*$")
HEX_RE = re.compile(r"(?<![\w.$%])(-?)0x([0-9A-Fa-f]+)\b")
# Registers cc1 saves and the bit each one owns in `.mask` (gcc mips.c: 1 << regno).
REG_NUM = {"$zero": 0, "$at": 1, "$v0": 2, "$v1": 3, "$a0": 4, "$a1": 5, "$a2": 6, "$a3": 7,
           "$t0": 8, "$t1": 9, "$t2": 10, "$t3": 11, "$t4": 12, "$t5": 13, "$t6": 14, "$t7": 15,
           "$s0": 16, "$s1": 17, "$s2": 18, "$s3": 19, "$s4": 20, "$s5": 21, "$s6": 22, "$s7": 23,
           "$t8": 24, "$t9": 25, "$k0": 26, "$k1": 27, "$gp": 28, "$sp": 29, "$fp": 30, "$s8": 30,
           "$ra": 31}
BRANCH_MNEMS = {"j", "jal", "jr", "jalr", "b", "beq", "bne", "beqz", "bnez", "blez", "bgez", "bltz",
                "bgtz", "bgezal", "bltzal", "bc1t", "bc1f", "bc2t", "bc2f", "beql", "bnel"}


class Refuse(Exception):
    pass


def parse_s(path):
    """-> (fn, [('label', name) | ('insn', text, is_delay_slot)], flags) or raise Refuse."""
    fn = None
    items = []
    seen_section = False
    prev_branch = False
    for raw in open(path, errors="replace"):
        line = raw.rstrip("\n")
        s = line.strip()
        if not s or s.startswith("nonmatching ") or s.startswith("/* Handwritten function */"):
            continue
        if s.startswith(".section"):
            sec = s.split()[1] if len(s.split()) > 1 else "?"
            if sec != ".text":
                raise Refuse(f"non-text section {sec!r} in {path} — migrated rodata/jtbl; not a §265 shape")
            seen_section = True
            continue
        if s.startswith(".align") or s.startswith(".set"):
            continue                     # splat framing; the block writes its own
        m = GLABEL_RE.match(s)
        if m:
            if fn is not None:
                raise Refuse(f"second glabel {m.group(1)} in {path} — one function per block")
            fn = m.group(1)
            continue
        if ENDLABEL_RE.match(s):
            break
        m = LABEL_RE.match(s)
        if m:
            items.append(("label", m.group(1)))
            prev_branch = False
            continue
        if s.startswith("dlabel") or s.startswith("jtbl_") or s.startswith("D_"):
            raise Refuse(f"data label {s[:40]!r} in {path} — not a §265 shape")
        m = INSN_RE.match(line)
        if not m:
            raise Refuse(f"unrecognised line in {path}: {s[:80]!r}")
        text = m.group(4)
        # strip splat's trailing annotations (`/* handwritten instruction */`)
        text = re.sub(r"\s*/\*.*?\*/\s*$", "", text)
        mnem = text.split()[0] if text.split() else ""
        if mnem in (".word", ".asciz", ".byte", ".half", ".short"):
            raise Refuse(f"data directive {mnem} inside the text stream of {path}")
        if "jtbl_" in text:
            raise Refuse(f"jtbl reference in {path} ({text!r}) — route through the carve chain")
        is_delay = bool(re.match(r"^\s{5,}\S", line[line.index("*/") + 2:])) if "*/" in line else False
        items.append(("insn", text, prev_branch))
        prev_branch = mnem in BRANCH_MNEMS
    if fn is None:
        raise Refuse(f"no glabel in {path}")
    if not any(k == "insn" for k, *_ in items):
        raise Refuse(f"no instructions in {path}")
    return fn, items


def hex_to_dec(text):
    """Rewrite every bare hex literal (immediates AND memory offsets) to decimal (§265/§383)."""
    def rep(m):
        v = int(m.group(2), 16)
        return f"{m.group(1)}{v}"
    return HEX_RE.sub(rep, text)


def frame_directives(items):
    """(.frame, .mask, .fmask) the way cc1 writes them, read off the prologue. Zero bytes emitted
    either way; a wrong guess cannot change the object, but a plausible one keeps `.ent`-aware
    tooling (maspsx's own function bookkeeping) on the path the two banked forms took."""
    insns = [t for k, t, *_ in items if k == "insn"]
    frame = 0
    for t in insns[:4]:
        m = re.match(r"addiu\s+\$sp,\s*\$sp,\s*(-?\d+)", hex_to_dec(t))
        if m and int(m.group(1)) < 0:
            frame = -int(m.group(1))
            break
    mask, top = 0, None
    for t in insns[:frame // 4 + 8 if frame else 8]:
        m = re.match(r"sw\s+(\$\w+),\s*(-?\d+)\(\$sp\)", hex_to_dec(t))
        if m and m.group(1) in REG_NUM and REG_NUM[m.group(1)] >= 16:
            mask |= 1 << REG_NUM[m.group(1)]
            off = int(m.group(2))
            top = off if top is None else max(top, off)
    if frame and mask and top is not None:
        mask_off = top + 4 - frame
    else:
        mask_off = 0
    return (f".frame\t$sp,{frame},$31", f".mask\t0x{mask:08X},{mask_off}", ".fmask\t0,0")


def render(fn, items, src_rel, comment=None):
    fr, mk, fm = frame_directives(items)
    out = []
    out.append("/* %s — cookbook §265 VERBATIM-ASM bank (file-scope form), generated by" % fn)
    out.append(" * tools/asm_verbatim.py from %s." % src_rel)
    if comment:
        for c in comment.splitlines():
            out.append(" * " + c)
    out.append(" * Byte-equivalent to the INCLUDE_ASM stub by construction; the function is NOT")
    out.append(" * decompiled (§265 ACCOUNTING). Immediates/offsets are decimal for maspsx (§383).")
    out.append(" */")
    out.append("__asm__(")
    out.append('    ".text\\n"')
    out.append('    ".align\\t2\\n"')
    out.append('    ".globl\\t%s\\n"' % fn)
    out.append('    ".ent\\t%s\\n"' % fn)
    out.append('    "%s:\\n"' % fn)
    out.append('    "%s\\n"' % fr.replace("\t", "\\t"))
    out.append('    "%s\\n"' % mk.replace("\t", "\\t"))
    out.append('    "%s\\n"' % fm.replace("\t", "\\t"))
    out.append('    ".set\\tnoreorder\\n"')
    for it in items:
        if it[0] == "label":
            out.append('    "%s:\\n"' % it[1])
        else:
            text = hex_to_dec(it[1])
            text = re.sub(r"\s+", " ", text).strip()
            # maspsx splits operands on WHITESPACE first and commas second (`rest[0].split(",")`
            # for sltu/div/divu/rem), so `sltu $v0, $s0, $v1` dies with "expected 3, got 2".
            # gcc never writes a space after a comma; neither may we.
            text = re.sub(r",\s+", ",", text)
            pad = " " if it[2] else ""
            out.append('    "%s%s\\n"' % (pad, text))
    out.append('    ".set\\treorder\\n"')
    out.append('    ".end\\t%s\\n"' % fn)
    out.append(");")
    return "\n".join(out) + "\n"


def convert(path, comment=None):
    fn, items = parse_s(path)
    return fn, render(fn, items, os.path.relpath(path, REPO), comment)


def check(c_path, fn, s_path):
    """Standalone byte-check via match_one (the pinned triple + relocation-masked compare)."""
    r = subprocess.run([sys.executable, os.path.join(REPO, "tools/match_one.py"), fn, "--c", c_path,
                        "--asm-subdir", os.path.dirname(s_path), "--json"],
                       capture_output=True, text=True, cwd=REPO)
    last = (r.stdout or "").strip().splitlines()
    verdict = None
    for ln in reversed(last):
        if ln.startswith("{"):
            try:
                verdict = json.loads(ln)
                break
            except json.JSONDecodeError:
                pass
    return r.returncode, verdict, (r.stdout + r.stderr)[-1200:]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("s", nargs="?", help="splat .s of the function")
    ap.add_argument("--out", help="write the C block here (default: stdout)")
    ap.add_argument("--check", action="store_true", help="byte-check the block standalone via match_one")
    ap.add_argument("--sweep", help="file of `binary:fn` lines; convert every one (resolved via corpus)")
    ap.add_argument("--outdir", help="with --sweep: write <fn>.c per function here")
    ap.add_argument("--ledger", help="with --sweep: JSON ledger path (default <outdir>/ledger.json)")
    a = ap.parse_args()

    if a.sweep:
        if not a.outdir:
            ap.error("--sweep needs --outdir")
        os.makedirs(a.outdir, exist_ok=True)
        sys.path.insert(0, os.path.join(REPO, "tools"))
        import corpus
        ledger = []
        cache = {}
        for ln in open(a.sweep):
            ln = ln.strip()
            if not ln or ln.startswith("#"):
                continue
            b, fn = ln.split(":", 1)
            if b not in cache:
                # corpus.stubs() is keyed by address; the sweep names functions by SYMBOL.
                cache[b] = {s.symbol: s for s in corpus.stubs(b).values()}
            st = cache[b].get(fn)
            row = {"binary": b, "fn": fn}
            if st is None:
                row["status"] = "NOT-A-STUB"
                ledger.append(row)
                print(f"{b}:{fn}  NOT-A-STUB (banked or unknown)")
                continue
            sp = os.path.join(st.asm_dir, fn + ".s")
            row["s"] = os.path.relpath(sp, REPO)
            try:
                _, c = convert(sp)
            except Refuse as e:
                row["status"] = "REFUSED"
                row["reason"] = str(e)
                ledger.append(row)
                print(f"{b}:{fn}  REFUSED — {e}")
                continue
            cp = os.path.join(a.outdir, f"{b}__{fn}.c")
            open(cp, "w").write(c)
            row["c"] = cp
            if a.check:
                rc, v, tail = check(cp, fn, sp)
                row["check_rc"] = rc
                row["verdict"] = v
                # match_one --json: {"status": "match"|"diff"|"maspsx-fail"|..., "verdict": {"klass": ...}}
                st = (v or {}).get("status")
                klass = ((v or {}).get("verdict") or {}).get("klass")
                if st == "match" or klass == "MATCH":
                    row["status"] = "MATCH"
                elif st in ("near", "diff"):
                    row["status"] = "NEAR" if st == "near" else "DIFF"   # a byte verdict about the block
                elif st:
                    row["status"] = "TOOLFAIL:" + st          # e.g. maspsx-fail — the BLOCK is at fault, not the bytes
                else:
                    row["status"] = "DIFF"
                if row["status"] != "MATCH":
                    row["tail"] = tail
                print(f"{b}:{fn}  {row['status']}  {v}")
            else:
                row["status"] = "EMITTED"
                print(f"{b}:{fn}  EMITTED -> {cp}")
            ledger.append(row)
        lp = a.ledger or os.path.join(a.outdir, "ledger.json")
        json.dump(ledger, open(lp, "w"), indent=1)
        n = len(ledger)
        kinds = sorted({r["status"] for r in ledger})
        print(f"sweep: {n} rows — " + ", ".join(
            f"{k}={sum(1 for r in ledger if r['status'] == k)}" for k in kinds) + f"  ledger={lp}")
        return 0

    if not a.s:
        ap.error("give a .s path or --sweep")
    try:
        fn, c = convert(a.s)
    except Refuse as e:
        print(f"asm_verbatim: REFUSED — {e}", file=sys.stderr)
        return 2
    if a.out:
        open(a.out, "w").write(c)
        print(f"asm_verbatim: wrote {a.out} ({fn})")
    else:
        sys.stdout.write(c)
    if a.check:
        cp = a.out
        if not cp:
            cp = os.path.join(REPO, ".run", "asm_verbatim", f"{fn}.c")
            os.makedirs(os.path.dirname(cp), exist_ok=True)
            open(cp, "w").write(c)
        rc, v, tail = check(cp, fn, a.s)
        print(f"asm_verbatim --check {fn}: {v if v else tail[-400:]}")
        ok = bool(v) and (v.get("status") == "match" or ((v.get("verdict") or {}).get("klass") == "MATCH"))
        return 0 if ok else 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
