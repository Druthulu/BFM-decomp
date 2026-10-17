---
ts: 2026-10-17T12:38:55.149Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm puzzled why cse2 didn't fold the (plus 75 k) addresses even though base 75 was set to sym with REG_EQUAL — reg 75 has two sets across insns 12 and 110, so cse should track it, unless the LOOP_BEG/END notes are splitting cse2's extended basic block boundary at LOOP_END.

Tracing through f2's `do { base = D; } while(0)` structure, the LOOP_END note lands right after base's assignment, so both cse1 and cse2 treat that as an EBB boundary, leaving base unknown afterward — and since the REG_EQUAL note shows n_sets=2 from the re-set, sched also treats it as unknown. For cse, the EBB breaks right after base's set; for sched, it's the n_sets≥2 condition or absence of the note. I'm now tracing the pass ordering (jump, cse1, jump, loop, cse2, jump, flow, combine, sched) to figure out which EBB breaks don't leave sched barriers — concluding the label would need to survive to cse2 and then get deleted by the jump pass that runs after cse2, which requires cse2 itself to have simplified the jump.

Alternatively, I'm considering that the label might persist all the way to sched2, creating a basic block boundary there instead, and I'm examining the target MIPS prologue and call sequence to see where such a boundary could sit without violating instruction ordering constraints.

A label could plausibly sit right after each jal instruction, before the hoisted argument setup for the next call, which is consistent within a block. But I realize any such label needs a referencing jump or it gets deleted as unused by the jump optimization passes — unless it's specially preserved, like a label whose address is taken via `&&label` in GNU C, which would prevent that deletion.

So I'm questioning whether the label survives long enough: if an earlier jump pass deletes it before the constant-folding pass runs, that pass wouldn't see through the symbolic reference. But if the label survives until that point, the folding could still happen — I need to check whether this pass actually consults this information when folding the addition with the symbolic constant.

Actually, this hinges on whether the resulting folded address is even valid for the target, and whether loop boundary markers persist long enough to act as a scheduling barrier blocking the instruction placement that's causing the mismatch — particularly the position of the zero-store instruction in that third block.

I'm checking whether sched2 still sees that same loop-note barrier, since sched1 reattaches notes to insns before removing them and sched2 re-emits them afterward — meaning the barrier should land at the same insn in both passes, keeping everything before `sw zero,-12(s0)` ordered freely but still preceding it.

But target order shows `move a0,zero` above the store too, which means the barrier can't actually be pinned at the store insn — I need to find where the loop-end note really falls relative to `move a0,zero`, since a0 is set up right before the call, not under my control.

Maybe the barrier is placed where LOOP_BEG precedes `base = D`, so the base-set happens inside the loop's scope and the EBB splitting occurs there instead — that would explain why cse treats everything after LOOP_END as a fresh block without needing the store to be the pivot.

I need to figure out where the barrier insn X could actually sit without blocking the move a0,zero hoist seen in the target. If X is placed right at the start of block 2, before the store to zero(s0), then the preceding li a0,1 and addiu a1 insns would need to stay above it — so I'm checking whether that's consistent with the target ordering.

Then I'm reconsidering whether the call insn itself acts like a scheduling barrier in this older GCC version — recalling that calls aren't full barriers but do flush pending memory dependency lists, so I need to check how sched_analyze_insn handles that.

Then I'm wondering if placing the loop end note right before the call could work, but the argument-setup moves sit between the base set and the call, complicating where the note actually attaches in the instruction stream.

I'm also considering whether wrapping the whole thing in a do-while(0) loop would let CSE treat it as one extended basic block, but that doesn't seem to solve the problem either.

Let me reconsider which block structure causes the barrier issue, and whether sched1 versus sched2 differ in how they handle notes re-emitted after the first scheduling pass.

I should trace whether a surviving label gets deleted by jump optimization only when cse2 actually modifies a jump, so let me check the ordering in toplev.c more carefully.
