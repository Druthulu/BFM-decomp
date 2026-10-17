---
ts: 2026-10-17T13:47:56.873Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm noticing that in g1 the CSE worked because bgez checks m which maps to s1, with t copied into s0 in the delay slot — and the target r also ends up in s0, suggesting the original source likely reused the same variable for t and r, something like t = rand() being reused directly as the target.

If t is reused for both t and r, t's pseudo lives much longer, which could affect whether t1 gets properly allocated versus just being a CSE artifact. I want to test variants i1, i2, and i3 — essentially a1, f1, and h2 but with r replaced by t throughout — to see if this reuse pattern reproduces the target allocation.

g1 confirms the CSE fix works, and since the target reuses `s0` for both the later `r` and `t`, the original source likely merged these into one variable. I'll try folding `r` into `t` next.
