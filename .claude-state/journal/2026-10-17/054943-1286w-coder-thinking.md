---
ts: 2026-10-17T11:49:43.369Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm noticing that the target version keeps the pointer p in register s1 across the whole function, making it a pseudo that lives across calls, while the free version just recomputes p's address each time it's needed since it's a constant.

This suggests the register allocator in free collapses p into a constant-folded address (lui/addiu then offset load) rather than preserving a live cross-call register, whereas target's version treats p's lifetime as spanning multiple cases including calls, forcing it into a callee-saved register like s1 instead of a0.

Maybe cse hoisted the symbol address into a shared pseudo across the extended basic block, which is why both versions compute it once near the top via lui/addiu. The callee-saved allocation for p might stem from instruction scheduling moving the lui after the jal call, making it look like p is live across the call even if it isn't in the original source ordering.

Other variants to test: declaring p as a local, indexing D_80078E78[0x42] directly without p, or treating p as a plain s32 index.

Pinning the `D_80078E78` base to s1 instead of a0 suggests the original pseudocode held it across a function call. I'll test this by moving `p`'s declaration and assignment earlier.
