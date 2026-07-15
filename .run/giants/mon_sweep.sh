#!/bin/bash
# Monitor the family_sweep --only 0x80133CD4 ×134 propagation. Emits key progress + terminal.
log=/home/musashi/bfm-decomp/.run/gate_cd4/sweep.log
last=0
while true; do
  n=$(wc -l < "$log" 2>/dev/null || echo 0)
  if [ "${n:-0}" -gt "$last" ]; then
    sed -n "$((last+1)),${n}p" "$log" | grep -E 'exemplars|staged|BANKED|Traceback|Error|error' ;
    last=$n
  fi
  grep -qE '\[sweep\] BANKED|Traceback' "$log" 2>/dev/null && break
  pgrep -f 'family_sweep.py --only 0x80133CD4' >/dev/null 2>&1 || { echo "family_sweep process gone"; break; }
  sleep 20
done
echo "FINAL: $(grep -E '\[sweep\] BANKED|\"banked\"' $log 2>/dev/null | tail -2)"
