---
ts: 2026-10-17T16:26:49.494Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm thinking about statement ordering and the scheduler's priority in hoisting the load—the long-latency load gets pulled earlier since it's on the critical path to the branch, so I need some barrier to stop that hoisting and preserve the source order.

That leaves the alias question: why does gcc 2.7 let the load from the symbol move above the stores, but not the field load through the register pointer? It seems like 2.7's alias heuristic treats a fixed scalar address as non-conflicting with a struct access through a varying pointer, which matches the classic gcc 2.x MEM_IN_STRUCT_P rule—so a symbol-based load is assumed not to alias a store through a register-based struct pointer, while two register-based accesses are assumed to possibly alias.

I'm wondering if changing the vo stores to raw pointer writes rather than struct-field assignments would drop the struct-access flag and force the load to stay put. Worth testing that rewrite to see if it reproduces the original ordering.
