#!/usr/bin/env bash
# THE LANE THAT MUST NEVER STOP. Drafting is the only thing gated by the free-ox clock; it touches
# nothing but .run/, so no code change to the gater, the tooling or the rules ever needs to stop it.
# Measured 2026-08-23: 139 of 162 idle minutes were this lane being killed to ship a fix.
#
# 1720 ox = the 10x Drew asked for. Both caps I previously set were measurement artifacts:
#   * "ox saturates at 9.8% 429s" — 961 of 964 429s landed in the FIRST 5-MINUTE BUCKET, the
#     thundering herd of 818 shards starting at once. Every later bucket was 0.0%. Fixed by
#     staggering shard startup, not by capping concurrency.
#   * "39 MB per agent" — a STARTUP snapshot with the card file freshly loaded. Steady state is
#     ~10 MB, so 45 GB carries thousands, not hundreds.
# TELLS REMOVED FROM THE DRAFTING ROTATION (P31 S58, 2026-08-24). Four waves measured:
#   as 5/9 gated of 57 drafts · aw 6/12 of 60 · az 4/10 of 55 · bd 3/9 of 56
# ~80% of tells drafts name symbols the target .s never references, so reloc_identity discards
# them before they reach a gate. Against the default lane's 73-86% of gated, that is ~55 drafts of
# fleet time per wave for 3-6 functions.
#
# NOTE: do NOT assume aprop_autodraft is the answer. Its input population overlaps the 1,040 tells
# member functions by only 44 (4.2%) — checked, after asserting the opposite three times from the
# failure signature alone. Where tells should go is an OPEN QUESTION requiring its own study.
#
# The remaining real constraint is CARD SUPPLY: a fleet is only as busy as the wave is large.
#
# BANDS ARE NOW MOSTLY FULL-RANGE. Narrow bands were right when each held thousands of
# candidates; they now FRAGMENT a shrinking pool — measured P31 S58: the 400-2000 band drew NINE
# cards for a 2,000-worker fleet (0.45% utilisation) because that band has 37 groups total and
# most are banked. One targeted 120-2000 slot is kept so large functions still get drawn
# deliberately; the rest draw from everything.
set -u
cd /home/musashi/bfm-decomp
export MAX_429=10
while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/ox_campaign.py --drafter \
      --workers 2000 \
      --models 'stealth/ox-alpha:1720,deepseek/deepseek-v4-flash-0731:280:REASON_EFFORT=high' \
      --bands '5-2000,5-2000,120-2000,5-2000' \
      --cards-per-wave 3000 --queue-depth 2 2>&1
  echo "[$(date +%H:%M:%S)] [drafter] exited; restarting in 20s"
  sleep 20
done
