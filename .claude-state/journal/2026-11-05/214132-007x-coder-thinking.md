---
ts: 2026-11-06T04:41:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i91jX3AOTdOh1Qs5GgvZ
---
Let me set up item dirs. First copy orig.c from src for each item.

Item 1: func_8017F5A4 — two barriers between the three byte-update statements. The barrier prevents cse from... Let's understand. The body:

```
u8 *p = a0;
s32 v0;
v0 = p[0] - a1;
if (v0 < 0) v0 = 0;
p[0] = v0;
barrier
v0 = p[1] - a1;
...
```

The barrier stops cse from reusing the address computation of p[0]/p[1]/p[2]? Or keeps v0 in a register... Actually more likely: it prevents combine/cse from folding the byte stores or from keeping the address offset. We need a lever-free body that scores 0.

The likely crack: barrier -> store through pointer with different spelling? The moves list shows barrier MATCHes often via writing the store differently (per-arm store, plain casts, etc.). For this one the barrier is between repeated pattern. Maybe cse would common the `p+1` address with something? Hmm.

Let me set up and try candidates. First copy orig.c and run baseline. Let me check how delever_search works with --body (body only presumably the function definition text). dt.sh <itemdir> <body file>.

Let me copy orig.c for each.
