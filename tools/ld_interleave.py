#!/usr/bin/env python3
"""Reorder splat's generated linker script to honour a .data -> .rodata -> .data
"sandwich" layout (Phase 7 Task 2', the rodata-island problem).

splat emits one output section (`.main`) section-major in `section_order`
(.rodata, .text, .data, .bss), which floats ALL rodata to one place. But this
EXE's real layout puts .data on BOTH sides of the compiler rodata. For the
SURGICAL LZSS carve (Phase 7), only jtbl_80072A38 is migrated to .rodata; the
rest of the island stays raw inside the tail data object:

    .text            0x80010000 .. 0x800629DC
    .data  (front)   0x800629DC .. 0x80072A38   531DC.data.o (globals, ptr tables)
    .rodata          0x80072A38 .. 0x80072A4C   800.o (ONLY the migrated LZSS jtbl_80072A38)
    .data  (tail)    0x80072A4C .. 0x80074800   6324C.data.o (rest of island raw + tail globals)

i.e. .data appears on BOTH sides of .rodata, which a single section_order can't
express. This script rewrites the `.main {...}` body to the interleaved order:
text -> front .data -> .rodata -> tail .data -> .bss, keeping splat's START/END/
SIZE symbols. Front vs tail .data is decided by object basename (FRONT_DATA /
TAIL_DATA). All other (empty) .data objects go in the front group.

Idempotent: keyed off splat's exact section-major output; re-running on an
already-patched script is a no-op (the markers won't match). Run post-extract.
"""
import re, sys, argparse

_ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
_ap.add_argument("ld", nargs="?", default="build/us/SLUS_007.26.ld",
                 help="splat-generated linker script to rewrite in place")
_ap.add_argument("--front", action="append",
                 help="object basename whose .data belongs to the FRONT region (repeatable)")
_ap.add_argument("--tail", action="append",
                 help="object basename whose .data belongs to the TAIL region (repeatable)")
_ap.add_argument("--order",
                 help="Phase-26 §8 MULTI-jtbl mode: a comma-separated, address-ordered list of "
                      "object LEAF names forming the data-region sandwich (text -> [these] -> bss). "
                      "A `*.data.o` or `trailing.o` leaf contributes its (.data); any other (code) "
                      "object leaf contributes its (.rodata) carve. Overrides --front/--tail. Every "
                      "unlisted .data/.rodata line must be an empty code-object section (parked with "
                      ".text, byte-neutral). Generalises the single-jtbl 3-piece sandwich to N pieces.")
_ap.add_argument("--section", default=".main",
                 help="output-section name to rewrite (default .main for the EXE; overlays "
                      "use their own, e.g. .ov_SC01_077). The linker START/END/SIZE symbol "
                      "prefix is derived by stripping the leading dot (Phase 26 §8 overlay carve).")
_a = _ap.parse_args()
LD = _a.ld
SECTION = _a.section                 # output section to rewrite
PREFIX = SECTION.lstrip(".")         # splat names its symbols <PREFIX>_TEXT_START etc.
# object basenames whose (.data) belongs to the front / tail region. Defaults are the EXE's
# LZSS-sandwich objects (TRANSITIONAL — the Makefile passes --front/--tail explicitly, and the
# whole step is gated to BINARY=main since overlays have no rodata island). See cookbook §8.
FRONT_DATA = tuple(_a.front) if _a.front else ("53198.data.o",)
TAIL_DATA  = tuple(_a.tail) if _a.tail else ("6324C.data.o",)

src = open(LD).read()

# Grab the output-section body (between its first '{' and matching '}').
m = re.search(re.escape(SECTION) + r"\b.*?\n[ \t]*\{\n(.*?)(\n[ \t]*\})", src, re.S)
if not m:
    sys.exit(f"ld_interleave: could not find {SECTION} {{ ... }} block")
head, body, tail = src[m.start():m.start(1)], m.group(1), m.group(2)

# Collect the object input-section lines by linker section, preserving order.
def grab(section):
    # lines like:  build/src/800.o(.rodata);
    return re.findall(rf"^[ \t]*build/\S+\({re.escape(section)}\);", body, re.M)

text_lines   = grab(".text")
rodata_lines = grab(".rodata")
data_lines   = grab(".data")
bss_lines    = grab(".bss")

I = "        "  # 8-space indent matching splat's body

if _a.order:
    # --- Phase-26 §8 MULTI-jtbl address-ordered mode ---------------------------------------
    # The data region is an explicit, address-ordered sequence of pieces (data subsegs and the
    # per-function .rodata jtbl carves). Emit each piece's linker line back-to-back so the linker
    # lays them out contiguously in exactly the original island order. ALIGN(.,4) between pieces
    # is a no-op on the word-aligned jtbl/data boundaries (kept as a safety net, matching the
    # proven single-carve path). Every code object contributes at most ONE contiguous .rodata run,
    # so a matched jr-function whose jtbl is non-adjacent to a sibling's MUST be in its own subseg.
    items = [x for x in _a.order.split(",") if x]

    def _sect_of(leaf):
        return ".data" if (leaf.endswith(".data.o") or leaf == "trailing.o") else ".rodata"

    def _find_line(leaf, sect):
        pat = f"/{leaf}({sect});"
        hits = [l for l in (data_lines + rodata_lines) if pat in l]
        if len(hits) != 1:
            sys.exit(f"ld_interleave --order: expected exactly 1 `{leaf}({sect})` line, found {len(hits)}")
        return hits[0]

    ordered = [_find_line(leaf, _sect_of(leaf)) for leaf in items]
    selected = set(ordered)
    # Everything not placed in the island must be an EMPTY code-object .data/.rodata section
    # (non-empty ones would be a real data conflict -> the byte-gate catches it). Park with .text.
    empties = [l for l in (data_lines + rodata_lines) if l not in selected]

    out_lines = [f"{I}FILL(0x00000000);", f"{I}{PREFIX}_TEXT_START = .;"]
    out_lines += [f"{I}{l.strip()}" for l in text_lines]
    out_lines += [f"{I}{l.strip()}" for l in empties]        # empty (0-byte) sections, byte-neutral
    out_lines += [f"{I}. = ALIGN(., 4);", f"{I}{PREFIX}_TEXT_END = .;",
                  f"{I}{PREFIX}_TEXT_SIZE = ABSOLUTE({PREFIX}_TEXT_END - {PREFIX}_TEXT_START);"]
    out_lines.append(f"{I}{PREFIX}_DATA_START = .;")
    for l in ordered:
        out_lines.append(f"{I}{l.strip()}")
        out_lines.append(f"{I}. = ALIGN(., 4);")
    out_lines += [f"{I}{PREFIX}_DATA_END = .;",
                  f"{I}{PREFIX}_DATA_SIZE = ABSOLUTE({PREFIX}_DATA_END - {PREFIX}_DATA_START);"]
    out_lines += [f"{I}{PREFIX}_BSS_START = .;"]
    out_lines += [f"{I}{l.strip()}" for l in bss_lines]
    out_lines += [f"{I}. = ALIGN(., 4);", f"{I}{PREFIX}_BSS_END = .;",
                  f"{I}{PREFIX}_BSS_SIZE = ABSOLUTE({PREFIX}_BSS_END - {PREFIX}_BSS_START);"]
    new_body = "\n".join(out_lines)
    out = src[:m.start()] + head + new_body + tail + src[m.end():]
    open(LD, "w").write(out)
    print(f"ld_interleave --order: {SECTION} island = {len(ordered)} pieces "
          f"[{', '.join(items)}]; text={len(text_lines)} empties={len(empties)} bss={len(bss_lines)}")
    sys.exit(0)

def is_named(line, names):
    return any(n in line for n in names)

front_data = [l for l in data_lines if not is_named(l, TAIL_DATA)]
tail_data  = [l for l in data_lines if is_named(l, TAIL_DATA)]
# Sanity: front must contain the FRONT_DATA object.
if not any(is_named(l, FRONT_DATA) for l in front_data):
    sys.exit("ld_interleave: front data object not found — config drift?")
if not tail_data:
    sys.exit("ld_interleave: tail data object not found — config drift?")

I = "        "  # 8-space indent matching splat's body
def grp(start, lines, end_sym, size_sym):
    out = [f"{I}{start} = .;"]
    out += [f"{I}{l.strip()}" for l in lines]
    out += [f"{I}. = ALIGN(., 4);", f"{I}{end_sym} = .;"]
    if size_sym:
        out += [f"{I}{size_sym} = ABSOLUTE({end_sym} - {start});"]
    return out

new = [f"{I}FILL(0x00000000);"]
new += grp(f"{PREFIX}_TEXT_START",   text_lines,   f"{PREFIX}_TEXT_END",   f"{PREFIX}_TEXT_SIZE")
new += grp(f"{PREFIX}_DATA_START",   front_data,   f"{PREFIX}_DATA_END",   f"{PREFIX}_DATA_SIZE")
new += grp(f"{PREFIX}_RODATA_START", rodata_lines, f"{PREFIX}_RODATA_END", f"{PREFIX}_RODATA_SIZE")
new += grp(f"{PREFIX}_DATA2_START",  tail_data,    f"{PREFIX}_DATA2_END",  f"{PREFIX}_DATA2_SIZE")
new += grp(f"{PREFIX}_BSS_START",    bss_lines,    f"{PREFIX}_BSS_END",    f"{PREFIX}_BSS_SIZE")
new_body = "\n".join(new)

out = src[:m.start()] + head + new_body + tail + src[m.end():]
open(LD, "w").write(out)
print(f"ld_interleave: rewrote {SECTION} — text={len(text_lines)} "
      f"front_data={len(front_data)} rodata={len(rodata_lines)} "
      f"tail_data={len(tail_data)} bss={len(bss_lines)}")
