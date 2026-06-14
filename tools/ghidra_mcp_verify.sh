#!/usr/bin/env bash
# tools/ghidra_mcp_verify.sh <addr> <expected-name>
#
# RULE R9: after a Ghidra save-shutdown, verify a recent edit actually persisted to disk.
# Read-only re-opens the SAVED project and checks the function/symbol name at <addr>.
# Run AFTER tools/ghidra_mcp_stop.sh (the server must be stopped — a read-only open needs
# the .rep lock free). Exit 0 = PASS (persisted), non-zero = FAIL / not verified.
#
# Example (after a phase's last edit was renaming 0x80018730 to LzssDecodeSector):
#   tools/ghidra_mcp_stop.sh && tools/ghidra_mcp_verify.sh 0x80018730 LzssDecodeSector
set -uo pipefail

ADDR="${1:?usage: ghidra_mcp_verify.sh <addr e.g. 0x80018730> <expected-name>}"
EXPECT="${2:?usage: ghidra_mcp_verify.sh <addr> <expected-name>}"

GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="$HOME/bfm-decomp/ghidra"
PROJ="bfm"
PROG="SLUS_007.26"
SCRIPTS="$HOME/bfm-decomp/tools/ghidra_scripts"
PORT="8080"

if ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then
  echo "verify: ERROR — server still serving on :$PORT. Run ghidra_mcp_stop.sh first (read-only open needs the lock free)."
  exit 2
fi

# A clean stop releases the lock; clear any leftover just in case (no analyzer running here).
rm -f "$PROJ_DIR/$PROJ.lock" "$PROJ_DIR/$PROJ.lock~" 2>/dev/null || true

out=$(timeout 220 "$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" \
  -process "$PROG" -noanalysis -readOnly \
  -scriptPath "$SCRIPTS" -postScript GetSymbolAt.java "$ADDR" 2>&1)

got=$(echo "$out" | sed -n 's/.*BFMVERIFY .* name=\[\(.*\)\].*/\1/p' | head -1)

echo "verify: read-only re-open of saved DB -> symbol@$ADDR = [${got:-<none>}]"
if [ "$got" = "$EXPECT" ]; then
  echo "verify: ✅ PASS — '$EXPECT' persisted at $ADDR in the saved project DB"
  exit 0
else
  echo "verify: ❌ FAIL — expected '$EXPECT' at $ADDR, saved DB has '${got:-<none>}'"
  echo "--- analyzeHeadless tail ---"; echo "$out" | tail -15
  exit 1
fi
