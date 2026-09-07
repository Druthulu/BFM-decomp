#!/usr/bin/env bash
# tools/ghidra_export_annotations.sh [--proj DIR] [--out DIR] [PROG ...]
#
# Read-only export of a Ghidra program's annotations (types, signatures, data, comments, bookmarks,
# equates, labels) to byte-stable JSON-Lines via tools/ghidra_scripts/ExportAnnotations.java (P33 B5).
# With no PROG every program in the project is exported (headless `-process` with no name).
# Output: <out>/<PROG>.jsonl (default .run/ghidra_export/). The splat symbol files are passed so the
# labels they already carry are skipped (ApplySymbols.java restores those on a rebuild).
#
# PRECONDITION: the MCP server is STOPPED (tools/ghidra_mcp_stop.sh) — even a read-only open needs
# the project lock free. Never writes to the project (-readOnly).
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="${BFM_GHIDRA_PROJ:-$REPO/ghidra}"; PROJ="bfm"
OUT="$REPO/.run/ghidra_export"
SCRIPTS="$REPO/tools/ghidra_scripts"
while [ $# -gt 0 ]; do
    case "$1" in
        --proj) PROJ_DIR="$2"; shift 2 ;;
        --out) OUT="$2"; shift 2 ;;
        *) break ;;
    esac
done
if ss -tln 2>/dev/null | grep -qE ":8080([^0-9]|$)"; then
    echo "export-annotations: ERROR — MCP server serving on :8080. Run tools/ghidra_mcp_stop.sh first." >&2; exit 2
fi
[ -f "$PROJ_DIR/$PROJ.gpr" ] || { echo "export-annotations: ERROR — no project at $PROJ_DIR/$PROJ.gpr" >&2; exit 2; }
mkdir -p "$OUT"
cd "$REPO"
SYMS=(config/symbols.us.txt config/symbols.us.ram.txt config/symbols.resident.txt)
for f in config/symbols.ov_*.txt config/symbols.md_*.txt config/symbols.proto-*.txt; do [ -f "$f" ] && SYMS+=("$f"); done
if [ $# -eq 0 ]; then
    procs=(-process)            # every program in the project folder
else
    procs=()
    for p in "$@"; do procs+=(-process "$p"); done
fi
rc=0
if [ $# -eq 0 ]; then
    timeout 7200 "$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" -process -noanalysis -readOnly \
        -scriptPath "$SCRIPTS" -postScript ExportAnnotations.java "$OUT" "${SYMS[@]}" 2>&1 \
        | grep -E 'BFMEXPORT|ERROR|Exception' ; rc=${PIPESTATUS[0]}
else
    for p in "$@"; do
        timeout 1800 "$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" -process "$p" -noanalysis -readOnly \
            -scriptPath "$SCRIPTS" -postScript ExportAnnotations.java "$OUT" "${SYMS[@]}" 2>&1 \
            | grep -E 'BFMEXPORT|ERROR|Exception' ; r=${PIPESTATUS[0]}; [ "$r" -eq 0 ] || rc=$r
    done
fi
echo "export-annotations: analyzeHeadless exit=$rc -> $OUT/"
exit $rc
