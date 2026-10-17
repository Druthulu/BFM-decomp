---
ts: 2026-10-17T16:05:12.678Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I notice the -1 constant is being hoisted out of the loop as invariant, which I want to avoid. I'm considering restructuring the loop condition itself, perhaps comparing against an unsigned pattern or using a different loop form like for(;;) with a break, to stop the compiler from treating it as loop-invariant.

Actually, since gcc 2.x only emits loop notes for natural loops from do/while/for constructs, converting to a goto-based loop with a label would avoid LICM entirely since there'd be no loop notes to trigger it. That's a cleaner approach than fighting the condition shape.
