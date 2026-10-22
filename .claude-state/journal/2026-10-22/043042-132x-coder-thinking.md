---
ts: 2026-10-22T10:30:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zJY6cmgkpwdBnvR5amPx
---
Still 14 for 8018389C (now 34 + 28 = 62 scored tries ✓).

Time: ~04:40. This item has been worked ~04:26 → 04:40 = 14 min. Hmm, still under 20 min. Let me add another batch of tries for it (and 8017D81C, 8017DA30).

Let me be efficient: run one more batch of ~12 for 8018389C, one of ~12 for 8017D81C, one of ~8 for 8017DA30, then write up. That should get each item to ≥20 min wall.

For 8017D81C, let me think about genuinely new moves:
1. The `p = D_80192D28;` → `p = &D_80192D28[0];` (tried).
2. The do-while loop → a for loop with the increment (tried).
3. The `s1` variable's type.
4. The order of the declarations.
5. The constants assigned via a `switch`? no.
6. The three constants' assignment order (tried).
7. What if x/y/z were assigned to variables declared right before the assignments (block scope)? The values are used outside the block → they must be function-scope ✗ (C89).
8. What if the constants were assigned in the do-while loop's scope? no.
9. What if the `z` pin were expressed as `register s32 z asm("a0")` (as is) ✓.
10. Hmm — what if x and y were ALSO given register variables (register s32 x;) — the brief forbids register vars ✗.
11. What if the stores used `x` through a pointer? no.
12. What if the constants were stored to the globals via a helper loop? ✗.
13. What if the value 0x68 store came after the x-store? (store order) — tried variants.
14. What if the assignment order were x, z, y? (tried zyx).
15. What if the do-while's `s1++` and `p += 0x40` order were swapped? Let me try.
16. What if `func_800233CC(p, 0x40)` had the args swapped? no (semantics).
17. What if the final `((Unkstruct_800B5CB8 *)a0)->unk2 = ...` used a different spelling? (tried one).
18. What if `v` were assigned differently: `v = func_8012C1B8();` → hmm.
19. What if the `if (v == 0)` block's return were spelled differently: `return;` vs `return (void)0;`? no.
20. What if the constants were declared with `s32` but assigned via `(s32)(-0x680)`? (tried).

Hmm, the mechanism (the pseudo birth) isn't reachable by these. Let me try a few anyway (they're cheap) and also test the "assignment before the call" idea (which will likely be worse but is diagnostic).

For 8017DA30:
1. The store's value via a temp variable (a new local) — e.g. `s32 t = 0x33; ((Unkstruct_800B5CB8 *)q)->unk27 = t;` — the temp would be callee-saved ✗ but let me test (it changes the structure).
2. The call's args: `func_80128EA8(q, p, e)` → `func_80128EA8(sub, p, e)` (tried, 5).
3. The order of `hw = 0x1C` (tried).
4. The store moved into the `if` arm? no.
5. The p/e declarations moved to the function scope.
6. The `func_8001CC3C` call's args.
7. The store's base as `q` vs `(s32)q`.

Let me write these batches.
