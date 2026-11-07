---
ts: 2026-11-06T16:54:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TGnTsGbS6LDcRVn429SU
---
3 rows + header = 4 lines. Item 4 remains.

Item 4: func_801888F4 (ov_SC02_000), kinds keepalive,launder. This one has pins (a0 $16, t0 $3, t1 $4, t2 $5) which are other kinds — allowed to stay.

The keepalive: `__asm__ __volatile__("" : : "r"(t0), "r"(t1));` — a sched barrier.
The launder: `__asm__ __volatile__("" : "=r"(q));` — cse remat kill.

Let me fresh-check and baseline, then remove both.
