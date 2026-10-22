---
ts: 2026-10-22T00:14:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Toi3vUoZMNObOjldmynE
---
Good survey. Now, the items and their launder lines:
1. func_801832A8 (ov_SC02_026): launder on `vol` at 7003 (and another function at 7252 — func_8018389C, which is also an item!). Both items are in the same TU: func_801832A8 and func_8018389C. The launder at 7252 is in func_8018389C presumably.

2. func_8018389C (ov_SC02_026): launder on vol at 7252.
3. func_8017DE84 (ov_SC02_039): launder on s0 at 3237.
4. func_80185380 (ov_SC03_014): launder on v6 at 3172 (and p10 at 3174) — that's in one function; another item func_8018AA98 in the same TU has the launder at 6811 (pv, out-only, "kills the sched1 birthing boost").
5. func_8018AA98 (ov_SC03_014): launder at 6811 (out-only, kills the sched1 birthing boost).
6. func_80180054 (ov_SC03_030): launders at 5435-5455 (xa, xb with spaces in the asm template!) and 5466 (p).
7. func_8017E780 (ov_SC03_092): launder on t at 4739.
8. func_80181CF4 (ov_SC03_097): launder at 5339 (pv, out-only, kills the sched1 birthing boost).

Interesting: items 5 and 8 have the "out-only" launder `__asm__ __volatile__("" : "=r"(pv));` — "zero-byte 2nd SET: kills the sched1 birthing boost". The moves.md recipe for such cases: "launder->real 2nd set pv &= 0xFF000000 split (real 2nd set)" — from other shards, e.g. G09/W05: "launder->pv=*p; pv&=0xFF000000 split; pv $3 pin dropped; ang $4 pin kept (not row kind), pin-free 4".

So for items 5 and 8, the recipe is known: replace the out-only launder with a real second set of pv (e.g. `pv = *p; pv &= 0xFF000000;`).

Let me look at items 5 and 8 first — they're likely the easiest wins.

Let me read the function func_8018AA98 around line 6811 in ov_SC03_014.
