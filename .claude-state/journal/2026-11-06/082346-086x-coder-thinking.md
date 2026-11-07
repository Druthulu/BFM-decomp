---
ts: 2026-11-06T15:23:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a1mIHpv9jdLhOmck21Yn
---
08:22:45. So item 2 has taken ~08:10→08:23 = 13 min. Hmm, my sense of time was off. The rule requires ≥20 min for a WALL.

Wait, let me re-read: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 20 minutes. I have 13. I have 50 tries. Let me keep working for ~7 more minutes — that's fine, and maybe I'll find the crack.

Let me think really carefully now, since I have time.

The core: cse records t==5 at the `bne t,five` and folds `t != 3` later in the same EBB. The only lever-free escape is to break the EBB or invalidate the equivalence.

Options for breaking the EBB between the branch and the test:
1. A surviving code_label. What produces one at -O2 after jump1?
   - A loop (do/while/for) — but jump1 flattens constant-trip loops.
   - A `goto` label that's the target of a real branch.
   - A `switch` — the case labels! The switch's case labels are targets of the dispatch branches, so they survive. If the test is inside a `case`, the case label is a boundary — but the branch knowledge (t==5) is established *before* the case label... Actually, if the t==5 test itself is a switch case, then the case body starts at a label. The dispatch compares t with 5; cse would process the dispatch and the case body in different blocks (a label separates them), so cse might NOT record t==5 for the case body!

   That's the l1 experiment: I made a switch with case 3 and case 5, and the test inside case 5. l1 scored 4 — so either gcc turned the switch into compares (beq/bne) and cse still recorded, or it used a jump table.

   Let me check l1's disassembly to see. Actually, the score was 4 = same residual, so it folded.

   Hmm, but maybe gcc compiled `switch(t)` with cases 3,5 into a jump table. Then the code would be very different (more than 4 score). Score 4 means nearly identical → it compiled to compares.

2. Invalidate the equivalence with a set of t. All value-preserving sets were folded or removed before cse.

   KEY: what about a set of t that flow deletes but cse keeps? The dead-reset C0414 pattern. We need: cse sees `t = X` (invalidating), and flow deletes it (so no bytes). For flow to delete it, the set must be dead (t not used after, or overwritten). But then t's value at the test must be the correct 5.

   What if we do: `t = 0;` right before the test, then the test compares `t` — but t is 0, wrong.

   What if the set is of a *different register that cse thinks t is equivalent to*? cse's equivalence classes: if t and u are in the same class (u = t), then a set of u doesn't invalidate t's class (it splits u off).

   Hmm.

3. Make the test compare a register whose value cse doesn't know, while the target's register is the same. The register is s0 = t. So we need t's *pseudo* to be unknown. 

   What if t is set to 5 via a path cse can't track — e.g., the t==5 branch compares t, but then we *reassign* t from a source cse can't fold: we tried m5 (a1|0x10000) and it folded. What about `t = (s16)(a1 * 1)`? folds. `t = (s16)(a1 / 1)`? folds.
   
   What about `t = (s16)(a1 & 0xFFFF);` → j1 folded.
   
   What about `t = (s16)(a1 % 65536);` — a modulo! gcc would emit a division (expensive). No.
   
   What about `t = (s16)(a1 - (a1 & ~0xFFFF));`? folds.

4. Make the t==5 branch compare t with a *non-constant* so cse's equivalence isn't "t == const":
   The compare in the RTL is `(ne (reg 88) (reg 90))` where reg 90 holds 3... wait, that was the t!=3 compare. The t==5 branch would be `(ne (reg t) (reg five))` or `(ne (reg t) (const 5))`.
   
   In the .rtl dump, the t==5 branch: let me look. Earlier grep showed `(ne:SI (reg/v:SI 77) (reg:SI 116))` at line 630 — that's t vs reg 116. So the t==5 test is reg-vs-reg where reg 116 = 5.
   
   cse's record_jump_cond records "reg 77 == reg 116" (an equivalence), and reg 116 == 5 (constant). So t is known 5.
   
   If reg 116 (the "5") were not known to be 5... but it is.

5. Change the order: what if the `if (t != 3)` test is in the *same block* as the `if (t == 3)` test but BEFORE the t==5 branch? The target's order is: beq t,3; bne t,5; bne t,3. What if the source has the t!=3 test earlier but the scheduler/branch optimizer reorders? No, branches aren't reordered like that.

6. Use a *function* to make t opaque: a call that returns its arg. Not available.

7. Use the `mode` variable (a runtime value from func_80029504) to make an opaque value that's 5? No.

8. What about making `t` a `u16`/`s16` and using the *other* half? no.

Hmm, let me look at this from the target's source-reconstruction view. The launder is `__asm__ ("" : "=r"(t) : "0"(t));`. What if instead the original source had `t` compared in a way that gcc 2.7.2 doesn't fold even without the asm — e.g., if the test were `if ((s16)t != 3)`? We tested f? Not exactly: h5 was `t == (s16)5` for the *branch*. Let me test the test as `(s16)t != 3`:
- s1: `if ((s16)t != 3) goto sel_094;` — t is already s16; (s16)t is a no-op → same.

What about `(u16)t != 3`? For t=5 → true; but the compiler knows t=5 → folds. And it may add an andi.

9. What about making the test a *signed comparison* against a value that's 3 but with a different mode: `if ((u32)t != 3)` — the compiler knows t=5 → folds.

10. What if the value t is known but the comparison is against a value whose known-ness is *not* established because it's a parameter? e.g., `if (t != a0)` — a0 = idx+1. Not 3 necessarily. No.

OK, let me try the switch idea more carefully — maybe with a `default` that goes to the test, so the case body label separates. Actually, here's a cleaner structural idea using the existing `sel_054` label as a join with two different t values:

The target's test `if (t != 3) goto sel_094` — what if we write the source so that this test is at a point where t can be either 3 or 5, making it non-redundant? That would change the control flow semantics... but maybe there's an equivalent structure.

Original semantics:
- t==3 → sel_054 (sel = &D_801C3C94)
- t==5 → sel_094 (call; sel = &D_801C3CD4)
- else → the code after.

What if we write:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t == 3) goto sel_054;   // dead
    goto sel_094;
}
```
The `if (t == 3)` folds to false → just goto. Not matching.

What if we write the test on a *variable that can be 3 or 5 at that point*? For the compiler to emit `bne t,3`, t must be live and unknown.

Hmm, what if we merge the two `t==3` tests into one by restructuring:

```
if (t == 5) {
    goto sel_094;
}
if (t == 3) {
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094: ...
}
```
No.

Let me look at the target's CFG once more:
- 6f4: beq t,3 → 70c (sel_054)
- 6fc: bne t,5 → 740 (after)
- 704: bne t,3 → 71c (sel_094)
- 70c: sel_054 body → j set_sel
- 71c: sel_094 body

Note that 70c (sel_054) is reached from 6f4 (t==3) and from 704's fall-through (t==3). So at 70c, t==3 always.

The `bne t,3` at 704 is redundant given t==5. But what if the source is written so that the fall-through of 704 can be reached with t==3? That would require the t==5 test to be bypassed... e.g., if the test at 704 were reached directly from the t==3 path. But then the code would differ.

Hmm, what if we write:

```
if (t == 5) goto L5;
if (t == 3) goto sel_054;
goto after;
L5:
    if (t != 3) goto sel_094;
sel_054:
    ...
```
Here L5 is a label reached only from the t==5 branch. At L5, flow knows t==5 → folds. Same.

What if L5 is reached from BOTH the t==5 branch and the t==3 branch? Then t is 3 or 5 at L5, and `if (t != 3)` would be a real test! But then the t==3 path would enter L5 and, if t==3, fall through to sel_054 — same as before! Let's see:

```
if (t == 3) goto L5;
if (t == 5) {
L5:
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094: ...
}
```
Hmm, the label L5 inside the t==5 block can't be the target of the t==3 goto (that would jump into the if block — legal in C). At L5, t is 3 (from the goto) or 5 (from the fall-through). flow would intersect: t==3 or t==5 → unknown → `if (t != 3)` is a REAL test! 

But wait: the target's code has the `beq t,3` at 6f4 jumping to 70c (sel_054), which is *after* the test at 704. If we make the t==3 goto target L5 (before the test), then the code would be: beq t,3 → L5; ... and the test at L5 would compare t against 3 again. That's exactly the target's shape IF the compiler arranges it as:
```
beq t,3,L5? 
```
Hmm, but the target's beq t,3 goes to 70c (sel_054), not to the test.

Hold on — if the t==3 goto targets L5 and at L5 the test `if (t != 3) goto sel_094`, then for the t==3 path, the test is false → falls to sel_054. So the compiler could either jump directly to sel_054 (since it knows t==3 on that edge) or jump to L5. The target's beq jumps directly to 70c (sel_054) — consistent with the compiler knowing t==3 on that edge.

But then the test at L5 would be reached only from the t==5 fall-through (since the t==3 path jumps directly to sel_054), so flow would know t==5 there → fold. Hmm.

Unless the compiler doesn't merge them.

Hmm, but actually the target's beq t,3 → 70c is exactly the "jump directly to sel_054" behavior. And the test at 704 exists because the asm blocked the fold. So in the target's source, the `if (t == 3) goto sel_054;` is separate from the launder test. My restructuring would change the target.

Hmm.

OK, what if we make the test's block have two predecessors where t isn't known? We'd need the t==3 path to flow *through* the test block. In the target's source, the test is inside the t==5 block, so only one predecessor.

What if we restructure so the test is at the join and the t==3 branch targets the test:
```
if (t == 5) {
    goto L5;   // hmm
}
if (t == 3) {
L5:
    if (t != 3) goto sel_094;
sel_054: ...
}
```
Semantics: t==5 → goto L5 → test t!=3 → true → sel_094. t==3 → L5 → test false → sel_054. Other → after. That's semantically identical to the original! And at L5, t is 3 or 5 → flow can't know → the test is real!

But the target's branch layout would be: beq t,5,L5? and beq t,3,L5? Hmm, the target has beq t,3 → sel_054 and bne t,5 → after. The compiler might merge both gotos to L5 into one block and then the test... Actually since both paths go to L5, the compiler might simplify `if (t==5) goto L5; if (t==3) goto L5;` into `if (t==5 || t==3) goto L5`. Then at L5, t is 3 or 5. The test `t != 3` would be real! And the layout: `beq t,3,L5; bne t,5,after; L5: bne t,3,sel_094; ...`. 

Wait, that's EXACTLY the target's sequence:
```
6f4: beq s0,v1,70c      # if t==3 goto sel_054
6f8: li v0,5
6fc: bne s0,v0,740      # if t!=5 goto after
704: bne s0,v1,71c      # (at L5) if t!=3 goto sel_094
70c: sel_054
71c: sel_094
```
If L5 is at 704 and sel_054 at 70c, then the beq at 6f4 targets 70c (sel_054), not 704 (L5). Hmm — but that's because the compiler knows that on the t==3 edge the test at L5 is false, so it jumps directly to sel_054. That's exactly the optimization we'd want to avoid... but it produces the target's bytes!

So: if the source is:
```
if (t == 5) goto L5;
if (t == 3) goto L5;
goto after;   // hmm, need to fall to the code after
L5:
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_801C3C94; goto set_sel;
sel_094:
    ...
```
Hmm, but the original structure is `if (t == 3) goto sel_054;` FIRST, then the t==5 block. Let me reconstruct the exact source that would compile to the target:

Target branches:
1. beq t,3 → sel_054
2. bne t,5 → after
3. bne t,3 → sel_094
4. fall-through → sel_054

For branch 3 to be non-folded, the block at 704 must not know t==5. So the block at 704 must have ≥2 predecessors with different t values, OR the compiler simply doesn't propagate.

In the target (with the asm), the asm killed the knowledge.

In a lever-free body, we need the same CFG: block at 704 reached from the t==5 fall-through AND from somewhere with t==3.

But branch 1 (beq t,3 → sel_054) goes directly to sel_054, so the t==3 path doesn't pass through 704. Unless the source's t==3 goto targets the test block and the compiler chooses to jump to sel_054 instead (as an optimization). Hmm, but then at 704 the only predecessor is the t==5 fall-through, so the compiler would know t==5 and fold branch 3.

Unless the compiler *doesn't* know because the t==3 edge also reaches 704 and the compiler's flow analysis keeps the conservative intersection. But then it would emit `beq t,3 → 704` (not → 70c), giving a different byte layout: beq t,3,704; bne t,5,after; 704: bne t,3,71c; 70c: sel_054...

Hmm wait — the target's beq t,3 → 70c. If the source had `if (t==3) goto L5` and L5 = 704, the compiler would emit beq → 704 unless it optimizes to 70c.

Hmm. But actually, maybe the original source is:

```
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054: ...
```
and the asm kills t's knowledge. For a lever-free version, we could restructure to make the test at a join:

```
if (t == 3) goto sel_054;
if (t == 5) {
    goto sel_094;
}
goto after;   // no
```
No.

What about:
```
if (t == 5) {
    if (t != 3) goto sel_094;
}
if (t == 3) {
sel_054: ...
}
```
Hmm, the label placement.

Let me think about the "two predecessors" idea concretely with a label shared by the t==3 path:

```
if (t == 5) goto Ltest;
if (t == 3) goto Ltest;
goto after;
Ltest:
    if (t != 3) goto sel_094;
sel_054:
    sel = &D_801C3C94;
    goto set_sel;
sel_094:
    if (...) goto call_45F;
    sel = &D_801C3CD4;
    goto set_sel;
after:
    if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) { ... }
```
At Ltest, t ∈ {5, 3}. The test `t != 3` is real. The compiler emits:
- `beq t,5,Ltest` (or bne)
- `beq t,3,Ltest` — but it might merge: `if (t==5 || t==3) goto Ltest`.
- At Ltest: `bne t,3,sel_094`; fall-through to sel_054.

Would the bytes match the target? The target has:
- beq t,3 → sel_054 (70c)
- bne t,5 → after (740)
- bne t,3 → sel_094 (71c)

My source would give something like:
- beq t,5 → Ltest
- beq t,3 → Ltest
- ... 
which differs (the target's first branch is t==3 → sel_054).

Hmm. But maybe the compiler would optimize the t==3 edge to go directly to sel_054 (since at Ltest with t==3 the test is false). That's a jump-threading optimization. If it does, we get exactly the target! And the t==5 edge would go to Ltest.

But the order of the branches would be: the source order is t==5 first, then t==3. The target has t==3 first. Hmm.

What if the source order is t==3 first?
```
if (t == 3) goto Ltest;
if (t == 5) goto Ltest;
goto after;
Ltest:
    if (t != 3) goto sel_094;
sel_054: ...
```
The compiler emits: beq t,3,Ltest; bne t,5,after; Ltest: bne t,3,sel_094; ... 

That's EXACTLY the target's instruction sequence (beq t,3; bne t,5; bne t,3), except the first branch targets Ltest (704) rather than sel_054 (70c). But wait — in the target, beq t,3 → 70c (sel_054). If our source's beq targets Ltest (704), the bytes differ (different target address).

Unless the compiler threads the jump: since at Ltest the test `t != 3` is false when arriving from the t==3 edge, jump optimization could redirect the beq to sel_054 directly. gcc 2.7.2's jump.c does "jump threading" — it might. But it also might not.

Hmm, but actually — wait. If the compiler knows that at Ltest t is 3 or 5, it can't simplify the test. But if it also tracks that on the t==3 edge the test is false, it can thread. That's exactly `jump_optimize`'s job? It's a "conditional jump to a block that starts with a conditional jump" — jump.c's `thread_jumps` handles that: if the target block's first insn is a jump on the same register, it can retarget. Here Ltest's first insn is `bne t,3` — a conditional on t. On the t==3 edge, the compiler could retarget the beq to the fall-through target (sel_054). gcc 2.7.2's `jump_optimize` does "if_then_else" and "thread_jumps". It might.

This is worth testing! Let me construct it.

But the structure must fit the original code. Let me write:

```
    case 5:
        t = (s16)a1;
        if (t == 0) { sel = &D_801C3C70; goto set_sel; }
        if (t == 3) goto sel_test;
        if (t == 5) goto sel_test;
        goto after_test;
    sel_test:
        if (t != 3) goto sel_094;
    sel_054:
        sel = (u32)&D_801C3C94;
        goto set_sel;
    sel_094:
        if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
        sel = (u32)&D_801C3CD4;
        goto set_sel;
    after_test:
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) { ... }
```
Hmm, but `goto after_test` where after_test is the next statement — jump.c removes it.

Wait, but the original code's flow after the t==5 block goes to `if ((func_800291B4(D_80183478[t])...`. And the `if (t == 3)` path goes to sel_054 which ends with `goto set_sel` (so it doesn't fall through to after). Good.

But careful: in the original, `sel_054` is *inside* the t==5 block, and after the block, the code continues to the D_80183478 check. With my restructure, sel_054 is a top-level label after the ifs, and the `after_test` label precedes the D_80183478 check. The control flow: t==3 or t==5 → sel_test → test → sel_094 or sel_054. Others → after_test.

This is semantically identical. Let me test it.

Let me write the candidate. I'll take the base and replace the case-5 block.

The base case 5 (nolaunder):
```
    case 5:
        t = (s16)a1;
        if (t == 0) {
            sel = (u32)&D_801C3C70;
            goto set_sel;
        }
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_801C3C94;
            goto set_sel;
        sel_094:
            if ((func_800291B4(0x40) & 0xFF) == 0) {
                goto call_45F;
            }
            sel = (u32)&D_801C3CD4;
            goto set_sel;
        }
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) {
```
New:
```
    case 5:
        t = (s16)a1;
        if (t == 0) {
            sel = (u32)&D_801C3C70;
            goto set_sel;
        }
        if (t == 3) {
            goto sel_test;
        }
        if (t == 5) {
            goto sel_test;
        }
        goto after_test;
    sel_test:
        if (t != 3) {
            goto sel_094;
        }
    sel_054:
        sel = (u32)&D_801C3C94;
        goto set_sel;
    sel_094:
        if ((func_800291B4(0x40) & 0xFF) == 0) {
            goto call_45F;
        }
        sel = (u32)&D_801C3CD4;
        goto set_sel;
    after_test:
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) {
```
This is valid C (labels in a switch case; falling through to after_test).

Hmm, one issue: `after_test:` is a label right before the `if`, and `goto after_test` from above. jump.c will remove the goto (jump to next). Fine.

Let me test this (s1.c).

Also a variant s2 where the t==5 test comes first:
```
        if (t == 5) goto sel_test;
        if (t == 3) goto sel_test;
```
(same set, different order) — the target order is t==3 first, so s1.

Let me write it.
