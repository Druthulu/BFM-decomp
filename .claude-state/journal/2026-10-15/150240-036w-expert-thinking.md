---
ts: 2026-10-15T21:02:40.477Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
The check-casts residue looks clean: no uncovered or unbacked cases. TNC dropped from 291,819 to 139,520, a 52% reduction, with types going from 13,736 to 12,742 and raw P falling from 257,470 to 174,987. The top_types list still shows Unkstruct_800D3888 with 19,259 sites, but that's expected since it's tracking all struct-map sites rather than just TNC—now I'm checking how many of the top 75 types remain TNC.

Rather than computing TNC by type from the ledger, I'll just note the c3 figure and move on. Next up is measuring header fan-out and R22—I'll touch struct_types.h and time an incremental check-all build, then run the full verify gate (check-structs, check-residue, clean, extract-all, check-all) as a separate job, estimating it could take several minutes given the earlier batch took 115s. I'll run the fan-out measurement as its own job too, likely around 6 minutes.
