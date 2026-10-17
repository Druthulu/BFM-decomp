---
ts: 2026-10-17T14:04:45.965Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm tracing how register coalescing merges the shift and copy instructions into the destination register, trying to figure out why the parameter swap produced a different diff in the six-reference case.

Since there's no shift+AND instruction available, these need to stay as separate operations, so I'm recalculating the priority weighting with four references against the span of two calls, checking whether the parameter's priority could be low enough to make this work out, or whether the function's structure differs from what I assumed.

Let me reconsider the register allocation entirely — maybe it's not the shift amount but a separate pseudo like `obj` that's conflicting with `param` for s1, since `obj` is live from the start through a load in the first arm and crosses a call to `func_80149374`. If `obj` took s1, that would conflict with `param` as needed, but then I need to check whether `obj` and the shift value `s1 = 8` could coexist without conflicting, which depends on whether the shift assignment happens after `obj`'s last use.

Tracing further, `ang` loads from `obj` and then `obj` dies right as `ang` is born, meaning they don't conflict and could share the same register — which matches the target code where `obj` actually ends up in s0, not s1. So `obj` can't be the thing occupying s1 after all, meaning I still need to find what else is live across that first call conflicting with `param`, and it circles back to `shift` being the likely occupant of s1.

I'm also reconsidering whether local-alloc (rather than global-alloc) could be deciding this, since local-alloc handles pseudos confined to a single basic block — but `shift` seems to span multiple blocks across the arm branches and the join point, so that doesn't quite fit either. I'm recalling that in the analogous s16 case, local-alloc assigned s0 to a subreg pseudo, which might be a useful parallel for understanding why s1 gets assigned here.

local-alloc's priority ordering by qty_compare likely assigns ang' to s0 and shift' to s1, pushing the global param to s2. I should try combinations with obj kept separate (since ang s16 can't hold a pointer), running v15 base against sh in {s16,s8} crossed with ang in {s16,u16}, plus e/k variants.

I've confirmed a global shift pseudo can't outrank the param, so I'll try narrowing the types for both the angle and the shift to get a block-local SImode copy prioritized by local-alloc.
