---
ts: 2026-10-17T16:26:52.370Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I need pb's priority to outrank r170's 1917, so with a live range of 74 I'd need around 8 references—meaning roughly 4 more real uses—or I could shrink the live range to about 41 instructions with only 4 refs. I'm checking where pb is defined and tracing its live range to see what's actually happening between its definition and last use.

Actually the live range of 74 comes from cse substituting pb for pb2's address, so pb stays live through the loop prelude where pb2 gets copied from it—and that copy exists in the target too, so shrinking the live range isn't really an option without breaking that dependency. I'd need genuine extra references, but adding a use inside the loop with loop-depth weighting pushes the live range out too far and the priority math doesn't work out either way.

I'm now looking at making r170 and r169 (j and k) lower priority instead—checking whether k could be eliminated as a separate pseudo (just reusing m directly) to change refs/live numbers, and comparing allocation order: pb in a2, r170 in a3, r169 in t0 matches the target if pb gets allocated first. The core issue keeps coming back to needing 4 more genuine references to pb that would appear in natural C code, which is the piece I still need to find.

Then I start wondering about loop-depth weighting in gcc 2.7's flow.c, where REG_N_REFS gets multiplied by loop depth—so if pb's pre-loop uses were nested inside a `do{}while(0)` wrapper, they'd be weighted higher and effectively counted more times. This matches a trick used successfully in another function (func_80181F4C), where the fake do-while loop was permitted under the brief's rules for marking non-faithful control flow.

I'm wondering whether gcc 2.7 weights loop depth for a do-while(0) construct the way T10's note suggests. Worth testing wrapping the pb set plus the extra statements in a do{}while(0) block, since the original macro might actually have been written that way rather than as a comma expression.
