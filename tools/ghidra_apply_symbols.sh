#!/usr/bin/env bash
# tools/ghidra_apply_symbols.sh — mirror config/symbols.us.txt (or given files) into the Ghidra program,
# headless, with a real save (R15/G6). Precondition: the MCP server is STOPPED (tools/ghidra_mcp_stop.sh);
# the write open needs the project lock. Verify afterwards with tools/ghidra_mcp_verify.sh <addr> <name> (R9).
#   tools/ghidra_apply_symbols.sh [PROG] [symbols files...]     (defaults: SLUS_007.26 config/symbols.us.txt)
set -uo pipefail
GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="$HOME/bfm-decomp/ghidra"; PROJ="bfm"
PROG="${1:-SLUS_007.26}"; shift || true
SYMS=("$@"); [ ${#SYMS[@]} -eq 0 ] && SYMS=("$HOME/bfm-decomp/config/symbols.us.txt")
SCRIPTS="$HOME/bfm-decomp/tools/ghidra_scripts"
if ss -tln 2>/dev/null | grep -qE ":8080([^0-9]|$)"; then
  echo "apply-symbols: ERROR — MCP server serving on :8080. Run tools/ghidra_mcp_stop.sh first."; exit 2
fi
cd "$HOME/bfm-decomp"
out=$(timeout 600 "$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" \
  -process "$PROG" -noanalysis -scriptPath "$SCRIPTS" -postScript ApplySymbols.java "${SYMS[@]}" 2>&1)
rc=$?
echo "$out" | grep -E "BFMAPPLY|moved holder|fail @|Save succeeded|ERROR|Exception" | head -40
echo "apply-symbols: analyzeHeadless exit=$rc"
