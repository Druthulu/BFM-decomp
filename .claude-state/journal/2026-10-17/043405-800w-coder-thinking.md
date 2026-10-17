---
ts: 2026-10-17T10:34:05.226Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
The tail block now mostly matches including the move arm, with arg0 now a2. The remaining mismatch is register allocation: diff gets a0 instead of v0 for the global alloc, and the hoisted load earlier in the function causes the register for e2 to end up as v0 instead of a0.

I think the ordering here depends on live-range length and reference count among the global pseudos (arg0, a, spd, diff, and the D_801ED9D8 temp). In the target, `a` is a0 and diff is v0, while mine swaps them. I want to look at the full disassembly around this block to see exactly how the register classes are being assigned, so I should pull up the detailed per-instruction diff output to inspect lines around the subu computation.
