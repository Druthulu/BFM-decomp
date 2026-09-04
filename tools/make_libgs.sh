#!/usr/bin/env bash
# Regenerate the curated libgs object dir (.run/obj40/libgs_used) for the Phase-7 FULL-libgs
# integration (Makefile LIBGS_ELF). SDK-derived + gitignored, like .run/obj40/libcd; the build is
# byte-identical WITH or WITHOUT it (the stubs reproduce the same bytes), so this only matters to a
# developer who wants the real SDK objects linked. Needs the LIBGS ELF objects from
# tools/psyq_build_libs.sh LIBGS (which needs tools/psyq/lib40/LIBGS.LIB from the DTL-S2002 redump).
#
# These are the 31 libgs objects BFM links, forming 6 contiguous blocks across vram
# 0x80051804-0x80057928, separated by 5 non-libgs gaps (80 / 48 / 1536[GS_001] / 48 / 304 B):
#   block 1: 2D_COM0                                                  (0x80051804)
#   block 2: 2D_LIN0 2D_COM1 2D_SP0                                   (0x80051DC8)
#   block 3: 2D_SP1                                                   (0x80052460)
#   block 4: GS_002 GS_003 MATRIX GS_103 GS_104 GS_105 GS_106 GS_107  (0x80052BDC)
#   block 5: GS_108 GS_109                                            (0x800538EC)
#   block 6: GS_110 GS_119 GS_120 GS_121 GS_122 GS_123 GS_127 GS_131
#            GS_133 GS_134 GS_135 GS_137 PRESET PRESET3 OBJT OBJT3    (0x80053AF8)
# GS_001 (the 1536 B gap before block 4) is EXCLUDED — psyq-obj-parser packs its scattered PSD*
# commons into .bss referenced via .bss+offset and 35 words differ at the global-zeroing run
# (cookbook §9.1 hard case); it stays an asm stub (gsgap3) and reproduces its bytes.
# The list is DISAMBIGUATED (session E): psyq_identify reports byte-identical-.text aliases — keep
# GS_131 (not RVWUNIT), GS_137 (not RVWLUNIT), PRESET3 (not PRESET2), OBJT3 (not OBJT2); the losers
# have a spurious .data/.rdata mismatch and do NOT link byte-exact. GS_106 is an 8-instruction object
# whose .text pattern recurs in game code, so it anchors uniquely only within the libgs window
# (psyq_identify/psyq_integrate take the 0x80051804..0x80057928 range — see make extract).
# psyq_link_region --verify confirms the chosen 31 are per-object .text byte-identical.
set -euo pipefail
cd "$(dirname "$0")/.."
LIBGS=.run/obj40/libgs
DST=.run/obj40/libgs_used
OBJS=(2D_COM0 2D_LIN0 2D_COM1 2D_SP0 2D_SP1 2D_BG0 2D_BG1 \
      GS_002 GS_003 MATRIX GS_103 GS_104 GS_105 GS_106 GS_107 GS_108 GS_109 \
      GS_110 GS_119 GS_120 GS_121 GS_122 GS_123 GS_127 GS_131 GS_133 GS_134 GS_135 GS_137 \
      PRESET PRESET3 OBJT OBJT3)

[ -d "$LIBGS" ] || tools/psyq_build_libs.sh LIBGS
rm -rf "$DST"; mkdir -p "$DST"
for o in "${OBJS[@]}"; do
    [ -f "$LIBGS/$o.o" ] || { echo "ERROR: $LIBGS/$o.o missing (run tools/psyq_build_libs.sh LIBGS)"; exit 1; }
    cp "$LIBGS/$o.o" "$DST/$o.o"
done
echo "libgs_used: ${#OBJS[@]} objects -> $DST"
# Optional self-check: verify the whole region links per-object .text byte-identical.
if [ "${1:-}" = "--verify" ]; then
    .venv/bin/python tools/psyq_link_region.py "$DST" 0x8005080C 0x80057928
fi
