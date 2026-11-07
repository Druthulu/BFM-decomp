---
ts: 2026-11-06T10:36:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RWW5zAXAZnIvqW1mYCTm
---
Excellent! r1/r2/r3 = score 2 (down from 5). The do-while around the casts (r1) reproduces the keepalive's ordering effect! Now the residual is the sign-ext temp (REG-mixed).

So r1: lever-free, score 2. The remaining issue is the sign-ext temp (`sll v1,s0,0x10; sra s0,v1,0x10` vs in-place).

Let me see r1's diff to confirm.
