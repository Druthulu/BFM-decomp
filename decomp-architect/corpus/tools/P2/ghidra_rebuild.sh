#!/usr/bin/env bash
# tools/ghidra_rebuild.sh <program> [--proof] [--keep]
#
# Rebuild ONE Ghidra program FROM TEXT + the disc, in a scratch project (.run/ghidra_rebuild/proj), and
# prove it: the committed config/ghidra/<program>.jsonl (ExportAnnotations.java's delta format) is the
# hand-authored RE work; everything else — the bytes, auto-analysis, the function set, the names — comes
# from the extracted payload, Ghidra, the built ELF and the splat symbol files. P33 B5; makes the Ghidra
# database regenerable so it can leave git (it embeds the program bytes).
#
#   1. import   PS-X EXEs (SLUS_007.26, the two prototypes) via the PSX loader; every other program is a
#               raw blob at its vram (`make -s print-EXE / print-VRAM_BASE BINARY=<alias>` — the build's
#               own registry, R33), + auto-analysis + ImportPsyqGdt.java (the psyq400 types).
#   2. functions DefineFunctions.java from the built ELF's text symbols (splat's validated boundaries).
#   3. symbols  ApplySymbols.java with the binary's splat symbol files (the yaml's symbol_addrs_path).
#   4. baseline ExportAnnotations.java -> .run/ghidra_rebuild/<program>.baseline.jsonl   (nothing hand-made yet)
#   5. import   ImportAnnotations.java config/ghidra/<program>.jsonl   (when the file exists)
#   6. export   -> .run/ghidra_rebuild/<program>.after.jsonl; delta(after, baseline) -> <program>.delta.jsonl
#   --proof     cmp <program>.delta.jsonl config/ghidra/<program>.jsonl -> "PROOF PASS" (exit 0) or FAIL (exit 1).
#   Without a committed file, step 5 is skipped and the delta of the LIVE export (.run/ghidra_export/<program>.jsonl,
#   from tools/ghidra_export_annotations.sh) against the baseline is written to <program>.candidate.jsonl — the
#   file to review and commit as config/ghidra/<program>.jsonl.
#
# PRECONDITION: the MCP server is STOPPED (tools/ghidra_mcp_stop.sh); the extracted payload and the built ELF
# exist (`make check BINARY=<alias>`). The live project (ghidra/) is never touched. --keep leaves the scratch
# project for inspection (the next run wipes it).
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO"
PROG="${1:?usage: ghidra_rebuild.sh <program> [--proof] [--keep]}"; shift
PROOF=0; KEEP=0
for a in "$@"; do case "$a" in --proof) PROOF=1 ;; --keep) KEEP=1 ;; *) echo "rebuild: unknown arg $a" >&2; exit 2 ;; esac; done
GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
HEADLESS="$GHIDRA/support/analyzeHeadless"
SCRIPTS="$REPO/tools/ghidra_scripts"
GDT="${PSYQ_GDT:-$GHIDRA/Ghidra/Extensions/ghidra_psx_ldr/data/psyq400.gdt}"
SCR="$REPO/.run/ghidra_rebuild"          # exports, deltas, function lists (plain files)
# Ghidra refuses a project path with a component starting with '.', so the scratch PROJECT lives under
# the gitignored build/ tree (wiped by `make clean`, which is the right lifetime for it).
PROJ_DIR="$REPO/build/ghidra_rebuild/proj"; PROJ="bfm"; STAGEDIR="$REPO/build/ghidra_rebuild"
CONF="$REPO/config/ghidra/$PROG.jsonl"
LIVE="$REPO/.run/ghidra_export/$PROG.jsonl"
say() { printf 'rebuild[%s]: %s\n' "$PROG" "$*"; }
die() { printf 'rebuild[%s]: %s\n' "$PROG" "$*" >&2; exit 1; }
[ -x "$HEADLESS" ] || die "no analyzeHeadless at $HEADLESS (GHIDRA_INSTALL_DIR)"
[ -f "$GDT" ] || die "no psyq400.gdt at $GDT (PSYQ_GDT)"
if ss -tln 2>/dev/null | grep -qE ":8080([^0-9]|$)"; then die "MCP server serving on :8080 — run tools/ghidra_mcp_stop.sh first"; fi

# ---- what is this program? ----
case "$PROG" in
    SLUS_007.26)      KIND=exe; ALIAS=main; EXE=extracted/retail/SLUS_007.26 ;;
    sep8_SLUS_007.26) KIND=exe; ALIAS=proto-sep8; EXE=extracted/proto/sep8_SLUS_007.26 ;;
    aug31_USA_DEMO.EXE) KIND=exe; ALIAS=proto-demo; EXE=extracted/proto/aug31_USA_DEMO.EXE ;;
    *)                KIND=raw; ALIAS="$PROG"; EXE="$(make -s print-EXE BINARY="$ALIAS")"; VRAM="$(make -s print-VRAM_BASE BINARY="$ALIAS")" ;;
esac
[ -n "$EXE" ] && [ -f "$EXE" ] || die "payload not found for $PROG ($EXE) — run make disc-extract (or extract_proto_exe.py for a prototype)"
case "$ALIAS" in
    proto-sep8) SYMS=(config/symbols.proto-sep8.txt); ELF="" ;;
    proto-demo) SYMS=(config/symbols.proto-demo.txt); ELF="" ;;
    *) ELF="$(make -s print-ELF BINARY="$ALIAS")"
       mapfile -t SYMS < <(.venv/bin/python - "$ALIAS" <<'EOF'
import sys, yaml
y = yaml.safe_load(open(f"config/splat.{'us.exe' if sys.argv[1]=='main' else sys.argv[1]}.yaml"))
p = y["options"].get("symbol_addrs_path", [])
print("\n".join(p if isinstance(p, list) else [p]))
EOF
) ;;
esac

# ---- scratch project ----
rm -rf "$PROJ_DIR"; mkdir -p "$PROJ_DIR" "$SCR"
run_headless() {   # args: the analyzeHeadless tail; prints the BFM* / REPORT / ERROR lines; returns its exit
    timeout 3600 "$HEADLESS" "$PROJ_DIR" "$PROJ" "$@" 2>&1 | grep -E 'BFM|REPORT:|ERROR|Exception|Analysis succeeded|Import' | grep -vE 'INFO  (Analysis|REPORT: Import)' | head -40
    return "${PIPESTATUS[0]}"
}

say "1. import ($KIND) $EXE"
if [ "$KIND" = exe ]; then
    run_headless -import "$EXE" -overwrite -scriptPath "$SCRIPTS" -postScript ImportPsyqGdt.java "$GDT" -postScript DumpProgramInfo.java || die "import failed"
else
    STAGE="$STAGEDIR/$PROG"; cp -f "$EXE" "$STAGE"
    run_headless -import "$STAGE" -overwrite -loader BinaryLoader -loader-baseAddr "$VRAM" -processor PSX:LE:32:default \
        -scriptPath "$SCRIPTS" -postScript ImportPsyqGdt.java "$GDT" -postScript DumpProgramInfo.java || die "import failed"
    rm -f "$STAGE"
fi

if [ -n "$ELF" ] && [ -f "$ELF" ]; then
    say "2. functions from $ELF"
    LO="$(make -s print-TEXT_LO BINARY="$ALIAS")"; HI="$(make -s print-TEXT_HI BINARY="$ALIAS")"
    mipsel-linux-gnu-nm "$ELF" | awk -v lo="$LO" -v hi="$HI" '
        $2=="T" || $2=="t" { a=strtonum("0x" $1); if (a%4==0 && a>=strtonum(lo) && a<strtonum(hi)) printf "0x%08X\n", a }' \
        | sort -u > "$SCR/${PROG}_funcs.txt"
    run_headless -process "$PROG" -noanalysis -scriptPath "$SCRIPTS" -postScript DefineFunctions.java "$SCR/${PROG}_funcs.txt" || die "DefineFunctions failed"
else
    say "2. functions: no built ELF for $ALIAS — keeping the analysis-found set"
fi

say "3. symbols: ${SYMS[*]}"
run_headless -process "$PROG" -noanalysis -scriptPath "$SCRIPTS" -postScript ApplySymbols.java "${SYMS[@]}" || die "ApplySymbols failed"

say "4. baseline export"
run_headless -process "$PROG" -noanalysis -readOnly -scriptPath "$SCRIPTS" -postScript ExportAnnotations.java "$SCR/$PROG.baseline.jsonl" "${SYMS[@]}" || die "baseline export failed"

if [ ! -f "$CONF" ]; then
    [ -f "$LIVE" ] || die "no $CONF and no live export $LIVE (run tools/ghidra_export_annotations.sh $PROG first)"
    .venv/bin/python tools/ghidra_annotations_delta.py "$LIVE" "$SCR/$PROG.baseline.jsonl" "$SCR/$PROG.candidate.jsonl" --census
    say "no committed file — CANDIDATE written: $SCR/$PROG.candidate.jsonl (review, then cp to $CONF)"
    [ "$KEEP" = 1 ] || rm -rf "$PROJ_DIR"
    exit 0
fi

say "5. import $CONF"
run_headless -process "$PROG" -noanalysis -scriptPath "$SCRIPTS" -postScript ImportAnnotations.java "$CONF" | tee "$SCR/$PROG.import.log" || die "ImportAnnotations failed"
# R49: a per-row failure inside a rc-0 run is still a failure — a proof over a partial import proves nothing
# (S87: main's 13 func rows failed on "/undefined" while the plate comments made the delta match anyway).
grep -q 'BFMANN .*failed=0 ' "$SCR/$PROG.import.log" || die "ImportAnnotations reported failures (or no BFMANN line) — see $SCR/$PROG.import.log"
say "6. export after import + delta"
run_headless -process "$PROG" -noanalysis -readOnly -scriptPath "$SCRIPTS" -postScript ExportAnnotations.java "$SCR/$PROG.after.jsonl" "${SYMS[@]}" || die "export failed"
.venv/bin/python tools/ghidra_annotations_delta.py "$SCR/$PROG.after.jsonl" "$SCR/$PROG.baseline.jsonl" "$SCR/$PROG.delta.jsonl" --census
if [ "$PROOF" = 1 ]; then
    if cmp -s "$SCR/$PROG.delta.jsonl" "$CONF"; then
        say "PROOF PASS — the rebuilt program's hand-authored delta == $CONF ($(wc -l < "$CONF") rows)"
        # the marker config/ghidra/ROSTER.md (tools/ghidra_roster.py) reports; scratch, never committed
        printf 'PASS %s config-sha1 %s\n' "$(date -u +%Y-%m-%dT%H:%MZ)" "$(sha1sum < "$CONF" | cut -c1-12)" > "$SCR/$PROG.proof"
        [ "$KEEP" = 1 ] || rm -rf "$PROJ_DIR"
        exit 0
    fi
    say "PROOF FAIL — delta differs from $CONF (diff below, first 40 lines; scratch kept in $SCR)"
    printf 'FAIL %s config-sha1 %s\n' "$(date -u +%Y-%m-%dT%H:%MZ)" "$(sha1sum < "$CONF" | cut -c1-12)" > "$SCR/$PROG.proof"
    diff "$CONF" "$SCR/$PROG.delta.jsonl" | head -40
    exit 1
fi
[ "$KEEP" = 1 ] || rm -rf "$PROJ_DIR"
say "done (no --proof requested)"
