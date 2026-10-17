---
ts: 2026-10-17T11:15:51.598Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: e556b3f3-3497-4364-81b2-e77d256de80a
---
I'm noticing that pointer dereference with an added offset gets matched as MEM_IN_STRUCT, which means my pattern of casting an integer plus an offset to a pointer type needs to account for the NOP_EXPR conversion wrapping that addition.

So the key insight is that marking the pointer type as const makes TREE_READONLY true, which flips on RTX_UNCHANGING_P for that load, even though COMPONENT_REF paths disable this. That means if I spell the second load as reading through a const-qualified pointer, CSE could treat it as immune to invalidation from the intervening flags store, letting it merge with the earlier load while skipping the dependency — and if the final load uses the same const spelling, CSE might unify all three accesses since the unchanging flag persists.

Also, an unchanging read avoids triggering anti-dependence against later stores. I think I should just brute-force this: keep the second load const-qualified while varying whether other operands use the scalar vs pointer-struct spelling, and sweep X's position across all slots, generating roughly a thousand variants to test in the background.
