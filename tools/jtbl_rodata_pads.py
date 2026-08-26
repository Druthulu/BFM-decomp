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


def parse_spec(spec):
    """'0,4,0t1' -> [(0,0),(4,0),(0,1)]: per jump table, (leading pad bytes, trailing pad WORDS).
    P31 S62 T3a: `t<n>` is the module-island shape (§154-A) — a matched body re-emits only the real
    entries while the retail island carries n zero words after the table."""
    out = []
    for tok in spec.split(","):
        m = re.fullmatch(r"(0|4)(?:t(\d+))?", tok.strip())
        if not m:
            sys.exit(f"jtbl_rodata_pads: malformed pad token {tok!r} (want 0, 4, 0t<n> or 4t<n>)")
        out.append((int(m.group(1)), int(m.group(2) or 0)))
    return out


def run(pads, lines, out):
    """Table-aware (P31 S62 T3a): only an `.align 3` that is FOLLOWED by a `$L` label is a jump
    table (cc1's emission shape); every other rodata line — const data (`.align 2`, `D_…:`,
    `.byte`), string pools, `.include`s — passes through untouched, so the filter now serves
    module TUs (whose .rodata mixes tables with data) as well as the overlay carves."""
    lines = list(lines)
    in_rodata = False
    consumed = 0
    in_table = False
    saw_words = False
    trailing = 0
    def end_table():
        nonlocal in_table, trailing, saw_words
        if in_table:
            for _ in range(trailing):
                out.write(".word 0  # jtbl_rodata_pads: original trailing pad word (module island)\n")
            in_table, trailing, saw_words = False, 0, False
    for k, line in enumerate(lines):
        s = line.strip()
        if s == ".section .rodata" or s == ".rdata":
            end_table(); in_rodata = True; out.write(line); continue
        if in_rodata and (s == ".text" or s.startswith(".section")):
            end_table(); in_rodata = False; out.write(line); continue
        if not in_rodata:
            out.write(line); continue
        if in_table and (WORD_RE.match(s) or (not saw_words and LABEL_RE.match(s))):
            if WORD_RE.match(s):
                saw_words = True
            out.write(line); continue
        if in_table:
            end_table()
        if s.startswith(".align"):
            parts = s.split()
            nxt = next((l.strip() for l in lines[k + 1:] if l.strip()), "")
            if len(parts) == 2 and parts[1] == "3" and LABEL_RE.match(nxt):
                if consumed >= len(pads):
                    sys.exit(f"jtbl_rodata_pads: more rodata jump tables than pad specs "
                             f"({len(pads)}) — table-count drift vs the carve")
                lead, trailing = pads[consumed]
                if lead == 4:
                    out.write(".word 0  # jtbl_rodata_pads: original inter-table .align 3 pad\n")
                consumed += 1
                in_table, saw_words = True, False
                continue
            out.write(line); continue
        out.write(line)
    end_table()
    if consumed != len(pads):
        sys.exit(f"jtbl_rodata_pads: consumed {consumed} rodata jump table(s) but {len(pads)} pad "
                 f"spec(s) given — table-count drift vs the carve")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pads", required=True,
                    help="comma list, one token per rodata jump table in emission order: the pad "
                         "BYTES before the table (0|4), optionally t<n> = n trailing zero words")
    a = ap.parse_args()
    run(parse_spec(a.pads), sys.stdin, sys.stdout)


if __name__ == "__main__":
    main()
