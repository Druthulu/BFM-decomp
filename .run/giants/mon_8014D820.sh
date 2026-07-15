#!/bin/bash
# Bounded progress monitor for the func_8014D820 permuter ILS.
# Emits: each new ILS log line (cycle results / terminal) + each best-score improvement.
# Exits on terminal marker or when the ILS process is gone.
log=/home/musashi/bfm-decomp/.run/giants/ils_8014D820.log
pd=/home/musashi/bfm-decomp/.run/permuter/func_8014D820
last=0; prevbest=""
while true; do
  n=$(wc -l < "$log" 2>/dev/null || echo 0)
  if [ "${n:-0}" -gt "$last" ]; then sed -n "$((last+1)),${n}p" "$log"; last=$n; fi
  best=$(ls -d "$pd"/output-*/ 2>/dev/null | sed -E 's#.*/output-([0-9]+)-.*#\1#' | sort -n | head -1)
  if [ -n "$best" ] && [ "$best" != "$prevbest" ]; then echo "best masked score -> $best"; prevbest="$best"; fi
  if grep -qE 'ILS done|WINNER score 0|setup FAILED' "$log" 2>/dev/null; then break; fi
  pgrep -f 'permuter_ils.py func_8014D820' >/dev/null 2>&1 || { echo "ILS process gone"; break; }
  sleep 30
done
echo "FINAL best=$(ls -d $pd/output-*/ 2>/dev/null | sed -E 's#.*/output-([0-9]+)-.*#\1#' | sort -n | head -1) | $(grep -E 'ILS done|WINNER' $log 2>/dev/null | tail -1)"
