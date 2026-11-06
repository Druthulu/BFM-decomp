---
ts: 2026-10-22T21:03:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CEctal37OKqZ4oHb4a5j
---
Same residual. The sched1 order is invariant to my source permutations.

Time 15:06; item 3 at 16 min. Let me try 3-4 more quickly (to reach 20 min), then finalize.

New angle: the sched1 order depends on the *insn priority*, which depends on the dependency graph and the "ref_count" (number of uses). by and ax each have 1 use (a store). What if I give `by` an extra use *that doesn't add code*: e.g., `prim.y0 = by;` appears twice (the second block also uses by — already). Both blocks use by and ax. by is used in block 1 (y0) and block 2 (y0); ax in block 1 (x1) and block 2 (x0). Same.

What if I swap the store order in the source (x1 before y0)? The target's store order is x0,y0,x1,y1 (struct order) — writing them in a different order would change the asm store order. But sched1 could still reorder... risky.

Actually, the residual shows both by/ax and ay/chain. What if I look at the target's *second* block (the one after `ax = (u16)ax;`)? It matched (no diff there).

Let me try one more idea for ay: make the ay add's result used *only* by the first store (prim.x0) and compute the second block's x1 from a *different* expression: `prim.x1 = ay;` (the updated ay) — it's already. What if the second block uses `prim.x0` (the stored value) instead of ay? `prim.x1 = prim.x0;` → that would load from the struct (a memory op) — different code.

What if ay is not updated in place, and the second block writes `prim.x1 = ay + 0x75;`? Then the add appears twice (cse merges into one? if cse keeps one, the second use extends ay's live range → the add might be scheduled earlier). w5 (no update, second block still `ay`) = 22.

Try: `prim.x0 = ay + 0x75;` in block 1 and `prim.x1 = ay + 0x75;` in block 2 (no ay update). cse would compute ay+0x75 once (a common subexpression) into a register → the target's single addiu s1,s1,117 feeding both stores? In the target, the second block's sh s1,40 uses the same s1. So this could work: the add is a CSE'd value used by two stores → sched1 might place it later (before the first store).

Let me try that (e1).

Also e2: same but with a temp `s16 ay2 = ay + 0x75; prim.x0 = ay2; ... prim.x1 = ay2;`

Let me run e1/e2.
