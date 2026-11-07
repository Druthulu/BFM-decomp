---
ts: 2026-11-06T10:14:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bycQMB4jFvRpf98cE2Rg
---
Wait, k4 adds `rv = 0;` at the top — that adds an instruction (move v0,zero at top), changing codegen. Target doesn't have it. So k4 will differ. But it might still reveal the allocation. Actually k4 is bad. Let me remove it mentally; I'll score all and see.

Also k3 changes `s32 x = D_801EEAEC[0];` to separate declaration+assignment — same code, different pseudo ordering.

Let me run.
