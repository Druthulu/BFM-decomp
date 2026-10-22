---
ts: 2026-10-22T09:58:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SZt6qDKRlZca5QNvuDZJ
---
Item 8018483C: best 5 (v9: 115 insns, count matches, but 5 insns differ — the missing "move s0,v0" and shifted branch targets).

The target:
```
313c: lui  s3,%hi(D_801E87B2)
3140: addiu s3,s3,%lo
3144: lui  v0,%hi(D_800B99DC)
3148: addiu v0,v0,%lo
314c: move s0,v0
3150: lui  s2,%hi(D_8018F078)
3154: addiu s2,s2,%lo
3158: lhu  v0,0(s0)
```

So the address &D_800B99DC is materialized into v0 and copied to s0.

Our version (v9?): let me look at the asm difference. The missing "move s0,v0" means ours materializes directly into s0 (lui s0; addiu s0).

Mechanism (from the notes): "gcc-2.7.2 cannot keep it: p = &D_800B99DC makes p a CONST pseudo (reg_equiv = the symbol_ref), cse's forward scan forwards that reg_equiv into every use, and local-alloc materialises the symbol straight into the $s register."

To get the copy, the address must be in a reg (v0) at the copy. In the target, the copy `move s0,v0` is a real copy — meaning the source was a REG, not a constant.

How can a C expression produce "materialize the address into a reg, then copy to s0"? If the source value is computed into a temp reg and then assigned to p:
```c
u16 *pb = &D_800B99DC;   /* pb is a local */
p = pb;                    /* copy */
```
gcc coalesces this (both are the same constant).

Hmm, what if the address is computed in a way that yields a REG: e.g. an expression that isn't a plain constant, like `&D_800B99DC[0]`? Same.

Hmm, what if p is assigned from a *pointer arithmetic* that yields the same address: `p = &D_800B99DC[0];` same.

What if p is assigned via a *cast through an integer*: `p = (u16 *)(s32)&D_800B99DC;`? The notes' v12 tried that → 5 (folded).

What if the value comes from a *volatile* global? no.

Hmm, what if the address is the result of a *conditional*: `p = cond ? &D_800B99DC : &D_800B99DC;` → gcc folds it.

What if p is a *parameter*? no.

Hmm. What if the *use* of p (the load `*p`) forces the copy? Hmm.

Let's think about the target's structure: v0 holds the address (materialized), then `move s0,v0`. Then "lhu v0,0(s0)" — the load uses s0 as the base. So s0 = the pointer (callee-saved, live across calls).

In our version, s0 = the pointer materialized directly.

The difference: the target has an extra v0 materialization + a move. So in the target, the pointer value was in v0 first and then copied to s0.

When does gcc 2.7 produce "lui v0; addiu v0; move s0,v0"? When the value is computed into a pseudo (v0) and then copied into a callee-saved reg (s0) — i.e. when the pseudo is *not* the same as s0. That happens when the source is a non-constant reg: e.g. `p = some_reg;` where some_reg holds the address.

So the original source probably had the address coming from a *variable* that isn't a compile-time constant in gcc's view... OR from a *function call*... OR the original had TWO pointers where one was used before the call.

Hmm! Wait: what about this: maybe the original source had the pointer as a *local* that was ALSO used before the call (e.g. `*p` was read before the loop, then p was used after the call). Then p is live across the call → s0. And the *value* is materialized into a temp reg v0 at the point of the first use, and the copy to s0 happens...

Hmm, in our source:
```c
    i = 0;
    q = &D_801E87B2;
    { u16 *pb = &D_800B99DC; __asm__(...); p = pb; }
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;
    ...
    for (; i < 4; i++) { *q = *p & 0xFFF; ... }
```
p is used before the loop and inside the loop (after calls) → live across calls → s0.

In the target: v0 = address, s0 = copy. So the address was materialized into v0 and copied to s0.

What if the *first* use of p is the load `*p & 1`? Then p would be... hmm.

Hmm, what if the pointer's value is used as a *base* for a load before the copy?

Honestly, the "copy" (move s0,v0) might come from the fact that in the original source, the pointer was assigned in a *different block* or the value was produced by an expression that yields a reg.

Let me think about the launder's effect: `__asm__("" : "=r"(pb) : "0"(pb));` — the asm makes pb a hard register (it must be in a register), so pb's value is materialized into a reg (v0) and then copied to p (s0). Without the asm, gcc sees pb = constant → coalesces.

So we need the value to be in a reg without an asm. Options:
- Make the pointer's value NOT a compile-time constant: e.g. read it from a *global* variable that holds it? Is there such a global? Hmm: is there a global pointer variable pointing to D_800B99DC? Let me check the src for D_800B99DC.

Actually! Interesting thought: maybe in the original source, the pointer came from a *function call* or from a *table*. But the target's materialization is lui/addiu of D_800B99DC — a constant.

So the value IS the constant address, but it was in a reg at the copy. This happens in gcc when the constant is the result of an expression that gcc materializes into a reg: e.g. `p = &D_800B99DC[0] + 0;`? folds.

Hmm, what about when the pseudo p is set by an insn that is NOT a simple constant set — e.g. `(set (reg p) (plus (symbol_ref) (const_int 0)))` → folded to the symbol.

What if p is set from a *volatile read* of the address? no.

Hmm, what if p is set in a way that involves a *cast* that gcc keeps as a reg: e.g. `p = (u16 *)(u32)&D_800B99DC;`? The notes tried a cast → folded.

What about the address being *offset* and then offset back? laundering (not allowed).

Hmm, what if the pointer p is assigned *before* the `if (--D_801E86BC != 0) return;` — i.e. in the preheader, so that the early return doesn't kill it? Hmm! That's interesting: if p is assigned BEFORE the early-return branch, then the value is live across the branch, and maybe gcc materializes it into a reg (v0) before the branch and copies to s0 later.

Look at the target's asm: the "lui v0; addiu v0; move s0,v0" appears AFTER the early-return branch (at 3130 bnez → 32a8). So the materialization is in the "fall-through" block, after the branch.

Hmm, and the target's `move s4,a0` is in the branch delay slot (3134) — the s4 = a0 assignment is in the delay slot of the bnez.

Our version must match that too.

So the target's block: after the early return check:
```
3138: move s1,zero
313c: lui s3; 3140: addiu s3     (q = &D_801E87B2 → s3)
3144: lui v0; 3148: addiu v0     (&D_800B99DC → v0)
314c: move s0,v0                  (p = v0)
3150: lui s2; 3154: addiu s2     (r = &D_8018F078 → s2)
3158: lhu v0,0(s0)
```

So the pointer p is copied from v0 into s0. Why would gcc keep v0? Because the value in v0 is used by something else? Or because the copy is a "reg_equiv" copy that gcc couldn't coalesce?

In gcc, `move s0,v0` is emitted when a pseudo v0 (holding the address) is copied into s0. The pseudo v0 was created because the value was materialized into a reg.

Hmm, why would the address be materialized into a reg at all, rather than directly into s0? Because the *value* was computed as an rtx into a pseudo: e.g. the set insn was `(set (reg p) (symbol_ref))` and p was allocated s0 → lui s0/addiu s0 directly (our version). To get v0 + copy, the set must be `(set (reg v0) (symbol_ref))` followed by `(set (reg s0) (reg v0))` — i.e., two steps. That happens when the source expression is a *variable* (pb) that is itself materialized.

So in the original source there was probably:
```c
u16 *pb = &D_800B99DC;    /* materialized into v0 (a temp) */
p = pb;                    /* copy into s0 (callee-saved) */
```
and gcc did NOT coalesce them because... the temp pb is used ONCE (so gcc would coalesce) — unless the copy was needed because p is callee-saved and pb isn't: gcc's local-alloc would assign pb to v0 and p to s0, emitting the copy — but the "coalescing" (cse's reg_equiv) would have replaced pb's use with the constant.

Hmm! The notes say: "cse's forward scan forwards that reg_equiv into every use" — so cse replaced pb's use with the symbol_ref, making the copy unnecessary.

How to prevent cse from forwarding? If pb had MORE THAN ONE use! E.g. if the address were used twice: e.g.
```c
u16 *pb = &D_800B99DC;
D_801E86C0 = D_800B99D8;   /* hmm */
```
Hmm, the original might have had the address used twice: e.g. `*p` and `p` passed somewhere.

In our def:
```c
    {
        u16 *pb = &D_800B99DC;
        __asm__("" : "=r"(pb) : "0"(pb));
        p = pb;
    }
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;
    D_801E86C0 = D_800B99D8;
    for (...) { *q = *p & 0xFFF; ... *p = *p + c0; ... }
```
p is used 3 times (the load, the store, the read) — but p is the *variable* (not pb). pb is used once.

If pb were used twice, cse couldn't fold it into a single use... Hmm, but cse CAN fold a constant into multiple uses (it would just materialize the constant each time). Hmm, but then the copy into p would remain!

Hmm, actually: the rule (from the moves.md note "single-set const addr r73 folded into lone use") suggests that cse folds a constant address into a LONE use but not into multiple uses (because with multiple uses it must keep the set insn). So if pb had 2+ uses, the set insn `(set (reg pb) (symbol))` would REMAIN, and pb would be allocated a reg (v0), with p = pb being a copy (move s0,v0) ✓✓✓!

So: give pb a second use! E.g.:
```c
    {
        u16 *pb = &D_800B99DC;
        p = pb;
        D_801E86BC = (*pb & 1) + 3;   /* second use of pb */
    }
```
Hmm, but that changes which pointer is used in the loop (*p vs *pb) — the asm must stay identical. If we use pb for the `(*p & 1)` load and p for the loop, the asm might be the same (both are the same address, and the loop's uses of p would keep p in s0).

Hmm, careful: the target's asm: "lhu v0,0(s0)" — the first load uses s0 as the base! So p (=s0) is used for the first load too. So if we made the first load use pb (v0), the asm would be "lhu v0,0(v0)" ✗.

Hmm. So the second use of pb must be somewhere that doesn't change the asm... e.g. a use that gcc can eliminate but that keeps the set insn alive at cse time? Hmm, if the use is eliminated before cse, it doesn't count.

Hmm! What about a use of pb that produces the SAME code as a use of p? E.g., if the first load were `*pb` — no, the base differs.

Alternatively: use pb in a way that gcc reuses the same register... Hmm.

What if the second use of pb is in a *dead* expression but not eliminated before cse? E.g. `if (pb == 0) { }` → gcc folds (pb is a constant address, never 0) → eliminated at expand.

Hmm.

What about making the set of pb NOT a simple constant: e.g.
```c
u16 *pb = &D_800B99DC;
```
Hmm.

Alternatively: make p itself have 2 sets? Hmm.

Let me look at the actual def again and think about which structure the ORIGINAL had. The original probably was:

```c
    i = 0;
    q = &D_801E87B2;
    p = &D_800B99DC;      /* hmm */
    r = &D_8018F078;
```
Hmm, but then the address would be materialized directly into s0 (as in our version).

Hmm, so the original had something like:
```c
    u16 *pb = &D_800B99DC;
    p = pb;
```
Hmm.

Wait — maybe the original was:
```c
    p = &D_800B99DC;
```
but the pointer p was assigned BEFORE the early return:
```c
    p = &D_800B99DC;
    s4 = a0;
    if (--D_801E86BC != 0) return;
    i = 0; q = ...; r = ...;
```
Then p's value is live across the branch → allocated early. Hmm, but the materialization is after the branch in the target.

Hmm, hold on: in the target, the materialization of &D_800B99DC into v0 and the copy to s0 are BOTH after the branch. So the value was computed in the same block.

Let me think about gcc's local-alloc: p is in s0 (callee-saved). The address constant is materialized into s0 directly. For the target, there's an extra v0 + move.

The v0 + move pattern arises when a pseudo holds the address and is copied to s0. When would gcc keep such a copy? If the pseudo has 2+ uses (so it can't be folded) — as I hypothesized.

So in the original source, some variable holding &D_800B99DC had ≥2 uses. E.g.:

```c
    u16 *pb = &D_800B99DC;
    p = pb;
    ...
    *q = *pb & 0xFFF;    /* pb used again */
```
But then the loop's load would use pb (v0) instead of s0 ✗ — the target has "lhu v0,0(s0)"? Let me check the target's loop body asm to see which register the load uses. Let me dump more of the target asm.

Actually the target's first load is "lhu v0,0(s0)" (line 3158). In the loop, the loads are probably "lhu v0,0(s0)" too.

Hmm, so p (s0) is used for the loads. So pb's second use must be something else.

What if the original was:
```c
    D_801E86C0 = D_800B99D8;
```
no.

Hmm, what if the original code passed the pointer to a function? e.g. `func_80049CAC((s32)q - 2, (s32)&D_801E8788)` — no.

Hmm, what if the original had:
```c
    u16 *pb = &D_800B99DC;
    p = pb;
    D_801E86BC = (*pb & 1) + 3;
```
Hmm, that gives "lhu v0,0(v0)"? Hmm, wait: if pb is in v0 and p in s0, then the first load through pb → "lhu v0,0(v0)" ✗ (target has s0).

Hmm, unless the load through pb is CSE'd with... no.

OK, let me think about the v9 variant (115 insns, count matches, 5 differ). What does v9 look like? The notes say: "v9 the same with the address used twice — 5, load base $v0". Hmm, so v9 has the load base v0.

Let me look at the existing variants to understand what was tried. Let me diff v9 vs orig.

Actually, let me try a different approach for this item: what if the copy comes from the *ordering*: the target materializes the address into v0 and copies to s0 — what if the source is the ADDRESS OF A DIFFERENT SYMBOL that happens to be the same? no.

Let me try: does gcc produce "lui v0; addiu v0; move s0,v0" if p is assigned from a *volatile* global? no.

Hmm, what about: p is assigned the address, and p is ALSO used in the *early return* path? e.g. if the code before the branch used p... no, the branch returns.

What if p is assigned before the branch and the branch is AFTER? Then the value would be live across the branch — but the target's materialization is after the branch.

Hmm, what if the source is `p = &D_800B99DC;` but with p being a *pointer that is later modified*? no.

Let me look at this from the "reg_equiv" angle: cse's reg_equiv forwarding happens for a pseudo set once to a constant. If the pseudo is set to the constant AND has 2+ uses, cse keeps the set but the uses may still be forwarded (cse's "is_const" class handling can substitute the constant into uses when the reg is not needed). Hmm.

Actually the note says: "cse's forward scan forwards that reg_equiv into every use" — the reg_equiv mechanism in cse (make_regs_eqv) creates equivalences between regs; the "forward scan" then replaces uses.

Hmm.

OK, let me try the EXPERIMENT: give pb a second use that produces the same asm. Idea: use pb for the LOAD in the loop but arrange for the loop's base to still be s0? No...

Alternative idea: the second use could be the *store* `*p = *p + c0;` — hmm, in the loop, p is used for both the load and the store; if pb were used for the store... the store's base would be v0 ✗.

Hmm, so all uses of the address are through p (s0) in the target.

So the extra v0 + move is NOT from a second use of a pointer variable. It must come from something else.

What if the copy comes from the *order of the materialization*: gcc materializes the constant into a temp reg (v0) and copies it to s0 because s0 is callee-saved and the temp is caller-saved — this happens when the value must be in a caller-saved reg at some point (e.g. used as a call argument!).

AH — that's a thought: if the address were passed to a function as an argument, gcc would materialize it into a caller-saved reg (v0) for the call... but the target has no call with that address.

Hmm, what if the *loop* uses p as a call argument? no.

Hmm, let me look at the target asm once more: 3144 lui v0; 3148 addiu v0; 314c move s0,v0. And 313c lui s3; 3140 addiu s3 (q → s3 directly, no copy!), 3150 lui s2; 3154 addiu s2 (r → s2 directly). So q and r are materialized directly into their callee-saved regs, but p gets the extra copy.

What's different about p? p is USED (dereferenced) — the others are just stored. Hmm, but the dereference is through s0 anyway.

Hmm! What if p's value is used in a *different mode* or with a different type in one place? E.g. `*p` (u16) vs `(u8 *)p`?

Hmm, what if p is used as `*p & 1` and later `*p = *p + c0` — the store through p kills the CSE (the notes mention "the `sh` through p kills the CSE (no TBAA in 2.7.2)").

Let me try: what if the address is used through p with a *cast* somewhere, e.g. `D_801E86BC = (*(u8 *)p & 1) + 3;`? Hmm, the target has "lhu v0,0(s0)" then "andi v0,v0,0x1" — a 16-bit load ✓ so it's a u16 load.

Hmm.

What if the difference is that p is assigned a *different* value later? no.

OK — what about the idea that the copy arises from the *early return*: `if (--D_801E86BC != 0) return;` — the code after the branch. p is assigned after the branch. Hmm.

What if p is assigned BEFORE the branch (in the preheader) and the branch skips it? Then p's value would be live across the branch → p in s0, and the materialization would be before the branch ✗ (the target has it after).

Hmm, what if the materialization is after the branch but p was assigned before? Then the copy would be after the branch: `lui v0; addiu v0` before the branch, `move s0,v0` after? The target has both after.

OK, let me try to think about what makes gcc emit "move s0,v0" instead of materializing directly into s0:
- The value's pseudo is a *different* reg than s0 (a copy).
- The copy survives because the source pseudo's value is needed in a caller-saved reg OR because the source pseudo has multiple uses / is live elsewhere.

In the target, v0 is dead after the move (the next use of v0 is "lhu v0,0(s0)"). So v0 is a temp.

So gcc decided: materialize the constant into v0 (a caller-saved temp), then copy to s0. Why not materialize directly into s0? Because the *pseudo* holding the constant is a caller-saved pseudo (v0) and p (s0) is a copy of it. This happens when the source expression is not a constant in gcc's view — e.g. the source is a *variable* whose value is the constant (a reg_equiv copy).

The notes' x3 tried exactly that (the orig's block with only the asm removed: pb temp + p = pb) → 5 (same). So gcc folded it.

So: to prevent the fold, pb must have ≥2 uses or its set must not be foldable.

Hmm, what if pb is used in a way that's *identical* to p's use but where gcc's CSE keeps both? E.g.:

```c
    {
        u16 *pb = &D_800B99DC;
        p = pb;
        D_801E86C0 = D_800B99D8;      /* unrelated */
    }
```
no.

Hmm, what if the *value* &D_800B99DC is used in a context where the SAME constant appears (e.g. `&D_800B99D8` is a different symbol).

What if pb is used in a *comparison* that gcc keeps? e.g. `if (pb == &D_800B99DC) {}` → folded.

What if pb's second use is in a *store* of the pointer value itself? e.g. `D_something = (s32)pb;` → changes the asm.

Hmm.

What if the second use is in the SAME statement but as a different type: e.g. `D_801E86BC = (*(u8 *)pb & 1) + 3;` → the load would be "lbu v0,0(v0)" ✗.

Hmm.

Let me look at the v9 variant (which had 115 insns — the count matches!) and its diff. Maybe it's closer. Let me look at the variants and their diffs.
