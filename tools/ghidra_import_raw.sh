#!/usr/bin/env bash
# tools/ghidra_import_raw.sh <blob-path> <base-vram> <program-name>
#
# Import a RAW (flat, headerless) PSX memory image into the "bfm" Ghidra project
# HEADLESS — the Gen2 counterpart to ghidra_import.sh (which is for PS-X EXEs only).
# Used for the resident engine blob (Phase 10) and, reusably, location overlays
# (Phase 13): images that load at a fixed vram with no PS-X EXE header, so the PSX
# loader's magic auto-detect does not apply.
#
#   - BinaryLoader at -loader-baseAddr <base-vram> (e.g. 0x800CEDF8 for the resident
#     blob), language PSX:LE:32:default (same as the retail EXE),
#   - auto-analysis (PsyQ Signatures + DetectPsyQ + the MIPS function finders),
#   - ImportPsyqGdt.java (PsyQ 4.0 types) + DumpProgramInfo.java (language/base/funcs).
#
# The program is named <program-name> (the blob is staged to a temp file of that name,
# since analyzeHeadless derives the program name from the import filename).
#
# PRECONDITION: the MCP server must be STOPPED (exclusive project lock) — run
# tools/ghidra_mcp_stop.sh first. analyzeHeadless commits + saves on a clean exit.
set -uo pipefail

BLOB="${1:?usage: ghidra_import_raw.sh <blob-path> <base-vram> <program-name>}"
BASE="${2:?usage: ghidra_import_raw.sh <blob-path> <base-vram> <program-name>}"
NAME="${3:?usage: ghidra_import_raw.sh <blob-path> <base-vram> <program-name>}"
GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="$HOME/bfm-decomp/ghidra"
PROJ="bfm"
SCRIPTS="$HOME/bfm-decomp/tools/ghidra_scripts"
GDT="${PSYQ_GDT:-$GHIDRA/Ghidra/Extensions/ghidra_psx_ldr/data/psyq400.gdt}"
LANG_ID="PSX:LE:32:default"
PORT="8080"
STAGE="$HOME/bfm-decomp/.run/$NAME"   # import filename -> program name

[ -f "$BLOB" ] || { echo "import-raw: ERROR — blob not found: $BLOB" >&2; exit 2; }
[ -f "$GDT" ]  || { echo "import-raw: ERROR — PsyQ gdt not found: $GDT" >&2; exit 2; }

# Guard: a serving MCP server holds the exclusive project lock — refuse to collide.
if ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then
  echo "import-raw: ERROR — MCP server serving on :$PORT. Run tools/ghidra_mcp_stop.sh first." >&2
  exit 2
fi
# Clear a stale lock only when no analyzer is alive (mirrors ghidra_import.sh).
if ! pgrep -f 'ghidra.app.util.headless.AnalyzeHeadless' >/dev/null 2>&1; then
  rm -f "$PROJ_DIR/$PROJ.lock" "$PROJ_DIR/$PROJ.lock~" 2>/dev/null || true
fi

mkdir -p "$(dirname "$STAGE")"
cp -f "$BLOB" "$STAGE"

echo "import-raw: ===== importing '$BLOB' as program '$NAME' @ $BASE ($LANG_ID) ====="
"$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" \
  -import "$STAGE" -overwrite \
  -loader BinaryLoader \
  -loader-baseAddr "$BASE" \
  -processor "$LANG_ID" \
  -scriptPath "$SCRIPTS" \
  -postScript ImportPsyqGdt.java "$GDT" \
  -postScript DumpProgramInfo.java
rc=$?
rm -f "$STAGE"
echo "import-raw: ===== analyzeHeadless exit=$rc for program '$NAME' ====="
exit $rc
