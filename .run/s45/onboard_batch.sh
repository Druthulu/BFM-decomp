#!/usr/bin/env bash
# S45 II.1 driver: onboard a batch of md_* modules via tools/new_binary.sh, logging per-module
# PASS/FAIL. A byte-gate failure PARKS that module (records it) and continues the batch — the
# plan's safety rule: never force a failing derived address.
set -uo pipefail
cd "$(dirname "$0")/../.."   # repo root
LOG=.run/s45/onboard.log
PARKED=.run/s45/parked.txt
touch "$LOG" "$PARKED"

onboard() {  # alias payload vram tlo
  local alias="$1" payload="$2" vram="$3" tlo="$4"
  if [ -f "config/check.${alias}.sha" ] && grep -q "^${alias}_EXE " config/modules.mk 2>/dev/null; then
    echo "SKIP  $alias (already onboarded)" | tee -a "$LOG"; return 0
  fi
  echo "=== $alias  $payload  $vram  tlo=$tlo ===" >> "$LOG"
  if tools/new_binary.sh "$alias" "$payload" "$vram" "$tlo" >> "$LOG" 2>&1; then
    if make check BINARY="$alias" >> "$LOG" 2>&1; then
      echo "PASS  $alias" | tee -a "$LOG"
    else
      echo "FAIL-CHECK  $alias — parked" | tee -a "$LOG"; echo "$alias check-failed" >> "$PARKED"
    fi
  else
    echo "FAIL-ONBOARD  $alias — parked" | tee -a "$LOG"; echo "$alias onboard-failed" >> "$PARKED"
  fi
}

batch="$1"
case "$batch" in
  slotA)
    M=extracted/retail/MAIN.CD.dir
    onboard md_MAIN_013 $M/FILE_013.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_014 $M/FILE_014.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_015 $M/FILE_015.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_016 $M/FILE_016.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_017 $M/FILE_017.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_018 $M/FILE_018.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_019 $M/FILE_019.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_020 $M/FILE_020.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_021 $M/FILE_021.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_022 $M/FILE_022.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_023 $M/FILE_023.dir/0.1 0x800CAE08 0x4
    onboard md_MAIN_024 $M/FILE_024.dir/0.1 0x800CAE08 0x4
    onboard md_MAIN_025 $M/FILE_025.dir/1.1 0x800CAE08 0xC
    onboard md_MAIN_026 $M/FILE_026.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_027 $M/FILE_027.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_028 $M/FILE_028.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_029 $M/FILE_029.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_030 $M/FILE_030.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_031 $M/FILE_031.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_032 $M/FILE_032.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_033 $M/FILE_033.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_034 $M/FILE_034.dir/1.1 0x800CAE08 0x80
    onboard md_MAIN_035 $M/FILE_035.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_036 $M/FILE_036.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_037 $M/FILE_037.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_038 $M/FILE_038.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_039 $M/FILE_039.dir/1.1 0x800CAE08 0xC
    onboard md_MAIN_040 $M/FILE_040.dir/1.1 0x800CAE08 0x4
    onboard md_MAIN_041 $M/FILE_041.dir/1.1 0x800CAE08 0x4
    ;;
  slotB)
    M=extracted/retail/MAIN.CD.dir
    onboard md_MAIN_042 $M/FILE_042.dir/0.1 0x800CCB1C 0x4
    onboard md_MAIN_043 $M/FILE_043.dir/0.1 0x800CCB1C 0x4
    onboard md_MAIN_044 $M/FILE_044.dir/0.1 0x800CCB1C 0x4
    onboard md_MAIN_045 $M/FILE_045.dir/0.1 0x800CCB1C 0x4
    onboard md_MAIN_046 $M/FILE_046.dir/0.1 0x800CCB1C 0x4
    onboard md_MAIN_047 $M/FILE_047.dir/0.1 0x800CCB1C 0x4
    ;;
  boot)
    M=extracted/retail/MAIN.CD.dir
    onboard md_MAIN_001 $M/FILE_001.dir/1.1 0x800CEDF8 0x4
    onboard md_MAIN_008 $M/FILE_008.dir/1.1 0x800CEDF8 0x4
    onboard md_MAIN_011 $M/FILE_011.dir/1.1 0x800CEDF8 0x7C
    ;;
  sc07)
    S=extracted/retail/SC07.CD.dir
    onboard md_SC07_003 $S/FILE_003.dir/1.1 0x801A00D8 0xFC
    onboard md_SC07_004 $S/FILE_004.dir/1.1 0x801A00D8 0x158
    ;;
  *) echo "usage: onboard_batch.sh slotA|slotB|boot|sc07"; exit 2 ;;
esac
echo "--- batch $batch done; parked: $(wc -l < "$PARKED") ---" | tee -a "$LOG"
