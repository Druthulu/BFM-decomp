---
ts: 2026-10-17T17:13:50.175Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm tracing register allocation: the call's return value in v0 gets copied to a pseudo and stored, while that pseudo dies at the store, and the frame pointer pseudo is born at the load, creating an anti-dependency that forces the fp load to wait until after the store completes.

Scheduling before allocation likely hoisted the fp load above the store, causing the overlap that pushes fp into v1 instead. To stop that hoisting, I'd need the store and load to appear dependent -- maybe through aliasing if accessed via a pointer of matching type, though that risks altering the generated code's addressing. Since sched1 can't reorder across the call itself, I'm comparing instruction orderings between my output and the target to see where the interleaving diverges.

I'm considering whether splitting the call and table lookup into separate basic blocks via a label would force a scheduling boundary, but a dangling label without a jump would just get optimized away. I should check the table's declared element type and look at surrounding code in the source file for other functions with the same pattern to see if there's a sibling case I can compare against.
