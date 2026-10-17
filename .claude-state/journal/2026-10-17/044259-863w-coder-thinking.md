---
ts: 2026-10-17T10:42:59.281Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm trying to figure out why constant-sym offsets get folded differently across the two halves—base seems known before the loop in one case but only inside in the other, which changes whether the register holding the symbol value gets reused versus recomputed as a constant.

To make the scheduler lose track of base, its assignment needs to lack a REG_EQUAL note or have more than one set. I'm considering a chain where an intermediate pseudo gets the symbol with a note, then base is assigned from that pseudo without cse noticing, so combine could later merge them and drop the note—then I need to check which cse pass actually produces the plus-base-k form for block 2's store addresses, since it may depend on whether base's set is visible in that extended basic block.
