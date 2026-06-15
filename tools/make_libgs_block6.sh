#!/usr/bin/env bash
# Regenerate the curated libgs block-6 object dir (.run/obj40/libgs_block6) for the Phase-7 Task-#9
# integration (Makefile LIBGS6_ELF). SDK-derived + gitignored, like .run/obj40/libcd; the build is
# byte-identical WITH or WITHOUT it (the stubs reproduce the same bytes), so this only matters to a
# developer who wants the real SDK objects linked. Needs the LIBGS ELF objects from
# tools/psyq_build_libs.sh LIBGS (which needs tools/psyq/lib40/LIBGS.LIB from the DTL-S2002 redump).
#
# Block 6 = the 6th of the 6 contiguous libgs blocks (vram 0x80053AF8-0x80057928), 16 objects. The
# list is DISAMBIGUATED (session E): psyq_identify reports 20 candidates because four objects have a
# byte-identical-.text alias — keep GS_131 (not RVWUNIT), GS_137 (not RVWLUNIT), PRESET3 (not
# PRESET2), OBJT3 (not OBJT2); the losers have a spurious .data/.rdata mismatch and do NOT link
# byte-exact. psyq_link_region verifies the chosen 16 are per-object .text byte-identical.
set -euo pipefail
cd "$(dirname "$0")/.."
LIBGS=.run/obj40/libgs
DST=.run/obj40/libgs_block6
OBJS=(GS_110 GS_119 GS_120 GS_121 GS_122 GS_123 GS_127 GS_131 GS_133 GS_134 GS_135 GS_137 \
      PRESET PRESET3 OBJT OBJT3)

[ -d "$LIBGS" ] || tools/psyq_build_libs.sh LIBGS
rm -rf "$DST"; mkdir -p "$DST"
for o in "${OBJS[@]}"; do
    [ -f "$LIBGS/$o.o" ] || { echo "ERROR: $LIBGS/$o.o missing (run tools/psyq_build_libs.sh LIBGS)"; exit 1; }
    cp "$LIBGS/$o.o" "$DST/$o.o"
done
echo "libgs_block6: ${#OBJS[@]} objects -> $DST"
# Optional self-check: verify the region links per-object .text byte-identical.
if [ "${1:-}" = "--verify" ]; then
    .venv/bin/python tools/psyq_link_region.py "$DST" 0x80053AF8 0x80057928
fi
