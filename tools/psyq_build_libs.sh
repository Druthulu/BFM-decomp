#!/usr/bin/env bash
# Build ELF .a archives from the PsyQ 4.0 .LIB files (Phase 7 — PsyQ-library linking).
# Pipeline per lib:  psyq_lib_split.py (.LIB -> .OBJ members) -> psyq-obj-parser (each
# .OBJ -> ELF .o) -> ar (-> <lib>.a).  Output (gitignored, SDK-derived):
#   tools/psyq/lib40_elf/<LIB>.a   +   .run/obj40/<lib>/*.{obj,o} scratch
# The .a are then linked into the build for the functions identified as PsyQ SDK code.
# Requires: tools/psyq/lib40/*.LIB (extracted from the DTL-S2002 redump), tools/psyq/
# psyq-obj-parser, mipsel-linux-gnu-ar. SDK assets stay out of git (.gitignore /tools/psyq/).
set -euo pipefail
cd "$(dirname "$0")/.."
LIBDIR=tools/psyq/lib40
OUTDIR=tools/psyq/lib40_elf
SCRATCH=.run/obj40
PARSER=tools/psyq/psyq-obj-parser
AR=mipsel-linux-gnu-ar
mkdir -p "$OUTDIR"
# BFM-relevant libraries (the SDK footprint in the EXE); pass args to override.
LIBS=("${@:-LIBCD LIBGS LIBSPU LIBSND LIBMCRD LIBSN LIBAPI LIBETC LIBGTE LIBGPU LIBMATH LIBCARD LIBC LIBC2}")
for L in ${LIBS[@]}; do
    lib="$LIBDIR/$L.LIB"
    [ -f "$lib" ] || { echo "  skip $L (no $lib)"; continue; }
    od="$SCRATCH/$(echo "$L" | tr A-Z a-z)"
    rm -rf "$od"; mkdir -p "$od"
    n=$(python3 tools/psyq_lib_split.py "$lib" "$od" | head -1 | grep -oE '[0-9]+ objects' | grep -oE '[0-9]+')
    ok=0
    for o in "$od"/*.obj; do
        if "$PARSER" "$o" -o "${o%.obj}.o" >/dev/null 2>&1; then ok=$((ok+1)); fi
    done
    rm -f "$OUTDIR/$L.a"
    $AR rcs "$OUTDIR/$L.a" "$od"/*.o 2>/dev/null || true
    printf "  %-10s %3s objs -> %3d .o -> %s.a\n" "$L" "${n:-?}" "$ok" "$L"
done
echo "done -> $OUTDIR/"
