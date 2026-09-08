#!/bin/bash
# auto_stop.sh — request a SAFE exit of the unattended Phase-16 run. The driver finishes the
# current function (gate+propagate+commit), writes a final heartbeat, and exits cleanly; the
# supervisor sees the sentinel and does not relaunch. Safe to run anytime, with or without a
# Claude session. Remove .run/auto/STOP to allow a future run.
cd "$(dirname "$0")/.."
mkdir -p .run/auto && touch .run/auto/STOP
echo "STOP requested -> .run/auto/STOP . The run will halt safely at the next function boundary."
echo "(Remove it with: rm .run/auto/STOP)"
