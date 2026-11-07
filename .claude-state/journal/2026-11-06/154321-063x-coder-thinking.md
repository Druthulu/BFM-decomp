---
ts: 2026-11-06T22:43:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1MzlAGz8dNSvXLcYKJt6
---
In w7: d=$s1, s1ang=$s0 still (the mask-in-place did NOT swap them here!). Wait, the register pairs: s1->s0 x6 (d in s1, target s0), s0->s1 x3 (s1ang). So w7 did NOT fix the d/s1ang swap. Hmm, but w6 did. The difference between w6 and w7: the do-while on the cast. So the do-while was needed for the mask-in-place to raise s1ang's priority above d? 

In w6 (do-while): s1ang = 7 refs/22 → pri 6363, d = 10000. d won.
In w7 (no do-while): s1ang = ? Let me check the alloc table. Maybe without the do-while, s1ang's refs are fewer.

Let me dump w7's alloc.

Also w7 has 74 ins (missing the arg0 move) — same as w6.

Hmm, the mask-in-place makes the arg0 copy disappear regardless of the do-while.

Let me dump w7's alloc to see s1ang's priority.
