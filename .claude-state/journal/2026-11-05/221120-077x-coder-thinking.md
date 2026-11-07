---
ts: 2026-11-06T05:11:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FI2Z3ky57WXiwK2MWejz
---
Line 55: "p1 reused as (u16 *)a0, p1[1]++" — a pointer reuse move, accepted as a crack (part of a MATCH). So `(u16 *)` casts on a pointer are used as real moves ("pointer reuse" in the C0505 catalog).

The C0505 catalog includes "pointer reuse" and "s16/u8 widths". A cast-load `*(s16 *)&D_80078EA6` is arguably a "width/type" move.

But the explicit prohibition: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". `*(s16 *)&D_80078EA6` is literally "an identity address spelling" — reading the same object at the same address through a cast.

Hmm. Risky. Let me find a different way.

Alternative: what if the two loads are of *different* objects that are aliases by declaration? E.g., declare `extern u16 D_80078EA6;` and also use a `union`? No decl changes allowed outside the body? "no signature or decl change outside the body" — I can add local declarations.

Hmm, what about a *local* `s16 *q = (s16 *)&D_80078EA6;` and use `*q` for the second load? Same identity address, just through a variable. Also a launder.

Let me think about the *real* target semantics: the target reloads EA6 after the store because the asm memory clobber. In real C, there's no way to express "reload this global" except to make the compiler believe the store might alias it. Type-based alias changes (casts) are the only way.

Hmm, but wait — maybe there IS a legitimate way: make the store to EA4 happen through a *pointer whose type differs* so that the compiler's alias analysis considers the two accesses conflicting. For example, if the store is `*(s32 *)(void *)&D_80078EA4 = ...`? The MEM's alias set would change; then the load of EA6 might conflict. But the store's alias set change would affect the store's MEM. Hmm.

Actually, the *same* concern applies: casting an address is an identity address spelling.

Hmm, hold on. Let me re-read the exact rule: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". I interpret this as: if your ONLY change is a no-op identity statement that tricks the compiler, it doesn't count. Our win.c has a real structural change (do-while block splits + the cast). The cast is one of several moves. But if the cast is the load-bearing trick for the reload, then a reviewer might say the crack rests on an identity address spelling.

Let me try to find a cleaner reload-forcer. Ideas:

1. **Reuse `base`**: what if the second comparison reads EA6 through a different global that the linker places there? No.

2. **A dead store to EA4 that survives**: e.g. `D_80078EA4 = D_80078EA4;` — cse deletes it. What about `D_80078EA4 = D_80078EA4 + 0;`? fold.

3. **A local temp that aliases**: `s16 *q = (s16 *)&D_80078EA4; ... q[1] >= 0x81` — reloc D_80078EA4+2 vs D_80078EA6. Mismatch.

4. **Make the *first* comparison consume the load such that cse can't reuse it**: e.g., if the first comparison is `if ((s16)D_80078EA6 < 0x80)` and the second is `if ((s16)D_80078EA6 >= 0x81)`, cse reuses. What if the first comparison's load is *modified* (e.g., `t = (s16)D_80078EA6; t += 0;`)? The MEM load is the same.

5. **Use different aliasing via a union**: `union { u16 a; s16 b; } *up = ...` — same address, same identity.

6. **Force a second load by making the store "possibly aliasing" via a `char *` store**: The store `D_80078EA4 += a1` through a `char *`? e.g., `*(s32 *)(char *)&D_80078EA4 = ...` — identity cast again, and the reloc stays D_80078EA4. But that's also an identity spelling.

Hmm.

7. **Statement order**: what if the inner `if` is moved to use a *precomputed* value in a way that requires the load? No.

8. **A do-while that actually splits cse's EBB**: if the split worked, the reuse would be impossible without any cast. u2's inner-if do-while didn't split (111 ins). Maybe the do-while needs to be around the *store* (not the if) to split between the store and the load? In q1, the do-while around the store: 111 ins (no reload either). Hmm.

So the do-while doesn't split cse's EBB here. C0535's claim might apply to a different structure (e.g., the EBB split at a loop note in cse1).

Let me check cse.c's EBB end determination. Look for `cse_end_of_basic_block` or the loop in cse_main.
