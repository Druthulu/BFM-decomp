---
ts: 2026-10-17T11:08:02.192Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm tracing through the first branch where a[0]==0, checking if the loop index matches a[5], and following how that index gets used to index into D_8019124C and passed into func_80140D68 along with the object table.

I'm now seriously considering whether an invisible reference is genuinely required here, and probing the idea of self-copies (like `j = j`) that would normally get deleted later by flow optimization but might survive long enough to reduce register pressure. I'm testing whether rewriting the increment or step in an unnatural form could introduce such a self-copy without breaking the loop's correctness, before deciding to step back and reconsider hoisting part of the branch out of the loop instead.

I'm now weighing whether hoisting k*2 out as a loop invariant changes the register count enough to match the target code, but that seems to conflict with where the shift actually appears in the delay slot. I'm also reconsidering whether k and m's roles could be swapped so the live range of k starts earlier at the load, which shifts the ratio enough to favor j over k — but then I need to figure out where the extra move instruction would actually originate from in that scenario.

But wait, m is also used in the comparison against i, so combine can't fold it since m is referenced twice—meaning the zero-extend move stays separate, equivalent to the andi/move pattern on MIPS, giving the same allocation as before. I'm also considering whether k could be assigned right at the point of the comparison itself, but that would make k the direct load target rather than a derived value, which contradicts the register pattern we need.

Now I'm trying to figure out why j ends up with a shorter live range—whether it's due to scheduling order differences between sched1 and sched2, since only sched2 can reorder instructions and ties are broken by LUID stability. Looking at the priorities in the sched2 dump after reload, like the zero-move getting priority 1 and the lui/addiu pair having a dependency that fixes their order anyway, I'm checking the block 0 schedule to see that the highest-priority instruction (the jump) ends up placed last.

I'm now checking whether an insn with lower priority gets placed earlier, and whether "birthing" in sched1 boosts certain constant-loading instructions to a higher max_priority, looking at the dump entries for the 16711680/65535 constant pair to see if their priorities actually differ.

If a load existed in the preheader with latency 2, single-set live-at-end registers (k, t3v, pb, m24, mhi) would get boosted to that max priority and scheduled later, while j — which has two sets and isn't boosted — would naturally end up earlier, which is exactly the mechanism needed to explain why j appears first in sched1's final order despite being later in source.

But actually, the live length is computed on whatever order sched1 produces, so if j ends up first, its live range should be longest and it should still lose the allocation unless it has more references. I keep coming back to needing j to have more refs than k, unless k's live range is actually longer because k is live somewhere j isn't — maybe k is live-in from the outer loop, or live on some path where it's used without being set, making the flow analysis treat it as live across a wider range than its simple def-to-use span suggests.

I'm now wondering if k is being reused for an earlier purpose in the outer loop, like holding one of the call arguments from earlier register moves, which would stretch its live range significantly and change the ratio comparison between j and k.

This matches: k being used as a call argument sets up a hard register preference for a3, so the allocator's find_reg would pick a3 for k first, pushing j to a2 instead. It fits the pattern of reusing a temp variable across a call argument and loop index, though I need to check whether k's lifetime as the argument actually crosses the call itself.

I'm now checking which call site precedes the inner loop — the third call where the fourth argument is 8 — since that's where the register preference assignment would actually take hold, but it overlaps with another variable already using that same literal value.

I'm also weighing other candidates for k's value — maybe it reuses D_801917AC in the first arm's call, or the literal 8 shared across calls — but the loop's size variable still needs its first mention to line up with the path-1 trick.

I should test these hypotheses (K1, K3, and K1+K3) against the allin_k base, where ordering is already correct, and check the actual lines in ak.c to confirm.

The register choices for k (`a3`) and j (`a2`) might stem from copy preferences in global.c's `find_reg` rather than priority—likely because k was reused as the 4th call argument earlier, biasing it toward `a3`. I'll test this theory on the order-correct body.
