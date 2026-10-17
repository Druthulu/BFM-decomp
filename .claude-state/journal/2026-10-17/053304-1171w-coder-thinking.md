---
ts: 2026-10-17T11:33:04.082Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm thinking about how the compiler's cross-jump optimization merges two identical blocks that both set a pointer and jump to a join point, and considering how to make the two branches differ slightly in their generated code—maybe by varying the expression form or the function call arguments—so the optimizer won't merge them despite producing the same result.

I'm wondering if gcc 2.7's constant-string sharing could explain identical symbols merging, or if the two blocks reference the same data via different offsets that mask to the same relocation. As an alternative, I'm considering restructuring the if-else ladder so the final else block falls through into the join point naturally, avoiding the duplicate "set register then jump" pattern that triggers cross-jumping.

Since cross-jump matching compares code preceding a jump against code preceding the shared label's fallthrough, I should actually look at the target assembly's block layout to figure out which blocks are really being merged here.
