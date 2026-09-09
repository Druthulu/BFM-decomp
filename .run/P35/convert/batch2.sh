#!/usr/bin/env bash
# Phase 35 T4 — the batch form of batch.sh: snapshot every listed binary's objects (A), ONE apply for the whole batch
# (the oracle setup — 218 sig files — is paid once), then per binary: rebuild + byte-check (L1) and compare every object (L0).
# Exit non-zero on the first failure (R97). Usage: batch2.sh <alias>...
set -o pipefail
cd "$(dirname "$0")/../../.." || exit 2
L=.run/P35/convert/ledger.txt
for a in "$@"; do
  objdir=build/src/$a; [ "$a" = main ] && objdir=build/src
  A=.run/P35/convert/objA/$a; rm -rf "$A"; mkdir -p "$A"
  ls "$objdir"/*.o >/dev/null 2>&1 && cp "$objdir"/*.o "$A/"
done
list=$(IFS=,; echo "$*")
.venv/bin/python tools/macro_to_header.py --apply --binaries "$list" --ledger .run/P35/convert/ledger_batch_$1.json > .run/P35/convert/apply_batch_$1.log 2>&1 || { echo "FAIL apply batch"; tail -3 .run/P35/convert/apply_batch_$1.log; exit 1; }
for a in "$@"; do
  objdir=build/src/$a; [ "$a" = main ] && objdir=build/src
  A=.run/P35/convert/objA/$a
  make check BINARY="$a" -j16 > .run/P35/convert/check_$a.log 2>&1 || { echo "FAIL check $a"; grep -E 'FAIL|rror' .run/P35/convert/check_$a.log | head -3; exit 1; }
  same=0; diff=0
  for f in "$A"/*.o; do [ -e "$f" ] || continue; b="$objdir/$(basename "$f")"; if cmp -s "$f" "$b"; then same=$((same+1)); else diff=$((diff+1)); echo "DIFFERS $a $(basename "$f")"; fi; done
  echo "$a BYTE-IDENTICAL obj A/B: $same/$((same+diff))" | tee -a "$L"
  [ "$diff" -eq 0 ] || { echo "FAIL object A/B $a"; exit 1; }
done
echo "batch done: $# binaries; apply ledger: $(cat .run/P35/convert/ledger_batch_$1.json | tr -d '\n ')"
