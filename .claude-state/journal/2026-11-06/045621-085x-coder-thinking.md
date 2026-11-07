---
ts: 2026-11-06T11:56:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vgtP45w5LYSWgHpaAKsR
---
All ≥1, best 1. Score 1 is the cse-forward residual.

x05 (temp_a0 as s32) = 2. Interesting.

Total tries: w1-w12 (12, some are w1-w12) + x01-x18 (18) = ~30. Let me count: w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12 = 12; x01-x18 = 18; total 30. Plus w7 was one. So 30 scored tries. Good.

Time: 04:58. Need 20 min → 05:07. Let me do a few more genuine attempts (maybe there's a crack) while waiting, then record WALL.

Let me think harder about a real-C crack. The barrier's effect: invalidate cse's memory table entry for (arg0+6) between the store and the load.

Real C constructs that invalidate memory:
- A function call. The target has a call AFTER the reload (func_801757A0), not between.
- A store to a potentially-aliasing address. Any store between would invalidate. The target has the `sb a0,5(s0)` AFTER the reload. If I could move a store between the sb+6 and lbu+6... but the target order has no store there.

Wait — actually, the `sh v1,16(s0)` etc. are after. What if I move ONE of the sh stores between the sb+6 and the lbu+6? Then cse would invalidate the QI entry (because cse_rtx_addr_varies_p is true for register-based addresses → ANY store invalidates ALL memory entries!). Look at invalidate_memory: `if (p->in_memory && (all || (nonscalar && p->in_struct) || cse_rtx_addr_varies_p (p->exp)))`. For our QI entry, `cse_rtx_addr_varies_p` is true (address = reg+6) → ANY store removes it!

So if a store occurs between sb+6 and lbu+6, the entry is invalidated and no forwarding. But then sched1 might reorder the sh store away... Let me test: move one of the sh stores between the sb and the lbu. But the target order is sb, lbu, addiu, sb, sh, sh, sh, sh, sh, sh. If I put a sh between sb and lbu in source, sched1 would likely keep it there? sched1 could move it. Let me test!

Actually, even better: the target has `addiu a0,a0,255` and `sb a0,5(s0)` after the lbu. If I reorder the source so that a sh store comes between, the final asm would differ (target order). But maybe sched1 moves it back? Let's test.

Hmm, but the target's sh stores come after the lbu, so any source order that puts them before would need sched1 to move them after — unlikely for a store (sched1 doesn't move stores across loads of the same address, but different addresses are fine).

Let me test: put `*(s16*)(arg0+0x10) = temp_v1;` right after the sb+6 and before the reload. Then cse invalidates, and sched1 might move it back to the target position (since stores are ordered? sched1 can reorder independent stores).

Let me try a few placements. This could actually crack it!

Variant y01:
```
temp_v0 = p[6] - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8*)(p+6) = (u8)temp_v0;
*(s16*)(p+0x10) = temp_v1;     // intervening store
temp_v0 = *(u8*)(p+6);
*(u8*)(p+5) = ...;
... rest
```
Let me test this and a few permutations of which store goes between.

This is promising! Let me test.
