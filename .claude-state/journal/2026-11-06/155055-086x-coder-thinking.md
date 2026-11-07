---
ts: 2026-11-06T22:50:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ztmqzQZ2OIflWpLw2ee1
---
w11 still has d=$s1, s1ang=$s0 (the swap) plus u5=$v1/iVar4=$a1. So the s16 didn't help the priority.

Hmm. w11 is 75 ins (arg0 copy present). But the swap remains.

Let me think about the priority again. In w11 (s16 s1ang), the mask-in-place gives s1ang 7 refs/22 = 6363, d 10000 (do-while). So d should win $s0. But the diff shows d=$s1. Let me check w11's alloc table.

Hmm, wait — maybe with s16 s1ang, the do-while doesn't raise d's refs the same way. Let me dump.

Actually, let me reconsider. The key insight from w6: the mask-in-place + do-while gives d=$s0. w11 is w6 + s16, and it's 38 with 75 ins. Let me dump w11's alloc.
