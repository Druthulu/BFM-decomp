#!/usr/bin/env bash
# THE INTEGRATION-RESOLVER LANE (P31 S61, frontier-analysis-s60 §4). Zero model tokens.
# Re-judges the ledgers' closeness-0 / reloc shape-MATCH stock against TODAY'S tree (rtu_match at the
# real TU, then reloc_identity as the disagreeing oracle), stages the doubly-verified bodies, gates
# them on the whole-binary SHA and commits at once (R42). The tool itself takes .run/auto/draw.lock
# for the judge+gate, so it serialises with the wave gater and the maintenance sweep (rtu reads the
# very src/ TUs a gate splices into). A pass with nothing new costs ~1 minute; the ledger skips every
# (draft, split-TU) pair it has already refused unless one of them changed.
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] [resolver-lane] $*"; }
while [ ! -e .run/ox_campaign.stop ] && [ ! -e .run/auto/STOP ]; do
  say "pass starting"
  .venv/bin/python tools/integration_resolver.py -j 16 --gate-jobs 12 --negative-control 8 2>&1 | tail -14
  say "pass done; sleeping 45m"
  sleep 2700
done
say "stopped"
