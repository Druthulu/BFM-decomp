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
# TELLS: RESTORED, BUT PINNED TO THE FULL BAND (P31 S59, 2026-08-24). S58 removed the lane on four
# waves — as 5/9 gated of 57 · aw 6/12 of 60 · az 4/10 of 55 · bd 3/9 of 56 — and attributed the
# failure to the LANE. The campaign ledger says it was the BAND: every one of those four ran at
# 120-2000, and the whole tells population splits cleanly by band:
#   tells @ 120-2000 (as/aw/az/bd): 228 drafts ->  18 banked =  7.9%
#   tells @ full band (ao/au/bb/bg): 655 drafts -> 161 banked = 24.6%
#   default @ full band            : 2,996 drafts -> 1,335 banked = 44.6%
# So tells is ~2x worse per draft than default, not dead, and it is the only lane that touches
# 1,040 members / 86,602 instructions. Of what actually reaches a gate the two lanes are the SAME
# (tells 54.4% of gated, default 56.4%) — the entire loss is reloc_identity discarding drafts that
# name symbols the target .s never references, i.e. cookbook §235 (the phantom symbol), which is a
# BRIEF fix, not a lane deletion. R40: exonerate the instrument before blaming the subject.
#
# S59 REFINEMENT, from the same ledger joined to the wave cards and to the BANKED FUNCTIONS the
# wave's own commit names (bank rate by size, cards->banked, pooled over waves bb/bg vs bc/bf):
#   nins    default        tells
#   0-50    303/528  57%   27/ 67  40%
#   50-80    43/145  30%   20/ 73  27%
#   80-120    9/ 41  22%   10/100  10%
#   120-200   1/ 30   3%    1/ 68   1%
#   200+      2/ 35   6%    0/ 30   0%
# At EQUAL SIZE the two lanes are close below 80 instructions and both collapse above it. What
# actually separated them is the card SIZE MIX: default's cards are median 37-39 ins, the tells
# pool is median 89-95 — 2.4x larger — so "the tells lane is broken" was measuring the population,
# not the lever. Tells therefore draws a SMALL band (5-80), where its yield is within a few points
# of default's; widen it only when that stratum is worked out.
#
# The rotation pins the arithmetic: lane = index%4, band = index%4, so slot 1 (tells) always draws
# the small band and slot 3 (the large band) is always default. Changing the length of either list
# breaks that alignment — change both together.
#
# NOTE: do NOT assume aprop_autodraft is the answer for tells. Its input population overlaps the
# 1,040 tells member functions by only 44 (4.2%) — checked, after asserting the opposite three
# times from the failure signature alone.
#
# The remaining real constraint is CARD SUPPLY: a fleet is only as busy as the wave is large.
#
# BANDS ARE NOW MOSTLY FULL-RANGE. Narrow bands were right when each held thousands of
# candidates; they now FRAGMENT a shrinking pool — measured P31 S58: the 400-2000 band drew NINE
# cards for a 2,000-worker fleet (0.45% utilisation) because that band has 37 groups total and
# most are banked. One targeted 120-2000 slot is kept so large functions still get drawn
# deliberately; the rest draw from everything.
# CREDIT STOP, 2026-08-24 ~14:15 (P31 S59). The paid deepseek lane was burning the OpenRouter
# balance at ~$1.43/h over the last three waves ($4.56 -> $2.56 between 11:54 and 13:18) and the
# balance was ~23 minutes from `--credit-floor 2.0`, which does not pause the paid lane — it BREAKS
# the whole drafting loop, and the shell then restarts a python that breaks again. ox-alpha is free
# for the rest of this window, so drafting continues on ox alone at zero burn; the floor drops to
# 0.25 because with a free model the balance is no longer a proxy for "can we draft".
#
# TO RESTORE the second provider pool after a top-up: put the deepseek lane back in --models and
# raise --credit-floor to 2.0. Its value is a pool with an independent 429 ceiling (it has never
# returned one), not throughput: it was 280 of 2,000 workers.
set -u
cd /home/musashi/bfm-decomp
export MAX_429=10
while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/ox_campaign.py --drafter \
      --workers 2000 \
      --models 'stealth/ox-alpha:2000' \
      --lanes 'default:,tells:extend-tell;swaprepeat-tell;s16-div-tell,default:,default:' \
      --bands '5-2000,5-80,5-2000,120-2000' \
      --cards-per-wave 3000 --queue-depth 2 --credit-floor 0.25 2>&1
  echo "[$(date +%H:%M:%S)] [drafter] exited; restarting in 20s"
  sleep 20
done
