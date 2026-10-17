---
ts: 2026-10-17T11:00:03.977Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm thinking about how combine can split a failed match into two insns both setting the same destination — like splitting a large constant load into high/low parts — which would make n_sets equal 2 if base's definition came from combining a plus with a symbolic constant.

Actually, movsi for MIPS handles large constants as a single "li" macro insn with no split needed, so that path doesn't apply here. Then I reconsider whether memrefs_conflict_p could fail if the store address canonicalizes to something non-constant, like reg+reg, but MIPS has no such addressing mode so that's ruled out too. I'm now looking at whether the load addresses themselves could involve varying bases, or whether the QImode stores versus SImode stores at different offsets could be the actual source of the scheduling conflict.

I'm questioning whether loads actually need a real dependence on the stores, or if the ordering just falls out of scheduler priorities without one — comparing the barrier-free c0 version, where loads get hoisted ahead of stores, against the barrier-containing c27 version where all source orders converge to the same result. I think I've covered this thoroughly, so now I want to check the scorer's f2/h2/w2 outputs and consider one more natural pattern: a variable reused as a call-argument base pointer across multiple blocks, each reassigning it to the same address.

I'll let go of that idea for now and instead run delever_search against the translation unit to compute consistent f2/w2/h2 scores, doing a single non-parallel run via the script to see how long it takes.

I'll score each candidate spelling individually using edit distance against the real TU context, running them one at a time since parallel execution proved unsafe.
