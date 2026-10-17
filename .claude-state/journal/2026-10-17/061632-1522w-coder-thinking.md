---
ts: 2026-10-17T12:16:32.705Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af2ee6465c53a6b51
model: claude-opus-5-5[1m]
effort: medium
turnId: ec6de330-34dd-4098-8a4a-06f0f8d4b28c
---
I'm examining block 8, the tail block, noting the register allocations and priorities for r78, r82, and r79, and figuring out that in the target, e2 maps to a0 (absolute), d to v0, and v to v1 - then ordering the local allocations by priority across r104, r105, r78, r106, and r82.

Global r79 ends up getting a0 since it conflicts with both v0 and v1. I'm working through why e2 would need to occupy a0 instead of v0 - it would require v0 to be taken by a higher-priority local during e2's live range, or for e2 itself to be treated as a global spanning multiple blocks so its allocation happens in the global pass. I'm also considering whether this relates to how the abs pattern expands into branch/move/negate instructions in this version of GCC's MIPS backend.

I'm checking whether the abssi2 pattern ties its destination to the source register, since that would prevent v and d from being separate — the move in the template suggests they needn't be equal. The key is getting v to stay live past the abs by having the X store happen after it before local-alloc, then letting the scheduler after reload move that store earlier.

Now I'm tracing whether sched2 could reorder the X store past the abs insn — since abs and the store have no memory dependency, but the store does alias with the sh flags store at offset 44, which constrains ordering so X must precede that flags store. That forces X to come before the flags store in source order while still needing to follow the abs, but the abs itself comes after the flags-store load, which is the contradiction I need to resolve.

Right, so sched1's reverse list scheduling boosts birthing instructions in priority while stores never get boosted, which explains the asymmetry. Now I'm trying to pin down what exactly local-alloc's tying logic requires—block_alloc ties registers when there's a single-set insn with an input that dies, checking constraints like matching operand "0" and no_conflict_p, and this tying attempt happens in two passes.

So this suggests the tying logic prefers combining registers when an operand dies and the instruction has exactly two operands or similar matching constraints—for an abs operation with two operands, it ties if v dies there. That means v must still be live after abs, so maybe it's read again from the global variable after the store rather than carried in a register directly.

But CSE would typically substitute that reload with the known value v unless something invalidates it—like an intervening store to a possibly-aliasing location invalidating the cached memory value. I'm thinking about whether the flags store to a struct field could trigger CSE's aliasing invalidation logic, depending on whether the target is a fixed address versus a varying struct access under the old MEM_IN_STRUCT_P aliasing rules.

Trying another angle: maybe the original source expresses the abs computation differently, perhaps through a macro, which would change how the compiler schedules the loads and stores.

This is matching the classic abssi2 pattern with bgez/move/negu, so any valid spelling has to compile down to the same RTL. The real puzzle is keeping d and v from being allocated to the same register — likely by keeping v alive past the abs operation through a later use.

I'm checking whether X's store could float past the abs in scheduling, since there's no real dependency between them, and whether aliasing rules would let it slot before the flags store to match the target ordering.

Without an explicit memory dependency forcing it late, sched1 could freely hoist X above abs — so I need to look at how backward list scheduling in sched.c picks the highest-priority ready instruction, particularly the priority adjustment in rank_for_schedule, to understand what's actually constraining the order.
