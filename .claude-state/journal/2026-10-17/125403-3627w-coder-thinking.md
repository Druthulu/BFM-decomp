---
ts: 2026-10-17T18:54:03.018Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm tracing how the copy of a0=u gets folded away: the subu writes into u, a0 becomes a tied copy, and the shift output lands in a fresh pseudo, so u ends up multi-set while a0 stays a simple copy — likely the result of a combine or CSE pass merging the sub and shift.

Now I'm looking at whether the CSE swap triggers because the previous instruction sets the same register as the copy source — if the dest register is cheaper/older, it swaps the assignment order. To break this, I want to insert some unrelated statement between the `u = ...` definition and the `a0 = u` copy, like reading a field into a temp before the comparison, since any intervening instruction should prevent the swap from matching its "previous instruction" condition.
