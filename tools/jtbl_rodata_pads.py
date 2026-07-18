#!/usr/bin/env python3
"""Phase-29 §8e: reproduce the ORIGINAL's jump-table padding in a multi-table .rodata carve.

The mechanism (byte-proven, .run/probe_jtbl/verdict.md):
  - cc1 (Sony gcc 2.7.2) emits `.rdata` + `.align 3` + label before EVERY switch jump table.
  - maspsx passes `.align` through VERBATIM (the maspsx/__init__.py:435 `continue` is in an
    inventory-only pass; the output path re-emits `.align` unchanged).
  - GNU as bakes the align pad into the section SECTION-RELATIVE — the linker can never remove it
    (SUBALIGN(2) caps only the section's *external* placement alignment).
  - The ORIGINAL image packs originally-separate TUs' tables TIGHT (the PSX linker 4-aligned
    section placement), while intra-TU consecutive tables carry REAL zero-word pads where the
    previous table ends ≡4 mod 8.

So when a decomp TU holds MULTIPLE matched jr-functions (originally separate TUs merged), cc1's
`.align 3` fires at boundaries where the original packed tight -> a +4 interior pad -> every
downstream data symbol shifts -> %lo relocs break image-wide. And conversely a table's alignment
pad must appear exactly where the original HAS one. `.align` cannot express this (it is relative
to the section start, whose vram parity varies per overlay sibling) — only explicit pad bytes can.

This filter sits between maspsx and as (Makefile `build/src/%.o` recipe, armed per-object by a
`JTBL_PADS` target-specific make var written by tools/jtbl_carve.py). It REPLACES each rodata
`.align` with the exact pad the original has at that table boundary:

    --pads 0,4,0   ->  table 1: no pad (specs[0] is always 0 — the table starts the section),
                       table 2: one `.word 0` pad, table 3: no pad.

Pads are derived by jtbl_carve from the carve intervals (pad[K] = start[K] - end[K-1], values in
{0,4}), so each overlay sibling gets its own spec from its own addresses. Unfiltered objects
(no JTBL_PADS var — every single-table carve) keep today's byte-identical pipeline.

Fail-loud guards (R32) — each converts a silent downstream SHA1 mismatch into an immediate,
attributable build error:
  - spec count != rodata `.align` count      (table-count drift: a sibling's switch compiled
                                              to a different number of tables)
  - a rodata `.align` other than `.align 3`  (unknown emission shape)
  - rodata content other than $L labels / `.word $L...` / blank  (strings, floats — the carve
                                              model does not cover them)
  - pads[0] != 0, or any pad not in {0, 4}
"""
import argparse
import re
import sys

LABEL_RE = re.compile(r"^\$L\d+:$")
WORD_RE = re.compile(r"^\.word\s+\$L\d+$")


def run(pads, lines, out):
    in_rodata = False
    consumed = 0
    for line in lines:
        s = line.strip()
        if s == ".section .rodata":
            in_rodata = True
            out.write(line)
            continue
        if in_rodata and (s == ".text" or s.startswith(".section")):
            in_rodata = False
            out.write(line)
            continue
        if in_rodata:
            if s.startswith(".align"):
                parts = s.split()
                if len(parts) != 2 or parts[1] != "3":
                    sys.exit(f"jtbl_rodata_pads: unexpected rodata align {s!r} "
                             f"(cc1 emits `.align 3` per jump table — see verdict.md)")
                if consumed >= len(pads):
                    sys.exit(f"jtbl_rodata_pads: more rodata .align directives than pad specs "
                             f"({len(pads)}) — table-count drift vs the carve")
                if pads[consumed] == 4:
                    out.write(".word 0  # jtbl_rodata_pads: original inter-table .align 3 pad\n")
                consumed += 1
                continue
            if s == "" or LABEL_RE.match(s) or WORD_RE.match(s):
                out.write(line)
                continue
            sys.exit(f"jtbl_rodata_pads: unexpected rodata content {s!r} — "
                     f"the carve model covers only jump tables ($L labels + .word entries)")
        out.write(line)
    if consumed != len(pads):
        sys.exit(f"jtbl_rodata_pads: consumed {consumed} rodata .align(s) but {len(pads)} pad "
                 f"spec(s) given — table-count drift vs the carve")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pads", required=True,
                    help="comma list of pad BYTES before each rodata jump table, in emission "
                         "order; pads[0] must be 0")
    a = ap.parse_args()
    try:
        pads = [int(x) for x in a.pads.split(",")]
    except ValueError:
        sys.exit(f"jtbl_rodata_pads: malformed --pads {a.pads!r}")
    if not pads or pads[0] != 0:
        sys.exit(f"jtbl_rodata_pads: pads[0] must be 0 (the first table starts the section): {pads}")
    if any(p not in (0, 4) for p in pads):
        sys.exit(f"jtbl_rodata_pads: every pad must be 0 or 4: {pads}")
    run(pads, sys.stdin, sys.stdout)


if __name__ == "__main__":
    main()
