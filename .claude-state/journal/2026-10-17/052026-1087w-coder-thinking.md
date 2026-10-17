---
ts: 2026-10-17T11:20:26.243Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm pragmatically narrowing down on when pe can be alive at cse2 — specifically considering whether a use that cse2 can replace but cse1 couldn't might stem from pe's defining set living in a different block in cse1's pass.

I'm also reconsidering the a2 case: maybe cse1 could only follow because LABEL_NUSES was actually 1 at that point, suggesting the jump structure or label merging differed between passes. I want to trace through the jump-handling code in cse_insn around lines 7020-7060 to see how jumps to labels get processed.
