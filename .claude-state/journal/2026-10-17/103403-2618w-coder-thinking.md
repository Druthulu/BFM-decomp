---
ts: 2026-10-17T16:34:03.546Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm tracing how the a0 register set merges into position after bx/by are scheduled, noting that it has anti-dependencies on earlier instructions 21 and 23, likely from an earlier use of a0 like a struct copy or block move call.

Sched1's tie-breaking by original ordering doesn't quite explain why my version ends up bx, ang, by instead of ang first like the target. I'm wondering if preventing combine from merging these instructions could restore the right ordering, since moving the argument evaluation around a call isn't something sched1 will do across call boundaries.

One idea: if bx or by is a volatile load, combine wouldn't be allowed to move it, which might force ang's pseudo to stay in place and get allocated to a0 as needed — I should check the r1 diff to see if that instruction count lines up.
