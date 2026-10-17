---
ts: 2026-10-17T11:39:57.291Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm looking at how this array decl likely produces a type mismatch, and tracing how the base address is computed from the param index, multiplying by 4 to get the offset into the struct array before combining with the upper/lower address parts.

The deeper puzzle is why gcc keeps that base pointer in a saved register across calls rather than folding it as a constant like cse normally would — it seems to depend on how MIPS's cost model weighs symbol references versus register reuse, which might explain the discrepancy between my version and the target.

I'm now suspecting this relates to cse's flow-insensitivity across extended basic blocks: since the target code contains a conditional branch (clamping some value against 1000), the constant equivalence for base may get lost after that join point, while earlier address computations before the branch still get folded. That would explain why some loads use `s2 + offset` directly while others don't.

I'm trying to pin down exactly where this constant gets set and whether it comes from something like a pointer load rather than a simple immediate, so I need to look closely at the first several instructions of the target disassembly.
