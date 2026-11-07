---
ts: 2026-11-06T15:13:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5X7soCvEaDjMgYVDeU7M
---
C0414: the dead-reset `p = 0;` after a use invalidates cse's equivalence and is deleted by flow before sched1, costing zero bytes.

Applied here: we need cse to not know t==5 at the `if (t != 3)` test. But t's value 5 comes from the *branch condition* (flow's known-value propagation), not from a cse equivalence. A dead-reset `t = 0;` after the test wouldn't help.

Hmm, but what if we put a dead-reset *between* the t==5 test and the t!=3 test? The compiler knows t==5 from the branch; a set `t = 5;`? That would be a real set of 5 → still knows. A dead-reset `t = 0;` would change semantics.

Wait — what about resetting a *different* variable that cse uses for the equivalence? 

Let me reconsider: how does the compiler know t==5 inside the if? It's from the branch condition `beq/bne`. The optimizer (jump/flow) propagates the known condition into the block. Specifically, `bne s0,v0,740` means on the fall-through s0 == v0 == 5. flow's constant propagation (`propagate_block` in flow.c) records that on the fall-through edge, s0 == v0 (equivalence), and since v0 is a constant 5, s0 is known 5. Then `if (t != 3)` is folded.

To break this, the comparison `t != 3` must be in a block where flow can't propagate the equality. E.g., if there's a label/join between the branch and the compare. flow propagates along edges; at a join with multiple predecessors it intersects.

So: put a label between the `if (t == 5)` test and the `if (t != 3)` test that is reachable from another path where t isn't known. Hmm.

Alternatively, do the `t == 5` test in a way that doesn't produce the known-value edge. E.g., `if (t == 5) goto body; ... body: ...` — flow propagates the condition along the edge to the label.

What if the t==5 test is `if (t != 5) goto skip;` — same.

Hmm, what if we make the `t == 5` comparison involve a value that flow can't equate to t: e.g. `if (t == five)` where `five` is a variable holding 5. Then on the fall-through, flow knows t == five, and five is a constant (if it can fold) → still 5. If `five` is a non-constant variable (e.g. loaded from somewhere), flow can't derive t==5. But we'd need `five` to be 5 at runtime without the compiler knowing — e.g. `s32 five = 5;` → the compiler knows five==5 and folds the whole test.

What if `five` is a parameter/global? Not available.

Hmm, what about `if (t == (s16)0x10005)`? folds.

OK here's another thought: maybe we don't need the `t != 3` compare to be *unfolded*; maybe we can restructure the source so the target's branch pattern arises from a *different* legitimate test. The target has:
```
beq s0,v1,70c   # if (t == 3) goto sel_054
bne s0,v0,740   # if (t != 5) goto after
bne s0,v1,71c   # if (t != 3) goto sel_094
```
What if we write:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t == 3) { }        // no
```
Hmm.

What if the third test compares t against 3 but with the *opposite* semantic use: e.g. `if (t >= 4) goto sel_094;`? Compiler knows t==5 → folds.

Everything folds because t==5 is known.

The real question: can we prevent the known-value propagation from the `t==5` branch? flow.c's `propagate_block` propagates `(reg == const)` through a conditional jump only along the edge. What if we insert an intervening conditional on another variable? flow propagates per-edge through the CFG; a branch that doesn't touch t doesn't invalidate the knowledge of t.

What if we insert a label that is a join of two paths, one where t isn't known? For example:

```
if (t == 5) {
    if (t == 3) goto sel_054;   // hmm
```
No.

What about using a loop? E.g. wrap the t!=3 test in a one-iteration loop: `do { if (t != 3) goto sel_094; } while (0);` — the loop head is a label with two predecessors (entry and back edge). flow at the loop head would intersect the entry knowledge (t==5) with the back-edge knowledge (t==5 still) → still knows. Hmm, but the back edge might come with no knowledge? flow propagates along the back edge too, and it would still know t==5 (nothing changes t). So it intersects to 5.

Unless something in the loop could change t: if the loop body could modify t, flow's intersection at the loop head would drop the knowledge. flow's `propagate_block` intersects the in-sets; if the back edge carries "t==5" it stays. Since nothing sets t, the back edge carries t==5.

But if we make the loop body contain a call that *might* modify t? t is a local; calls can't modify a local unless its address escapes. But flow doesn't know that? Actually flow knows local pseudos are not modified by calls (they're in registers saved across calls). Hmm.

What if t is declared as a `static`? no.

Let me try a different tack: use the `& 0xFFFF` mask idea but check whether it really costs an insn. f2 scored 4 — same as baseline, so the mask didn't change the code at all (it folded). Because t is s16 and the compiler knows the value.

Hmm, what if we make t an `s32` (not s16) and mask? t = (s16)a1 is inherently s16-valued.

Let me look at how the original launder's RTL looks, to see exactly what it changes. Dump the orig (with launder) function's RTL and compare with nolaunder. But more useful: find which pass folds the `t != 3` test in nolaunder. Let me dump.

Actually, let me reconsider the whole item. The score is 4 with 279 ins = target 279. Only 5 instructions differ (v0/v1 pair + branch shape). The wall tag would be flow-known-value. But maybe there's a trick.

Let me look at the *original* function's structure again:
```
case 5:
    t = (s16)a1;
    if (t == 0) { sel=&D_801C3C70; goto set_sel; }
    if (t == 3) goto sel_054;
    if (t == 5) {
        launder(t);
        if (t != 3) goto sel_094;
    sel_054:
        sel = &D_801C3C94;
        goto set_sel;
    sel_094:
        if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
        sel = &D_801C3CD4;
        goto set_sel;
    }
    ...
```
Note the label sel_054 is inside the `if (t == 5)` block. The launder forces the compiler to keep the `t != 3` test so that sel_054 remains reachable (dead-code-wise). Without it, sel_054 is only reachable from the earlier `if (t == 3)` goto — and the compiler keeps that block.

What if we restructure so the `t != 3` test is naturally needed because sel_054 is reached from the t==3 path *through* the same block? For example:

```
if (t == 3) goto sel_054;
if (t == 5) {
    goto sel_094;
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094:
    ...
}
```
This is semantically identical to the launder-free version (t==5 → sel_094). The compiler would emit: `beq t,3,sel_054; li v0,5; bne t,v0,after; j sel_094`. That's 3 branches + j, vs target's 3 branches. The target has `bne t,3,sel_094` instead of `j sel_094`. So we'd be one insn short? Actually target: beq, li, bne(t,5), nop, bne(t,3), nop. Mine would be: beq, li, bne(t,5), nop, j, nop? Same count! 279 ins? Hmm, the diff showed mine has `j 740` at 99 and target has `bne s0,v1,71c`. So both have an insn there. The score 4 comes from the branch shape and register allocation.

Could a `j` vs `bne` be forced differently? The target's `bne s0,v1,71c` falls through to sel_054 (70c) when t==3. If we write `goto sel_094` after the if, the compiler emits `j sel_094`. To get `bne t,3,sel_094`, the source must have a conditional.

So we need a conditional test that the compiler can't fold, i.e., t's value unknown.

Hmm, what if we compare `t` against 3 *before* the t==5 test, using the result later? E.g.:

```
s16 is3 = (t == 3);
if (t == 3) goto sel_054;
if (t == 5) {
    if (!is3) goto sel_094;
    ...
}
```
The compiler knows is3 = (t==3) = 0 when t==5 → folds.

What if we compute `is3` from a value whose relation to t the compiler doesn't track, e.g. `is3 = ((s16)a1 == 3)` computed *before* `t = (s16)a1;`? The compiler might still equate.

What if we compute `is3` from a *separate load* of a1? a1 is a register parameter; no reload.

What if we pass a1 through a volatile? banned.

Hmm, what about a different variable: `if ((s16)a1 != 3)` — f1 scored 4, folded. So the compiler does equate.

What about `if (a1 != 3)` (without the cast)? a1 is the full s32 arg; its low 16 bits are 5 but the compiler may not know the full value. Wait — the compiler knows t = (s16)a1 == 5, which implies a1's low 16 bits are 5 but a1 could be 0x10005 etc. So `a1 != 3` is NOT provably true (a1 could be 3? no — if a1 == 3 then t == 3, contradicting t==5; but does the compiler reason that?). The compiler knows t==5 and t == sign_extend(a1[15:0]). If a1 were 3, t would be 3. Can the compiler derive a1 != 3? It would need to know a1's low bits. cse might have the equivalence t ↔ sign_extend(subreg(a1)). Hmm, comparing the full a1 against 3 is a different comparison, and the compiler's known-value logic may not fold it. Let me test `if (a1 != 3)`. But semantics: if a1 = 0x10005, then a1 != 3 is true, same as t != 3 (t=5). If a1 = 3, t=3 → not in this block. So `a1 != 3` inside the t==5 block is always true, equivalent. But is the emitted compare against a1 or t? The target compares s0 (t) against v1=3. If we compare a1, gcc would compare a1's register (s1? a1 is the second param, likely in s1 or a1). That would be a different register → mismatch.

Hmm.

OK, let me look at this from the "what does the target's source look like" angle. The target was compiled from the orig.c WITH the asm launder. Our job: a lever-free body with identical bytes. Since the launder's only effect here is to keep `t` opaque at that point, maybe we can achieve opacity with a construct that has zero footprint.

Zero-footprint opacity: the dead-reset trick! `p = expr; f(p); p = 0;` — flow deletes the dead set. But the opacity here needs to come *before* the test, making t unknown. A dead-reset sets t to 0, not 5.

What about `t = t;`? cse would remove it as a no-op (self-assignment) or keep it? If kept until after cse, it would invalidate... but a self-copy is deleted early.

What about `t = t + 0;`? folded at gimplification.

Hmm, what about making t's value come through a variable that is set to 5 by a *dead* store the compiler can't see through? E.g.:

```
t = (s16)a1;
...
if (t == 5) {
    t = t;        // dead self-copy
```

Let me think about flow's known-value propagation more concretely. In flow.c, `propagate_block` uses `regs_live`/`reg_last_use`? Actually constant propagation in flow.c 2.7.2: it records `regs_ever_live`, and for constant propagation it's in `jump.c`'s `jump_optimize` (the `simplejump_p`/`if_then_else` optimization) or in `cse` (fold_rtx with `reg_equiv_constant`) — but cse's equivalence classes are per EBB, and the branch's fall-through edge within an EBB carries the known value.

Hmm, in the .cse dump we saw "Processing block from 2 to 24". The t==5 branch and the t!=3 test are in the same EBB (the fall-through of a conditional branch is part of the same extended block in cse). So cse's fold_rtx knows t==5 from the branch? cse's fold_rtx handles conditional branches: it records "this register is equal to this constant on the taken/not-taken path" — in cse.c there's `record_jump_equiv` / `record_jump_cond`. Yes! cse records jump equivalences (reg == const) for the fall-through path. That's how it folds.

So to defeat it: put the `t != 3` test in a *different* cse block (after a label) or break the jump equivalence. cse's record_jump_cond records the equivalence until invalidated by a set of t.

A *dead set* of t after the branch would invalidate the equivalence... but it also changes the value. Unless the set is deleted before cse. Hmm.

What invalidates a cse equivalence? A set of the register. So a `t = something` between the branch and the test would break it — but t must stay 5.

What about a set of t that cse can't fold but is value-preserving: this is the same problem.

OK — alternative: make the test compare a register whose equivalence isn't recorded. cse's record_jump_cond records the equivalence for the *register compared in the branch*. The branch compares t with 5. So t is known. If the third test compares a *different register* that is known-equal to t... cse might have made them equivalent.

What if the third test compares `a1` (the parameter)? The branch equivalence is on t, not a1. cse's jump recording: `record_jump_cond` makes t equivalent to the constant. a1 is separate. Then `a1 != 3` — cse's fold_rtx would need to know a1's value. It has the equivalence t == (sign_extend (subreg a1))? If cse recorded that from `t = (s16)a1`, then a1's subreg is equivalent to t = 5. Then comparing `(s16)a1 != 3` → fold. But comparing the FULL a1 against 3: the fold_rtx of `(ne (reg a1) (const 3))` would look at a1's equivalence class. Is a1 in an equivalence class with t? The copy `t = sign_extend(subreg(a1))` creates an equivalence between t and the expression, not directly between t and a1 (different modes). So fold_rtx of `a1 != 3` likely does NOT fold. And the emitted code would compare a1 against 3 — but a1's register: the target compares s0 (t). If we compare a1, gcc emits a compare of a1's hard reg (which is s1? no — a1 the parameter is in $5, moved to a callee-saved? Let me check: in the target, t is in s0. a1 (the second arg) is in... let me check the prologue. Actually the function's params: a0 (idx) and a1. Let me check where a1 lives.

Hmm, this is getting complicated, and the register would differ. But maybe gcc would compare the same physical register if a1 is in s1 and t in s0 — no.

Let me step back and consider the budget: I have 5 items, 20-30 min each. This item is complex. Let me try a few more targeted ideas and then possibly record a WALL.

Ideas:
g1: `if (a1 != 3) goto sel_094;` (full 32-bit compare).
g2: move the `if (t == 3) goto sel_054;` inside the `if (t == 5)` block? Changes structure.
g3: use a `switch` for the t==3/t==5 part.
g4: break the cse jump equivalence by putting the test after a label that's a join: e.g. 
```
if (t == 5) {
    if (t == 0) goto ...;  // no
```
g5: insert a `do { } while (0);` between the t==5 branch and the t!=3 test (C0535 EBB split). That might break the cse block! Since the do-while(0) label survives to cse1 in some cases (C0535 says it splits cse1's EBB). Let me try: 
```
if (t == 5) {
    do { } while (0);
    if (t != 3) goto sel_094;
```
Hmm, the empty do-while would be removed. But C0535's trick wrapped two copies. Let me try anyway.

g6: `do { if (t != 3) goto sel_094; } while (0);` — wrap the test itself.
g7: put the test inside a `while (1) { ... break; }`.

Also: maybe the fold is done by jump.c's `if_then_else` optimization (which propagates conditions). In 2.7.2, `jump_optimize` has `if_then_else_optimize`? There's `jump.c`'s `thread_jumps`. And `flow.c` does constant propagation (`propagate_block` uses `regs_ever_live`?). Let me actually check which pass folds it. That's the efficient move: dump the nolaunder body's passes and find where the `beq t,3` disappears.

Let me do that. Use the --keep scratch from the last run (f7? no, --keep wasn't used for f's). Let me run --keep on nolaunder and dump.

Actually, the dumps take time (~seconds). Worth it to target the right pass.

Let me run --keep for nolaunder and dump.
