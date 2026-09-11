#!/usr/bin/env python3
"""alloc_table.py <tag> [fn] [dump_root]: the ALLOCATION TABLE of one function, read from gcc 2.7.2's own dumps.

For every pseudo: references, live length, block, the hard register it got, and `global.c allocno_compare`'s priority
`floor(log2 refs) * refs / live * 1e4` — plus, when the `.greg` dump prints them, the allocation ORDER line
(`;; N regs to allocate: …`) and each allocno's copy PREFERENCES (`;; N preferences: …`).

Written at P32 T4c to read the callee-saved bank order. The `.greg` dump carries the INPUTS to global allocation — the order, each allocno's conflicts and its copy
preferences — and not the final assignment, so a global allocno's hard register prints as `-` here; that is the dump's
shape, not a gap, and the order line plus the preferences are what decide it. **Widened at P36 S102, after four T7
agents asked for exactly this table and two reported the tool printing an EMPTY or one-row result** (`func_80143D28`, `func_8016C49C`): it had
only ever printed pseudos that landed in `$s0..$s7`/`$fp`, and it depended on `Register N in M.` lines that the dumps
often do not emit at all — the silently-narrowed-scope defect class, a true number about a scope far narrower than the
reader believes. It now prints every pseudo, takes the hard register from either dump or from the order line, and
ASSERTS ITS OWN COVERAGE (R32): if the `.greg` order line names allocnos this table does not hold, it says so and exits
non-zero rather than printing a confident subset.

Why the table settles arguments the residual cannot: agent a4 flipped a 34-instruction residual to zero by moving one
allocno's priority 6524 → 6808 past another's 6666, and agent a16 closed a body by shortening a live length from 44 to
43. Both are arithmetic on these columns, not a search.
"""
import math, pathlib, re, sys

NAMES = {2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3", 8: "t0", 9: "t1", 10: "t2", 11: "t3", 12: "t4",
         13: "t5", 14: "t6", 15: "t7", 16: "s0", 17: "s1", 18: "s2", 19: "s3", 20: "s4", 21: "s5", 22: "s6",
         23: "s7", 24: "t8", 25: "t9", 28: "gp", 29: "sp", 30: "fp", 31: "ra"}


def section(path, fn):
    """The dump text for one function, or "" when the dump has no such section (a missing dump is not an empty table)."""
    p = pathlib.Path(path)
    if not p.exists():
        return ""
    s = p.read_text(errors="surrogateescape")
    i = s.find(f";; Function {fn}\n")
    if i < 0:
        i = s.find(f"Function {fn}\n")
    if i < 0:
        return ""
    j = s.find(";; Function ", i + 20)
    return s[i:j if j > 0 else None]


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    tag = sys.argv[1]
    fn = sys.argv[2] if len(sys.argv) > 2 else None
    root = sys.argv[3] if len(sys.argv) > 3 else ".run/P36/dumps"
    d = f"{root}/dumps_{tag}"
    if fn is None:
        print("alloc_table: a function name is required (arg 2)")
        return 2
    lreg, greg = section(f"{d}/{tag}.i.lreg", fn), section(f"{d}/{tag}.i.greg", fn)
    if not lreg and not greg:
        print(f"alloc_table: NO DUMP for {fn} under {d} — the section is absent, which is not an empty table. "
              f"Check that cc1_dumps_tu.sh ran (it refuses a short preprocess now) and that the function is in this TU.")
        return 3
    regs = {}
    for m in re.finditer(r"Register (\d+) used (\d+) times across (\d+) insns(?: in block (-?\d+))?([^\n]*)", lreg):
        regs[int(m.group(1))] = dict(refs=int(m.group(2)), live=int(m.group(3)), block=m.group(4),
                                     extra=m.group(5).strip())
    hard, pref, conf = {}, {}, {}
    for txt in (greg, lreg):
        for m in re.finditer(r"Register (\d+) in (\d+)\.", txt):
            hard.setdefault(int(m.group(1)), int(m.group(2)))
        for m in re.finditer(r";;\s*(\d+) in (\d+)\b", txt):          # the `;; 74 in 5` form
            hard.setdefault(int(m.group(1)), int(m.group(2)))
        for m in re.finditer(r";;\s*(\d+) preferences:\s*([0-9 ]+)", txt):
            pref[int(m.group(1))] = [int(x) for x in m.group(2).split()]
        for m in re.finditer(r";;\s*(\d+) conflicts:\s*([0-9 ]+)", txt):
            conf[int(m.group(1))] = [int(x) for x in m.group(2).split()]
    order = []
    mo = re.search(r";;\s*(\d+) regs to allocate:\s*([0-9 ]+)", greg)
    if mo:
        order = [int(x) for x in mo.group(2).split()]
    rows = []
    for n, r in regs.items():
        # global.c:594-603 stores the priority in a `register int` — TRUNCATED — and breaks a tie by allocno number (:607).
        # S104 e12/e14: two closes hinged on ties the old float column hid (245.6 vs 245.2 are both 245).
        pri = int((math.floor(math.log2(r["refs"])) * r["refs"] / r["live"]) * 10000) if r["refs"] > 0 and r["live"] > 0 else 0
        rows.append((pri, n, r))
    rows.sort(key=lambda x: (-x[0], x[1]))
    print(f"alloc_table {fn} ({tag}): {len(regs)} pseudo(s) in the .lreg table"
          + (f"; .greg order: {' '.join(str(x) for x in order)}" if order else "; .greg printed no order line"))
    print(f"  {'pseudo':>7} {'hard':>5} {'pri':>10} {'refs':>5} {'live':>5} {'blk':>5}  prefs / notes")
    tied = {p_ for p_, c in __import__("collections").Counter(p_ for p_, _n, _r in rows).items() if c > 1 and p_ > 0}
    for pri, n, r in rows:
        h = hard.get(n)
        hn = NAMES.get(h, str(h)) if h is not None else "-"
        note = r["extra"][:44]
        if n in pref:
            note = f"prefers {','.join(NAMES.get(x, str(x)) for x in pref[n])}  " + note
        if n in conf:
            hardconf = [NAMES[x] for x in conf[n] if x in NAMES]      # the HARD regs it may not take
            if hardconf:
                note = f"conflicts {','.join(hardconf)}  " + note
        if pri in tied:
            note = "TIE (lower allocno wins, global.c:607)  " + note
        print(f"  r{n:<6} {hn:>5} {pri:10d} {r['refs']:5d} {r['live']:5d} {str(r['block']):>5}  {note}")
    # R32: the order line over-approximates the allocnos; anything it names that this table lacks is a SILENT GAP
    missing = [x for x in order if x not in regs]
    if missing:
        print(f"  COVERAGE GAP: the .greg order line names {len(missing)} allocno(s) absent from the .lreg table: "
              f"{missing} — the table above is a SUBSET, not the allocation.")
        return 1
    if order:
        print(f"  coverage OK: every allocno in the .greg order line ({len(order)}) is in the table")
    return 0


if __name__ == "__main__":
    sys.exit(main())
