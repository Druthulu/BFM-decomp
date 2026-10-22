---
ts: 2026-10-21T23:37:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nSTH64iXyugOL87DjKUD
---
There's a lot here. Relevant cookbook entries:
- §326 DEFEATING ADDRESS-CSE: SPELL TWO READS OF THE SAME HALFWORD DIFFERENTLY AND GCC CANNOT SHARE THE ADDRESS
- §349 RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY ... REPRODUCING A REMATERIALISED `addiu $aN,$sp,K`
- §145(b) pointer-bump: ANY second SET of a pseudo in the address's equivalence chain kills the fold
- §461 LAUNDERING AN INVARIANT CAN BE THE DEFECT
- §471 A LAUNDER'S REAL COST IS AN ALLOCNO

The §145(b) rule: "the pointer-bump `addiu` is saved by cse, not combine: ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is invalidate's reg_tick++".

That's exactly it! The address sp+24 gets CSE'd into a register across the call. If we give the pseudo a second SET (e.g. `p1 = p1;` or `p1 += 0`), the CSE chain is invalidated, and then... hmm, would that cause gcc to rematerialize `addiu a1,sp,24` and `addiu a0,sp+24` separately? Possibly!

Actually, look at moves.md line 4: "launder,pin | func_8017F584 | MATCH — field post-decrement per arm (f--; else f=(rand()&3)+8), spacer dropped (W01)" and line 44: "launder,pin | func_80186368 | MATCH — launder: p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)".

So the technique: self-assign a pointer to stale the CSE.

For our case: p1 = sp10+4 used in call 1 (a1) and sp10+4 used in call 2 (a0). If we make the p1 chain have 2 sets, e.g.:
```
p1 = sp10 + 4;
p1 = p1;      // second set → kills CSE
func_800D20C0(p0, p1, 1);
func_800D23D0(sp10 + 4);
```
Hmm, but `p1 = p1` is an identity statement... The constraint says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm! That's about a *launder* not counting as a crack. A pointer self-assign `p1 = p1` — is that an "identity-statement launder"? Possibly. The listed example `w = (w>>16<<16)|x` is an identity value statement. `p1 = p1` is an identity assignment too.

But moves.md line 44 shows "p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)" — so a self-reassign after a real computation (p += 0x2D) is fine because it's not an identity: p += 0x2D changes the value. But it creates a second SET of the pseudo, staling the cse.

Hmm, in our case, p1 = sp10+4 and we want a second set of p1 that still yields sp+24. Options:
- `p1 = sp10 + 4;` then `p1 = sp10 + 4;` again? Two sets of the same value — that's an identity reassign. Hmm, but gcc's cse: the second assignment to p1 creates a new set of the pseudo p1. Then the use of p1 in the call reads that set. And the use of `sp10+4` in the second call is a different expression (not the pseudo p1). So gcc can't unify p1's value with sp10+4's address? Actually gcc's CSE works on the address expression: p1's value is (plus (symbol_ref sp10) (const 8)) and sp10+4 is the same rtx → cse unifies them into one pseudo → the pseudo gets 2 sets? Hmm.

Let me think about gcc's actual mechanism: `p1 = sp10 + 4;` — after expand/gimplify, this is a local variable assigned a value. The value is a MEM address. Then `func_800D20C0(p0, p1, 1)` uses p1. cse.c would see the assignment and substitute. The "second set" rule: after `p1 = p1` (or `p1 += 0`), the pseudo p1 has a new set, so cse's `invalidate` bumps reg_tick and the old equivalence is dropped.

Actually the key mechanism per §145(b): the address of the local (or the pointer value) is held in a pseudo; a second set of that pseudo invalidates cse's ability to share the address.

Hmm, but here, we want gcc to NOT share the address between the two uses. Actually more precisely we want gcc to not keep sp+24 in s0 across the call.

Alternative from §349: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY to make `n_times_set > 1` — that kills both loop.c's INVARIANT HOIST and the ADDRESS GIV, reproducing a REMATERIALISED `addiu $aN,$sp,K`". That's very close to our need: we want a rematerialised `addiu a0,sp,24`.

So: reassign the base pointer so that its n_times_set > 1. In our case, the base pointer for the address is `sp10` (the array). If we write:
```
u16 *p1 = sp10 + 4;
...
```
Hmm.

Let's think concretely: the pseudo holding the address sp+24 in mine. It has n_times_set = 1? Then it should be rematerializable. Hmm, but gcc assigned it s0 anyway.

Actually, let's reconsider. In mine (a1.c, launder removed), what does gcc do? The diff showed mine[4]=`sw s0,32(sp)`, mine[5]=`addiu s0,sp,24`, mine[6]=`move a1,s0`. So gcc computed sp+24 into s0 early (insn 5) and used it at 6 and at 16 (`move a0,s0`). Register allocation put it in s0 (callee-saved) because it's live across the call.

Why didn't gcc rematerialize? Because the pseudo's "n_times_set" is 1 but it's live across a call, and gcc's reload/regalloc prefers... hmm, actually gcc DOES rematerialize simple constants. But an address (plus (frame_pointer) (const 24)) — in gcc's RTL, a stack slot address is a symbol_ref, and `sp+24` is computed via `plus`. Regalloc can rematerialize it if `REGNO_SET_P`... The relevant pass is reload.c's `reload_remat` / `find_reg_uses`. Hmm.

Anyway, per §349 the trick is to make n_times_set > 1 by reassigning the base pointer, which kills the "address GIV" and gives a rematerialised addiu.

But here the address is of a local ARRAY `sp10` which is address-taken (passed to a function). So sp10 is a stack slot, and `sp10+4` = frame_pointer + 24.

Hmm, the "address GIV" in §349 is about a pointer variable holding a base address. Here, sp10's address is a frame-relative constant.

OK let me just try things empirically. Fast iteration: write candidate, score.

Let me set up a quick workflow. I'll create candidate files in the item dir and score them.

Candidate ideas for 80180D54:
c1: p1 self-reassign before the call:
```
p0 = sp10; p1 = sp10 + 4;
p1 = p1;   // hmm identity
```
Hmm, but is `p1 = p1` an "identity-statement launder"? The rule in the brief: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". I read this as: you can't claim a MATCH by replacing an asm launder with an identity statement. So `p1 = p1` might be disallowed as "not a real move".

Safer: use a real re-assignment with a different spelling that yields the same address, e.g.:
```
p1 = sp10 + 4;
p1 = (u16 *)((u8 *)sp10 + 8);
```
This is a "reassigned pointer" — like §349's "re-assign a base pointer". It's not an identity statement in the "launder" sense; it's a different address spelling. Hmm, "identity address spellings" are explicitly called out as not counting! `p1 = (u16 *)((u8 *)sp10 + 8)` is arguably an "identity address spelling".

Hmm. So I need a move that is a genuine restructuring, not an identity.

Let me reconsider from §349: "RE-ASSIGN A BASE POINTER AT THE END OF THE LOOP BODY to make n_times_set > 1". In that case the reassignment was to a *different* value (the next iteration's base) — a real change.

Here, what if we restructure so that the address is genuinely computed twice from two different bases? E.g., use a struct pointer:

Actually, think about the target semantics again:
- call 1: func_800D20C0(sp10, sp10+4, 1)
- call 2: func_800D23D0(sp10+4)

Both use sp10+4 = sp+24.

What if we restructure the C to have the two pointers be genuinely different variables, e.g.:

```
u16 sp10[6];
u16 *p1 = sp10 + 4;
...
func_800D20C0(sp10, p1, 1);
func_800D23D0(p1);
```
Then p1 is a variable; gcc keeps p1 in a register (or recomputes). Hmm, with p1 a variable that's live across the call, gcc would keep it in s0 too. Unless gcc rematerializes because p1 = sp10+4 is a constant known value.

Hmm.

Alternative: What if the second call's argument uses a DIFFERENT variable that holds the same address, where the variable is assigned from a different source? E.g.

```
u16 *p1 = sp10 + 4;
u16 *p2 = p1;   // p2 = p1 : a copy, not identity-statement laundering
func_800D20C0(sp10, p1, 1);
func_800D23D0(p2);
```
Hmm, `p2 = p1` is a copy. gcc's cse would unify p2's value with p1's value... p1's value is the address; p2 = p1 copies it. Then both uses reference p2/p1 → cse could still unify to one pseudo.

Hmm. What actually made the launder work? `__asm__("" : "=r"(p1) : "0"(p1))`. The output is a NEW pseudo (the asm's output reg), tied to input p1. Then p1 (the asm output) is used in call 1. The asm output pseudo is a hard reg, so it cannot be CSE'd with anything. And after the asm, gcc knows p1's value is in a specific register. Then... the point: the value used for call1's a1 is a hard reg, and the value for call2's a0 is a separate computation of sp10+4 → two separate address computations → two `addiu`.

So to reproduce in real C, we need the call-1 arg to be in a form that gcc cannot CSE with the call-2 arg, yet both are `addiu aN,sp,24`.

What if call 1's second arg is spelled as a *different* pointer type with a different scale? e.g. `p1 = (u16 *)((u8 *)sp10 + 8)` vs call2 `sp10 + 4`. The rtx after simplification: both (plus (symbol_ref) (const 24))? Actually with u8* arithmetic, the const is 8 scaled... In RTL, `p + 8` where p is a pointer of mode P: the address is (plus (symbol_ref sp10) (const 8)) in bytes → for u16* target type the value is (plus (symbol_ref) (const 8)). And `sp10 + 4` (u16*) → (plus (symbol_ref) (const 8)). Identical! Because the address arithmetic is in bytes and the symbol_ref is the same. So they CSE.

Unless the base DECLs differ. Two different objects at the same address? Impossible.

Hmm, what if the base is a *pointer variable* rather than the array? E.g.:
```
u16 sp10[6];
u16 *base = sp10;      // base is a var
func_800D20C0(base, base + 4, 1);
func_800D23D0(base + 4);
```
Then base's value is (symbol_ref sp10) held in a pseudo; base+4 is (plus (pseudo) (const 8)). The two uses of base+4: cse would unify → one pseudo → kept in s0.

Hmm.

OK, different approach: maybe use the "reload-remat constant" (§368) or the "dead-reset CSE-breaker" (§373).

Hmm, §373: "THE DEAD-RESET CSE-BREAKER" — a dead store that resets a pseudo, breaking cse.

Let me read some cookbook entries. Let me find the cookbook files for §326, §349, §461, §471, and §456 (C0505 catalog, which the brief explicitly points to).

The brief says "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". So the catalog is C0505. Let me read that cookbook file, plus §349 and §326.

Let me find the file names.
