# Autonomous lanes (P31 S58)

The unattended campaign architecture. These are the RUNNING copies' source of truth — the live
lanes execute from `.run/`, which is gitignored, so a fresh clone would otherwise have none of it.
Copy back with `cp tools/lanes/*.sh .run/` before launching.

| lane | role | rule |
|---|---|---|
| `drafter.sh` | draw → shard → draft → queue a ready marker, forever | **NEVER stop it to ship a code change.** Measured 2026-08-23: 139 of 162 idle minutes were exactly that |
| `gater.sh` | reloc pre-filter → gate → commit → harvest → ledger | safe to kill/restart at will |
| `maintenance.sh` | the free A-prop sibling lane | triggers on 150+ newly banked functions, not a timer |
| `stallguard.sh` | 60s: revive dead lane shells, kill agents silent >20min, kill gates >90min | the only thing that works at 3am |
| `resolver_lane.sh` | **(P31 S61)** the integration-resolver lane: re-judges the ledgers' closeness-0 / shape-MATCH stock at the real TU (`tools/integration_resolver.py`), stages, gates, commits — zero tokens | holds `.run/auto/draw.lock` for judge+gate (rtu reads TUs a gate splices into); not yet in stallguard's revive list — restart by hand |

Start: `setsid nohup .run/<lane>.sh >> .run/<lane>.log 2>&1 </dev/null &`
Stop everything: `touch .run/ox_campaign.stop`

**Editing a lane requires replacing its SHELL, not just its python** — bash has the loop body
parsed, so killing the python restarts it with the old arguments. Verify from the startup banner,
never from the file.
