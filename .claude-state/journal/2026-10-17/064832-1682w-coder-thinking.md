---
ts: 2026-10-17T12:48:32.461Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm comparing how the target loads v1=3 once and reuses it, versus my version which reloads constants and branches separately on the same register. I need to find a way to prevent the compiler from folding the "t != 3" check, perhaps by having the inner test compare against a different value rather than t itself.

Then I'm tracing through how CSE's jump-equivalence logic works: after a conditional branch like `bne t,5`, the fallthrough path records that t equals 5, so when the code later checks `t != 3`, fold_rtx substitutes the known value and simplifies it away — unless t is a pseudo whose value class prevents that substitution.

I'm also reconsidering the compiler pass ordering: whether jump threading happens before or after CSE in rest_of_compilation, since that determines whether the redundant comparison gets folded by cse1, survives until cse2, or gets threaded away entirely by the separate thread_jumps call.

For the redundancy to persist, there'd need to be another live jump into the inner test block that prevents threading — maybe from a slightly different source structure, like nested case/if logic where t==3 and t==5 share a branch.

In the target, the first beq t,3 jumps directly to 054, leaving the inner block with a single fallthrough predecessor from bne t,5, which cse2 should normally fold away unless something stops it from following that path — I'm trying to figure out what blocks cse2 from collapsing it here.

Maybe the inner test uses a different pseudo (B) that's a copy of A, and record_jump_equiv merges B into A's class when A==5 is recorded, so B becomes equivalent to 5 too. Or perhaps the inner test is actually reachable from another path entirely, like one of case 5's later checks on mode, which would explain why cse2 doesn't treat it as dead.

I'm also considering that the outer test combines t==3 and t==5 into one branch structure, where testing t!=3 inside the merged block is how the compiler re-derives the t==5 case from a combined conditional.

But this threading pattern would make cse2 fold the inner label entirely, which contradicts what we see in the target — so I need to check whether cse2 actually ran, or whether the extended basic block boundaries (via fallthrough after the bne t,5 block) prevent that fold here.

That still hinges on whether L_in's label uses drop to zero after jump threading deletes the label, which would determine the EBB boundary for cse. Rather than keep reasoning abstractly, it's probably faster to just run the test case directly and inspect the actual diff produced.
