---
ts: 2026-10-17T17:06:35.356Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm noticing the constant isn't hoisted out of the loop because the OR with a large immediate isn't a valid 16-bit operand, yet CSE still seems to propagate it, while the mask operation does get hoisted. I'm also checking how the code extracts the low byte of blockSize via an AND mask for the comparison.

The trickier issue is that with a pseudo register, combine tracks the union of all possible nonzero bits across every assignment to blockSize, so if blockSize is only ever set to 8 or 16, it deduces the AND mask is redundant and strips it out — whereas the hardware register keeps the mask because its value is opaque. To preserve the mask, I need blockSize's value to be genuinely unknown to combine, perhaps by deriving it from some flag bits in a way that doesn't let combine narrow down its nonzero bit range. I'm going to try reworking the test to operate on the flags value directly instead of blockSize.

Given the difficulty, I'll treat this as two separate obstacles: combine deleting the redundant mask because it can track the small set of values a pseudo is assigned, and the loop-hoist pass pulling the mask constant out. I should just pick the best available score among the attempts rather than keep forcing a fix.
