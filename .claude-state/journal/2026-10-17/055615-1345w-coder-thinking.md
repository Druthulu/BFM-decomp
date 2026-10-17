---
ts: 2026-10-17T11:56:15.966Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm checking func_80180850 in another function of the same class for similar patterns, noting the pointer register differs (a1 vs a0) and wondering if the hoisted constant load before the branch delay slot hints at a different compiler ordering in the target binary.

My best theory now is that v0 ends up hard-live across block 2 because local-alloc ran before global-alloc, and the pseudo for the return value P was assigned hard register v0 globally even though block 2's own locals never reference v0 directly — making v0 appear "live" through that block purely due to allocation order rather than actual use.

Local-alloc can't span multiple basic blocks for a pseudo, so that avenue seems closed. I'm wondering if the original compilation had a different control-flow shape — maybe a branch-free body, or the join structure differs so that block 2's live registers line up differently than I assumed, letting v0 actually be free there.

For P to end up in v0 globally without a copy at the join, block 2 must not have claimed v0 for its locals in the target. Since local-alloc picks the lowest-numbered free register in MIPS allocation order, something must have kept v0 blocked in block 2 while v1/a0/a1 went to the locals — meaning v0 was likely live through block 2 in the target RTL, probably tied to that pseudo from earlier in the tree.

I'm wondering if the structure is actually `return f(x);` where expand_return could pass the hard return register directly as the target for expand_call, bypassing the usual pseudo-then-copy pattern — that would explain v0 staying live without an explicit move. That also makes me think about whether a comma operator is involved, like `return (P = f(...))`.

Given I've spent about 12 minutes on this class, I'll try a couple more cheap variants — adding `register` to a declaration, reusing a fresh local in place of the K&R parameter, and an ANSI-style prototype version — before settling on 27 as my best answer if none of these pan out.
