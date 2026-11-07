---
ts: 2026-11-06T13:20:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UnGPYMYvrrGR9ESW2gyp
---
Item 1 done (took ~25 min? started 06:08, now maybe 06:35). Let me check time and start item 2.

Item 2: func_8017E464. Remove the memory barrier. Score, see diff.

The barrier is inside the do-while loop:
```
            s0 = rand();
            t = rand();
            aa = (s32)(q + 1);
            nn = (s32)buf;
            __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory
            s0 &= 0x1F;
            s0 <<= 2;
            t = (t & 0x1F) - 0x50;
            s0 = s0 + t;
            d[2] = s0;
            func_80015978(aa, (s32 *)nn);
```
The memory barrier prevents sched1 from hoisting `s0 &= 0x1F` etc. above? Or prevents cse from forwarding d[] values? Let's test.

Note item2's pins: flag($2), aa($4), nn($5), c1($5), c2($6) — these are "levers of other kinds the def already had" and may stay.

Let me create w1.c (barrier removed) and score.
