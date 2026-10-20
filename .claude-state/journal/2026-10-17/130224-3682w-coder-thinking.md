---
ts: 2026-10-17T19:02:24.617Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm checking that reorganizing the delay slot with addu after bnez is safe — since subu overwrites v0 on the fallthrough path anyway, filling that slot doesn't break correctness either way the branch goes.

So the real issue is why target labels get nops instead of filled slots: reorg stops at the label because it's the start of the alternate thread. To block reorg from filling with the arm's insn, I could make the arm's destination register something that's live on the other path, like reusing s1 instead of v0 — but that changes the register used, which doesn't match what's actually needed, so that approach doesn't quite work as-is.

I'm trying different source-level tweaks to see which produces the matching asm: a ternary assignment, a direct subtraction inside each branch, or some other variant of computing t from s1 and s0.
