---
ts: 2026-11-06T16:41:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zfRRCM8WtUno00J6Qowv
---
In the initial RTL, both blocks use 73 (self). Then flow/cse/combine/sched1/local_alloc transform. The final asm has then using a1 and else a0. Since both blocks use 73 in the RTL, the split must come from regmove or local-alloc.

Global dispositions: 72 in 5, 73 in 4. Both blocks use 73, which is a0 → both should be a0! But the asm shows then using $5. So regmove must have rewritten the then block's uses to 72? Actually regmove optimizes `(set 73 72)` copy: it may change the copy direction and uses.

Hmm wait, maybe I mixed up: perhaps 72 is used in block1 after local-alloc's combine? local_alloc can substitute the copy source for uses within a block: in block0, 73's uses after the copy could be replaced by 72? No, local-alloc ties registers but doesn't rewrite uses (that's cse).

Let me look at the lreg dump (after local-alloc) for w1 to see which pseudo each block uses.
