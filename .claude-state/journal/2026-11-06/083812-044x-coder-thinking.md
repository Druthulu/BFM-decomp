---
ts: 2026-11-06T15:38:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vnV1YzUT8GZECMtePNpH
---
Target: s0 = &D_800AF630 at 111-113, then two addiu a0,s0,24, then s0 = sp+104 at 121 (for the gte pointers p0 etc.), and move a0,s0 at 188 etc.

So s0 is reused after: `addiu s0,sp,104` — the p0 pointer. So the base &D_800AF630 is only live for the two calls.

In c1: s0 = &D_800AF630+24 (line 113-115?), let me check c1's s0 uses.
