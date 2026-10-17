---
ts: 2026-10-17T11:15:41.882Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm working through how register equivalence classes get picked when making regs equivalent — specifically, the class is ordered by cost and the first REG of matching mode is chosen, but I need to consider the edge case where the source value's class has no REG of the same mode at all.

I'm also checking whether cse2 actually runs with the build's optimization flags — confirming that at -O2, flag_rerun_cse_after_loop gets set, so cse2 should indeed execute after loop optimization.

Now I'm tracing where loop.c places hoisted insns relative to the preheader assignment `k = m`. The key question is whether `k = m` itself sits inside the loop body and gets hoisted too, which would change the ordering and canonicalization I'm trying to work out.

I wonder if it's actually m used in the loop body for both t3v and the arms, with k only playing a role elsewhere, or whether loop.c's combine_movables logic merges k=m with another movable computing the same value—trying to pin down how cse2 would choose its head register under that scenario.

Then I consider whether local-alloc's optimize_reg_copy pass is the real culprit: a copy `k = m` where m stays live until a later use, so the register allocator substitutes k for m in intervening instructions until m's final use, meaning t3v ends up reading k while m dies at the copy point—trying to place this against the actual pass ordering in 2.7.2 (flow, combine, scheduling, local-alloc).

It also checks that src doesn't die before reaching dest and that dest isn't set again before that point—so if k gets set twice due to register reuse, that condition could block the rewrite. I should trace through those bail-out checks carefully.

I see that a plain copy makes k the head of m's class, and local-alloc's `optimize_reg_copy_1` rewrites a later m read into k, with K3's reuse causing k to be set twice. I'll now check that function's bail-out conditions.
