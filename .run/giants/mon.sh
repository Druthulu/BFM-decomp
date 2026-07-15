#!/bin/bash
# General bounded permuter-ILS monitor. Usage: mon.sh <fn>
# Emits each new ILS log line (cycle results) + terminal; exits on done/win/process-gone.
fn="$1"
log=/home/musashi/bfm-decomp/.run/giants/ils_${fn}.log
last=0
while true; do
  n=$(wc -l < "$log" 2>/dev/null || echo 0)
  if [ "${n:-0}" -gt "$last" ]; then sed -n "$((last+1)),${n}p" "$log"; last=$n; fi
  grep -qE 'ILS done|WINNER score 0|setup FAILED' "$log" 2>/dev/null && break
  pgrep -f "permuter_ils.py ${fn}" >/dev/null 2>&1 || { echo "ILS process gone"; break; }
  sleep 20
done
best=$(ls -d /home/musashi/bfm-decomp/.run/permuter/${fn}/output-*/ 2>/dev/null | sed -E 's#.*/output-([0-9]+)-.*#\1#' | sort -n | head -1)
echo "FINAL best=$best | $(grep -E 'ILS done|WINNER' $log 2>/dev/null | tail -1)"
