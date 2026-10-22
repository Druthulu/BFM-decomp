---
ts: 2026-10-22T09:05:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QZk8kuPoyFsguEEzs0xj
---
The s16 flags lever WORKED partially:
- `move s4,s0` (flag2 in s4) now survives ✓ (the copy is there!)
- But the callee-saved order is SWAPPED: `move s2,a0` (ot in s2!) and `move s1,a1` (w0 in s1) — the target has ot in s1 and w in s2.

Score 24 (down from 29). The remaining diff is the register swap (and the flag3/flag4 copies?).

So now I need to flip the callee-saved order: ot → s1, w → s2.

Currently: ot (a0 → s2) and w0 (a1 → s1). So the compiler gives s1 to w0 (the param) and s2 to ot.

To flip: ot must have a higher allocation priority than w0.

Per the density formula: pri = floor(log2(refs))*refs/live*10000.
- w0: refs ~11, live ~110 → 3*11/110 = 0.3 → 3000
- ot: refs ~6-7, live ~90 → 2*7/90 = 0.155 → 1555

To make ot > w0: either increase ot's refs or shorten w0's live range or shorten ot's live range.

Hmm! Note: the live length. w0's live range spans the whole function (it's used in the final call). ot's live range: from the first assignment (after the first call) to the final use.

Hmm, what if the `w = w0` copy is kept? Then w0 dies early (in the entry block) and `w` is the global. The copy `w = w0` would be coalesced into... hmm. The target has `move s2,a1` — the param copy. With `w = w0` kept as a real copy, gcc would emit `move sX,a1` where sX = w's reg — the same shape ✓. And the priority of w (the copy) would be the same as w0's (same refs, similar live).

Hmm, so that doesn't flip the order.

Let me think about "ot +2 refs > w in greg" (from moves.md). The idea: give ot 2 more refs. In our function, ot is:
1. assigned: ot = func_800D2650(...) [#1]
2. used as an arg: func_80188F14(ot, ...) [#2]
3. assigned: ot = func_80188F14(...) [#3]
4. used: func_800D2650(ot, ...) in the loop [#4]
5. assigned: ot = func_800D2650(...) in the loop [#5]
6. used: func_800D27DC(flag4 != 0, ot, ...) [#6]

So ~6 refs.

To add 2 refs to ot: hmm! What if the *return* value were split from ot? I.e.:
```
s32 *ret = func_800D29F8(flag4, func_800D27DC(flag4 != 0, ot, w0->f4, w0->fC, 0), w0->f8, w0->fE, 0);
return ret;
```
That adds a pseudo `ret` — but `ret` is not ot. Hmm. The moves.md entry says "ot = inner call split from the return (ot +2 refs > w in greg)". Hmm, in func_8017E1D4 the return WAS an ot-like value. Hmm.

In our function, could the final call's result be assigned to `ot`? Semantically the return value is a different pointer, but hmm — what if we assign it to ot and return ot? That changes the semantics (ot would be overwritten) ✗ — but wait, does it? The final return value is `func_800D29F8(...)` — if we did `ot = func_800D29F8(...); return ot;` then ot's value changes, but ot isn't used after that point ✓ — semantically equivalent!! (ot is dead after the final call.)

Hmm! But careful: the order of evaluation: `func_800D29F8(flag4, func_800D27DC(flag4 != 0, ot, w0->f4, w0->fC, 0), w0->f8, w0->fE, 0)` — the inner call uses ot. If we assign the outer result to ot AFTER the inner call is evaluated ✓ (the assignment happens after the whole expression is evaluated). So `ot = func_800D29F8(...); return ot;` is semantically identical ✓✓.

That gives ot +2 refs (the assignment and the return use) → ot's refs 8 → pri = floor(log2(8))=3 → 3*8/live*10000. With live ~90: 3*8/90 = 0.267 → 2667. And w0: 3*11/110 = 0.3 → 3000. Hmm, still w0 > ot. Hmm.

Hmm, the live lengths matter. Let me get the actual numbers from the .greg dump of the current z1 variant. Let me dump it.

Actually, let me think about the *return value* pseudo too: in the target, the return value is in v0 (the call's result) and `return` uses it. If we split it into `ot`, then ot's live range extends to the end ✓ and the return would be `move v0, ot`?? Hmm, that would add a move insn ✗ (the target has `lui v0; addiu v0` then the epilogue).

Hmm! Careful: `return ot;` where ot holds the call's result → the compiler would need `move v0,ot` (a copy) — an extra insn ✗. Unless the copy is coalesced (local-alloc): the call's result pseudo → v0, and ot → the same reg? Hmm, if ot is a global in s1, the return needs a move to v0 ✗.

Hmm! But the moves.md entry says exactly this lever worked for func_8017E1D4: "ot = inner call split from the return (ot +2 refs > w in greg)". Hmm, "the inner call" — maybe it means the inner of two calls.

Hmm, in our case the return is `func_800D29F8(...)` — its result goes to v0 (the return reg) ✓ (the target: `lui v0,0x0; addiu v0,v0,0` = the address of func_80172710?? hmm, that's a different function's constant). Hmm, let me look at the target's ending.

Let me get the tail of the target asm.

Also, I should dump the .greg for z1 to get the exact priorities. Let me do that — it's the most informative next step.
