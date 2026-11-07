---
ts: 2026-11-06T17:41:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rlLnxjUwqr01KanWUQaY
---
Time 15.4 min. Still 7.

Let me run 3 more batches (each ~20-30s) to reach 20 min. I'll try more shapes.

p1: make the then arm's shift read from a *volatile* copy? no.
p2: use `s32 sh16;` and assign via a helper: `sh16 = angle << 16;` where angle is cast to `(s32)((u32)angle & 0xffff)`? adds andi.

Let me try a set of expression variants around the final store (which might change 75's qty):
p3: `p[0x79] = (u16)((sh16 >> 16) + ((u32)sh16 >> 31)) >> 1;` (i1=17)
p4: `p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) / 2);` (b2=18)

Hmm.

Maybe try changing the *first temp*'s creation order: e.g., compute the >>31 part FIRST:
```
s32 lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);
```
The instruction order would be srl first, then sra — different bytes. But maybe sched1 reorders? Let me test; if the score drops, interesting.

Also:
```
s32 hi = sh16 >> 16;
s32 lo = (u32)sh16 >> 31;
p[0x79] = (u16)((hi + lo) >> 1);
```
Two named temps; the order may match the target's sra/srl.

Let me test these two.
