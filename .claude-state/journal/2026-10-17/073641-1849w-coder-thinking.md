---
ts: 2026-10-17T13:36:41.825Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
That explains it—local-alloc/update_equiv_regs relocates the single-set equivalent initialization to right before its first use, so p's birth point already coincides with where it's actually needed. So the lifetime really tracks from first use to last use, and I'm now checking whether p4 (p+4), used in the second statement, has its first use pushed later depending on how it's computed.

Trying different orderings between r79 and p doesn't help since r79's death point is fixed before p's final use in the target code, and I can't extend r79's life without altering emitted instructions. Looking at the priority formula, bumping p's reference count enough to drop its priority below the threshold seems like the real lever — I'm counting how many lhu loads plus the set contribute to its ref count.

Then I wonder if loop_depth weighting matters: since REG_N_REFS gets multiplied by loop_depth, if any of these uses sit inside a loop construct, that could explain unexpected weight differences. A `do {} while(0)` construct emits loop notes in this gcc version even though the condition is constant false, so I'm checking whether those loop notes survive jump optimization or get stripped by the dead-loop deletion pass.

I'm trying to figure out which statements to wrap in a do{}while(0) block to get the right reference counts — testing whether isolating the `p4 = p + 4` line alone pushes p's weighted count just over the threshold, since each statement touches aB9A02 once and most touch p once too.

But I need to account for register-equivalence motion: update_equiv_regs might move p's defining insn before its first use, which affects where its ref count gets tallied during local-alloc, so flow's counting and the final scheduled position could differ. The actual target code places the `addiu` for p4 after the first store, not where it's declared, so I should try both placements — one at the original declaration site and one after the store — to see which matches.

I'll try wrapping the p-only use (p4 = p + 4) in a `do { } while (0)` loop, since flow weighting by loop depth should boost p's priority to 1875, above the 1842 threshold.
