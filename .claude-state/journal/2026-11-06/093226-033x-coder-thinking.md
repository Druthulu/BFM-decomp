---
ts: 2026-11-06T16:32:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YLR1HjPqvTrjSRaw90eV
---
So combine_regs ties pseudo self to hard reg a0 when the copy insn is scanned and arg0 isn't clobbered in the block. In the then block, a0 is clobbered (mask), so the copy dies? Actually local_alloc processes insns in order; combine_regs ties qty_phys_sugg[pself] = a0 for the block where valid. Hmm, "Return failure so the lifespan of UREG is terminated here" — the hard reg a0 gets a suggestion.

So in the else block, self gets tied to a0. To prevent, the else block must define a0 before self's uses, or self must not be a copy of a0 in that block.

Hmm... but note: the copy insn itself is in the entry block. Local_alloc scans each basic block separately, and the copy is in the entry block. Within the entry block, a0 isn't modified (mask is in then block), so self is tied to a0 in the entry block! Then the then block: a0 clobbered → self's uses must go elsewhere (a1, allocated). In the else block, no clobber → uses get a0. That matches.

To prevent tying in the entry block, a0 must be clobbered in the entry block before/at the copy? The copy is at entry start. If mask is computed before the if (entry block), the order is `li a0,-129` then... if the copy is before the li, tie still possible for the copy point. But local_alloc ties based on whether a0 is modified later in the block? Let's read more of combine_regs.
