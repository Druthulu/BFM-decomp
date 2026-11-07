---
ts: 2026-11-06T04:23:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZhA86pbN7YLFzhDjJ5nX
---
u1 = 32, worse. The pointer reuse in the `==0` arm changed the schedule badly.

Let me step back. Time: item 4 started ~21:22; it's now maybe ~22:00? Let me check date. I've done ~15 tries. Budget 20-30 min per item; WALL needs ≥20 min and ≥30 tries.

Let me reconsider the whole approach. The current best is w4/w5/w6/w7/w9 at 14 (107 ins). The target's 108 ins. The main issue: p's reload hoisted above the multiply chain → p gets a0 instead of v1.

Key idea: make the p reload depend on the multiply. What if we make the multiply result the store's *address offset*? No.

What if we reorder so the p load is after the multiply AND sched1 won't hoist because the p load's *address* (s1) is used... no.

Another idea: use `n` (the s32 variable) to hold the multiply result, and `v`... no.

What if the p load's use is moved further down so its priority is lower? In target, the p load's use is addiu then sh. In mine too.

Hmm, what about the `+0x600` placement: target has addiu AFTER the p load. The fence kept +0x600 below p's load. If +0x600 were BEFORE p's load (source), then the chain is complete before p, and sched might place the whole chain first then p. Let me test: 
```
v = *(s32*)(obj+0x1C) * 3 * 32;
v = v + 0x600;
p = ((Unk*)a0)->unk20;
```
Then the RTL order: chain, add, p. sched might emit chain, add, p (target: chain, p, add). Hmm, not matching, but the register might become v1 (p born after v's last use → can share v1). Then the only diff would be add/p swap.

Actually, target order: sll/addu/sll/lw/addiu/sh. If source is chain/add/p, sched could produce chain/add/lw/sh — the addiu before the lw. That's a 2-insn order diff. But maybe sched moves the p load before the addiu (load latency hiding) → target! Because the addiu depends on the chain and the lw is independent; sched might put the lw before the addiu to hide latency. That's plausible and would match the target.

Let me test (x1): move `v = v + 0x600;` before the p load.

Also x2: `v = (*(s32*)(obj+0x1C) * 3 * 32) + 0x600; p = ...;`

Let me test.
