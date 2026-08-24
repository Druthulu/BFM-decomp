#!/usr/bin/env bash
# Keep the wave campaign running indefinitely (Drew, 2026-08-23: "rinse and repeat forever").
#
# ox_campaign already loops draw -> draft -> gate -> bank -> next wave on its own; this only
# survives the two things that end it: the --waves cap, and a crash. It NEVER starts a second
# campaign alongside a live one — two campaigns would gate into one src/ tree concurrently.
#
# Clean stop:  touch .run/ox_campaign.stop      (current wave finishes, then everything exits)
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] [watchdog] $*"; }

while true; do
  if [ -e .run/ox_campaign.stop ]; then say "stop file present — watchdog exiting"; break; fi
  if pgrep -f 'tools/ox_campaign\.py' >/dev/null || pgrep -f 'tools/idiom_serial\.py' >/dev/null; then
    sleep 120; continue
  fi
  say "no campaign running — relaunching the chain"
  .run/campaign.sh >> .run/campaign.log 2>&1
  say "chain exited; restarting in 30s"
  sleep 30
done
