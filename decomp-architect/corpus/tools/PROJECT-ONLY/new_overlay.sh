#!/usr/bin/env bash
# tools/new_overlay.sh <SCxx> <FILE_nnn> [ENTRY] — onboard a BFM location overlay as a build binary (Phase 13).
# =============================================================================
# One command: instantiate the splat config from config/splat.us.overlay.template.yaml,
# compute the build-identity hash + code/data boundary, register the binary in the
# generated config/overlays.mk (the Makefile -include's it — the hand-maintained Makefile
# body is NEVER touched) and in the report/diff tools' BINARIES dicts (sentinel-anchored,
# idempotent, syntax-checked), then `make extract && make build` to byte-verify the overlay
# against its on-disk decompressed payload. Re-running is a clean no-op (idempotent).
#
# All overlays load to the shared slot vram 0x80128158 (position-locked, Phase 3). The
# trailing-partial-word carve (for the ~75% of overlays whose decompressed size isn't
# 4-aligned) + the objcopy end-align trim are handled automatically.
#
# ENTRY (optional, default "0.4") = the PAC {index}.{type} of the overlay payload. The first 134
# overlays put their code at PAC entry 0 (0.4.dec). The Phase-27 disc-completeness audit found four
# SC07 overlays (FILE_006/007/010/011) that put GRAPHICS at entry 0 and the CODE overlay at entry 1
# (1.4.dec) — invisible to the hardcoded 0.4 for a month. Their index-0 is a type-0 blob, so the
# alias ov_SC07_006 is unambiguous. Pass ENTRY to reach a non-0.4 payload.
#
#   tools/new_overlay.sh SC01 005          # -> ov_SC01_005 from 0.4.dec
#   tools/new_overlay.sh SC07 006 1.4      # -> ov_SC07_006 from 1.4.dec (index-1 overlay)
# =============================================================================
# P30 S44: this script is now a WRAPPER over tools/new_binary.sh (the generalized onboarder for
# every flat-blob class — overlays AND md_* modules). All behavior above still holds; the
# implementation lives in new_binary.sh. Kept as the overlay-shaped entry point (same CLI).
set -euo pipefail
cd "$(dirname "$0")/.."
[ $# -ge 2 ] && [ $# -le 3 ] || { echo "usage: tools/new_overlay.sh <SCxx> <FILE_nnn> [ENTRY]"; exit 2; }
exec tools/new_binary.sh "ov_${1}_${2}" "extracted/retail/${1}.CD.dir/FILE_${2}.dir/${3:-0.4}.dec" 0x80128158
