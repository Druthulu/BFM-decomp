#!/usr/bin/env bash
# S58 dual-pool campaign. Two provider pools drafting at once, ONE serial gate.
#
# DOUBLED 2026-08-23 (Drew): every 429 ever recorded here is `upstream_provider_shared_pool` — the
# PROVIDER's pool, never OpenRouter refusing this account. A shared pool saturates because of
# everyone on it, so those 429s measure the POOL's total load and say nothing about OUR ceiling,
# which has therefore never been tested. 128 workers produced 1,836 requests and ZERO 429s.
#
# 640 workers (ox 512 / deepseek 128) is the MEASURED ceiling for this box, not a round number:
#   * one shard's real RSS is 31 MB (import chain + the full card file), and WSL sees 30 GB
#     available -> ~685 agents at 70% headroom. The host's spare ~50 GB is NOT ours; WSL2 gets
#     only what .wslconfig allocates (32 GB here). Raising that is the route to 1000+.
#   * --cards-per-wave caps concurrency independently: shards are dealt targets[i::workers], so
#     a 220-card wave feeds exactly 220 shards no matter how many we start. Hence 1400 cards.
#     The 120-400 band holds 442 groups and 400-2000 holds 37, so those waves self-limit.
# The ledger records free memory per wave: if the box swaps, throughput collapses for a LOCAL
# reason that looks exactly like a provider ceiling (R40 - exonerate the instrument first).
#
# COMMENTS MUST STAY ABOVE THE COMMAND. A `#` line between backslash-continued argument lines
# swallows every remaining argument and the run falls back to argparse DEFAULTS (8 waves / 24
# workers / no lanes) while looking completely normal. `bash -n` does NOT catch it — the construct
# is syntactically valid — and grepping the file finds the arguments even though they never reach
# the program. The only reliable check is the startup banner, which prints what it actually got.
set -u
cd /home/musashi/bfm-decomp
PY=.venv/bin/python
say(){ echo "[$(date +%H:%M:%S)] $*"; }

say "dual-pool campaign starting"
$PY tools/ox_campaign.py \
    --waves 40 --workers 640 --max-workers 1024 --step 128 --sustained 3 \
    --models 'stealth/ox-alpha:512,deepseek/deepseek-v4-flash-0731:128:REASON_EFFORT=high' \
    --lanes 'default:,tells:extend-tell;swaprepeat-tell;s16-div-tell' \
    --cards-per-wave 1400 --gate-jobs 12 2>&1

say "campaign done; serial idiom lane (jtbl-carve, ov_* only)"
MAX_429=10 $PY tools/idiom_serial.py --lever jtbl-carve --n 8 --min-ins 60 2>&1
say "ALL DONE"
