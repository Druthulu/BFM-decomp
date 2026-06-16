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
_a = _ap.parse_args()
LD = _a.ld
# object basenames whose (.data) belongs to the front / tail region. Defaults are the EXE's
# LZSS-sandwich objects (TRANSITIONAL — the Makefile passes --front/--tail explicitly, and the
# whole step is gated to BINARY=main since overlays have no rodata island). See cookbook §8.
FRONT_DATA = tuple(_a.front) if _a.front else ("53198.data.o",)
TAIL_DATA  = tuple(_a.tail) if _a.tail else ("6324C.data.o",)

src = open(LD).read()

# Grab the .main output-section body (between its first '{' and matching '}').
m = re.search(r"(\.main\b.*?\n[ \t]*\{\n)(.*?)(\n[ \t]*\})", src, re.S)
if not m:
    sys.exit("ld_interleave: could not find .main { ... } block")
head, body, tail = m.group(1), m.group(2), m.group(3)

# Collect the object input-section lines by linker section, preserving order.
def grab(section):
    # lines like:  build/src/800.o(.rodata);
    return re.findall(rf"^[ \t]*build/\S+\({re.escape(section)}\);", body, re.M)

text_lines   = grab(".text")
rodata_lines = grab(".rodata")
data_lines   = grab(".data")
bss_lines    = grab(".bss")

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
new += grp("main_TEXT_START",   text_lines,   "main_TEXT_END",   "main_TEXT_SIZE")
new += grp("main_DATA_START",   front_data,   "main_DATA_END",   "main_DATA_SIZE")
new += grp("main_RODATA_START", rodata_lines, "main_RODATA_END", "main_RODATA_SIZE")
new += grp("main_DATA2_START",  tail_data,    "main_DATA2_END",  "main_DATA2_SIZE")
new += grp("main_BSS_START",    bss_lines,    "main_BSS_END",    "main_BSS_SIZE")
new_body = "\n".join(new)

out = src[:m.start()] + head + new_body + tail + src[m.end():]
open(LD, "w").write(out)
print(f"ld_interleave: rewrote .main — text={len(text_lines)} "
      f"front_data={len(front_data)} rodata={len(rodata_lines)} "
      f"tail_data={len(tail_data)} bss={len(bss_lines)}")
