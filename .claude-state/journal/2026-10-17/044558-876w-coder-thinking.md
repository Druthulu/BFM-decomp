---
ts: 2026-10-17T10:45:58.686Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm thinking about where to place a second set so it disappears before sched1 but still gets counted in reg_n_sets -- since reg_scan runs before cse2, having cse2 delete the insn rather than reduce it to a trivial self-set might preserve that count while leaving no scheduling artifact.

I'm trying to recall whether cse_insn in 2.7.2 actually deletes no-op moves directly, or whether that cleanup happens later in jump_optimize after cse2, or even later during flow/reload -- since flow doesn't remove self-sets and reload typically does. I'm also considering whether placing the second set in a block structure sched1 treats differently, like around a call insn that may not terminate a basic block in this version's scheduler, could avoid the problem entirely.

I'm testing various placements for the no-op set -- right before block 2's call, inside block 1 before the first use, or adjacent at the very top of the function wrapped in a trivial do-while -- to see if any location lets cse1 collapse it harmlessly within a single extended basic block without disturbing the instruction counts elsewhere.

Looking at block 1 specifically, the target has a0 set to zero right before base's own set, so the store happens right after base in the same scheduling pattern as block 3. This makes me think the gcc 2.7.2 scheduler is processing instructions backward from the end of each block, and I want to trace that logic to understand why base's set isn't directly followed by the store in the target version.

Checking block 2 of f2, the order starts with the a0/a1 setup instructions before the remaining stores, suggesting ties favor placing those first. Looking at block 3, insn 110 needs to precede 124 and 163 since 163 depends on 75, so I'm trying to pin down whether rank_for_schedule breaks ties by priority first, then by original instruction order (luid) as a fallback.

The no-op `(set 75 75)` persists into sched1 with anti-deps, and the following block schedules its first store ahead of the argument moves. I'll check cookbook C0052 on the LUID dial, which covers sched tie-breaks.
