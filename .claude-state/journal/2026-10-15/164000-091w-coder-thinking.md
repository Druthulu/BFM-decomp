---
ts: 2026-10-15T22:40:00.736Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a27f5e99cd45ba1f7
model: claude-opus-5-5[1m]
effort: medium
turnId: 93fc0445-54f4-44e8-8ad6-986fd7c917ec
---
I notice check-structs wrote to struct_map.json during this run, overwriting it, but that should be fine since a fresh census happens later anyway with --sites. Now I need to regenerate the twins and write out the dead-kept entries, organized by tool.

For the dead-kept list, I'll write a small script that reads structs_dead and appends bullets for names matching the T3 definitions (Unkstruct_ prefixed, within the T3 block), verifying all 157 dead entries match the new defs exactly. Since dead_kept is only 2, the T2 defs (2885-2893) must still be live, which checks out.

My plan is to run struct_twins --write first, then rerun check-structs once more -- each pass takes about 3.6 minutes. Since type_census.json was just refreshed by check-structs, struct_twins should pick up current dup classes without needing another census run first.
