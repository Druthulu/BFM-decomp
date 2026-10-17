---
ts: 2026-10-17T10:53:49.955Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
Any instruction that sets a single register whose value is still needed gets boosted and scheduled as late as possible, right before its use — so the abs instruction gets placed right before the sh's. Since X is a store, it's never boosted, so it gets deferred and placed early (right after v) unless some dependent instruction forces it later.

I'm checking whether a later load of the same memory could force X's placement, but CSE would eliminate such a load by substituting v directly. I'm also checking output/anti dependencies with later stores to fixed scalars — different symbol_refs are treated as non-conflicting in memrefs_conflict_p, so those don't create a dependency either, unless the competing store is to a scalar type that does conflict, which creates an output dependency. Even then, since abs is boosted and becomes ready right after the sh's, it wins the scheduling slot, forcing X to be placed before abs instead.

I'm wondering if abs could lose its boost if reg_n_sets isn't exactly 1 — perhaps because flow deletes a dead earlier assignment, affecting how reg_n_sets gets counted, though it's unclear whether flow's deletion happens before or after that count. I also consider whether d might be reassigned or folded in a way that changes this, but nothing concrete comes to mind yet.

Then I'm testing the case where d is set in an earlier block too, making it global — this maps to the m7 scenario where abs isn't boosted due to having three sets, and scheduling puts X after abs, keeping v alive longer and matching the e2 local v0 pattern. I'm trying to combine frameworks: keeping abs as a single-set local temp while making d global but unboosted, since the boost specifically triggers when reg_n_sets[d] equals 1 — maybe there's a structural trick, like wrapping the abs computation in a PARALLEL, that breaks the boost condition.

Now I'm considering whether the destination being a SUBREG matters, since birthing_insn_p requires a plain REG destination — if d is a narrower type like s16 computed via abs on a wider SI temp, the resulting move might still get boosted on the temp rather than d. I'm also wondering about cases where d itself is accessed through a subreg of a larger register, which could change whether the boost condition applies.

I'm also exploring whether making birthing_insn_p false by checking liveness after the set would work, or whether I could delay abs's readiness so it doesn't win the tie against X — since both abs and X become ready at the same scheduling point due to their shared dependency, I'd need to give X a dependent that forces it to be ready later, breaking the tie in X's favor.

I should stop theorizing and focus on the m7 result, which looks promising since X naturally ends up after abs. I still need e2 a0, but making e2 global seems to break scheduling by losing its boost when reused across blocks — unless the tail block splits after e2's load, perhaps via the abs introducing control flow.

Let me think about non-folding abs implementations that still compile to the same branch sequence: things like `d = -(d)`, `d = (0 - d)`, or `d = d * -1` all get recognized as negation at expand time, but a nor+addiu sequence might only get folded into neg later if combine manages to simplify `(plus (not d) 1)` into `(neg d)`.

I'm now wondering whether this simplification actually exists in the compiler version I'm looking at, and whether the fold I'm chasing is actually happening in jump.c at all -- so I should grep jump.c for references to "abs" to confirm.
