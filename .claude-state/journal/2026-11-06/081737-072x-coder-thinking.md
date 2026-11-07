---
ts: 2026-11-06T15:17:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gup8whNXC4V8TvdXXgMh
---
All fold. Time to consider: g1 scored 1 — the best lever-free body is g1 with score 1. Is g1 lever-free? Yes: `if (a1 != 3)` is plain C, launder removed. So best = 1.

Per the brief: "WALL (best = lowest score of a lever-free body)" and "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I've done: nolaunder(1) + f1-f7(7) + g1,g2,g3,g4,g6,g7(6) + h1,h3,h4,h5,h6,h7(6) + i1-i8(8) + j1-j6(6) = 34 scored tries. Time: started ~08:12, now ~08:40 = 28 min. So a WALL is justified with best 1.

But wait — before declaring a wall, can I try one more idea that's promising? The wall tag from moves.md: flow-known-value. The evidence: flow/cse records t==5 on the fall-through and folds `t != 3`; comparing a1 (not narrowed) keeps the branch but moves the compare to a1's register (score 1).

Hmm, actually — one more idea: what if we compare `t` against 3 but the t==5 test is *after* a label that's the target of the `t==3` goto? Wait: the `if (t == 3) goto sel_054;` jumps to sel_054 which is INSIDE the t==5 block. So sel_054's block has two predecessors: the t==3 goto and the fall-through from the t==5 test. If the t!=3 test were placed *at sel_054* (the join), flow's intersection at the join would be t==3 on one path and t==5 on the other → t is NOT a known constant at the join! Then `if (t != 3)` at the join would NOT fold!

But the target's layout: sel_054 is at 70c, and the test is at 704 before it. Hmm. Let me think about the CFG:

Target:
```
6f4: beq s0,v1,70c      # if (t==3) goto sel_054
6f8: li v0,5
6fc: bne s0,v0,740      # if (t!=5) goto after
700: nop
704: bne s0,v1,71c      # if (t!=3) goto sel_094
708: nop
70c: sel_054: ... sel=&D_801C3C94; goto set_sel
71c: sel_094: ...
```
So sel_054 (70c) is reached from the t==3 goto and from the fall-through of the t!=3 test (when t==3). In both cases t==3! So the join at 70c has t==3 from both paths. The compiler could know t==3 there, but sel_054 doesn't test t.

Now, what if we restructure so the t!=3 test happens at a join where t isn't known? For example:

```
if (t == 5) {
    if (t != 3) goto sel_094;
    ...
}
```
→ move the test to a block reachable from both the t==3 path and the t==5 path. Hmm.

What if we write:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t == 3) goto sel_054;   // folds to false
```
no.

Hmm, what about the opposite: make the `t != 3` test *guard* the sel_054 body, placed at a join:

```
if (t == 5) {
    goto sel_094;
sel_054:
    if (t == 3) { ... } 
}
```
No.

Honestly, the compiler's knowledge at the test point is inherent. I'll take the WALL with best 1 (g1).

But hold on — before that, let me reconsider: is the register difference in g1 fixable by making `t` and `a1` share? No.

Actually, one more: what if we compare `t` against 3, but the value of t is made unknown by a *call* between the t==5 test and the test? The target has no call there. Adding one changes bytes. No.

What about `if (t != 3)` where t is declared `volatile`? banned.

OK. Let me also consider: the item's `lines` column says 101 — maybe the expected difficulty. Whatever.

Decision: record WALL with best 1 (g1). But wait — the brief says for WALL, "best = lowest score of a lever-free body". g1 is lever-free (no launder; it's plain C). Let me double-check g1 has no levers: it's nolaunder + `a1 != 3`. Yes.

Hmm, but is g1 "PARTIAL"? PARTIAL means win.c scores 0 keeping only some levers. Not our case. So WALL.

Wall tag: `flow-known-value` exists in walls.txt: "flow/jump a redundant test on a known value is folded away; target keeps it (G22)". Our evidence: cse records t==5 on the fall-through of the t==5 branch and folds `t != 3`; the full-width `a1 != 3` spelling keeps the branch but compares a1's register (s1 vs s0), best 1.

Let me double-check g1's score and save win.c = g1? For a WALL, do we write win.c? The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c needed, but I'll keep g1.c as the best and note it.

Actually, let me reconsider one thing: maybe I should try to fix g1's register issue by changing WHERE a1 is compared — e.g., compare a1 but after `t = (s16)a1`... no.

One more idea: what if we use `if (a1 != 3)` but ALSO make the t==5 test use a1? Then both branches use a1's register — but the target's t==5 test uses s0. No.

What about making t's register also hold a1's full value? No.

Let me finalize item 2 as WALL best 1, tries 34.

Actually, wait. Let me reconsider the possibility that the target's source didn't have `t != 3` but something else, and the launder was for a different purpose. The target's `bne s0,v1,71c` — the launder makes t opaque so the test stays. Yes.

Alternatively: maybe we can get the target by making the *first* test (`t == 3`) not create the jump equivalence that folds the second. Hmm, the equivalence comes from the t==5 test.

What if we reorder the source: put the `if (t == 5)` test BEFORE `if (t == 3)`? Then:
```
if (t == 0) {...}
if (t == 5) { if (t != 3) goto sel_094; sel_054: ... }
if (t == 3) goto sel_054;
```
The target's layout has beq t,3 first. So no.

OK, finalize. Let me write notes, results row, moves line.

Wait, actually — one more consideration on g1: the compare `a1 != 3` compares the full 32-bit a1. The target's is `t != 3` (s16). Are they semantically equivalent? Inside the `t == 5` block, t == (s16)a1 == 5. So a1's low 16 bits are 5, but a1's high bits could be anything → a1 != 3 always true. So yes, equivalent. Good.

Let me also record: g1.c is the best lever-free body (score 1).

Let me write the notes.
