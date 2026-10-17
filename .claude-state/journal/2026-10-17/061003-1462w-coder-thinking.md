---
ts: 2026-10-17T12:10:03.105Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
In backward scheduling, when the last scheduled insn depends on producers with latency greater than 1, those producers get demoted to class 1 so they're scheduled earlier to hide the latency — loads like lhu, with latency 2, fall into this case.

I'm checking whether sched2's hard-register dependencies after reload change anything for the move/sll sequence, but nothing seems to differ. I wonder if the real distinction comes from delay-slot filling in reorg: the beqz's nop delay slot could have been filled with a dead-after-branch move, but the target output left it as a nop instead.

Now I'm considering whether j might get reused elsewhere, like as the constant argument 2 in the third call, since CSE could fold it directly into the li a2,2 instruction and leave j's assignment dead.

But that still doesn't explain the gap, since constant propagation would make a fn-scope j reuse moot anyway unless j holds a non-constant value. Let me step back and try a different angle on the register blocking issue, maybe looking at optimize_reg_copy instead.

Actually, maybe the key is ordering: sched1 runs before local-alloc, so if it reorders the copy `k = m` to come before the later use of m, that would let optimize_reg_copy_1 fire — but cse2 runs on the pre-sched order and wouldn't catch this since the use precedes the copy there. That timing mismatch between cse2's view and sched1's reordering could be exactly why the copy survives undetected.

Then I'm checking whether expand_preferences would instead handle it: if m dies right at the copy, that's the "pseudo-pseudo copy when SRC is dead" case, which tries to replace k with m going forward but only works if k dies within the same block — otherwise it likely doesn't apply. Falling back to preference merging, m dying at the copy lets it coalesce with a3 when K3 is present, while without K3 there's no such merge and the final code just keeps the use before the copy, unless sched2 reorders them later.

Since k is referenced by t3v and m is born right after, k ends up with an even shorter live range than I expected, which tips things further in k's favor — not what I want. At this point I'm abandoning the theoretical approach and just going to brute-force try natural code variants on the no-K3 base case (score 10), things like flipping the conditional direction, rewriting the loop structure, reordering the declaration of q, or declaring k before j so it gets a lower pseudo register number and wins ties.

None of these actually change the reference counts though, since they're superficial syntactic rewrites rather than structural changes to live ranges. I'm also reconsidering whether hoisting the t3v read affects k's or m's live range, but it seems not to matter either.

I need to actually check the sched dump for the kj preheader directly, comparing why sched1 kept k first while sched2 swapped the order, to see if there's a concrete rationale I can replicate.
