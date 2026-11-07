---
ts: 2026-11-06T13:38:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NL2R654HiWRIldJEK97Z
---
v10 uses `m` which is D_80192CC0 — that would change code (extra loads). Remove it. Let me replace v10 with something else: `d = cc * (500 + D_80126950);`.

Actually the m one adds a subtraction of two globals — code changes. Let me replace with a struct alias:
`d = cc * (((struct { s32 v; } *)&D_80126950)->v + 500);` — hmm, that's a MEM_IN_STRUCT load; the code should be the same lw. But sched's dependence might differ (nonscalar). Worth a try.

Let me edit.
