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
set -euo pipefail
cd "$(dirname "$0")/.."   # repo root

[ $# -ge 2 ] && [ $# -le 3 ] || { echo "usage: tools/new_overlay.sh <SCxx> <FILE_nnn> [ENTRY]   e.g. tools/new_overlay.sh SC01 005  |  tools/new_overlay.sh SC07 006 1.4"; exit 2; }
SC="$1"; FILE="$2"; ENTRY="${3:-0.4}"
ALIAS="ov_${SC}_${FILE}"
DEC="extracted/retail/${SC}.CD.dir/FILE_${FILE}.dir/${ENTRY}.dec"
VRAM="0x80128158"
PYV=".venv/bin/python"

[ -f "$DEC" ] || { echo "ERROR: payload not found: $DEC (run extraction first)"; exit 1; }

SHA1="$(sha1sum "$DEC" | cut -d' ' -f1)"
EOFSZ="$(stat -c%s "$DEC")"
EOFHEX="$(printf '0x%X' "$EOFSZ")"
TEXTHI="$(printf '0x%X' $((0x80128158 + EOFSZ)))"

# code_end = end of the last sig_image function as a file offset (vram - base). Sign if absent.
SIG=".run/sig.${ALIAS}.jsonl"
[ -f "$SIG" ] || $PYV tools/sig_image.py --image "$DEC" --vram-base "$VRAM" --bootstrap --name "$ALIAS" >/dev/null
CODEEND="$(tail -1 "$SIG" | $PYV -c "import sys,json; r=json.loads(sys.stdin.readline()); a=int(r['addr'],16); print('0x%X' % (a + r['nins']*4 - 0x80128158))")"

echo "Onboarding $ALIAS  ($DEC)"
echo "  sha1=$SHA1  size=$EOFHEX  code_end=$CODEEND  text_hi=$TEXTHI"

# 1) splat config from the template (sed the @TOKENS@), then resolve @TRAILING@ (the non-4-aligned carve)
YAML="config/splat.${ALIAS}.yaml"
sed -e "s|@ALIAS@|$ALIAS|g" -e "s|@DEC_PATH@|$DEC|g" -e "s|@SHA1@|$SHA1|g" \
    -e "s|@VRAM@|$VRAM|g" -e "s|@CODE_END@|$CODEEND|g" -e "s|@EOF@|$EOFHEX|g" \
    config/splat.us.overlay.template.yaml > "$YAML"
if [ $((EOFSZ % 4)) -ne 0 ]; then
  FLOOR="$(printf '0x%X' $(( (EOFSZ/4)*4 )))"; NB=$((EOFSZ - (EOFSZ/4)*4))
  sed -i "s|^@TRAILING@\$|      - [$FLOOR, bin, trailing]    # final $NB bytes (EOF not 4-aligned; spimdisasm drops a partial word)|" "$YAML"
else
  sed -i "/^@TRAILING@\$/d" "$YAML"
fi
echo "  wrote $YAML"

# 2) build-identity hash
echo "$SHA1  $ALIAS" > "config/check.${ALIAS}.sha"

# 3) overlay-local symbols (don't clobber an existing curated file)
if [ ! -f "config/symbols.${ALIAS}.txt" ]; then
  cat > "config/symbols.${ALIAS}.txt" <<EOF
// config/symbols.${ALIAS}.txt — overlay ${SC}/FILE_${FILE} local symbols (Phase 13+)
// R13/R15: overlay-REGION ONLY (vram ${VRAM}..${TEXTHI}); NEVER merged into config/symbols.us.txt.
// count=0
EOF
fi

# 4) register in config/overlays.mk (generated registry, -include'd by the Makefile). Idempotent.
MK="config/overlays.mk"
if ! grep -q "^${ALIAS}_EXE " "$MK"; then
  grep -qE "^OVERLAY_BINARIES :=.* ${ALIAS}( |\$)" "$MK" || sed -i "s|^OVERLAY_BINARIES :=.*|& ${ALIAS}|" "$MK"
  cat >> "$MK" <<EOF

# --- ${ALIAS} (location overlay ${SC}/FILE_${FILE}, vram ${VRAM} — onboarded by new_overlay.sh) ---
${ALIAS}_EXE        := ${DEC}
${ALIAS}_NAME       := ${ALIAS}
${ALIAS}_OUT_DIR    := build/${ALIAS}
${ALIAS}_OUT        := \$(${ALIAS}_OUT_DIR)/\$(${ALIAS}_NAME)
${ALIAS}_ELF        := \$(${ALIAS}_OUT).elf
${ALIAS}_MAPFILE    := \$(${ALIAS}_OUT).map
${ALIAS}_LD_SCRIPT  := \$(${ALIAS}_OUT).ld
${ALIAS}_SPLAT_YAML := config/splat.${ALIAS}.yaml
${ALIAS}_CHECK_SHA  := config/check.${ALIAS}.sha
${ALIAS}_SYMBOLS    := config/symbols.${ALIAS}.txt
${ALIAS}_SIG        := .run/sig.${ALIAS}.jsonl
${ALIAS}_GHIDRA_PROG := ${ALIAS}
${ALIAS}_VRAM_BASE  := ${VRAM}
${ALIAS}_TEXT_LO    := ${VRAM}
${ALIAS}_TEXT_HI    := ${TEXTHI}
${ALIAS}_ASM_DIR     := asm/${ALIAS}
${ALIAS}_SRC_DIR     := src/${ALIAS}
${ALIAS}_UNDEF_SYMS  := build/${ALIAS}/undefined_syms_auto.txt
${ALIAS}_UNDEF_FUNCS := build/${ALIAS}/undefined_funcs_auto.txt
EOF
  echo "  + config/overlays.mk"
fi

# 5) register in the report/diff tools' BINARIES dicts (sentinel-anchored, idempotent, syntax-checked).
# difficulty.py was DROPPED from this list (Phase-27 T6): it now DERIVES its per-binary paths from the
# alias (cfg_for), so a new overlay needs no hand-registration there — the remaining 3 tools still carry
# hand-lists (migrating them is future work; each is byte-gated per the audit's one-at-a-time cadence).
$PYV - "$ALIAS" <<'PY'
import sys, ast
alias = sys.argv[1]
SENT = "inserts ov_* entries above this line"
entries = {
 "diff_settings.py": (f'    "{alias}": dict(baseimg="expected/build/{alias}/{alias}.elf",\n'
                      f'                        myimg="build/{alias}/{alias}.elf",\n'
                      f'                        mapfile="build/{alias}/{alias}.map"),\n'),
 "tools/progress.py": (f'    "{alias}": dict(build="build/{alias}/{alias}", check="config/check.{alias}.sha",\n'
                      f'                        src="src/{alias}", asm="asm/{alias}/nonmatchings", out="docs/progress.{alias}.md"),\n'),
 "tools/dup_report.py": (f'    "{alias}": dict(sig=".run/sig.{alias}.jsonl", md="docs/duplicates.{alias}.md"),\n'),
}
for path, entry in entries.items():
    txt = open(path).read()
    if f'"{alias}":' in txt:
        continue  # idempotent
    out, done = [], False
    for ln in txt.splitlines(keepends=True):
        if SENT in ln and not done:
            out.append(entry); done = True
        out.append(ln)
    new = "".join(out)
    ast.parse(new, path)   # syntax-check before writing
    open(path, "w").write(new)
    print(f"  + {path}")
PY

# 6) extract + build + byte-check
echo "Building $ALIAS ..."
make extract BINARY="$ALIAS" >/dev/null
make build BINARY="$ALIAS"
echo "Done. $ALIAS onboarded; run 'make check BINARY=$ALIAS' anytime, or 'make check-all' for the fleet."
