---
ts: 2026-11-06T20:29:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mUIKbLQfKQSHESUHSrNF
---
Interesting! In nolau, the pre-sched2 RTL order is already: 95 (move a0), 101 (li 7), 103 (sh), 108 (const a1), 110 (call).

So the const was ALREADY placed at the call's arg setup (insn 108), not at the declaration! That's because `r = 0xFFF80000` was NOT emitted as a separate insn at the declaration — the constant is materialized at the call argument setup (expr.c puts the constant into the arg register directly).

Wait, but the source has `s32 r = 0xFFF80000;` — a local variable initialized to a constant. gcc 2.7.2 apparently defers the constant load to the use (it creates a pseudo with a REG_EQUAL note and lets combine emit the constant at the use).

Hmm, but the pin on q (`register s32 q __asm__("$4") = s0;`) emits move a0,s0 at the declaration. And the store `((Unk*)s0)->unk2 = 7` emits li + sh.

So where does the const insn 108 come from? It's placed after the store. That's from expand (the arg setup for the call). So the C source order doesn't matter — the constant is materialized at the call.

But then how did the ORIG get `lui a1` BEFORE the store? Because the launder asm is a *statement* in the source: `r = 0xFFF80000; asm(...); unk2 = 7; call(q, r);` — the asm forces `r` to be materialized into a register at that point (the asm needs r in a register). So the const insn is emitted before the store, at the asm's position.

So the launder's real role: force the constant into a register BEFORE the store. That's a real C problem: we need the constant materialized before the store, but the compiler defers it to the call.

Real C way to force materialization early: use the variable in a way that requires its value before the store, without adding instructions. Options:
- Use r in a comparison/branch before the store? adds a branch.
- Use r as an operand of another computation before the store that is dead? deleted.
- Make r a `register` variable? That's a pin (banned).
- Use `r` as a function argument to another call? no.
- Make r's value feed the store in a value-preserving way? That forces materialization before the store!

Idea: make the store's value depend on r: `unk2 = 7;` → `unk2 = 7 + (r & 0);`? identity-ish but the compiler folds `r & 0` to 0 (constant fold) → no dependency.

We need a real dependency that the compiler can't fold, while keeping the value 7. Since r is a known constant 0xFFF80000, any expression with r is constant-folded. Unless r is not a known constant to the compiler.

So: make r a value the compiler doesn't know at compile time, yet equals 0xFFF80000 at runtime. That's an identity launder in disguise... unless it's a real computation with a runtime-known value. Hmm.

Wait — what about the other arm? r2 = 0x100000. Same issue.

Hmm, what if we make the store's value depend on `v` (the local) instead, and v's value feeds r? Let's see the target: `li v0,7; sh v0,2(s0)` where v0 is the store's value. And `lui a1,0xfff8` before. The target's r is a plain constant.

What if we write the constant as a *computed* expression from a live variable with a mask that yields the exact constant? E.g., `r = (s32)((u32)q | 0xFFF80000);` — q = s0 (a pointer, unknown). `q | 0xFFF80000` ≠ 0xFFF80000 unless q's bits 19-31 are 0. s0 is a RAM pointer (0x80xxxxxx) — high bits 0x80.. so no.

`r = 0xFFF80000 | (q & 0)` identity.

Hmm, is there a value-preserving real computation? The callee probably masks the arg anyway, but we can't assume.

OK, so the launder's function is: materialize the constant at a specific point (before the store) and make it opaque. In plain C, the constant is rematerialized at the call.

What if we store r into a *local variable's address*? no.

What if we make r a `static`/global? That would use memory.

What if we use a `volatile` read? no.

Hmm, what about this: `s32 r = 0xFFF80000; ... ((Unk*)s0)->unk2 = 7; func_8012B178(q, r);` — the compiler materializes the const at the call. What if we write the call as `func_8012B178(q, r);` but reference r earlier in a way that's free: e.g., `if (r) { }`? A constant condition → folded.

What about `q = (s32)((u32)q & 0xFFFFFFFF);`? no.

Hmm, what if the constant's materialization point can be shifted by making the call's arg setup order different: e.g., swap the argument order in the source? `func_8012B178(q, r)` — the target has a0=q, a1=r. If we call `func_8012B178(q, r)` the setup order is a0 then a1. The const is materialized at the arg setup, which happens right before the call, after the store. That's inherent.

Unless the store comes AFTER the call setup? No, the store is a separate statement before the call.

Wait — what if we move the store statement AFTER the call? Target order: move a0, lui a1, li v0,7, jal, sh(delay). The sh is the delay slot, so the store's insn is after the call in the source order? No — in RTL, the delay slot is part of the call's sequence but the store is emitted before the call. Hmm, actually reorg moves the store into the delay slot.

If the store were written after the call in the source, the sh would be after the jal in RTL (not in the delay slot, unless reorg moves it up, which it can't for a jump).

So the target's store must be before the call.

OK, so we need the constant materialized before the store. The only real-C way: make the constant's materialization *required* before the store. That means a use of r before the store.

Idea: use r in a store that's already in the target! Look at the target: after the call, `v = 0x20;` (li v0,32) and then `unk1C = v;`. Not r.

Idea: make `v` and `r` the same variable? no.

Hmm, what about using a *conditional* store with r: no.

What about making the constant part of the *store address* computation? The store is `unk2 = 7` at offset 2. What if we write the address using r: `*(s16 *)((u8 *)s0 + (r & 2)) = 7;` — identity-ish, and r&2 is constant-folded to 0... Actually r = 0xFFF80000, r & 2 = 0, folded. Identity launder.

What about `*(s16 *)((u8 *)s0 + (2 & ~(r | ~r)))`? absurd.

OK. Let me consider: maybe we don't need to reproduce this exact schedule. Maybe another C formulation produces the target bytes by a different route, e.g., by making the store's value not 7 but something that schedules differently... but the target is the target; we must produce exactly those bytes.

Hmm, what if we split the store: `((Unk*)s0)->unk2 = 7;` → `v = 7;` then `((Unk*)s0)->unk2 = v;`? Then v is used and later reassigned to 0x20. The store's value comes from v. But this doesn't involve r.

What if we do: `v = 7; r = r;`? no.

Hmm, what about assigning r to v: `v = r; ...` no.

Let me think about the OTHER direction: maybe the constant CAN be materialized early if it's used by a *memory store* that comes before. E.g., if r were stored somewhere before the call... 

Actually — wait. What about making r's value flow through `v`? In the then-arm: `v = 0x20;` after the call. The target has `li v0,32` after the call (in the j's delay slot at 21cc/21d0: `j 21ec; li v0,32`). Hmm.

New idea: what if we assign the constant to `v` before the call and then use v as the arg? `v = 0xFFF80000; ... call(q, v); v = 0x20;` — v is a local used later (0x20). The compiler would still defer the constant to the call.

Hmm.

Let me look at how the orig (with the launder) RTL looked: insn 100 (const a1), insn 102 (asm), insn 105 (li 7), insn 107 (sh). So the const was materialized at the asm, before the store. Right.

So the asm forces early materialization. Real C alternatives that force materialization:
- An asm (banned).
- A `register` variable (pin, banned).
- A use of the value.

A use that costs nothing: what about using r in the *same store* as a value that gets masked? e.g.:
```
((Unk*)s0)->unk2 = 7;
```
→
```
((Unk*)s0)->unk2 = 7;
```
and use r in the `v` computation? 

Hold on, let me re-read the target's then-arm:
```
move a0,s0        (q = s0)
lui a1,0xfff8     (r)
li v0,7           (store value)
jal func_8012B178
sh v0,2(s0)       (delay: unk2 = 7)
j 21ec
li v0,32          (v = 0x20, delay)
```
So `r` is materialized before the store's li.

In C, the statement order is: q=s0; r=const; unk2=7; call(q,r); v=0x20.

The compiler defers r's const to the call. To force it earlier, we need a use of r between the declaration and the store... 

What if we use r in the store's value in a way that's NOT constant-folded because r is... no, r is a known constant.

WAIT. What if we make the constant not known at compile time by making it depend on a *volatile* read? no.

Alternatively: is the deferral due to `r` being a local with a constant initializer, and gcc's `expand_expr` for a VAR_DECL with a known constant value returns the constant (CONSTANT_P) and materializes at the use? If we prevent the compiler from knowing r's value — e.g., by assigning it via a pointer/union — it would materialize at the assignment.

E.g.:
```
s32 r;
*(s32 *)&r = 0xFFF80000;   // pointer store to a local — forces a stack slot? 
```
Likely a stack slot.

What about a union:
```
union { s32 i; u32 u; } u;
u.u = 0xFFF80000;
r = u.i;
```
Stack traffic.

What about `r = 0xFFF80000;` where r is declared `volatile`? Stack.

Hmm, what if the *constant* is written as a cast of a float? no.

What about making r's value come from the q pin? `r = (s32)((u32)q * 0 + 0xFFF80000);` — constant fold: q*0 = 0 → folds to 0xFFF80000. Identity.

OK, what if the store's value depends on r *without* being folded because r is volatile? no.

Let me reconsider. Maybe there's a different way to get the target's final code: what if we make the CALL's delay slot filled by the store by making the store the last insn before the call? In nolau, the const is last (at the arg setup). If the const were materialized *after* the call (in the delay slot) — that's what happens. If we could make the const materialize *at the call but not in the delay slot*... 

The sequence at the call: the arg setup emits `lui a1` right before the call. reorg then fills the delay slot with it. If the const insn had a REG_DEAD or some dependency preventing its use in the delay slot... The delay slot fill requires the insn to be safe (not a jump, and its result not needed by the branch). A `lui` is safe.

What if the const were materialized into a *callee-saved* reg or a reg used across the call? no.

Hmm, what if the arg order is swapped: `func_8012B178(r, q)`? The signature is (s32 a0, s32 a1) and the target passes q in a0, r in a1. Swapping would change semantics (the callee reads a0 as q).

What if we make the constant the FIRST arg setup and the copy second: the arg setup order follows the argument order: a0 then a1. If the const were a0... no.

OK, maybe the wall for cluster 2 is real. But let's also consider: maybe a `do{}while(0)` around the *call* or around the store changes reorg's behavior.

Actually, let me revisit: reorg fills the delay slot with the insn immediately before the call (the const). If the const insn were followed by a NOTE or something that stops... In plain C, no.

What if we put the call's args through a temp variable that is used twice? e.g., `s32 rr = r; func(q, rr);` — adds a move.

Hmm, what about making the constant an argument of an *expression* at the call: `func_8012B178(q, r + 0)`? folds.

Let me try a few cheap experiments:
1. `s32 r = 0xFFF80000;` → `u32 r = 0xFFF80000u;` (maybe expand doesn't defer unsigned?)
2. Declare `r` as `s32 r;` then `r = 0xFFF80000;` as a statement (not initializer).
3. Put `r = 0xFFF80000;` before the store and also use `r` in the store value via a non-foldable-looking but value-preserving expression... banned.

Actually, maybe the deferral is because gcc's expand for a constant initializer of a local VAR_DECL with a single use does `store_expr` → the constant goes into a pseudo with REG_EQUAL; the actual insn is emitted at the use. If we assign r *conditionally* or in a way that creates a real set, the insn appears.

Test 2 (`r = 0xFFF80000;` as a statement after declaration) — probably same.

Hmm, what about the ORDER: if `r = 0xFFF80000;` is the FIRST statement in the arm, before the q pin? vD tested that (declaration order swap) — but both are initializers. In C, declarations with initializers are expanded in order. The q pin's initializer emits move a0,s0 at that point; r's initializer is deferred. So vD's order const-then-q still defers r.

What if `r = 0xFFF80000;` is an ASSIGNMENT statement (not an initializer)? gcc's expand_assignment to a VAR_DECL with a constant... it might still defer (store_expr into a pseudo with REG_EQUAL). Likely deferred too.

Let me just test a batch quickly:
vG: `s32 r = 0xFFF80000;` → `s32 r;` + statement `r = 0xFFF80000;` placed before the store.
vH: `u32 r = 0xFFF80000u;` (type change) — but the call expects s32; same value.
vI: `s32 r = -0x80000;` (decimal spelling).

Also try for the barrier:
vJ: restructure the if/else to put the xori in a block with a label: e.g., add an `else` branch around the xori? Hmm.

Let me test vG, vH first.
