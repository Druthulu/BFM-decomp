#!/usr/bin/env python3
"""wall_sweep.py — enumerate the §332 maspsx `la`-in-a-delay-slot walls, fleet-wide. (P31 S68)

WHY THIS EXISTS. Cookbook §332 states the class is "6 FUNCTIONS FLEET-WIDE, NONE BANKABLE FROM C"
and names TWO of them (`func_80062144`, `func_8005DBD8`). §332a then says, correctly, *"Filter
before drafting"* — but a filter needs the LIST, and the other four were never written down. So the
draw kept handing them to agents:

    S68 `main/func_80061FA8` — a FABLE agent produced C that `oracle_reorder` proves BYTE-CORRECT
    (0 diffs / 103 ins) and that the pinned triple still cannot emit: two §332 `la`-in-jal-slot
    sites plus one §188 epilogue. 92,684 tokens to rediscover a known class.

**A count without an enumeration cannot drive a filter.** The detection is mechanical, so this
turns the sentence into a list.

THE TELL. gcc-2.7.2's `movsi_internal` emits a symbolic address load as ONE atomic RTL insn of
length 2 (the `lui`+`addiu %lo(...)` pair; this MIPS backend has no HIGH/LO_SUM define_split). A
delay slot holding the SECOND HALF of such a pair therefore cannot be produced from C — the
assembler filled it, and maspsx cannot reproduce that.
So: a delay slot (the line after an unconditional jump / jal / branch) whose text is an
`addiu <reg>,<reg>,%lo(<sym>)`.

COVERAGE (R32). The denominator is every `.s` under the asm tree for every OPEN stub — printed, with
the count of files that could not be read. A hit list that does not state what it scanned is not
evidence.

    tools/wall_sweep.py                 # report
    tools/wall_sweep.py --emit-exclude  # binary:fn lines, ready for draw_waves --exclude
"""
import argparse
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus     # noqa: E402
import progress   # noqa: E402

# THE .s LINES CARRY A COMMENT PREFIX: `    /* 52854 80062054 3771010C */  jal   func_X`.
# My first version anchored the mnemonic at ^\s* and therefore matched NOTHING — the sweep
# returned a confident 0 across 1,378 files while a function I already KNEW had two of these sat in
# the scan set. That null was caught only because the rule "a sweep returning 0 must prove it can
# return non-zero" was applied to my own tool (R32/R40). Skip the comment before matching.
_PFX = r"^\s*(?:/\*[^*]*\*/)?\s*"
BRANCH = re.compile(_PFX + r"(jal|j|jr|b|beq|bne|beqz|bnez|blez|bgez|bltz|bgtz|bc\w+)\s")
# WIDER THAN `addiu ...,%lo(` ALONE. The first version matched only the `la` second half and so
# MISSED func_8005DBD8, which §332a names — its slot holds `sw $v0, %lo(D_800729A0)($at)`, the
# second half of a `lui $at,%hi / sw %lo($at)` STORE macro. Same mechanism, different mnemonic: any
# `%lo(` in a delay slot is the tail of an assembler macro pair that gcc emits as ONE atomic insn,
# so C can never put it there. Iterating the detector against a KNOWN member is what exposed the
# narrowness — a hit list that cannot reproduce the members you already know is not evidence.
LA_LO = re.compile(_PFX + r"\S+\s+.*%lo\(")


def scan(path):
    """[(lineno, branch_text, slot_text)] for every delay slot holding a macro tail (%lo)."""
    try:
        with open(path, errors="replace") as fh:
            lines = fh.readlines()
    except OSError:
        return None
    hits = []
    for i, ln in enumerate(lines[:-1]):
        if BRANCH.match(ln) and LA_LO.match(lines[i + 1]):
            hits.append((i + 1, ln.strip(), lines[i + 1].strip()))
    return hits


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--emit-exclude", action="store_true",
                    help="print `binary:fn` lines only, for draw_waves --exclude")
    a = ap.parse_args()

    scanned = unreadable = 0
    walls = []
    for b in progress.BINARIES:
        try:
            stubs = corpus.stubs(b)
        except Exception as e:
            print("  oracle refused %s: %r" % (b, e), file=sys.stderr)
            continue
        for s in stubs.values():
            p = os.path.join(s.asm_dir, s.symbol + ".s")
            if not os.path.exists(p):
                unreadable += 1
                continue
            scanned += 1
            hits = scan(p)
            if hits is None:
                unreadable += 1
            elif hits:
                walls.append((b, s.symbol, corpus.s_ins_count(p), hits))

    if a.emit_exclude:
        for b, fn, _n, _h in sorted(walls):
            print("%s:%s" % (b, fn))
        return 0

    print("scanned %d open stub .s file(s); %d unreadable/absent" % (scanned, unreadable))
    print("§332 `la`-in-a-delay-slot WALLS: %d function(s)\n" % len(walls))
    for b, fn, n, hits in sorted(walls):
        print("  %-14s %-18s %4d ins  %d site(s)" % (b, fn, n, len(hits)))
        for ln, br, slot in hits[:2]:
            print("        line %-6d %-28s | slot: %s" % (ln, br, slot))
    return 0


if __name__ == "__main__":
    sys.exit(main())
