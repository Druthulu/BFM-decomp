---
ts: 2026-11-06T06:21:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RAifdbeT9ksCR3MxpXCS
---
Only 15 minutes in. Good, plenty of time.

Let me think harder with the dump data. Let me check the w2 .combine dump more closely: which pass folded. Actually maybe I can check the .flow dump (after flow, before combine) and .combine (after). The fold happened in combine.

Combine's try_combine needs a LOG_LINK from i2 to i3. LOG_LINKs are built in flow's find_basic_blocks within a block. The LOOP_CONT/LOOP_END notes between them: notes don't split blocks. So 151 and 164 are in the same basic block after jump_optimize merged the do-while loop.

Hmm wait, actually the do-while loop has a back edge (condition 0 → never loops, but the compiler doesn't know? it does: `while (0)` is constant). jump_optimize would delete the branch and merge.

So how did RM1's do-while keep the copy? In that case the copy `tmp = (s16)v; c = tmp;` — the *HImode copy* (s16) escapes cse because it's a SUBREG. So it's not the loop that saved it; it's the HImode copy! The notes say: "s16 tmp; tmp = (s16)v; c = tmp;` [2]: the copy IS `or v1,v0` (HImode copy escapes cse) but combine then rewrites the slti operand to the copy" — and then "MATCH: the copy wrapped in do-while(0) ... keeps the copy in v1 AND leaves the slti on the load's reg v0". So the do-while fixed the *second* half (combine rewriting the slti operand), not the copy itself.

So the HImode copy is what kept the move. Interesting: for our otz, a HImode copy would be `otz = (s16)otz` = sll+sra (2 insns) — but wait, if otz is declared `s16`, the assignment `otz = RotTransPers4(...)` would store into a HImode reg and the arg would need sign extension... 2 insns.

Hmm. But what about the *call result* being assigned to an s16 variable — the RTL is `(set (reg:HI otz) (subreg:HI (reg:SI v0) 0))` — that's a no-op move (move s1,v0)! And then using otz in the call arg requires a sign extension (sll/sra) — 2 insns. Target doesn't have those. Hmm, unless the sign extension folds into the use... func_801823D4(otz, ...) with otz s16 → sign-extend to s32 = 2 insns.

No good.

OK here's another thought — what about making otz's first value used in the **AddPrim** index expression in a way that's dead? no.

Let me look at the problem from the "what does the target RTL look like" angle. Since the target was compiled WITH the asm, its RTL has the asm insn. We need to reproduce that exact instruction sequence in plain C. The asm is a `use` of otz between the two.

Is there a C construct that emits a `use` of a variable with no instruction? Hmm... In GCC, an asm with no operands is the classic. Without asm... 

What about a **function call whose argument is otz but which is elided**? no.

What about `goto`? no.

What about a **label**? no.

What about a `while (0)` with otz in the condition: `while (otz && 0);` — folds.

What about `if (0) otz++;` — folded away.

Hmm, what about the *existing* `if (i != 11)` — no.

OK, radical idea: what if we make otz's first value **live across the second call** by using it after:

```
otz = RotTransPers4(...);
otz = func_801823D4(otz, -0x1A);
```
→
```
s32 t = RotTransPers4(...);
otz = func_801823D4(t, -0x1A);
if (t) { }        /* no */
```
no.

Alternatively, use `t` in a place that already has a value: e.g. the loop's `i` increment? no.

Hmm, what if the first call's result is used as the argument AND stored somewhere free: e.g. `q->xy0 = ...` no.

Let me reconsider: maybe I'm wrong that the target requires the first set. Maybe with a different *loop structure* the otz set materializes naturally. E.g. if otz's value is live across a basic block boundary: `otz = RotTransPers4(...);` at the end of one block and used at the start of the next (e.g. after an if). 

In loop 1, after the RotTransPers4 call there's no conditional. But what if we restructure the loop body so the call result flows through the `if (i != 11)`... no.

Hmm, what about moving the `if (i != 11)` block *after* the RotTransPers4 call? No, the pointers are needed for the call.

What about splitting the loop body with a conditional that already exists? The `if (i != 11)` is before the call.

Idea: move `otz = RotTransPers4(...)` to the top of the loop and the `if (i != 11)` block after? No, the args depend on it.

OK, what about a completely different spelling: assign the call result to otz *inside* the `if (i != 11)` else? no.

Let me try: **`otz` declared as `s32` but the call result assigned via an `if/else` that assigns the same value in both arms**? That creates two blocks and two sets — combine would fold each arm's copy into the arg? The arg is after the join, so the value must be materialized. Hmm! That's interesting:

```
if (i != 11) {
    otz = RotTransPers4(...);
} else {
    otz = RotTransPers4(...);   /* same call */
}
```
No, the call must happen once.

Hmm.

Alternative: what if otz's set and use are separated by the *existing* `if (i != 11)` in a reordering:

```
q = ...;
c = ...;
...
otz = RotTransPers4(v0p, ..., pp, pf);
otz = func_801823D4(otz, -0x1A);
```
The if is before. 

What if we compute v0p..v3p AFTER the call? Impossible.

OK, what if the loop is restructured so that the pointer selection happens at the top and the call in a nested block... adds branches.

Let me try yet another thing: the **`do { } while (0)` empty block placed between the call and the copy** (w1) didn't help because it doesn't create a lasting block. But what about `do { } while (0)` with a *non-constant* condition that's always false at runtime? e.g. `do { } while (i < 0);` — i is a loop counter 0..11, but the compiler can't prove i >= 0? Actually i is initialized to 0 and incremented, so it could prove... maybe not. This creates a real conditional branch → extra insns.

Hmm.

OK let me try the w4 path (both do-whiles) and fix the loop-2 register flip by boosting `i` or by other means. First, let me see w4's alloc table to understand the swap.

Actually — wait. Before that, let me reconsider whether the second do-while is even needed. In w2, the fold happens in combine. What if instead we prevent the *first* call's result from being foldable by making the argument to func_801823D4 not the same pseudo — e.g. pass a *copy* made in the loop block:

```
do {
    otz = RotTransPers4(...);
    t = otz;
} while (0);
otz = func_801823D4(t, -0x1A);
```
RTL: (set otz v0); (set t otz); (set a0 t). Combine folds (set t otz) + (set a0 t) into a0=otz, and then (set otz v0) into a0=v0. Hmm, but cse2 might propagate t→otz anyway.

What if the copy is HImode? `s16 t; t = (s16)otz;` then arg `t` needs sign extension.

Hmm.

What about making the arg copy a *different mode* operation that combine can't undo: e.g. `func_801823D4(otz, -0x1A)` with otz declared `u32`? no.

OK, let me look at what actually distinguishes "move s1,v0" from being folded: it's that otz (r80) is used by more than one insn, OR the LOG_LINK is broken. In the target RTL (with asm), otz is used by the asm and by the copy.

**What if we give otz a use in the `AddPrim` expression that is dead?** e.g. `AddPrim(D_800A651C[...].a + otz * 4, q)` — here otz is the SECOND value (after func_801823D4). The first value is dead after the arg copy.

Hmm hold on — is it? `otz = RotTransPers4(...)` then `otz = func_801823D4(otz, -0x1A)`. The first value's only use is the arg.

What if we could make the first value used in the AddPrim too — but the AddPrim comes after the second call, so otz has been reassigned. Unless... we use a second variable for the second value:

```
s32 o1 = RotTransPers4(...);
otz = func_801823D4(o1, -0x1A);
AddPrim(D_800A651C[...].a + otz * 4, q);
```
o1's only use is the arg.

What if AddPrim used `o1`? It needs the *depth-sorted* value. Semantically wrong but codegen-wise... that would use o1 after the call → o1 must be callee-saved and live across the call. Target: after the second call, `move s1,v0` then sll a0,s1,2. So the value used in AddPrim is in s1 = the *second* value. If we used o1 there, the codegen would differ.

OK, let me try the empirical batch approach: generate 8 variants and score them all at once. Variants:

v1: `do { otz = RotTransPers4(...); } while (0);` + second call plain [=w2, score 3]
v2: w2 + `s32 t = otz;` inside the do-while after the call, arg = t.
v3: w2 + the second call wrapped [w4, 36]
v4: no do-while, but `otz = RotTransPers4(...)` assigned to a temp declared as `u32`? 
v5: `otz = RotTransPers4(...);` then `otz = (s32)(u32)otz;`
v6: swap: `do { otz = RotTransPers4(...); } while (0);` and pass `otz` to func_801823D4 — w2.
v7: `for` loop change? no.

Hmm, what about the "second set" family: make the first otz set a *real* set by an in-place operation: `otz = RotTransPers4(...); otz |= 0;` — tree folds. `otz += 0` folds.

What about `otz = RotTransPers4(...); otz = (otz & -1);` folds.

Hmm what about `otz &= -1`? folds.

OK: what about using a **struct/union member** read to block cse: e.g. `((union { s32 i; } *)&otz)->i`? A memory read → adds lw/sw. no.

Let me test v2 (temp copy in the do-while) and a couple more, plus check w4's table. Actually, let me think about w4's swap more concretely: otz vs i in loop 2. In w4, the second do-while is inside loop 1, so otz's uses there are at depth 2. otz's refs increase → priority up → otz takes s1 (it already had s1 in target!). Wait, w4's diff showed `move s2,v0` vs target `move s1,v0` for the *second* call in loop 2 and `move a0,s2` vs `move a0,s1`. And `slti v0,s1,12` vs `slti v0,s2,12` — so in w4, i=s1 and otz=s2; target i=s2, otz=s1. So w4 made i take s1 and otz s2? That's the opposite of what I'd expect.

Hmm, w4: `move a3,s7 | move a3,s6` at 124 — pf moved to s7. And `addiu s6,s6,8 | --` — an extra instruction! So w4 also broke pf's allocation and added an insn.

Let me get w4's alloc table. Actually, let me not go down this path.

NEW IDEA: What if instead of wrapping the second call, we wrap the **arg copy** by making the second call's first argument an expression that creates a separate statement... 

Hmm, what about using a **conditional operator** that folds but keeps the set? e.g. `func_801823D4(i ? otz : otz, -0x1A)` — both arms same, folds at tree.

What about `func_801823D4(otz, -0x1A)` → `func_801823D4(*(&otz), -0x1A)` — the address-of/deref folds at tree? For a scalar local whose address isn't taken elsewhere, gcc folds `*(&otz)` to `otz`. If the address IS taken (e.g. pp = &p... no, that's p not otz).

What if we take otz's address somewhere? `s32 *po = &otz;` — then `*po` reads memory → extra insns.

OK.

What about making otz's first value used in a **second call argument that folds**: e.g. `func_801823D4(otz, -0x1A)` — what if the second argument were `otz - otz - 0x1A`? Folds.

Alright, let me try the "real 2nd set" family in the direction of moves that cracked similar things:
- G14 line 192: "a real 2nd set (the same expression) inside the true arm".
- The C0414 dead-reset.

What about: `otz = RotTransPers4(...); do { } while (0); otz = func_801823D4(otz, -0x1A);` — w1 = 8, no.

Hmm, w1 scored 8 meaning neither the register nor the move was fixed. So the empty do-while did nothing at all.

What about `do { } while (0)` wrapped around the *arg copy* — impossible.

Hmm, what if we put the func_801823D4 call inside a do-while but ALSO compensate the loop-2 issue by adding a symmetric do-while in loop 2 around the same statement? Let's see: in loop 2, otz = func_801823D4(otz, -0x1A) as well. If both loops have the do-while, the refs are symmetric and maybe the allocations stay. Let's test that! w4 wrapped only loop 1's. Adding the same in loop 2 might rebalance.

Let's try w5: w2 + do-while around BOTH func_801823D4 calls.

Actually wait — in w4, only loop 1's func_801823D4 was wrapped. And in loop 2, the same call is plain. So loop 2's otz refs (depth 1) vs loop 1's (depth 2). Adding the do-while to loop 2 too would make both depth 2. Let's test.

Also w6: no do-while anywhere except... hmm.

Let me generate w5 and score.
