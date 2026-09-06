#!/usr/bin/env python3
"""ghost_census.py — the frame-residue oracle for gcc-2.7.2 dumps (P32 T4b hand pass, 2026-09-06; cookbook §501-M).

A GHOST is a pseudo that still carries flow's `reg_n_refs > 0` but has NO occurrence left in the insn stream.
Reload gives every ghost with `reg_renumber < 0` and no REG_EQUIV an 8-byte `alter_reg` slot (reload1.c:658,
align -1 = BIGGEST_ALIGNMENT) — the "never-referenced frame slot" residual (§172, §501-M).  Whether a ghost
actually gets the slot depends on WHEN it was minted:

  * minted by combine (the `newi2pat` split paths, combine.c:1887 / 1963) — BEFORE regclass, so regclass sees no
    occurrence and gives it `ST_REGS or none`: unallocatable → slot.   [these are the ones that matter]
  * minted by local-alloc's `optimize_reg_copy_2` (`tmp = x; tmp = tmp op c; x = tmp;`) — AFTER regclass, so it
    keeps `GR_REGS` and no conflicts: global allocates it → NO slot.  (byte-measured, P14 in
    .run/P32/t4c/func_80032A74/)

So the census reads the `.lreg` dump (post-sched, pre-alloc: the register headers are flow's counts as updated by
combine/sched/update_equiv_regs) and reports every header whose pseudo does not occur in the insn stream, with its
class — `ST_REGS or none` ⇒ this ghost WILL take a slot; `GR_REGS …` ⇒ it will not.  Use `vars=` on the `.frame`
line as the final arbiter (tools/cc1_dumps.sh prints both).

usage: ghost_census.py <tag>.i.lreg [<tag>.i.lreg ...]
exit 0 always (a census, not a gate); prints one line per ghost, nothing when there are none.
"""
import re
import sys


def census(path):
    text = open(path, errors="replace").read()
    first_insn = text.find("\n(")
    headers, body = (text[:first_insn], text[first_insn:]) if first_insn >= 0 else (text, "")
    regs = re.findall(r"^Register (\d+) used (\d+) times[^\n]*?;\s*([^\n]*)$", headers, re.M)
    occurrences = set(re.findall(r"\(reg[^ ]* (\d+)\)", body))
    out = []
    for regno, refs, tail in regs:
        if regno not in occurrences:
            cls = tail.strip().rstrip(".")
            slot = "SLOT" if "ST_REGS" in cls or "NO_REGS" in cls else "allocatable, no slot"
            out.append((int(regno), int(refs), cls, slot))
    return out


def main(argv):
    if len(argv) < 2 or argv[1] in ("-h", "--help"):
        print(__doc__)
        return 0
    for path in argv[1:]:
        rows = census(path)
        tag = path if len(argv) > 2 else ""
        for regno, refs, cls, slot in rows:
            print(f"   GHOST{(' ' + tag) if tag else ''}: pseudo {regno} refs={refs} [{cls}] -> {slot}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
