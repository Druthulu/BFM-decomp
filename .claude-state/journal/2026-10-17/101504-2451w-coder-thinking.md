---
ts: 2026-10-17T16:15:04.468Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm puzzling over why the loaded u16 value ends up in v1 instead of v0 — checking whether the return-value register allocation conflicts with the li v0,1 placed in the delay slot after sh, even though the node's value should already be dead by that point.

Maybe the explanation is that the return value is actually a shared pseudo across multiple return statements, assigned by global-alloc rather than local-alloc, which is why it preferentially claims v0 while the locally-allocated node gets pushed to v1. That suggests a fix: make the node's pseudo live across blocks, perhaps by reusing it as a function-wide variable, so global-alloc handles it the same way.
