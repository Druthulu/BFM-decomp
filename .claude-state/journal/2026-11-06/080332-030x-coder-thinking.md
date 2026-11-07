---
ts: 2026-11-06T15:03:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9oOCHVtr8erkT76QGvz4
---
Exactly one insn differs: target `sll a0,s0,0xa` at 1f68 vs mine `move a0,zero` at 1f64 (and target's at 1f68 is one slot later because target also has the sll there; wait target has sll at 1f68 and mine has move at 1f64 then sll at ... hmm mine has `move a0,zero` at 1f64 and `sw ra` at 1f68; target has `sw ra` at 1f64 and `sll a0,s0,0xa` at 1f68). So the ordering also shifts by one — but same count. Target: sw ra at 1f64, sll at 1f68. Mine: move a0,zero at 1f64, sw ra at 1f68, sll(v0) at 1f6c.

So in target the pre-loop shift is scheduled after the prologue `sw ra`; in mine move a0,zero is before `sw ra`. Interesting.

To get `sll a0,s0,0xa` instead of `move a0,zero`: need s0's zero-ness to be unknown to the pass that folds. The launder achieves this.

Plain C ideas:
1. Give s0 a second, non-constant set that dominates but is provably 0 at runtime only through arithmetic gcc won't fold. E.g. `s0 = 0; s0 = s0 & 0;`? combine folds. `s0 = s0 * 0`? folds. `s0 = (s0 + 1) - 1`? folds. gcc 2.7.2 folds all.

2. Read s0 from a memory location that is known-zero? No.

3. Use a loop structure where the pre-loop value isn't a literal 0 but the previous iteration's value... 

Idea: restructure to a while loop with the counter starting at -1 and incrementing at the top:
```
s0 = -1;
do {
    s0 = s0 + 1;
    a0 = s0 << 10;
    ...
} while (s0 < 4);
```
Hmm but target's order is sll a0,s0,0xa then sll v0,s0,1 then lh then addiu s0,s0,1. So s0 increment is after. The pre-loop sll uses s0=0.

Alternative: hoist differently — what if we make the first sll come from the loop-bottom statement, by writing the loop so that the a0 assignment happens at the loop head before use but gcc rotates? Hmm.

Wait, think about what the launder does *in the target's actual codegen*: it's a use+def of s0 at the point right after `s2 = D_8019B538`. That asm acts as a barrier: s0's value after it is "unknown" to gcc. So `a0 = s0 << 10` becomes a real shift. Then the loop uses s0 = 0... but wait, if s0 is unknown after the asm, then the loop's `v0 = s0 << 1` would also be unknown, and `s0 = s0 + 1`, and the loop condition `s0 < 4` — gcc doesn't know initial value. But the code still works because the asm is tied (identity). Fine.

So to replicate in plain C: need s0 to be an unknown value that happens to be 0. Could be `s0 = s0 & 0;`? No that's known.

What about making s0 be assigned from a volatile or a global? Adding a global read is a new lever probably (and changes instructions).

What about `s0 = (s32)(u8)some_expr`? Still known.

Hmm — maybe we don't need s0 unknown. We need gcc to not fold `s0 << 10` to 0. What if the shift is expressed through a pointer/int union? E.g., `a0 = *(s32*)&s0 << 10`? gcc may not track memory; but s0 is a local in a register, so `*(s32*)&s0` forces it to memory (address taken) — changes everything.

What if a0 = s0 << 10 where s0 is a `u16`? Known zero still.

Alternative: maybe target can be matched by making `a0 = 0` at that point be *dead* and instead the sll be the loop-bottom one moved? No — target clearly has two sll (1f68 and 1fa8).

Hold on: what if we remove the pre-loop `a0 = s0 << 10;` entirely and instead compute a0 inside the loop from a variable that starts at 0? E.g.:

```
s0 = 0;
do {
   v0 = s0 << 1;
   ...
   a1 = *(u16*)v0;
   a1 = a1 + (s0 << 10);
   ...
} while (s0<4);
```
But target computes a0 before the loop and reuses across iterations (a0 = previous s0<<10). Actually the loop-bottom `a0 = s0<<10` computes next iteration's value. So a0 is loop-carried. If instead we compute `a1 = a1 + (s0 << 10)` in the loop, gcc would emit sll at the use point — likely different scheduling.

Hmm, but actually that's a promising restructure: the target's a0 is just `s0_prev << 10` where s0_prev is the value at the top. Equivalent to `a1 = a1 + (s0 << 10)` computed at the top before the increment. But scheduling: target has sll a0,s0,0xa at the very top of the loop (1f68), before sll v0,s0,1. If we write it as a use inside the loop, the compiler may schedule it similarly. And the first iteration (s0=0) — it would be `sll a0,s0,0xa` naturally, no folding because it's inside the loop! That could crack it.

Let's restructure:
```c
void func_8017DE00(a0p)
s32 a0p;
{
    s32 s0;
    s32 s1;
    s32 s2;
    s32 v0;
    s32 v1;
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    s32 a2;

    s1 = a0p;
    s0 = 0;
    s2 = (s32)D_8019B538;
    do {
        a0 = s0 << 10;
        v0 = s0 << 1;
        v1 = ((Unkstruct_800B5CB8 *)s1)->unk70;
        s0 = s0 + 1;
        v1 = (v1 << 3) + s2;
        v0 = v0 + v1;
        a1 = *(u16 *)v0;
        a2 = s1;
        a1 = a1 + a0;
        a1 = a1 << 16;
        a0 = 0x199;
        func_8012C658(a0, a1 >> 16, a2);
    } while (s0 < 4);
}
```
Now a0 computed at loop top. But then the loop-bottom a0 = s0<<10 is gone; instead the loop-top a0 = s0<<10. Target's 1fa8 (delay slot) is the loop-bottom sll of the *next* iteration value... hmm actually if the statement is at loop top, the delay-slot fill would steal the loop-top sll from the next iteration into the bnez delay slot! That's exactly what target has at 1fa8: sll a0,s0,0xa in the bnez delay slot. Wait no: 1fa8 is in the delay slot of bnez at 1fa4, and the branch target is 1f6c (loop top, sll v0). The delay slot executes before jumping — it computes a0 for the next iteration. That is the loop-bottom statement `a0 = s0 << 10;` after the increment. But it could equally be the loop-top statement of the next iteration hoisted into the delay slot by reorg (stealing from the branch target!). reorg can steal an instruction from the branch target only if it's safe (target insn not needed on fall-through, and the delay slot executes on both paths). Since the loop is do-while with a single exit at bottom, the branch target insn sll a0,s0,0xa could be moved to the delay slot if it's the first insn at the target. Hmm, but then the fall-through path would execute it too — the fall-through path exits the loop, and a0 is dead there. So reorg CAN steal it. So the loop-top placement could produce the identical code!

But careful: after stealing, at the loop top 1f6c starts with sll v0 (the second statement). The first insn 1f68 is the pre-loop a0 = s0<<10 — wait if a0 is computed at loop top, there's no pre-loop statement. Then 1f68 would be... target has sll a0,s0,0xa at 1f68 (pre-loop) plus at 1fa8. So target DOES have a pre-loop statement (the loop-carried init) AND the loop-bottom statement. With loop-top placement there'd be only one static sll (at loop top, possibly stolen to delay slot), so 1f68 would not exist → count 32. Not matching.

So the target's structure is exactly: pre-loop a0 = s0<<10, loop-bottom a0 = s0<<10. We need the pre-loop one to be sll.

So we need gcc to not const-fold s0 at that point. Hmm.

Idea: initialize s0 with a value that gcc knows is 0 but doesn't fold through? For instance `s0 = 0; s0 = s0 + s0;`? flow/combine folds.

gcc 2.7.2's constant folding: `combine` folds `(0 << 10)`? Actually the folding of `s0 << 10` where s0 has reg_known_value 0 happens in combine's `try_combine`/`simplify_shift_const`? Or in `cse` via `simplify_rtx`? The launder defeated it, so it's a pass that respects asm.

What about `s0` being set to 0 through a `for` init? Same.

What about using a *different* variable for the pre-loop shift that is a copy: `s0 = 0; a0 = s0 << 10;` — the copy s0 is known.

Hmm. What if we make the pre-loop a0 assignment depend on a value loaded from the struct that is *known* to be 0 only at runtime? E.g., `a0 = ((Unkstruct_800B5CB8*)s1)->unk70 << 10`? No, that's a different value.

What about using the loop counter's *previous* value stored in another variable that is not constant: e.g.
```
s0 = 0;
a0 = s0 << 10;
```
→ what if we write:
```
s0 = 0;
s3 = s0;      // s3 known 0 too
a0 = s3 << 10;
```
No.

What about making the pre-loop a0 computed by the same expression as the loop-bottom through a goto that jumps into the loop? E.g.:

```
s0 = 0;
goto head;   // hmm
do {
  ...
  a0 = s0 << 10;
} while (s0<4);
```
Can't skip the first a0.

Alternative: use a for loop with the shift in the increment:
```
for (s0 = 0; s0 < 4; s0++) {
   ...
}
```
That changes control flow (test at top) — target tests at bottom.

What about `while (1) { ... if (s0>=4) break; }`? Loop shape changes; gcc may produce different.

Hmm. Let's reconsider: the folding that kills it is probably in cse or combine. There's a classic trick: make the shift's operand be an expression that cse can't fold because of a side effect between the assignment and the use. E.g., insert a call between `s0 = 0;` and `a0 = s0 << 10;`? But a call would clobber and s0 is callee-saved... gcc would still know s0=0? Actually after a call, gcc's reg_known_value for s0 might be invalidated (calls invalidate all regs? No — s0 is callee-saved, so its known value might survive... in cse, a call kills memory and call-clobbered regs, but s0's equivalence might survive).

Hmm, what if we assign s0 = 0 *after* a call... no.

Better idea: exploit that `s2 = (s32)D_8019B538;` is a load of a symbol address. Could we reorder so `a0 = s0 << 10` is computed... no.

Wait. Maybe there's a cleaner reading: in the target, is 1f68's `sll a0,s0,0xa` really from the pre-loop statement? The instruction order: 1f64 sw ra, 1f68 sll a0,s0,0xa, 1f6c sll v0,s0,0x1. In source, the pre-loop statement is `a0 = s0 << 10;` before the do. Yes.

What if instead of a separate pre-loop statement, we make a0's first value come from the *loop-bottom* statement of an unrolled... no.

Let me try the simple restructure: move `a0 = s0 << 10;` into the loop top but keep the loop-bottom one as well? That would be two statements, one redundant:
```
s0 = 0;
a0 = s0 << 10;
do {
  a0 = s0 << 10;   // redundant
  ...
  a0 = s0 << 10;
}
```
gcc would CSE/eliminate the redundant one. No.

Alternative plain-C way to defeat constant propagation: make s0 not a compile-time constant by computing it: `s0 = (s32)((u32)0);`? folds.

Use a union? `union { s32 i; } u; u.i = 0; s0 = u.i;` → memory, gcc may keep in memory; changes allocation.

What about `s0 = 0; s0 = s0 << 0;`? folds.

Hmm, what about using the `&&`/`||` trick from C0505 catalog? Not applicable.

What about initializing s0 = 0 but then using `s0` in the shift before... no.

OK, maybe the trick is different: maybe we don't need s0 unknown — we need gcc to schedule/emit `sll a0,s0,0xa` because a0 is used in a way that requires it. Wait, if a0 = 0 constant, gcc folds to move a0,zero (which it did). Could we instead make the *constant* be materialized via a shift? E.g., write `a0 = s0 << 10;` but ensure gcc keeps it as shift because the result is used in a context... no.

Alternatively: get gcc to emit `sll a0,s0,0xa` where s0 is a register holding 0 by using a *different* expression: `a0 = (s0 << 10) | 0;`? folds.

What if we use `s0` as a pointer? `a0 = (s32)((u8 *)s0 + (s0 << 10))`? no.

What about `a0 = s0 * 1024;`? With s0=0 → 0. folds.

Hmm. Let's consider: is `move a0,zero` really the only difference? Score 2. If we can't remove it via C, maybe the launder can be replaced by an equivalent plain-C construct that also happens to be a "real 2nd set" as in moves.md patterns. In those moves, the launder was replaced by a real 2nd set like `pv = *p; pv &= mask;` — that makes cse see two sets and prevents merging. Here, the launder makes s0's value unknown. A real 2nd set of s0 with a value that's not a constant... but the value must be 0.

Could we make the 2nd set be `s0 = s0 & 0;`? No.

What about `s0 = (s16)s0`? value-preserving, known 0 → still folds? Maybe not! A narrowing conversion might produce a SUBREG that blocks the constant fold in the shift? Actually `(s16)0` folds to 0.

Hmm what about the reverse: make the shift operand not s0 but a copy created by a *conversion* that gcc treats as opaque? Unlikely.

Let's look at how other shards cracked launders on this exact pattern. Search moves.md for "2nd set" and "do-while". Also cookbook C0535 and C0414. But more useful: search for a move that kept an sll. Let me grep moves for "sll" and "const".
