---
ts: 2026-10-17T16:34:56.234Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm thinking about whether combine could fail to merge if the two instructions land in different basic blocks, since combine only operates on insns linked within the same block, or if some other combine limitation around usage counts blocks the merge.

I'm reconsidering the width mismatch—ang is s32 but the load is s16, so maybe the sign extension happens in a separate instruction that combine later merges. I'm also wondering if reordering the ang load relative to the sb stores would change aliasing behavior, but that doesn't match the target ordering either, so I need another angle on why the load placement differs.

Looking at scheduling order, my compiled version places bx, ang, by before the jal, while the target wants bx, by, ang instead. I'm tracing through gcc's backward scheduling from the call site to figure out why the priority differs—likely tied to which register (a0 vs s4) is consumed sooner by the call versus later uses.

I'm thinking about how priorities differ: ang's priority traces its latency path to the call, while bx's load has no real dependency on the call itself. But calls act as barriers in gcc 2.x scheduling, since sched_analyze makes the call depend on all prior memory references and pending insns, which could explain why bx ends up ordered differently relative to the call boundary.

If priorities end up roughly equal, it comes down to tie-breaking via RTL position — specifically where the copy into the hard register a0 gets emitted relative to the bx/by loads. That position is set when the call is expanded, which happens after those loads, so I'm wondering whether rearranging the source so bx/by are computed inline rather than as separate statements could shift that ordering.

I'll note this as WALL candidate 4, tagged sched1-birth-boost. One more variant worth trying: declaring ang differently or computing the D_801D4472 read through an offset expression, but checking the address math shows it's off by a constant, so that path doesn't line up — I'll skip it and record WALL 4 with p1 as the current best.
