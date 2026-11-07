---
ts: 2026-11-06T17:04:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l31RE9RzOTmoWyy6vMR6
---
All four rows present, one per item. 

Now append the moves.md lines. The format: `kind | func | MATCH: move / WALL tag — mechanism (W47)`.

- launder | func_8018AB20 | MATCH: split `pv = pv & 0xFF000000` into its own statement — a real live 2nd SET (reg_n_sets=2) demotes sched1's birthing boost; bytes identical (W47)
- pin | func_8017F200 | MATCH: `v1 <<= 16; v1 >>= 16;` self-set sign-ext (no temp steals $2) + `s16 a0r` keeps `move a0,v0`; v0 split at JOIN (W47)
- barrier,keepalive,pin | func_800D1E9C | WALL jump2-crossjump-arms — jump2 merges the two identical 4-call arms; only a byte-changing reorder blocks it (best 5); expand void-return keeps li v0,1 (W47)
- keepalive,launder | func_801888F4 | MATCH: `do { m = D_800AE620; } while (0)` struct assign splits cse1's EBB (&m remat not cached) + q launder→dead reset `q = 0` (W47)

Let me append these as one command (one action). Actually "One action per command: a results.tsv fix is its own step" — moves.md appends can be one command. I'll do one printf with all four lines.

Then write the log phase-ends/current/logs/T11.cW47.md.

The log needs: timeline per item (start/end time, minutes, tries), moves that cracked, walls with evidence. Plus "Friction" section if any denied commands. I had bwrap collisions (not denials) and two compile errors. No permission denials. I'll note the bwrap reruns? Not friction.

Let me append moves.md.
