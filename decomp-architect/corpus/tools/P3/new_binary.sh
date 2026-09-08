#!/usr/bin/env bash
# tools/new_binary.sh <ALIAS> <PAYLOAD> <VRAM> [TEXT_LO] — onboard ANY flat-blob binary (P30 S44).
# =============================================================================
# The generalized form of new_overlay.sh (Phase 13), for every flat-payload binary class:
#   * location overlays  (ov_*, shared slot 0x80128158, payload 0.4.dec / 1.4.dec / raw 0.1 / 1.1)
#   * md_* modules       (own slot: 0x800CAE08 / 0x800CCB1C / 0x801A00D8 / ..., §S44 loader table)
# One command: instantiate config/splat.us.overlay.template.yaml, compute the build-identity hash +
# code/data boundary, register in the class registry (config/overlays.mk for ov_*, config/modules.mk
# for md_* — the Makefile -include's both; its body is NEVER touched) and in the report/diff tools'
# BINARIES dicts (sentinel-anchored, idempotent, ast-checked), then extract+build to byte-verify.
# Idempotent: re-running is a clean no-op.
#
# TEXT_LO (optional, default 0) = FILE OFFSET where code begins. The §154 module-id law: 75/78
# payloads open with a module-id word (sometimes + a fn-ptr table) — code is NOT at offset 0. A
# non-zero TEXT_LO (a) carves [0x0, rodata, hdr] ahead of the code (the resident's leading-word
# trick, SETUP §6.7), and (b) makes the sig bootstrap start at the right vram (--text-lo), without
# which sig_image finds 0 functions (§154-A).
#
#   tools/new_binary.sh ov_MAIN_012 extracted/retail/MAIN.CD.dir/FILE_012.dir/1.1 0x80128158
#   tools/new_binary.sh md_MAIN_013 extracted/retail/MAIN.CD.dir/FILE_013.dir/1.1 0x800CAE08 0x4
#   tools/new_binary.sh md_SC07_004 extracted/retail/SC07.CD.dir/FILE_004.dir/1.1 0x801A00D8 0x158
# =============================================================================
set -euo pipefail
cd "$(dirname "$0")/.."   # repo root

[ $# -ge 3 ] && [ $# -le 4 ] || {
  echo "usage: tools/new_binary.sh <ALIAS> <PAYLOAD> <VRAM> [TEXT_LO_fileoff]"; exit 2; }
ALIAS="$1"; DEC="$2"; VRAM="$3"; TLO="${4:-0x0}"
PYV=".venv/bin/python"

case "$ALIAS" in
  ov_*) MK="config/overlays.mk"; MKVAR="OVERLAY_BINARIES"; KIND="location overlay" ;;
  md_*) MK="config/modules.mk";  MKVAR="MODULE_BINARIES";  KIND="module" ;;
  *) echo "ERROR: alias must start ov_ or md_ (got '$ALIAS') — the registry is chosen by class"; exit 2 ;;
esac

[ -f "$DEC" ] || { echo "ERROR: payload not found: $DEC (run extraction first)"; exit 1; }

SHA1="$(sha1sum "$DEC" | cut -d' ' -f1)"
EOFSZ="$(stat -c%s "$DEC")"
EOFHEX="$(printf '0x%X' "$EOFSZ")"
TEXTHI="$(printf '0x%X' $((VRAM + EOFSZ)))"
TLO_VRAM="$(printf '0x%X' $((VRAM + TLO)))"

# sign (bootstrap honors the header via --text-lo, §154-A); code_end = last function's end fileoff
SIG=".run/sig.${ALIAS}.jsonl"
if [ ! -f "$SIG" ]; then
  if [ $((TLO)) -ne 0 ]; then
    $PYV tools/sig_image.py --image "$DEC" --vram-base "$VRAM" --bootstrap --text-lo "$TLO_VRAM" --name "$ALIAS" >/dev/null
  else
    $PYV tools/sig_image.py --image "$DEC" --vram-base "$VRAM" --bootstrap --name "$ALIAS" >/dev/null
  fi
fi
[ -s "$SIG" ] || { echo "ERROR: $SIG is empty — sig_image found no functions (wrong VRAM/TEXT_LO? §154)"; exit 1; }
CODEEND="$(tail -1 "$SIG" | VRAM="$VRAM" $PYV -c "
import sys, json, os
r = json.loads(sys.stdin.readline())
print('0x%X' % (int(r['addr'], 16) + r['nins']*4 - int(os.environ['VRAM'], 16)))")"

echo "Onboarding $ALIAS  ($KIND, $DEC)"
echo "  sha1=$SHA1  size=$EOFHEX  vram=$VRAM  text_lo=$TLO  code_end=$CODEEND  text_hi=$TEXTHI"

# 1) splat config from the one shared template; a non-zero TEXT_LO swaps the code-at-0 line for
#    the hdr carve + shifted code start (the resident's rodata-head trick — no second template, R33)
YAML="config/splat.${ALIAS}.yaml"
sed -e "s|@ALIAS@|$ALIAS|g" -e "s|@DEC_PATH@|$DEC|g" -e "s|@SHA1@|$SHA1|g" \
    -e "s|@VRAM@|$VRAM|g" -e "s|@CODE_END@|$CODEEND|g" -e "s|@EOF@|$EOFHEX|g" \
    config/splat.us.overlay.template.yaml > "$YAML"
if [ $((TLO)) -ne 0 ]; then
  # The header is emitted as a DOT-typed .rodata subsegment PAIRED with the c segment (same name),
  # not a standalone `rodata, hdr` object: a module header can contain a function's JUMP TABLE
  # (md_MAIN_034, S45 — switch jtbl stored before the code), and splat emits jtbl words as
  # .L<addr> LOCAL labels, which only resolve when the jtbl and its function land in the SAME
  # object (the EXE's [0x63238,.rodata,800] precedent). Pairing also covers the plain id-word
  # header. (`bin` is wrong here too — assets link in the data block, after text.)
  TLOHEX="$(printf '0x%X' $((TLO)))"
  sed -i "s|^      - \[0x0, c, ${ALIAS}\].*|      - [0x0, .rodata, ${ALIAS}]      # module-id header (+jtbl/ptr table) — §154-A\n      - [${TLOHEX}, c, ${ALIAS}]|" "$YAML"
fi
if [ $((EOFSZ % 4)) -ne 0 ]; then
  FLOOR="$(printf '0x%X' $(( (EOFSZ/4)*4 )))"; NB=$((EOFSZ - (EOFSZ/4)*4))
  sed -i "s|^@TRAILING@\$|      - [$FLOOR, bin, trailing]    # final $NB bytes (EOF not 4-aligned; spimdisasm drops a partial word)|" "$YAML"
else
  sed -i "/^@TRAILING@\$/d" "$YAML"
fi
echo "  wrote $YAML"

# 2) build-identity hash
echo "$SHA1  $ALIAS" > "config/check.${ALIAS}.sha"

# 3) binary-local symbols (don't clobber an existing curated file)
if [ ! -f "config/symbols.${ALIAS}.txt" ]; then
  cat > "config/symbols.${ALIAS}.txt" <<EOF
// config/symbols.${ALIAS}.txt — ${KIND} ${ALIAS} local symbols
// R13/R15: this binary's REGION ONLY (vram ${VRAM}..${TEXTHI}); NEVER merged into config/symbols.us.txt.
// count=0
EOF
fi

# 4) register in the class registry (generated, -include'd by the Makefile). Idempotent. Creates
#    config/modules.mk with its contract header on first module.
if [ ! -f "$MK" ]; then
  cat > "$MK" <<EOF
# config/modules.mk — GENERATED registry of module-class binaries (P30 S44; tools/new_binary.sh).
# Same contract as overlays.mk: -include'd by the Makefile BEFORE 'BINARIES :=' (silent when
# absent); the hand-maintained Makefile body is never edited to add a binary. Each md_* loads at
# its OWN vram (the §S44 loader table: docs/memory-map.md). _TEXT_LO is a VRAM (code start), read
# by 'make sig-modules' as --text-lo (§154-A: bootstrap past the module-id header).
${MKVAR} :=
EOF
  echo "  + created $MK"
fi
if ! grep -q "^${ALIAS}_EXE " "$MK"; then
  grep -qE "^${MKVAR} :=.* ${ALIAS}( |\$)" "$MK" || sed -i "s|^${MKVAR} :=.*|& ${ALIAS}|" "$MK"
  cat >> "$MK" <<EOF

# --- ${ALIAS} (${KIND}, vram ${VRAM} — onboarded by new_binary.sh) ---
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
${ALIAS}_TEXT_LO    := ${TLO_VRAM}
${ALIAS}_TEXT_HI    := ${TEXTHI}
${ALIAS}_ASM_DIR     := asm/${ALIAS}
${ALIAS}_SRC_DIR     := src/${ALIAS}
${ALIAS}_UNDEF_SYMS  := build/${ALIAS}/undefined_syms_auto.txt
${ALIAS}_UNDEF_FUNCS := build/${ALIAS}/undefined_funcs_auto.txt
EOF
  echo "  + $MK"
fi

# 5) register in the report/diff tools' BINARIES dicts (sentinel-anchored, idempotent, ast-checked —
#    the fully-generic step of new_overlay.sh, reused verbatim; the sentinel says ov_* but anchors
#    ALL generated entries).
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
