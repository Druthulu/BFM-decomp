---
ts: 2026-11-07T01:19:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rb29RmLJVhH3ctASnCMu
---
Time 18:19:46. Item 2 started 18:09 → ~11 min. Need until ~18:29 (20 min).

I'll continue trying a few more variants for item 2 for ~7 minutes, then do the final checks and report.

More ideas to try (real C):
1. `new_var` as a `void *` and the store cast to s32*.
2. The call arg `(u8 *)s0` where the function's parameter is declared `char *`.
3. Make the second store's value a *pointer*? no.
4. Reorder the two `v0 = ...` assignments.
5. Use `register` on nothing.
6. Store 2's base: `(char *)(s0)` with the call arg `(u8 *)(char *)s0` — same.
7. Try making the first store use new_var and the second s0 (x14 = 1).
8. Try a body where the call arg is `s0` but s0 is assigned *after* the stores? Invalid (the call needs it).
9. Try `s0 = a0; ... ((void (*)(void*))func_8017EE68)(s0);` — x00 = 1.
10. Try removing `new_var` entirely and using s0 for both stores (w02 = 1).
11. Try `char *new_var = (char *)a0;` before s0 = a0 (same value).
12. Try storing through `*(s32 *)(void *)((char *)s0 + 0x204)`.

Let me also try something structural: declare the function's parameter as `char *a0` (the signature's param type is inside the body; callers pass void* — a type change in the definition could affect the codegen? The ABI is the same; the parameter type doesn't change the caller's call). Hmm, but "no signature or decl change outside the body" — the parameter type is part of the signature. Changing `void *a0` to `char *a0` changes the function type. Callers declare it as `void func_8017E98C(void *)` in the TUs; a mismatch in the definition would be a type conflict? In C, the definition's type must match the declaration in the same TU (the header is the definition, and callers just call it). Changing the param type to char* would make the definition's type `void(char*)` while callers call with void* — that's allowed (implicit conversion) but the declaration in the header IS the definition. So the callers see `char *`. That's a signature change → not allowed.

Let me do a few safe variants and call it.

Actually, I realize there might be one more angle: the target's function has the store in the delay slot with base $16. What if we make the second store's base be *the parameter a0* but re-set it before the store? I.e., after the call, `a0 = s0;` then store via a0. Then the store's base is a0 (hard reg!) — but the target's base is $16, not $4. Mismatch.

What if s0's pseudo were allocated to $4 (a0)? Then the store base would be $4 ≠ target $16.

No.

OK — the wall is solid. Let me do a handful of final variants for the clock, then verify and report.

Actually, I've done 70 tries; the 20-min requirement is about time. I'm at 11 min. Let me spend 8 more minutes doing a careful final check of the *best* body (w00) — e.g., verify it's lever-free and that the do-while is fine — plus a few more variants.

Let me run a final batch of 6 variants (quick) and then do the final checks.
