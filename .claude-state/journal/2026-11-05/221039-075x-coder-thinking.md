---
ts: 2026-11-06T05:10:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SzXoakK6rpLTzl0gV20b
---
Item 2 MATCH on all 141 includers! 

Wait — I need to double check that tryinc.py with the absolute D path works and that the header is correct. The failures: 0. 

But hold on: is tryinc.py actually testing the right thing? It prints the includer line and the score. The check greps "score 0 (". Good.

Now, the "lever-free" constraint: win.c must not contain any barrier/asm. Let me check: u3 has no `__asm__`. And the kinds in <dir>/kinds = "barrier". The win.c has no asm. ✓

Also the constraint: "no `register` vars, no `__asm__`; identity-statement launders do NOT count as a crack". The cast `*(s16 *)&D_80078EA6` — is that an "identity address spelling" launder? The brief says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm! `*(s16 *)&D_80078EA6` is arguably an identity address spelling. Hmm.

But here it's not a *launder* to fool the compiler — it's a load through a cast pointer that changes cse's aliasing behavior. Is it an "identity address spelling"? The phrase "identity address spellings" means writing `&x` and casting back to get the same address, used to break cse. Here, `*(s16 *)&D_80078EA6` is exactly the same address as `D_80078EA6`, spelled differently. Hmm, that IS an identity address spelling.

Hmm. But wait: does it count as a "lever"? The constraint says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." And "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack".

So `*(s16 *)&D_80078EA6` might be considered an identity address spelling → not a crack. That's a problem.

Let me reconsider. Is there a different way to force the reload that isn't an identity address spelling?

Hmm. The cast changes the *type* of the lvalue: `*(s16 *)&D_80078EA6` — the load is still HImode at the same address, so it's an identity spelling. The compiler treats it identically at the RTL level (a MEM with the same address and mode). Why did it force the reload then? Because... hmm, maybe cse's equivalence table keys on the MEM expression including its alias set/type. Casting through `s16 *` might change the alias set (TBAA?). In 2.7.2, alias sets exist for C? The `-fstrict-aliasing` flag... Actually gcc 2.7.2 has `alias_sets` in C++ and maybe C. If the cast changes the alias set, cse treats the two loads as different → reload.

Hmm, but is that a legitimate "real C move" or a "launder"? The brief's C0505 catalog: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse". "s16/u8 widths" is a real move! The cast changes the access width/type — that's in the catalog ("s16/u8 widths"). Hmm, `*(s16 *)&D_80078EA6` where D_80078EA6 is already u16 — the load is s16 (signed) instead of u16. That's a *width/sign* change: `(s16)D_80078EA6` loads u16 (zero-extend?) — actually `(s16)D_80078EA6` loads HImode and the comparison is signed. `*(s16 *)&D_80078EA6` loads HImode signed. The generated `lh` is the same.

Is the difference a "real C move"? It's a type-cast on a load. Hmm. The identity-statement launder examples are `w = (w>>16<<16)|x` (a value launder) and "identity address spellings". `*(s16 *)&D_80078EA6` is an identity address spelling of `D_80078EA6`... 

I'm worried. Let me find an alternative that's clearly a real move.

Alternative ways to force the reload:
1. Use a temp variable for the second comparison, but ensure the compiler can't reuse the first load. E.g., a dead-reset (C0414) between them.
2. Make the store potentially alias the load (not possible without reloc changes).

Hmm, what about reordering the source so the two loads are *different expressions*: e.g., the first load via `(s16)D_80078EA6` and the second via `(s32)(s16)D_80078EA6`? cse's MEM is the same.

What about using a u16 vs s16 comparison: `if ((u16)D_80078EA6 >= 0x81)` — same MEM (HImode). cse reuses.

Hmm. What about a *temp* with a different mode: `s16 t2 = D_80078EA6;` — same MEM.

The reload requires killing cse's memory equivalence. The real mechanisms: a store that may alias, or a type-based alias change (the cast).

What about a *volatile* load? Lever.

What about accessing EA6 through the `base` pointer? No.

Hmm, what about this: the target reloads because of the memory clobber. The clobber is a *memory barrier*. A real-C construct that acts as a memory barrier without asm... a function call! If we insert a call, it clobbers memory. But that adds an instruction (jal). The target has no call there. No.

So the cast seems to be the only lever-free-ish way. But is it acceptable?

Let me re-read: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". The concern is that a launder is an *identity* operation that exists only to trick the compiler, producing no real semantic change. `*(s16 *)&D_80078EA6` is an identity address spelling — it reads the same object.

Hmm. But wait — is it? `D_80078EA6` is declared `extern u16 D_80078EA6;`. `*(s16 *)&D_80078EA6` reinterprets it as s16. That's a *type* change (u16 → s16), which is a real C move (the value read has a different type). The bit pattern is the same, but the type is different, and the generated code differs only via cse's alias analysis. In the "s16/u8 widths" catalog, changing widths is a legitimate move.

Hmm, but the *value* semantics: `(s16)D_80078EA6 >= 0x81` vs `*(s16 *)&D_80078EA6 >= 0x81` — identical. So it's a no-op at the source level. That smells like a launder.

Let me look for a cleaner alternative. What about changing the *first* load instead? The reload happens because cse has the first load's value available. If the first load's MEM is different from the second's (e.g., the first is u16 and the second s16), cse won't reuse... but the cast makes them different types. If I change the *first* comparison's type instead: `if ((u16)D_80078EA6 < 0x80)` — D_80078EA6 is already u16, so that's the same. What if I write the first as `(s16)D_80078EA6 < 0x80` (already s16) and the second as `(s32)D_80078EA6 >= 0x81` (u16 → s32, a different mode: HImode vs SImode?). Hmm, `(s32)D_80078EA6` would load HImode then extend; the comparison might use the HImode load with a different mode. Let me test: change the inner comparison to `(s32)D_80078EA6 >= 0x81`. The generated code might be `lh; slti` or `lhu; sltiu`. The target uses `lh v0; slti v0,v0,129` (signed). `(s32)D_80078EA6` where D_80078EA6 is u16 → zero-extend → `lhu` + `sltiu`. Mismatch.

What about making the *second* load a different mode that still generates `lh`? `(s16)(D_80078EA6)` is HImode. No.

Hmm, so the cast trick relies on the alias-set difference, which is a type pun. Is that a launder? Let me check how the project classifies this. Let me grep moves.md/cookbook for "identity address" or "cast" to see prior rulings.

Actually, the brief says "identity-statement launders ... identity address spellings do NOT count as a crack". I think `*(s16 *)&D_80078EA6` is exactly an identity address spelling. I should find a different move.

Hmm, let me think again. What if instead of forcing the reload via a cast, we prevent cse from *having* the first load? E.g., make the first comparison use the value in a way that... no.

Alternative: use a *dead-reset* (C0414) to kill the equivalence. The C0414 technique: a dead store to a register kills a cse equivalence. For memory, a dead store to the same memory would kill it. Can we write a dead store to D_80078EA6 that the compiler keeps? `D_80078EA6 = D_80078EA6;` — a self-store; cse might delete it (it's redundant). If it survives to cse, it would kill the equivalence and force a reload. But it would also emit an instruction (lui at; sh) — unless it's deleted as a no-op later.

Hmm, what about a store to D_80078EA4? That's the store that's already there. cse knows it's a different symbol.

What about a store through a pointer that might alias? Adds instructions.

Hmm, what about the do-while(0) *between* the store and the second load? u2 wraps the inner if — the second load is inside the do-while body, and the store is outside. If cse's EBB is split at the do-while, the load can't be reused. But u2 showed it still reuses (111 ins). So the do-while didn't split cse's EBB here. Why did C0535 work then? Maybe do-while only splits when it contains specific things.

Hmm, maybe cse's EBB splitting happens at `NOTE_INSN_LOOP_BEG`? Let me check cse.c for LOOP_BEG.

Actually, maybe the reuse isn't cse but `loop.c` (invariant hoisting). Let me look: the value is loaded once and reused in two comparisons. This could be cse1 or cse2 or gcse. In 2.7.2 there's no gcse. cse.c handles the EBB.

Let me check if the do-while created a loop note in u2's dump. Let me look at the .cse dump for u2 around the third block. Hmm, time.

Let me take a step back. Maybe I can avoid the reload issue entirely by restructuring the third block differently. The target's third block:
```
lh v0,EA6; slti v0,v0,128; beqz v0,join
lw v0,EA4; addu; sw v0,EA4
lh v0,EA6; slti v0,v0,129; bnez v0,skip
lui v0,0x80; sw v0,EA4
```
The second load happens because of the barrier. Without the barrier, the compiler reuses the first load. Is there a C spelling where the second comparison naturally uses a *fresh* load? If the first comparison's result is stored in a temp that's killed... 

What if the first comparison uses `D_80078EA6` directly and the second uses a *different object* that happens to be the same address? No.

What if we reorder: the target's second load is after the store. If we write the second comparison using a variable loaded *before* the store, we'd get reuse (mine). If we write it as a fresh load, cse still reuses.

Hmm, unless the store is to EA6's neighbor... 

Wait! Actually, what if we make the store a *wider* store that covers EA6? No.

What if the store is to `D_80078EA4` but through a `s16 *`? The target's store is `sw` (s32). No.

OK, what about the cse-killer being a *call* — no.

Let me reconsider the cast: maybe it's fine. The rule says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm, `*(s16 *)&D_80078EA6` is an identity address spelling. I'd be violating the letter of the rule.

Let me look for a genuinely different spelling: what if the second load is `*(u16 *)&D_80078EA6` (same type as declared, no cast)? Then it's identical to the direct load → cse reuses.

What if the second comparison uses `((s16)D_80078EA6) & 0xFFFF`? fold.

What if the first comparison is on a *copy* stored in a local, and the second is a direct load? The first load goes into a temp; the second load is a new MEM expression. cse would still reuse the MEM.

What if we introduce a store to EA6 in between that is dead? E.g.:
```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    D_80078EA6 = D_80078EA6;   // dead self-store
    if ((s16)D_80078EA6 >= 0x81) ...
}
```
The self-store would be deleted by cse as redundant (it stores the same value). Hmm, but if it survives, it kills the equivalence AND emits an insn. Let me test what happens.

Alternatively, a dead store of a *different* value to a variable that's never read: e.g., `D_80078EA4 = D_80078EA4;`? Same issue.

Hmm, C0414's dead-reset: `p1 = 0;` where p1 is a *local* that's dead. It kills a register equivalence. For memory, `D_80078EA6 = 0;`? That changes the global (visible side effect) — not dead.

What about a local pointer? `s16 *q = 0;` between the store and the load — a dead reset that might kill the cse equivalence? No, it's a different object.

Hmm, what about the *register* equivalence: the first load is in v1; the second load reuses v1. If we could make the value in v1 dead/reset... cse's memory equivalence is what matters.

OK, let me look at cse.c's EBB and see if a do-while note splits it. Let me grep cse.c for LOOP_BEG / NOTE.
