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

This filter sits between maspsx and as (Makefile `build/src/%.o` recipe). It is armed two ways:
  * a stored `JTBL_PADS` target-specific make var (written by tools/jtbl_carve.py into
    config/overlays.mk) -> `--pads <spec>`; or
  * `--derive <binary> --tu <tu>`, which derives the spec at BUILD TIME from the retail island plus
    the emission stream, with no stored spec at all. The Makefile arms this for every `md_*` object
    **and, since P31 S72, for `main`** — `_file0_vram` returns the code segment's `vram - start`, so
    the same expression indexes the flat overlay blobs and the PS-X EXE past its 0x800 header.
It REPLACES each rodata `.align` with the exact pad the original has at that table boundary:

    --pads 0,4,0   ->  table 1: no pad (specs[0] is always 0 -- the table starts the section),
                       table 2: one `.word 0` pad, table 3: no pad.

Pads are derived by jtbl_carve from the carve intervals (pad[K] = start[K] - end[K-1], values in
{0,4}), so each overlay sibling gets its own spec from its own addresses. Unfiltered objects
(neither a JTBL_PADS var nor --derive) keep today's byte-identical pipeline.

Fail-loud guards (R32) -- each converts a silent downstream SHA1 mismatch into an immediate,
attributable build error. The `--derive` path adds its own: an anchor that does not land where the
island says fails the build with the offset, rather than padding to a guess.
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


# ---------------------------------------------------------------------------------------------
# --derive <binary> (P31 S62 T3a): the MODULE path. No stored spec: the pads are DERIVED at build
# time from the retail island + the stream (R33 — nothing to drift). Items in rodata emission order:
#   .include "….s"   a stub's/blob's block, span read from its `/* off vaddr … */` comments (anchor)
#   D_XXXXXXXX:       C const data, start = the address in its name (anchor), size from directives
#   .align 3 + $L     a C jump table: lead 4 iff the retail word at the position is zero, N in-range
#                     code words, then trailing zeros up to the next anchor (or the next non-zero)
# A walk that misses an anchor refuses with the offset — a CARVE-DRIFT verdict at build time.
# ---------------------------------------------------------------------------------------------
import os, struct

def _splat_yaml(binary):
    """main's config is `splat.us.exe.yaml`; every other binary is `splat.<binary>.yaml`.

    `corpus.splat_config` says the same thing, but this filter sits in the hot `build/src/%.o`
    recipe (once per object, every build), so it stays free of the corpus layer's import cost.
    Kept to one expression so the two cannot drift apart in shape."""
    return "config/splat.us.exe.yaml" if binary == "main" else "config/splat.%s.yaml" % binary


def _file0_vram(y):
    """The vram that byte 0 of the target file corresponds to.

    For a flat overlay blob this IS the segment vram: the payload starts at file 0. main is a
    PS-X EXE whose code segment starts at FILE offset 0x800 (the header), so the vram matching
    raw[0] is `vram - start` = 0x80010000 - 0x800. Returning the FILE-0 vram rather than the
    segment vram is what makes both `raw[a - vram]` (address -> bytes) and `vram + <yaml offset>`
    (yaml piece -> address) correct in BOTH shapes with one expression instead of two code paths.
    Derived from the same yaml the build reads (R33); `family_remap.vram_of` derives it the same
    way for the family engine."""
    m = re.search(r"-\s*name:\s*\w+\s*\n\s*type:\s*code\s*\n\s*start:\s*(0x[0-9A-Fa-f]+)"
                  r"\s*\n\s*vram:\s*(0x[0-9A-Fa-f]+)", y)
    if m:
        return int(m.group(2), 16) - int(m.group(1), 16)
    m = re.search(r"^\s*vram:\s*(0x[0-9A-Fa-f]+)", y, re.M)
    if not m:
        sys.exit("jtbl_rodata_pads: no vram in the splat config (R32 — refusing a default)")
    return int(m.group(1), 16)


def _module_target(binary):
    y = open(_splat_yaml(binary)).read()
    vram = _file0_vram(y)
    tgt = re.search(r"^\s*(?:target_)?path:\s*(\S+)", y, re.M).group(1)
    return vram, open(tgt, "rb").read()

def _s_rodata_span(path):
    """[lo, hi) vaddr span of everything the included .s emits into .rodata (comments carry vaddr)."""
    lo, hi, in_ro = None, None, False
    for ln in open(path, errors="replace"):
        st = ln.strip()
        if st.startswith(".section"):
            in_ro = ".rodata" in st or ".rdata" in st
            continue
        if not in_ro:
            continue
        m = re.match(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})(?:\s+([0-9A-Fa-f]+))?\s*\*/\s*(\S+)\s*(.*)$", st)
        if m:
            a = int(m.group(1), 16)
            if m.group(2):
                n = len(m.group(2)) // 2
            else:
                d, rest = m.group(3), m.group(4)
                if d in _DIRSIZE:
                    n = _DIRSIZE[d] * len([x for x in rest.split(",") if x.strip()])
                elif d in (".ascii", ".asciz"):
                    body = rest.strip()
                    txt = body[1:-1].encode().decode("unicode_escape") if body.startswith('"') else ""
                    n = len(txt) + (1 if d == ".asciz" else 0)
                else:
                    continue
            lo = a if lo is None else min(lo, a); hi = a + n if hi is None else max(hi, a + n)
    return lo, hi

_DIRSIZE = {".word": 4, ".long": 4, ".half": 2, ".short": 2, ".byte": 1, ".float": 4, ".double": 8}

def _items(lines):
    """rodata items in emission order: ('s', path) | ('cdata', addr, size, align) | ('ctable', n)."""
    items, in_ro, k = [], False, 0
    cur = None       # current cdata: [addr, size, align]
    pend_align = 0
    while k < len(lines):
        st = lines[k].strip(); k += 1
        if st == ".section .rodata" or st == ".rdata":
            in_ro = True; cur = None; continue
        if in_ro and (st == ".text" or st.startswith(".section")):
            in_ro = False; cur = None; continue
        m = re.match(r'\.include\s+"([^"]+)"', st)
        if m:                      # a stub's .s switches sections itself — record it in ANY context
            if m.group(1).endswith(".s") and "/nonmatchings/" in m.group(1):
                items.append(("s", m.group(1)))
            cur = None; continue
        if not in_ro or not st:
            continue
        if st.startswith(".align"):
            n = int(st.split()[1])
            nxt = next((l.strip() for l in lines[k:] if l.strip()), "")
            if n == 3 and LABEL_RE.match(nxt):
                cnt, j = 0, k + 1
                while j < len(lines) and WORD_RE.match(lines[j].strip()):
                    cnt += 1; j += 1
                items.append(("ctable", cnt)); cur = None; k = j; continue
            pend_align = 1 << n; cur = None; continue
        m = re.match(r"^(D_[0-9A-Fa-f]{8}):$", st)
        if m:
            cur = [int(m.group(1)[2:], 16), 0, pend_align]; pend_align = 0
            items.append(("cdata", cur)); continue
        d = st.split()[0]
        if cur is not None and d in _DIRSIZE:
            cur[1] += _DIRSIZE[d] * len([x for x in st[len(d):].split(",") if x.strip()])
        elif cur is not None and d in (".ascii", ".asciz"):
            body = st[len(d):].strip()
            txt = body[1:-1].encode().decode("unicode_escape") if body.startswith('"') else ""
            cur[1] += len(txt) + (1 if d == ".asciz" else 0)
        elif cur is not None and d in (".space", ".skip"):
            cur[1] += int(st.split()[1])
    return items

def _tu_piece(binary, tu):
    """(start, end) vaddr of the yaml `.rodata` piece bound to TU — the frame for a TU whose rodata
    stream has no anchor before its first C table (an isolated §260 object)."""
    if not tu:
        return None
    y = open(_splat_yaml(binary)).read()
    vram = _file0_vram(y)
    segs = [(int(a, 16), k, n) for a, k, n in re.findall(r"^\s*- \[0x([0-9A-Fa-f]+), (\S+), (\S+?)\]", y, re.M)]
    for i, (a, k, n) in enumerate(segs):
        if k == ".rodata" and n == tu:
            end = segs[i + 1][0] if i + 1 < len(segs) else None
            return vram + a, (vram + end) if end is not None else None
    return None

def derive(binary, lines, tu=None):
    vram, raw = _module_target(binary)
    lo_code, hi_code = vram, vram + len(raw)
    word = lambda a: struct.unpack_from("<I", raw, a - vram)[0]
    items = _items(lines)
    if not any(it[0] == "ctable" for it in items):
        return []                       # nothing to pad -> nothing to derive, nothing to refuse
    piece = _tu_piece(binary, tu)
    pos, spec = None, []
    def zero_gap(a, b):                 # assembler alignment padding between two blocks
        return 0 < b - a < 4 and all(raw[x - vram] == 0 for x in range(a, b))
    def anchor_start(it):
        if it[0] == "s":
            return _s_rodata_span(it[1])[0]
        if it[0] == "cdata":
            return it[1][0]
        return None
    for idx, it in enumerate(items):
        if it[0] == "s":
            lo, hi = _s_rodata_span(it[1])
            if lo is None:
                continue
            if pos is None:
                pos = lo
            if lo != pos and zero_gap(pos, lo):
                pos = lo
            if lo != pos:
                sys.exit("jtbl_rodata_pads --derive %s: %s starts at 0x%X but the walk is at 0x%X "
                         "(%+d) — island layout drift" % (binary, os.path.basename(it[1]), lo, pos, lo - pos))
            pos = hi
        elif it[0] == "cdata":
            addr, size, al = it[1]
            if pos is None:
                pos = addr
            ap = pos if al <= 1 else (pos + al - 1) // al * al
            if ap != addr and zero_gap(ap, addr):
                ap = addr
            if ap != addr:
                sys.exit("jtbl_rodata_pads --derive %s: C data D_%08X expected at 0x%X (walk 0x%X, align %d)"
                         % (binary, addr, ap, pos, al))
            pos = addr + size
        else:
            n = it[1]
            if pos is None:
                if piece is None:
                    sys.exit("jtbl_rodata_pads --derive %s: a C jump table precedes every anchor and "
                             "no yaml .rodata piece is bound to TU %r — cannot place it" % (binary, tu))
                pos = piece[0]
            lead = 4 if word(pos) == 0 else 0
            pos += lead
            for e in range(n):
                w = word(pos)
                if not (lo_code <= w < hi_code):
                    sys.exit("jtbl_rodata_pads --derive %s: C table entry %d at 0x%X is %08X, not a code "
                             "address — island layout drift" % (binary, e, pos, w))
                pos += 4
            nxt = next((anchor_start(j) for j in items[idx + 1:] if anchor_start(j) is not None), None)
            if piece and piece[1] is not None and (nxt is None or piece[1] < nxt):
                nxt = piece[1]
            trailing = 0
            while (nxt is None or pos < nxt) and pos + 4 <= hi_code and word(pos) == 0:
                trailing += 1; pos += 4
            spec.append((lead, trailing))
    sys.stderr.write("jtbl_rodata_pads --derive %s: %s\n" % (binary, ",".join(
        "%d%s" % (l, ("t%d" % t) if t else "") for l, t in spec) or "(no C jump tables)"))
    return spec


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--derive", metavar="BINARY",
                    help="MODULE path: derive the pads from the retail island + this stream (no stored spec)")
    ap.add_argument("--tu", help="with --derive: the TU name (its yaml .rodata piece frames an anchorless stream)")
    ap.add_argument("--pads", required=False,
                    help="comma list, one token per rodata jump table in emission order: the pad "
                         "BYTES before the table (0|4), optionally t<n> = n trailing zero words")
    a = ap.parse_args()
    if a.derive:
        lines = sys.stdin.readlines()
        run(derive(a.derive, lines, a.tu), lines, sys.stdout)
        return
    if a.pads is None:
        sys.exit("jtbl_rodata_pads: give --pads SPEC or --derive BINARY")
    run(parse_spec(a.pads), sys.stdin, sys.stdout)


if __name__ == "__main__":
    main()
