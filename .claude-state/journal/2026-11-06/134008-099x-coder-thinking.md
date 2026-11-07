---
ts: 2026-11-06T20:40:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LVRk9ROGjRGQRB8f009p
---
vD compile error (probably a declaration-after-statement issue or the replacement put a statement among declarations). vB: ent assigned inside the do-while — still 7 (probably copy-prop still).

Let me check vB's disassembly to see if the copy moved. Actually the score is the same.

Let me think differently. The target's copy is `move a0,s0` at ed4c, right after the RotTransSV call's delay slot. Actually ed48-ed50:
```
ed48 lhu v0,16(sp)   ; v[0]
ed4c move a0,s0      ; ent = a0
ed50 sh v0,6(s0)     ; *(s16*)(a0+6) = v[0]  -- wait, target uses s0 here!
```
Look: `ed50: a6020006 sh v0,6(s0)` — uses s0! And `ed54 lhu v0,18(sp)`, `ed5c sh v0,10(a0)` — uses a0.

Hmm, so the target uses s0 for the first store (unk6 = v[0]) and a0 for the rest. The first store `((Unk*)a0)->unk6 = v[0];` is outside the block (before the `{`), using a0 (the parameter, s0). Then inside the block, `ent` is a0.

OK. So `ent` = a0, and the stores inside the block use a0.

Mine: all stores use s0, and the final call gets `move a0,s0`.

So the target's ent pseudo = a0 (not coalesced with the parameter's s0).

How did the pin do it? `ent = (s32)a0 + zr` where zr is $0 → `addu ent, a0, $0`. The compiler emitted a real add? Or a move. Then ent is a new pseudo, allocated to a0 (since a0 is free after the calls until the final call). The copy `move a0,s0` is emitted at the definition.

Without the pin, ent is copy-propagated to the parameter a0 (in s0).

What real-C construct makes a copy that cse1 won't propagate? A copy through memory, a call, or an opaque asm. Or... a copy whose source is not a plain register (e.g., an expression).

What if we make the expression `(s32)a0` non-trivial in a way that survives: e.g., `ent = (s32)(u32)a0;` — same.

What about `ent = (s32)a0 & -1;`? folds.

Hmm, what about a cast to a different integer size then back: `ent = (s32)(u16)(s32)a0;` — truncates.

What if a0 is `void *` and we do pointer arithmetic: `ent = (s32)((u8 *)a0);` copy.

Hmm, what about `ent = (s32)a0;` where `ent` is `volatile`? stack.

What about using `ent` before its assignment (uninitialized)? Undefined.

What about making `ent` a `static`? no.

OK, different angle: instead of forcing a copy, maybe we can get the target's register allocation by *removing* the ent variable and using a0 directly, but preventing the compiler from using s0? No — a0 is call-clobbered, so gcc must copy it to s0 at entry (it does: move s0,a0 at ecc8). The target uses s0 for the first part and a0 for the second (after RotTransSV).

What if we introduce a *second* variable that aliases a0 but is used only after the RotTransSV call, and the compiler allocates it to a0? That's what ent is. Copy-prop kills it.

What if the second variable is assigned from s0... we can't name s0.

Hmm, what if we assign ent from `a0` through a *function pointer*? no.

What about using the do-while to create a block boundary AND assigning ent inside: vB did that (assignment inside the do-while) — still 7.

Let me look at vB's diff to see if the copy moved. Maybe it partially changed.

Alternatively, maybe the residual is fixable by a different means: the extra `move a0,s0` at the end (mine's 70th insn) — if we could make the final call use a0 already... 

What if the *last* use of a0's value before the final call is a store, and we force a0 to hold it? Hmm.

Let me look at the mine disassembly to understand.

Actually, let me try: what if `ent` is used as the *first* thing after RotTransSV and the compiler runs out of... no.

Let me look at the pin's RTL: `ent = a0 + $0`. gcc emits `(set ent (plus a0 (reg 0)))`. Since reg 0 is a fixed register (zero_reg), the compiler might not fold it because it's a register read. So the addition is real → no copy propagation (it's an add, not a copy).

Real-C equivalent: any non-foldable zero. Hmm... What about `(s32)(a0 - (void *)0)`? Pointer subtraction → folded? `a0 - 0` = a0 (pointer arithmetic with null) — gcc might fold.

What about `ent = (s32)a0 + (s32)(a0 == a0 ? 0 : 1);`? The ternary is folded (a0==a0 is 1).

What about `ent = (s32)a0 + (v[3] & 0);`? v[3] is uninitialized... no.

What about using a *volatile* zero global? adds a load.

Hmm, what about `ent = (s32)a0 + (s32)((u32)a0 >> 31 & 0);`? folded.

What about the value from a function: `ent = (s32)a0 + (func_8012C1B8() & 0);`? That's a second call — no.

OK. What if we approach it from the other side: make the compiler allocate the *parameter's* pseudo to a0 after the calls? The parameter is used across calls, so it's in s0.

Hmm, what if we split the parameter into two variables: `void *a0` used early, and a second variable `b` assigned `a0` after the last early use. Copy-prop again.

Unless the copy is *not* a copy because of a type change that requires an instruction... e.g., `s32 ent = (s32)a0;` where a0 is `void *` — a pointer-to-int cast is free.

What if `ent` is an `s16`? truncation.

Hmm, what if we make `ent` an array index or something that requires an instruction?

What about `s32 ent = (s32)a0;` and then `ent = ent + (v[0] - v[0]);`? v[0]-v[0] = 0 but the compiler may not fold (it's a memory load twice? cse would fold to 0).

Hmm, `v[0] - v[0]` with v[0] loaded once → x - x = 0, folded by cse/fold.

What about a value the compiler can't fold: `v[0] & 0`? folded.

OK, what about this: instead of forcing a copy, can we make the final `func_80188650((void *)ent)` use a0 without a move by having a0 already hold the right value? The last store `*(s16 *)(ent + 0xE) = v2;` is in the call's delay slot (target: `sh a1,14(a0)`). The call needs a0 = ent. If ent is in s0 (mine), the call needs move a0,s0.

What if we make the stores use a0 by... hmm.

What if we pass `a0` (the original parameter) to the final call instead of ent? Then the call's arg would be the parameter (s0) → `move a0,s0` again.

Hmm.

Wait — maybe we can restructure so that the compiler naturally uses a0: e.g., make `ent` the result of a *dereference*: `s32 ent = *(s32 *)&a0;`? That would load from the stack (a0's home) — adds a load.

What about `ent = (s32)(a0);` where a0 is declared as an `s32` parameter? The signature is `void *a0` — we can't change the signature.

Hmm, what about using `ent` in a *store to memory* that forces a distinct pseudo? no.

Let me reconsider: is there another wall tag for this? walls.txt has `sp-stack-switch`, `no-c-spelling`, `hand-asm`, `global-hardreg-reserve`, etc. The pin here is $0 — the zero register! The pin's purpose is to force a real add with the zero register so the copy isn't propagated. That's a "no-c-spelling" style wall: no C expression can force a non-propagated copy of a register.

But wait — maybe a different real-C formulation gets the same bytes: what if we use `ent` as the base for the stores AND the call, but ensure a0 is allocated by making `ent` live across the RotTransSV call? No — ent is defined after it.

What if we define `ent` BEFORE the RotTransSV call? Then ent would be live across the call → it would need a callee-saved reg (s0), not a0. No.

What if ent is defined right after RotTransSV (as now) — a0 is free there.

The copy-prop is the issue.

Hmm, what about using a `union` to pun the pointer: 
```
union { void *p; s32 i; } u;
u.p = a0;
ent = u.i;
```
Stack.

What about `ent = (s32)((char *)a0);`? copy.

What about making ent an `s32` and doing `ent = (s32)a0, ent |= 0;`? folded.

I think this is a WALL: the pin on $0 is needed to make `a0 + 0` a real add. Real-C has no way to spell an opaque zero (other than a load/call).

But before walling, let me check the OTHER residual (the lhu a1 position). Maybe if we fix the copy differently, the schedule follows.

Also, maybe a different structural change (e.g., moving the `ent` definition or the do-while) could make the copy survive. Let me test:
- vF: `s32 ent = (s32)a0;` moved to AFTER the first store (unk6 = v[0]) — i.e., define ent right before the block. Currently ent is defined before `((Unk*)a0)->unk6 = v[0];`? Let me look: 

```
    ((Unkstruct_800B5CB8 *)a0)->unk6 = v[0];
    {
        register s32 zr ...
        s32 ent = (s32)a0 + zr;
```
So ent is defined inside the block, after the unk6 store. In the target, `move a0,s0` is at ed4c, AFTER the `lhu v0,16(sp)` (ed48) and BEFORE `sh v0,6(s0)` (ed50). So the copy is emitted between the load of v[0] and its store — i.e., at the `ent` definition point (sched1 moved it there).

OK.

Let me try more variants for the copy:
- vG: `s32 ent = (s32)a0;` with `ent` used in a `volatile`? no.
- vH: declare `ent` as `register s32 ent;`? That's a register variable without an asm — in gcc, `register` alone is just a hint, not a lever. Hmm, `register s32 ent;` is a plain hint; allowed? It's not a pin (no asm). It doesn't force anything in gcc.
- vI: `s32 ent = (s32)a0; asm` no.

Let me look at the problem from the "what does the target imply" angle: the target was compiled with the pin. The lever-free body scores 7. To reach 0 we need the copy.

Given the wall criteria (≥20 min, ≥30 tries), and this item started at 13:38, I'd need until ~14:00 with 30 tries. That's a lot, but let me first see if there's an easy crack.

Idea: what if we make the copy non-propagatable by making it a *conditional* assignment? e.g.:
```
s32 ent;
if (a0) ent = (s32)a0; else ent = (s32)a0;
```
Adds a branch.

Idea: use the do-while block to define ent in a nested scope and use it outside via a pointer? no.

Idea: make `ent` a global? no.

Idea: what about `s32 ent = (s32)a0;` where the compiler must keep it because `a0` is `void *` and ent is `s32` and there's an aliasing issue? No.

Hmm, what about making `ent` a `u32` and doing `ent = (u32)a0;`? copy.

What if we write `s32 ent = (s32)a0;` and then use `ent` in an expression that the compiler can't see through: e.g., pass ent to a function that returns it? no.

OK — what about the `do{}while(0)` trick: the do-while creates a loop. If `ent = (s32)a0;` is inside the do-while AND the uses are after the do-while, cse might not propagate across the loop boundary. Let me test that: vB put the assignment inside the do-while but the uses of ent in the do-while too. What if we put ONLY the assignment inside the do-while and the uses outside?

```
do { ent = (s32)a0; } while (0);  // !FAKE: do-while
```
Then ent is defined in a loop block and used after. cse1 might still propagate (a single block loop). But the loop creates a NOTE_INSN_LOOP_BEG/END and a jump; cse's copy propagation across the loop... Let me test.

Also: what if the do-while's jump prevents cse1 from seeing the definition as a copy? Worth a try.

Let me create:
vF: `do { ent = (s32)a0; } while (0);  // !FAKE: do-while` before the uses.
vG: ent defined with a *cast through a pointer-to-s32*: `s32 ent = *(s32 *)&a0;` (stack load).

Let me test vF.
