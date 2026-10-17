---
ts: 2026-10-17T16:05:46.980Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I need s1 to have two separate assignment sets rather than being treated as equivalent, so I'm considering making the pointer assignment come from a non-constant expression instead of a direct constant set.

I'm thinking about how update_equiv_regs in old gcc moves a register with exactly one set and one use before its use, which would produce the observed lui/lbu sequence. The challenge is figuring out how to make s1 have genuinely two uses in the RTL without collapsing into the single reference that triggers this rematerialization behavior.

I'm wondering if the move-to-use rule actually requires same basic block, which doesn't match here since calls and branches intervene. I should check the gcc 2.x dump condition more carefully, maybe by inspecting the dumps directly, but first I want to try cheap variations: declaring s1 later, or forcing the reference count to 2 by adding another use of s1 somewhere in the expression.

Then I consider loop depth weighting — since there are no actual loops, a `do{}while(0)` construct might still register as a loop for flow analysis purposes in gcc 2.x, incrementing loop_depth and affecting REG_N_REFS weighting, which could explain why the earlier example used that trick.
