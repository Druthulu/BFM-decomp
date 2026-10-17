---
ts: 2026-10-17T16:56:34.631Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm thinking about removing the pin from c7 but keeping the launders, specifically targeting the second pointer offset. I want to test reusing the same pointer variable for both chains, but CSE would still recognize the base reference, so I should just test c7 without the launders to see the effect.

I'm also recalling how GCC 2.7.2's cse.c handles folding of PLUS expressions involving constants, specifically the logic in fold_rtx that checks whether a register has an equivalent register-plus-constant form via lookup_as_function. Tracing this fold path to see if it explains the register substitution behavior...

Actually I realize since `p += 45` reassigns p in place, the old equivalence tying p to the memory load gets invalidated before cse can fold it, since the plus expression still references the same now-changed register rather than its prior value.

So this means no fold happens for the second addition either — the stale equivalence just gets dropped without producing the right instruction. This matches the target pattern of loading, then immediately adding the offset via addiu. I should try a new test case combining a simple pointer-plus-offset load with a cast pointer arithmetic variant to see if that produces matching code.
