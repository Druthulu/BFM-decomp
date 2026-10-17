---
ts: 2026-10-17T09:09:28.035Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm realizing the scheduling difference might be due to aliasing: since otz's address was passed to the asm block, gcc may treat it as potentially aliased by pointer stores, forcing the store through p to happen before the otz load is reordered.

In mine the store happened after the otz load, suggesting gcc decided that particular store didn't conflict with otz's address—likely tied to how gcc 2.7.2's alias analysis treats fixed-frame stack addresses versus arbitrary pointer dereferences differently.

Actually, this clicks: gcc 2.7.2's alias logic says a struct-tagged memory reference (MEM_IN_STRUCT_P) can never conflict with a plain scalar reference, so p->rgb being struct-typed let it reorder freely past the scalar otz load. In the target where ordering is preserved, the write must not be struct-typed—so it's probably written as a raw pointer cast like `*(long*)((char*)prim + 4) = ...` rather than a struct field access, since array indexing in 2.7.2 might still trigger the in-struct flag but a cast pointer dereference wouldn't. I want to test that cast-based write to see if it reproduces the target's ordering.
