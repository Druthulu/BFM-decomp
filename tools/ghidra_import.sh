#!/usr/bin/env bash
# tools/ghidra_import.sh <exe-path>
#
# Import a PS-X EXE into the "bfm" Ghidra project HEADLESS, the same way the retail
# SLUS_007.26 was imported (Phase 1): auto-detect the PSX loader, run auto-analysis
# (which applies PsyQ Signatures + DetectPsyQ), import the PsyQ 4.0 type archive
# (ImportPsyqGdt.java), then DumpProgramInfo.java to print language/base/func-count/
# PsyQ version. analyzeHeadless commits + saves the imported program on a clean exit.
#
# The program name in the project defaults to the EXE's basename (e.g. importing
# extracted/proto/sep8_SLUS_007.26 creates program "sep8_SLUS_007.26").
#
# PRECONDITION: the MCP server must be STOPPED (the project lock is exclusive).
# Run tools/ghidra_mcp_stop.sh first. Used in Phase 3.5 to add the two prototypes
# (sep8_SLUS_007.26, aug31_USA_DEMO.EXE) alongside retail; reusable for any PS-X EXE.
set -uo pipefail

EXE="${1:?usage: ghidra_import.sh <path-to-ps-x-exe>}"
GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="$HOME/bfm-decomp/ghidra"
PROJ="bfm"
SCRIPTS="$HOME/bfm-decomp/tools/ghidra_scripts"
GDT="${PSYQ_GDT:-$GHIDRA/Ghidra/Extensions/ghidra_psx_ldr/data/psyq400.gdt}"
PORT="8080"

[ -f "$EXE" ] || { echo "import: ERROR — exe not found: $EXE" >&2; exit 2; }
[ -f "$GDT" ] || { echo "import: ERROR — PsyQ gdt not found: $GDT" >&2; exit 2; }

# Guard: a serving MCP server holds the exclusive project lock — refuse to collide.
if ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then
  echo "import: ERROR — MCP server serving on :$PORT. Run tools/ghidra_mcp_stop.sh first." >&2
  exit 2
fi

# Clear a stale lock only when no analyzer is alive (mirrors ghidra_mcp_start.sh).
if ! pgrep -f 'ghidra.app.util.headless.AnalyzeHeadless' >/dev/null 2>&1; then
  rm -f "$PROJ_DIR/$PROJ.lock" "$PROJ_DIR/$PROJ.lock~" 2>/dev/null || true
fi

echo "import: ===== importing '$EXE' into project '$PROJ' ====="
echo "import: gdt=$GDT  (program name = basename; -overwrite for idempotent re-import)"
"$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" \
  -import "$EXE" -overwrite \
  -scriptPath "$SCRIPTS" \
  -postScript ImportPsyqGdt.java "$GDT" \
  -postScript DumpProgramInfo.java
rc=$?
echo "import: ===== analyzeHeadless exit=$rc for '$EXE' ====="
exit $rc
