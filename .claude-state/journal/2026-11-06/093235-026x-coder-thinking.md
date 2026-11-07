---
ts: 2026-11-06T16:32:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mQIGltxGkoS4Nr4FYHiq
---
This is v1's jump2 (before dbr). Look:

```
408: bnez v0 -> 426 (else arm)
412: slti v0,v1,81
421: jump -> 523    (unconditional jump!)
...
426: label
430: slti v0,v1,513
523: label
431: beqz v0 -> 452 (branch_zero with if_then_else (ne) (pc) (label)) -- i.e. bnez to skip? target...
443: a0=s3
445: call
```

Wait, interesting: 421 unconditional jump to 523 — that's then-arm jumping over the else arm to 523 which precedes the beqz! Hmm, then 523 label then insn 431 beqz->452. So the then arm jumps to 523, then executes the shared beqz (the else arm's compare test!). Wait 430 is slti 513, and label 523 is after 430, before 431. So the shared tail is insn 431 (branch on v0 which holds... then-arm's v0 = slti 81? No: then-arm jumps from 421 to 523; v0 was set by 412 slti 81. Else arm sets v0 = slti 513 then falls into 523 → 431. So the beqz at 431 branches to skip when v0==0. For then arm: v0 = (d<81); branch skip when !(d<81) i.e. d>=81. For else: v0=(d<513), branch skip when d>=513. Clever cross-jump merge: it merged the beqz and the call tail, making then arm jump into the middle. That's exactly the merge.

Target keeps them separate: then arm `slti 81; beqz skip; j call` and else `slti 513; beqz skip; call`.

So the merge in mine is: the beqz at 431 is shared, and the then arm's unconditional jump 421 jumps to 523 to reach it. This is the "jump-around-jump" reduction (minimum reduced because i1 is a jump whose label is just before e1). In find_cross_jump, `if (GET_CODE (i1) == JUMP_INSN && JUMP_LABEL(i1) && prev_real_insn(JUMP_LABEL(i1)) == e1) --minimum;`. Here e1 is the then-arm's jump (421) — wait no. Let me identify the two blocks being compared: e1 and e2.

At jump.c:1993 or 2024 find_cross_jump(insn, target, 2, ...). The merge joined the two arms' tails.

Anyway, to stop it we need the arms' tails not equal. The asm added an insn in the then arm (asm input) which made the then arm longer and the tails differ.

Real-C alternatives that add RTL but no instruction: A zero-byte asm is the classic. What other C produces RTL that doesn't emit? A `(void)0`? no RTL. A cast to void of an expression? The expression still evaluated. A `use`? A volatile? Hmm.

What about making the two arms structurally different such that cross-jump can't match but instructions stay identical. For instance, in the then arm compute the comparison into a different register/order: e.g. write `if (d >= 0x51) goto skip;` versus `if (d - 0x51 >= 0) goto skip;` — the latter compiles to different insns (addiu + bgez?) not matching.

Or invert the else test: `if (!(d < 0x201)) goto skip;` → same RTL basically.

What about the then arm using an `unsigned` comparison `if ((u32)d >= 0x51)` → sltiu? emits sltiu instead of slti — instruction differs → won't match target.

Hmm. What about swapping the arm order? `if (unk70 != 0) { if (d >= 0x201) goto skip; } else { if (d >= 0x51) goto skip; }` — this reverses which arm comes first. Then layout: else-arm? Let's see what target needs: then (unk70==0) arm first with j to call, else arm second falling into call. If we swap source arms, GCC emits unk70!=0 arm first... Then the target layout would change. But maybe cross-jump still merges; the insns order would differ from target (bnez vs beqz first). Target: `lh; bnez v0,else; slti 81 (then)` — bnez to else arm means then arm is fallthrough. If we write `if (unk70 != 0) { ... } else { ... }`, GCC would generate `beqz v0, else` (branch when ==0) and fall through the !=0 arm. Target has bnez to 2bb0, meaning fallthrough is the ==0 arm. So no.

Idea: make the two tails differ by having the then arm's jump destination differ: put the call inside the else arm's block and have the then arm goto it. But GCC threaded it.

What if the call is duplicated and cross-jump merges the call tails differently? Let's think about what target's RTL was. In target, the then arm's tail: slti; beqz skip; j call. The else arm: slti; beqz skip; [fall to] call. The difference is only the then arm's j. That means in the RTL before jump2, the then arm had an unconditional jump at its end while the else arm fell through. That's exactly the source:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;      /* or a statement that ends with a jump */
} else {
    if (d >= 0x201) goto skip;
}
docall: call;
```

But GCC's jump pass removed the goto (threaded it). Why would the asm prevent the removal? The asm was *before* the goto... hmm, in the original with asm:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    __asm__("");     // barrier
} else {
    if (d >= 0x201) goto skip;
}
func_801822A4(param_1);
```
There is no goto; the call is after. With the asm, the then arm's RTL: slti; beqz skip; asm; then fall through (the asm insn is last). Else arm: slti; beqz skip; fall through. Cross-jump compares backward from the end of each block: then arm ends [asm], else ends [beqz...]. Not equal → no merge. Without asm, both end [beqz] → merged.

But target's then arm ends with `j 2bb8` + nop, i.e. jump to the call block! So the with-asm source must have produced: then arm: beqz skip; j call. Hmm, where does that j come from? If cross-jump refused to merge, the layout would be: then arm: slti; beqz skip; asm(nothing); then call. Else arm: slti; beqz skip; then call?? But there's only one call. So the call must be placed after the else arm, and the then arm jumps to it. GCC places it there because the then arm's block has the asm and the call is in a join block... Actually the call is a separate block after the if-else; the then arm falls through to the else arm if not careful.

Right: blocks: B_then (then body), B_else (else body), B_join (call). In target, the order is B_then, B_else, B_join. B_then ends with a jump to B_join (since B_else is between). B_else falls through to B_join. That's the natural layout without cross-jump. With cross-jump (no asm), B_then's `beqz skip` and B_else's `beqz skip` get merged into a new block placed... and then B_then can fall through.

So the asm merely prevented the merge. The target's j comes from the layout, not from source.

So we need to prevent cross-jump merging the two `beqz skip` tails. Since both arms end with the same branch, the merge is legal. To prevent without a barrier: make the two branches' RTL differ. The branch insn pattern is `(if_then_else (ne (reg v0) 0) (label_ref skip) (pc))`. Both identical. The delay slot nop is separate insn? In the jump2 dump above, after each branch there's a note, and the nop is inserted at dbr. So matching backward from the end of the block: the last insn is the branch. Before it, slti (differ) → minimum=1 after matching the branch, so no merge! But merge happened. So the matching must be on something else — the merged block is the branch at 431 shared plus the call tail? Let's look at where the merge happened: in mine, B_then: 412 slti; 421 jump->523. B_else: 430 slti; 431 beqz->452; 443 a0=s3; 445 call; 447 jump epilogue. Hmm 421's target 523 is a label inserted right before 431, which is B_else's branch! So the merge shared the whole tail [431 beqz, 443 move, 445 call, 447 jump] between B_then and B_else. But B_then's own tail was... B_then ended with a jump to B_join (the call). So B_then: [slti 81][jump join]; B_else: [slti 513][beqz skip][move][call][jump epilogue]. Cross-jump found the common suffix [move a0,s3; call; jump] (3+ insns) and merged, then B_then jumps into the merged block at 523, just before the beqz? Hmm, no: the merged block starts at the beqz 431 because B_then jumped to the join label, which is right after the else's slti... Actually the shared part: B_then's tail after the jump is the join block (move, call, jump). B_else falls through from beqz to move, call, jump. So the common suffix [move, call, jump] matched (minimum 2 satisfied: 3 insns). Cross-jump moved the join block to after the else arm and made B_then jump there — that's what it already was. Hmm, but then why the difference in instruction count?

Wait mine (v1) jump2: 421 `jump -> 523`; 523 is a label placed *after* 430 (else slti) and before 431 beqz. That means the shared block includes insn 431 (the beqz)! So the merge matched [beqz 431? no...]. Let me re-read: the then arm's original tail must have been its own beqz-to-skip followed by jump-to-join. The merge matched the then-arm's beqz with the else-arm's beqz (identical pattern, same label 452). Then it also matched the move/call/jump tails? The merged block at 523 contains beqz 431 + move + call + jump. Then arm jumps to 523 (before the beqz) — reusing the else arm's compare value v0! That's why the then arm's slti 81 sets v0 and jumps to 523; 431 branches on v0. And the else arm sets v0=513 and falls into 523.

So the merge included the beqz despite minimum. minimum=2 and matching [jump(447) or...]. Let's count backward from e1=end of then arm (the jump to join?) Hmm.

Anyway the practical question: what real C breaks it? The merge requires the then arm's `beqz skip` and else arm's `beqz skip` to be rtx_renumbered_equal. If the two compares use different structures, e.g. one `slti` + `beqz`, the other `slti` + `beqz` — same. Make one arm test `d` directly differently: e.g. else arm: `if (d >= 0x201) goto skip;` vs then: `if (d >= 0x51) goto skip;` — both slti+beqz.

What if one arm's branch is inverted: then arm `if (d < 0x51) { } else goto skip;` — same.

What about a different but instruction-identical C spelling: then arm `if (d >= 0x51) { goto skip; }` with braces no change.

Alternatively make the join block not reachable by fallthrough from the else arm: e.g., put a `return` in each arm and share... no.

What about changing the *call site* so the shared tail differs: e.g., call `func_801822A4((void *)param_1); return;` vs the target's `j epilogue`. If we instead structure the then arm as an early-return:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    func_801822A4(param_1);
    return;
} else {
    if (d >= 0x201) goto skip;
}
func_801822A4(param_1);
return;
```
Two call sites; cross-jump merges them into one. That yields the same merged result likely.

Hmm, what about making the two arms differ in the *comparison* by using a different constant that's still 0x51? Like `0x33 * ...`? const folding gives 0x51, same.

Different RTL with same insns: `d >= 0x51` vs `0x51 <= d` → same RTL probably.

Could use `if ((u32)(d - 0x51) < ...)`? no.

Key: the compare insn patterns differ only if the comparison op differs. We need an equivalent comparison that emits the same slti. E.g. `if (d + -0x51 >= 0)` → addiu + bgez, no.

Maybe: use `s16` width for one comparison: `if ((s16)d >= 0x51)` → d is already s32 from s16 arithmetic; cast to s16 could produce sign_extend insn (sll/sra) — extra insns.

Hmm. Alternatively, defeat cross-jump by making the else arm not fall through into the join: add `return` in the then arm and let the else fall through? Already.

Let me reconsider: maybe target's source structure is different: perhaps the original code had the call duplicated and cross-jump merged the two calls into one, leaving the then arm's jump. If cross-jump merges the two call tails, it leaves the then arm with a `j` to the merged call block placed after the else arm — exactly target's layout! And mine's merge differs because with the single call after the if, cross-jump merged the branches instead.

Let's test: duplicate the call in both arms:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    func_801822A4(param_1);
    return;
} else {
    if (d >= 0x201) goto skip;
    func_801822A4(param_1);
    return;
}
```
Hmm, but then target has the call once, shared — cross-jump merging the two identical call+return tails gives exactly one call block placed after the else arm, and the then arm jumps to it. That matches target! And it's a real C structure (no lever). Let's try it.

But wait: would cross-jump merge the calls? The two call blocks are identical: [move a0,s3; call; jump epilogue]. Merging them yields: then arm: slti; beqz skip; j merged; else arm: slti; beqz skip; fall to merged. That's exactly target. 

Let's test.
