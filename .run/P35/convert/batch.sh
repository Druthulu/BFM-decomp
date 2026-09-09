#!/usr/bin/env bash
# Phase 35 T4 — convert one binary at a time: snapshot its objects (A), apply the include form, rebuild + byte-check (L1),
# compare every object (L0), append the ledger. Exit non-zero on the first failure (R97). Usage: batch.sh <alias>...
set -o pipefail
cd "$(dirname "$0")/../../.." || exit 2
L=.run/P35/convert/ledger.txt
for a in "$@"; do
  objdir=build/src/$a; [ "$a" = main ] && objdir=build/src
  A=.run/P35/convert/objA/$a; rm -rf "$A"; mkdir -p "$A"
  n_obj=$(ls "$objdir"/*.o 2>/dev/null | wc -l)
  [ "$n_obj" -gt 0 ] && cp "$objdir"/*.o "$A/"
  .venv/bin/python tools/macro_to_header.py --apply --binaries "$a" --ledger .run/P35/convert/ledger_$a.json > .run/P35/convert/apply_$a.log 2>&1 || { echo "FAIL apply $a"; tail -3 .run/P35/convert/apply_$a.log; exit 1; }
  make check BINARY="$a" -j16 > .run/P35/convert/check_$a.log 2>&1 || { echo "FAIL check $a"; grep -E 'FAIL|rror' .run/P35/convert/check_$a.log | head -3; exit 1; }
  same=0; diff=0
  for f in "$A"/*.o; do [ -e "$f" ] || continue; b="$objdir/$(basename "$f")"; if cmp -s "$f" "$b"; then same=$((same+1)); else diff=$((diff+1)); echo "DIFFERS $a $(basename "$f")"; fi; done
  sites=$(python3 -c "import json;d=json.load(open('.run/P35/convert/ledger_$a.json'));print(d.get('sites',0),d.get('tus',0),d.get('headers_written',0))")
  echo "$a BYTE-IDENTICAL obj A/B: $same/$((same+diff)) sites/tus/new-headers: $sites" | tee -a "$L"
  [ "$diff" -eq 0 ] || { echo "FAIL object A/B $a"; exit 1; }
done
echo "batch done: $# binaries"
