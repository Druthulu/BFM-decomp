---
ts: 2026-11-06T11:40:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R2eejf3VEUd0s01Odos8
---
Wait, I dropped the `pmask = ...` assignment inside the block? I have it. And I removed the barrier at the end (v0 had no barrier anyway). But v0 had the order: pmask = ...; *(u32*)p = ...; tag2 = 0xE1000200; ot store. In v2 I wrapped tag2..pmask store. Fine.

Hmm, I also need to double check that in v2 the first group is un-wrapped (yes).

Score v2.
