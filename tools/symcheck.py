#!/usr/bin/env python3
"""symcheck.py — the pre-gate SYMBOL-SET guard (BFM Phase 29 SESSION-18).

Diff the set of symbols a draft's object REFERENCES against the set the target `.s` references
(`%hi`/`%lo`/`jal`). A mismatch is a link-level defect that every masked-diff oracle we own is
STRUCTURALLY BLIND TO:

  * `tools/match_one.py` / `tools/masked_diff.py` compare relocation-MASKED words, so a reloc against
    the wrong symbol scores as a match at that position (object-vs-.s mode is symbol-agnostic by
    construction — see masked_diff's docstring).
  * `tools/rtu_match.py` COMPILES but never LINKS, so an extern that no symbol table can resolve is
    invisible to it *by construction*, not merely masked.

That combination produced the SESSION-17 `func_801463A0` trap: the draft invented `_s`-suffixed alias
externs (`D_80126BE0_s`) that no symbol table defines, read MATCH under rtu_match, and could never
bank. The whole-binary byte-gate caught it (G3/P9, as always) — but only after a full gate cycle, and
the *cause* took a symbol-set comparison to find. This makes that comparison a one-command check you
run BEFORE paying for a gate.

Two failure directions, both reported:
  MISSING  — in the target, absent from the draft: a dropped reference, or a symbol renamed/aliased
             into something that resolves elsewhere. This is the invented-alias signature.
  INVENTED — in the draft, absent from the target: a symbol the original function never touched.

Exit 0 iff the sets are equal. Not a match oracle and not a substitute for the byte-gate — a cheap
necessary condition (R34: a second oracle that can DISAGREE with the masked ones).

  python3 tools/symcheck.py func_8014D820 --c .run/giants/s18_func_8014D820_close14.c \
      --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_after
  python3 tools/symcheck.py func_8014D820 --obj build/.../foo.o --asm-subdir <dir>
"""
import argparse
import glob
import os
import re
import subprocess
import sys

OBJDUMP = "mipsel-linux-gnu-objdump"
PY = ".venv/bin/python"
HERE = os.path.dirname(os.path.abspath(__file__))

# `%hi(sym)` / `%lo(sym)` / `jal sym` in a splat .s. The target .s is RESOLVED (no reloc records), so
# the symbol names only survive in this operand syntax — which is exactly why the masked oracles,
# which work on the encoded word, cannot see them.
_S_SYM = re.compile(r"%(?:hi|lo)\(([A-Za-z_][A-Za-z0-9_]*)\)|\bjal\s+([A-Za-z_][A-Za-z0-9_]*)")
_O_SYM = re.compile(r"R_MIPS_\S+\s+([A-Za-z_][A-Za-z0-9_]*)")


def target_syms(s_path):
    out = set()
    with open(s_path) as fh:
        for line in fh:
            for a, b in _S_SYM.findall(line):
                out.add(a or b)
    return out


def object_syms(obj, fn=None):
    """Symbols referenced by relocations in `obj`. With `fn`, only relocs inside that function's
    section slice — objects here are one-function-per-file, so the whole-object set is the same."""
    txt = subprocess.run([OBJDUMP, "-drz", "-r", obj], capture_output=True, text=True).stdout
    return set(m.group(1) for m in _O_SYM.finditer(txt))


def compile_draft(fn, c_path, asm_subdir, o0=False):
    """Compile via match_one so the triple/flags can never drift from the real gate path (R33:
    derive, don't re-derive). Returns the object it left behind."""
    work = os.path.join(".run/symcheck", f"{fn}.{os.getpid()}")
    cmd = [PY, os.path.join(HERE, "match_one.py"), fn, "--c", c_path,
           "--asm-subdir", asm_subdir, "--work", work]
    if o0:
        cmd.append("--o0")
    subprocess.run(cmd, capture_output=True, text=True)
    hits = glob.glob(os.path.join(work, "**", "*.o"), recursive=True)
    if not hits:
        sys.exit(f"symcheck: match_one produced no object for {fn} (does the draft compile?)")
    return hits[0]


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fn")
    ap.add_argument("--c", help="draft C (externs + def); compiled via match_one")
    ap.add_argument("--obj", help="pre-compiled object instead of --c")
    ap.add_argument("--asm-subdir", required=True, help="dir holding <fn>.s")
    ap.add_argument("--o0", action="store_true", help="compile at -O0 (the _o0 split subsegments)")
    a = ap.parse_args()

    if not (a.c or a.obj):
        ap.error("one of --c or --obj is required")

    s_path = os.path.join(a.asm_subdir, f"{a.fn}.s")
    if not os.path.exists(s_path):
        sys.exit(f"symcheck: no target .s at {s_path}")

    obj = a.obj or compile_draft(a.fn, a.c, a.asm_subdir, a.o0)
    tgt, mine = target_syms(s_path), object_syms(obj, a.fn)

    missing = sorted(tgt - mine)
    invented = sorted(mine - tgt)

    if not missing and not invented:
        print(f"SYMS-OK  {a.fn}   {len(tgt)} symbols agree")
        return 0

    print(f"SYMS-DIFF  {a.fn}   target={len(tgt)} draft={len(mine)}")
    for s in missing:
        print(f"  MISSING   {s}   (target references it; draft does not -- dropped ref, or an "
              f"invented alias standing in for it)")
    for s in invented:
        print(f"  INVENTED  {s}   (draft references it; target does not -- if no symbol table "
              f"defines it, rtu_match will still read MATCH and the gate will always reject)")
    return 1


if __name__ == "__main__":
    sys.exit(main())
