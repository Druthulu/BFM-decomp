---
ts: 2026-11-06T16:36:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H5zMibJHRT6xeR3WVvUO
---
So conditional-jump cross-jump requires `x = prev_real_insn(JUMP_LABEL(insn))` and `jump_back_p(x, insn)`. The merged case: the else arm's branch (431) has target skip (452); prev_real_insn(skip) = the barrier/... In target's layout, before skip is the call's `j epilogue` (jump 447). jump_back_p(447, 431): 447 jumps to the epilogue, not back to 431, so false → x=0 → no conditional cross-jump. Hmm.

For the unconditional-jump cross-jump: `find_cross_jump(insn, JUMP_LABEL(insn), 1)` where insn = the then arm's jump to join. This compares the then arm's code before the jump with the code before the join label (i.e., the else arm's code). minimum 1. Backward: i1 = branch skip (413), i2 = branch skip (431) — equal! minimum 1→0. Then i1 = slti 81, i2 = slti 513 differ → break, minimum=0 ≤0 → MERGE with last1=branch, last2=branch. That's it!

So the merge is cross-jumping the unconditional jump (then arm's `j join`) with the join label: it merges the common suffix [branch skip] — merging the two branches. minimum=1 suffices because one matched insn.

In v0 (asm), the then arm's insns before the jump: [asm 421, branch 413] — backward: i1 = asm, i2 = branch → GET_CODE differ → break immediately, minimum stays 1 → no merge.

So we need to break the match of the two branches, or add an insn between. Since the merge matches only 1 insn (the branch), any RTL difference in the branch pattern suffices. rtx_renumbered_equal_p compares patterns. The patterns are `(if_then_else (ne (reg v0) (const_int 0)) (pc) (label_ref 452))` — identical.

How to make them differ with real C, keeping emitted insns identical? The register is v0 in both. Hmm.

Wait — what if one branch uses a different comparison instruction form that still emits slti+beqz but with different RTL? E.g. `if (d >= 0x51)` gives `(lt (reg v1) (const_int 81))` then `(if_then_else (ne (reg v0) 0)...)`. Both arms same shape.

What if the else arm's branch condition is written so that the comparison result is used differently, e.g. `if ((d - 0x201) >= 0)`? Different insns.

Alternative: prevent the then arm's unconditional jump from existing. If the then arm's fallthrough naturally reaches the join, no jump → no cross-jump of the unconditional jump. But then the layout would put the call right after the then arm, before the else arm — different from target.

Hmm, but wait: what if the then arm's jump target is NOT the join label but something else, e.g. the then arm jumps to the call via a label that the else arm doesn't reach by fallthrough? Then find_cross_jump(insn, JUMP_LABEL(insn),1) compares the code before the jump with the code before the label. If the label is at the call and the else arm falls into it, same as now.

What if the else arm has a jump to the join as well (so both arms jump)? Then the unconditional-jump cross-jump compares then-jump with the code before join = the else arm's jump; backward: i1=branch(413), i2=branch(431) equal → merge again.

What if the two arms' branches differ because the else arm's `d >= 0x201` is written as `d > 0x200`? Same slti 513, same RTL.

Hmm, what if one arm's compare uses a different temp variable: e.g. `if (lim2 >= 0x51)` where lim2 is another copy of d? That changes the insns (extra move?).

Wait — maybe we can make the branch RTL differ by making one branch test the register with a different mode. E.g. one arm compares an `s16` variable directly: if the then arm uses `s16 d16 = d; if (d16 >= 0x51)` → extra sign-extend insns.

What about making one comparison against a `u16` constant? no.

Alternatively, use the `&&`/`||` fold or a different control structure that produces the same instruction sequence but different RTL at the branch. For example, the then arm could be:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else if (d >= 0x201) {
    goto skip;
}
```
Same RTL.

Hmm, think about the target's RTL more. The target layout with the asm is what the asm produced. But maybe the true original source produced this layout via a different C construct, and the asm was a hack that happened to reproduce it. The task says crack the barrier with real C.

What real-C construct leaves an insn-like RTL between the branch and the jump? A statement with no code but RTL: e.g. a `volatile` read? no, emits. A `(void)` cast of a variable? no RTL. A label! A code_label is skipped by the backward scan (`while (i2 && (GET_CODE(i2)==NOTE || CODE_LABEL)) i2 = PREV_INSN(i2);`) — for i2 only, not i1. i1 = prev_nonnote_insn(i1) — that skips notes but NOT labels? prev_nonnote_insn skips NOTE but stops at CODE_LABEL. So if the then arm had a CODE_LABEL between the branch and the jump, i1 would be that label → GET_CODE(i1)==CODE_LABEL → `--minimum; break;` with minimum 0? Let's see: at the top of the loop, `if (GET_CODE (i1) == CODE_LABEL) { --minimum; break; }` — minimum was 1, becomes 0, break; then `if (minimum <= 0 && last1 != 0 ...)` — last1 is 0 (no match yet) → no merge. 

So if there's a code label between the then arm's branch and its jump to the join, the merge is prevented! Can we get a code label there from real C? A label in the then arm after the if:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
lbl:
    ;
} else ...
```
A label with an empty statement might be deleted (NOTE_INSN_DELETED_LABEL). Hmm. But a label that's used (goto target) stays. We could do `goto lbl; lbl: ;`? That's an identity-ish goto... but goto control flow is real C, though it may be seen as a launder. The constraint says identity-statement launders (value ops) don't count; a goto is control flow. But it would add an unconditional jump unless optimized.

Actually the then arm already ends with a jump to the join. If we put a used label right before the end:

```
if (d >= 0x51) goto skip;
if (0) goto lbl;   /* dead */
lbl: ;
```
Hmm, a label only reachable by fallthrough — GCC deletes unused labels.

Better: a label that's the target of a branch from elsewhere but lands between the branch and the jump. For example, `goto docall;` where docall is after the else — that jump is the block end. We want a label between branch 413 and jump 423.

What if the then arm is:
```
if (d >= 0x51) goto skip;
goto docall;
```
At jump1 the `goto docall` block has label docall... The label is at the destination, not here.

Hmm, what about a `switch`? Or a loop?

Alternative: make the then arm's last insn before the jump not a branch but something else that matches nothing. E.g., in the then arm do the comparison differently so the branch is not adjacent to the jump.

Actually, what if the then arm has TWO tests: `if (d >= 0x51) goto skip;` and then something. The target's then arm ends with beqz+j, so only one test.

Let's consider making the *else* arm's branch not match the then's. The merge matches branch(413) with branch(431) because both are `(if_then_else (ne (reg v0) 0) (pc) (label_ref 452))`. If the else arm's branch uses a different register, e.g. `at` or v1, they'd differ. Can we influence the register of the comparison result in one arm? Post-reload, the compare result goes to v0 both. If one arm's comparison is `slt` with the operands in a different order: `if (d >= 0x201)` vs `if (0x201 <= d)`: GCC canonicalizes both to (lt d 513)? Probably.

What about `if (!(d < 0x201))`? Same RTL.

What if the else arm's test is expressed with `>=` on an unsigned... no, sltiu.

What if we make the else arm's branch a `bnez` on the same comparison by writing `if (d < 0x201) { goto docall; }` with docall being the call, and skip falling after? Structure:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d < 0x201) goto docall;
    goto skip;
}
docall: call;
```
Hmm, that adds a jump in the else arm. Not target.

Alternatively swap: then arm `if (d < 0x51) goto docall; goto skip;` → then arm: slti; bnez docall; j skip. Target has beqz skip; j call. Different.

OK here's another thought: the merge requires the then arm's unconditional jump to the join. Where does that jump come from in the target? If the then arm *falls through* to the join, there'd be no jump and no merge. The target has the jump because the else arm is laid out between. So if we reorder the source arms so that the then arm comes after the else arm, the then arm would fall through and the else arm would need the jump. But target's layout has the ==0 arm first (fallthrough from the unk70 test with bnez to the else arm).

Wait, actually target: `bnez v0,2bb0` → if unk70 != 0 goto else arm. So the ==0 arm is fallthrough = laid out first. Then the ==0 arm ends with j to call. So yes.

Could we instead make the join block unreachable by fallthrough: put the call in a block that's only reached by jumps. E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
    goto docall;
}
docall: call; return;
```
Both arms jump to docall → cross-jump of unconditional jumps: then-jump vs code before docall = else-jump. backward: i1=branch, i2=branch equal → merge again. Same.

Hmm.

What if the call block is placed BEFORE the arms? Not with source order.

What if we split the join: then arm jumps to call1, else arm jumps to call2, and cross-jump merges the two calls into one... that's what the target has (one call). Cross-jump of unconditional jumps would merge branch tails again.

OK, think about breaking rtx_renumbered_equal_p on the branches. The branch pattern includes the label_ref to skip. If the two branches target DIFFERENT labels (both eventually skip), the patterns differ. So: use two separate skip labels that GCC does not merge. We can force two labels if there is code between them that prevents the jump optimizer from merging. But the skip code is shared...

What if one arm jumps to `skip` and the other jumps to `skip2` where `skip2:` is a label immediately before `skip:`? Jump optimization merges adjacent labels. But if skip2 is placed elsewhere, e.g. after the skip code with a jump back? That adds insns.

Hmm, what about making the branch in one arm target the join directly? E.g. then arm: `if (d >= 0x51) goto skip;` else arm: `if (d >= 0x201) goto skip;` — same label.

Let me look at other cracked examples in moves.md for barrier: e.g. "barrier | func_801564B0 | MATCH — ||-fold of the two return-0 tests". And "barrier | func_801835B0 | MATCH — goto loop". "barrier | func_8017E180 | MATCH — arr reads as member arr[k].v[0] (de-cast)". These are cases where the barrier was a volatile that changed RTL and the crack changed C structure.

Maybe for this one, the trick is to make the then arm's branch a different RTL by *reordering the condition*: e.g. `if (0x51 > d) goto docall;` no.

Wait, maybe we can make one arm's comparison produce the branch via a *different* instruction sequence that is code-identical: e.g. `slti v0,v1,81` vs `slti v0,v1,81` — can't differ.

Alternatively make the then arm's branch use `blez`/`bgez` forms: `if (d - 0x51 >= 0) goto skip;` compiles to `addiu v0,v1,-0x51; bgez v0,skip`? That's 2 insns vs 1. Not target.

Hmm, what about a `do { } while(0)` around the then body? C0535: do-while splits cse1 EBB. Would it create a label between branch and jump? A do-while(0) with no body might be optimized away.

What about making the then arm's body contain a *label used by a later goto* — e.g. the skip label is reached by both gotos; if we give one goto its own label:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip1;
    ...
} else {
    if (d >= 0x201) goto skip2;
}
...
skip1:
skip2:
```
Adjacent labels merge.

Alternatively place `skip2` after the skip body but jump back? adds insns.

Hmm hold on. Let me reconsider the merge mechanics with minimum=1: the unconditional-jump cross-jump finds the then-jump and the join label; compares the code before each. The then arm's branch matches the else arm's branch. One matched insn suffices. But note: `if (GET_CODE (i1) == CODE_LABEL) { --minimum; break; }`. What if the then arm has a label between? That's the code-label idea.

Could a real C construct create a CODE_LABEL there? A label that's used by a goto elsewhere but whose block is empty. E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
docall:
    func_801822A4(...);
    return;
```
Here docall label is before the call. In the then arm's RTL: branch 413, jump 423 (to docall). The label docall is elsewhere.

What if we add a label at the end of the then arm that is the target of a goto from somewhere that gets optimized... 

Alternatively: what about `if (d >= 0x51) goto skip; else { }` — the else empty block might create a label? no.

Let's try a different approach: use a switch statement for the inner dispatch. `switch (unk70) { case 0: if (d>=0x51) goto skip; break; default: if (d>=0x201) goto skip; break; }` — switch on 0/default generates a compare + branch, maybe different layout. Target's outer test is `lh; bnez v0,else`, i.e. a simple compare with 0 — a switch with case 0/default compiles exactly to that (bnez). And the structure might leave different RTL for the tails! Worth trying.

But first, let me test the simplest thing: does a label in the then arm prevent the merge? I can test with a variant where I add a used label. E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
docall: ...
```
already tried (v1) — the label is at docall, not between branch and jump.

What about:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    ;
    goto docall;
} else {
    ...
}
```
An empty statement produces nothing.

What about a label that is targeted from the else arm? Like the else arm's skip goto targets a label inside the then arm? no.

Hmm, let me look at how the actual original source might have been. Perhaps the target was produced by GCC from a source with the barrier... The item was created by a previous coder who needed the barrier; the "true" source likely had something else. But our job is just to find a lever-free body that scores 0.

Let me try the switch idea and a few others in a batch.

Variant ideas:
A) switch(unk70) with case 0/default.
B) then arm: `if (d >= 0x51) goto skip;` but the else arm's test uses a different variable/type.
C) `if (d < 0x51) { call; return; } else if (unk70 != 0) { if (d>=0x201) goto skip; }` — restructure.

Let me first try switch.
