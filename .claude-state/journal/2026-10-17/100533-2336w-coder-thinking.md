---
ts: 2026-10-17T16:05:33.096Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm digging into why register allocation picked a3 instead of v0 for the return pseudo—the pin forces v0, but global alloc seems to prefer a3 since v0 might be tied up with comparison temps in an overlapping live range, whereas on the target those temps use v1, freeing v0 for the return value.

In mine, the comparison temps are local-alloc'd first and claim v0, while ret (being global, since it spans blocks) ends up with a3 instead. I'm wondering if gcc naturally ties the return pseudo to v0 without needing a pin, perhaps because `move v0,zero` appears in the delay slot of the first branch, setting ret=0 right after the first comparison—so I should check how b4's diff handles this to see if the branch structure itself is what drives the natural v0 assignment.
