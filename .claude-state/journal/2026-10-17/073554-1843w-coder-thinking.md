---
ts: 2026-10-17T13:35:54.809Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm noticing the store base register just got renamed—likely GCC's post-reload CSE choosing a0 as equivalent. The key difference might be that with the pinned hard register s0, the store address uses $16 directly, with the argument copy happening before the store.

Trying to trace where the rename to a0 actually occurs in RTL: maybe the scheduler reorders the a0 assignment before the second store, then reload_cse_regs substitutes the pinned register with a0 since they're equivalent in cost. But I'm unsure whether scheduling would behave differently with a hard-pinned register versus a pseudo, since hard-reg dependencies might block that reordering.

I need to figure out what levers actually control this order: maybe changing how the second store's address is computed (separate pseudo vs. folded by cse), or how the call argument is cast, could shift the generated order, but cse likely folds these attempts anyway. I should check whether sched1 is even enabled for this compilation unit and look at the Makefile or compiler flags, and maybe grep through documentation for "reload_cse" or "delay slot" to find the relevant lever.
