#!/usr/bin/env python3
"""reorder_passthrough.py — the §332b assembler-REORDER path, for the objects that were built that way.

THE PINNED PATH is `cc1 -> maspsx -> as -O1`, and maspsx force-emits `.set noreorder` after every
`.ent`. That is correct for the whole fleet EXCEPT the `800c2` / `800c3` PsyQ island, whose ORIGINAL
objects were assembled in REORDER mode: the assembler itself filled delay slots. `as` cannot be asked
to do that once `.set noreorder` is in the stream, so a whole class of functions there looked like a
permanent compiler wall (§332) when it is really a per-OBJECT assembler MODE.

This filter is the maspsx replacement for those objects, and it does exactly what the proven oracle
(`tools/oracle_reorder.py`, measured 0 diffs on func_80061FA8 where the pinned path gave 57) does:
take cc1's output and rewrite `move` into the `addu rd, rs, $0` form, leaving `.set noreorder` absent
so `as -O2` performs the original reorder-mode slot filling.

WHY NOT MASPSX WITH A FLAG: maspsx's other transforms (div expansion, li expansion, macro handling)
are not needed by these two objects — §332b measured the swap BYTE-INERT across the whole of both —
and adding a mode to a pinned submodule to serve two objects is the larger, less reversible change.

  cc1 ... | python3 tools/reorder_passthrough.py | as -O2 ...

The whole-binary byte gate remains the sole arbiter (G3/P9): if this were wrong for any object it is
built into, main's SHA1 changes and the build fails.
"""
import re
import sys

# `move $a, $b` -> `addu $a, $b, $0`. gcc-2.7.2 emits the macro; the original objects carry the
# expanded form. Identical semantics, and it is what oracle_reorder.py proved byte-exact.
_MOVE = re.compile(r"\tmove\t(\$\w+),(\$\w+)")


def convert(text):
    return _MOVE.sub(lambda m: "\taddu\t%s,%s,$0" % (m.group(1), m.group(2)), text)


if __name__ == "__main__":
    if "--selftest" in sys.argv:
        got = convert("\tmove\t$v0,$a0\n\tnop\n\tmove\t$s1,$zero\n")
        want = "\taddu\t$v0,$a0,$0\n\tnop\n\taddu\t$s1,$zero,$0\n"
        ok = got == want
        # negative control: a line that merely CONTAINS "move" must be untouched
        neg = convert("\tjal\tremove_thing\n")
        ok &= neg == "\tjal\tremove_thing\n"
        print("reorder_passthrough selftest:", "OK" if ok else "FAILED")
        sys.exit(0 if ok else 1)
    sys.stdout.write(convert(sys.stdin.read()))
