---
ts: 2026-10-22T00:36:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_SW0whfmtgUAq2Q5gKqLG
---
In c1, GCC hoisted 6 constants into t7 (-150), t6 (4), t5 (-139), t4 (3), t3 (-106), t2 (2) and the last two (-57, 1) are materialized in delay slots.

In the target, only 2 are hoisted (t3=-150, t2=4) and the other 4 are in delay slots.

So the target has *less* constant hoisting. The lever (12 asms) somehow reduced it.

The asm's effect on the register allocator: 12 refs to v. v is compared 4 times. Hmm, with the asms, v gets 12+ refs → v's priority is high → v gets a good register (v1) and the constants get worse treatment.

Hmm, but the asms are *dead* (v is not used after them) — do they add refs? The asm's output defines v → the pseudo v has 12 sets → 12 refs (REG_N_REFS). And the "keepalive" effect: the asm forces the value into a reg at that point.

In the target, v is in v1 and the constants -139, -106, -57, 3, 2, 1 are materialized in the delay slots (v0). So the allocator chose to rematerialize them.

How to reproduce in plain C? We need to make GCC *not* hoist the constants into the loop preheader. The hoisting happens in the "loop invariant motion"/"constant propagation into the loop" — hmm, actually the constants are hoisted by the *combine/loop* pass: "loop.c" does "prescan" and moves constants out of loops? Or the register allocator's "loop invariant reg allocation"?

The 6 `li` instructions are before the loop in c1 (at the top: li t7,-150, li t6,4, li t5,-139, li t4,3, li t3,-106, li t2,2). So they were hoisted out of the loop by the loop optimizer (loop.c's "move invariant registers"? or by the RTL "loop invariant motion" in the "loop" pass).

In the target, 2 of them (t3=-150, t2=4) are hoisted and 4 stay in the loop body (materialized in the delay slots).

So the lever reduced the *number* of hoisted invariants. Why? Because the 12 asms create a "barrier" for the loop optimizer? Hmm, the asms are inside the loop body, between the load and the comparisons. The loop invariant motion pass moves constants out of the loop if they're used in the loop and are invariant. The asms don't block that.

Hmm, but maybe: with the asm, the *value* v is redefined 12 times → the load `lh v1,2(a3)` is followed by 12 asm redefinitions of v → the *first* comparison's v is the asm's output (unknown) → hmm.

Wait, actually, maybe the effect is this: the *asm* redefines v, so the *register* holding v must be a real register at that point; the register allocator then can't use the "constant in register" trick...

Honestly, let me try the empirical route: what if I *reduce* the number of hoisted constants by restructuring the chain? For instance, if the *store values* were computed from a common expression (e.g. `idx[i] = 4 - k`), the constants would be different.

Alternatively: what if the comparison chain used a *single* variable for the constants? e.g.:

```
if (v == -150) { idx[i] = 4; }
else if (v == -139) { idx[i] = 3; }
...
```

What if I write it as:
```
s32 k;
if (v == -150) k = 4;
else if (v == -139) k = 3;
else if (v == -106) k = 2;
else if (v == -57) k = 1;
else k = 0;
idx[i] = k;
```
This changes the store structure (a single store at the end) — the target stores in each arm (sh t2,0(a2) / sh v0,0(a2)) → different.

Hmm.

What if the *order* of the comparisons is reversed (e.g. -57 first)? The target's order is -150, -139, -106, -57. The C source's order matches.

What if the constants were written as *hex* or with different expressions? Same.

Hmm, what if the *loop* were structured differently so that the constants aren't loop-invariant? E.g. if the loop body had a *call* that could modify... no, constants are constants.

What if the loop's *trip count* or the idx pointer...

OK, what about the "pressure" hypothesis: the target has 2 constants in regs because the register pressure is higher. What's using the registers in the target? t0 (dst pointer), t1 (i), t2 (4), t3 (-150), a2 (idx), a3 (src), v0, v1. In c1: t0, t1, t2(2), t3(-106), t4(3), t5(-139), t6(4), t7(-150), a2, a3, v0, v1.

In the target, t4-t7 are free! So the target is NOT under pressure — it *chose* to rematerialize.

So the difference is a *choice*, not pressure. The choice: keep the constant in a reg (hoisted out of the loop) vs rematerialize it in the loop body (in the delay slot).

The delay-slot filler (final phase) can rematerialize a constant into a delay slot *if* the reg is free. So the target's shape = "don't hoist the constants; let the delay-slot filler materialize them".

What decides the hoisting? The RTL loop-invariant motion (in loop.c: "cse/loop" or "liveloop"?) — hmm, in GCC 2.7.2 the pass "loop" (loop.c) does "loop invariant register allocation" hmm.

Actually, I bet the hoisting is done by the *reload* pass: when a constant is needed in a loop and the allocator doesn't have a reg for it, it's rematerialized. The decision to *keep* it in a reg is made by the allocator (global.c) based on the "qty" (number of refs) of the constant: a constant used N times in a loop gets a reg if the benefit is high.

So the difference is in the *cost model* of the allocator, influenced by the 12 extra refs to v?! Hmm, that doesn't directly affect the constants.

Hmm, wait. Maybe the difference is the *order* in which things are considered: with the asm, the value v has 13 sets (1 load + 12 asms) → the pseudo v has a *high* REG_N_REFS → the allocator gives it a reg; and the constants' pseudo... hmm.

Honestly, let me try the *empirical* approach: what if I write the comparison chain so the constants are *fewer* or *shared*? E.g.:

```
if (v == -150) idx[i] = 4;
else if (v == -139) idx[i] = 3;
else if (v == -106) idx[i] = 2;
else if (v == -57) idx[i] = 1;
else idx[i] = 0;
```
That's the current source. GCC hoists 6 constants.

What if the store values were *derived*: e.g. `idx[i] = 4;` `3;` `2;` `1;` — the values 4,3,2,1 are the "hoisted" ones in c1 (t6=4, t4=3, t2=2) — three of them, plus the compare constants -150, -139, -106 (three).

In the target: t3=-150, t2=4 → only the FIRST compare and the FIRST store value are hoisted. The rest are materialized in delay slots.

Hmm! So the target's shape = "hoist only the first pair". That's what you'd get if the *later* comparisons' constants were rematerialized because the allocator decided they were "not worth a reg" (used once in the loop body → rematerialize).

In c1, GCC hoisted 6. So the allocator decided differently.

What could change that decision? The *number of refs* of the constants: each constant is used once per loop iteration (1 ref each, but the loop repeats 65 times → the allocator's "qty" counts the loop-weighted refs). The decision to keep a constant in a reg is based on the cost/benefit: a constant used once per iteration in a loop → keeping it in a reg saves 1 instruction per iteration but costs a register.

So the allocator's decision depends on the *register pressure* — and the 12 asms in the target increase the pressure (v is forced into a reg, and each asm needs a reg...). Hmm, but the target's t4-t7 are free!

Hmm, unless the asm's *pseudo* v with 13 sets consumes a reg... no.

Hmm, hmm. Let me look at the target's asm again: is v1 (the loaded value) reused for the comparisons? Yes: `lh v1,2(a3)` then `bne v1,t3`, `bne v1,v0` (v0 = -139 loaded in the delay slot), `bne v1,v0` (v0 = -106), `bne v1,v0` (v0 = -57).

So the compare constants are materialized into v0 (one reg, reused) in the delay slots. And the store values (3, 2, 1) are also in v0 (`li v0,3` etc.).

In c1, the store values 3, 2, 1 → t4, t2, and v0 respectively.

So the difference: the target rematerializes 4 constants in the loop body; c1 keeps 6 in regs.

To flip this, I need the allocator to see that keeping those constants in regs isn't worth it. That happens when the register pressure is higher OR when the constants' benefit is lower.

Hmm, what if the *loop* had more live values? E.g. if the source kept more variables alive across the loop... e.g. the `src` pointer: in the target, `lw a3,12(v0)` is re-loaded each iteration (v0 = D_801937DC) — in both.

Hmm.

What if the *store* to idx[i] used a *different* address computation (more live values)?

Honestly, maybe the lever's effect here is not about the constants but about the *number of loop iterations*... no.

Let me try a different tack: what if the comparison chain is written with the *value* first? e.g. `if (-150 == v)`. Same.

What if the chain is written as a *nested* if (not else-if)? Same.

What if the store values are written as `4 - 0`? Same.

Let me try: what if the *comparison* uses a different form, e.g. `v + 150 == 0`? → `addiu v0,v1,150; beqz` — different instructions.

Hmm, what if the *else* branch (idx[i] = 0) is written as `idx[i] = 0;` (as now) → `sh zero,0(a2)`.

Let me try a couple of quick variants:
c2: `switch (v) { case -150: idx[i] = 4; break; ... }`
c3: the chain with the *values* computed as `4 - 1`? no.

Let me test c2 (switch). If the switch generates the same chain shape (bne with constants), maybe the constants get rematerialized differently.

Let me also consider: maybe the *right* answer for this item is a WALL, and I'm spending too long. Let me timebox: 10 minutes per item from now.

Let me test the switch variant.
