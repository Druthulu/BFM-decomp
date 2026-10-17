---
ts: 2026-10-17T10:39:25.756Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
Both approaches fold the base to a constant, count 76 -- the problem is CSE substituting the constant instead of keeping the base in a register. I'm wondering if combining p1 with h2's loop-splitting structure would help, and whether the address cost model is treating constant symbol addresses cheaper than register-plus-offset in this gcc version.

Looking at target block 2, only the register holding base+4 stays live, while the other offset accesses aren't folded -- suggesting CSE lost track of the base's equivalence at some point, possibly across a call or label boundary where equivalences get invalidated. This would mean the base value comes from something opaque to both CSE and scheduling, which is consistent with the stores staying in their original order -- like a "la sym" sequence treated as an unknown constant rather than something foldable.

I'm wondering whether the base address is formed through HIGH/LO_SUM relocation pairs rather than a plain la macro expansion, which would depend on whether -msplit-addresses was active, though that's non-default for this era of MIPS GCC. Alternatively, the opaque source might trace back to a do-while(0) macro pattern that obscures the constant's origin from the optimizer.

This also makes me think about loop boundary notes — whether cse_basic_block actually terminates its scan at loop beginning/end markers, which would explain why the compiler fails to propagate the constant across these notes rather than treating them as ordinary statements.

Right, so h2's do-while(0) wrapping likely does emit real LOOP_BEG/LOOP_END notes even for a single-pass loop, and if cse treats those notes as a block boundary, the base-address equivalence established inside the loop body gets invalidated before reaching blocks 2 and 3 — which would explain why cse fails to fold the offset there.

But sched can still work around that if reg_known_value shows n_sets==1 with a REG_EQUAL note, since it would hoist the load anyway and still hit 10 occurrences. So I need both conditions: the do-while structure to keep cse from propagating the base value, and some way to break the single-set/REG_EQUAL property that sched relies on — maybe by introducing a dead parameter copy that survives just long enough to bump n_sets to 2, assuming flow doesn't eliminate it first. I'm testing a variant with a `base` parameter stripped of its local declaration, plus trying the possibility that each of the three blocks is wrapped in its own do-while macro, with the base register set fresh only in the first one's macro expansion.

Let me quickly test p2 to see if it produces the right result.

Both versions still fold `base` into the constant 76 — h2 only keeps it in a register because its do-while(0) ends the cse1 block. I'll now combine h2's structure with a second real assignment to `base` so it stays unknown through sched1 too.
