---
ts: 2026-11-06T16:39:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qKqATe6tzRPXG3q4hliW
---
Same merge; do-while vanished.

Let me think about a label that definitely survives: the target's own code has `skip` label. What if the then arm's branch targets a label that is NOT skip but a new label `skip_t` placed just before the skip label, and the skip label is used by the else arm. Then the branch LABEL_REFs differ but point to labels in adjacent positions: next_real_insn(label1) == next_real_insn(label2) → equal per rtx_renumbered_equal_p. So still merge.

Unless there's a real insn between skip_t and skip. Then the emitted stream differs from target.

Hmm. What if we can make the then arm's branch a *different* jump insn but the same emitted instruction? E.g. the MIPS branch_zero pattern has variants: `branch_zero` and `branch_zero2`? There might be an insn for `bne` vs `beq` with a nop delay. Same.

Let me look at the target's with-asm jump2 shape once more: then arm [slti 412, branch 413, asm 421, jump 423->join]. The cross-jump of the unconditional jump 423 compares code before 423 (i1 = asm) with code before join label 438 (i2 = branch 430). GET_CODE differ → break; minimum=1; last1=0 → no merge. 

So any non-emitting insn works. Could a `(use)` insn be produced by C? Actually, there's one classic: a `__volatile__` asm... forbidden. What about a `volatile` *memory* access to an unused variable? emits.

What about taking the address of a label? GNU C `&&label` — creates a label ref, and the label is kept (address taken). E.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    if (0) goto endthen;  /* dead */
endthen:
    ;
}
```
If we take the label's address: `void *p = &&endthen;` — but that emits an insn (lui/addiu of the label). Unless unused and optimized away... but then the label is deleted.

Hmm, what about `goto *p`? no.

What about a label inside a statement expression `({ ... })`? GCC extension, might not be allowed by style.

OK, another angle entirely: change the *else* arm so its last insn before the join is not a branch identical to the then's. E.g. give the else arm two tests:

Target else arm: `beqz v0,2bc8` with slti 513 in the bnez delay slot. If we make the else arm's test structurally different, we'd change insns.

Wait — actually, look at the target again. The slti 513 is in the delay slot of the bnez. The delay slot filler (dbr) put it there. In the RTL at jump2, the else arm is [slti 513, branch]. Fine.

What if we make the else arm's comparison a `slti` that's placed AFTER the branch in RTL? no.

Hmm, let me reconsider the possibility that the target's layout comes from a different source structure that avoids the unconditional-jump cross-jump because the then arm's jump targets something whose preceding code is not the else arm's branch. 

What if the call is not in a join block after the else arm but is duplicated and the *skip* label is the join? Let's imagine:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    call; return;
} else {
    if (d >= 0x201) goto skip;
    call; return;
}
skip: ...
```
Layout: then arm [slti; branch skip; move; call; jump epilogue]; else arm [slti; branch skip; move; call; jump epilogue]; skip. Cross-jump would merge the two call tails: then arm becomes [slti; branch skip; jump sharedcall]; else [slti; branch skip; fall sharedcall]; sharedcall [move; call; j epilogue]; skip after. That's exactly target's layout! And the cross-jump that merges the calls is the unconditional-jump cross-jump of the then arm's `j epilogue`? No wait, the shared call block ends with `j epilogue`. Hmm, the merge of the call+return tails: both blocks end with [move; call; jump epilogue]. find_cross_jump on the unconditional jump `j epilogue` (simplejump): find_cross_jump(insn=j, JUMP_LABEL(j)=epilogue, 1): compares code before the j in the then arm with code before the epilogue label... The epilogue label's preceding insn is the else arm's j (also to epilogue). Hmm.

We tried v3 which is exactly this (duplicated call with return), and got score 9 (merged). So cross-jump merged the branches instead.

Hmm, but maybe order matters: in v3 the call was `func_801822A4(param_1); return;` and the merge result was the same.

Let me look at v3's diff more carefully — maybe it merged the calls AND the branches differently. It gave the same 197.

What if we duplicate the call but with slightly different argument spellings so the call blocks differ in RTL (e.g. one uses `(void *)param_1` and the other a `void *p = (void *)param_1; f(p);`)? The call insn RTL would be the same after CSE... but cse might not equate them if spelled differently, and cross-jump's rtx_renumbered_equal_p on the call compares CALL_INSN_FUNCTION_USAGE too. If the arg copy uses a different pseudo, after reload same reg.

Hmm.

Let me approach from the "4 instructions" clue: target has 4 more insns: `beqz; nop; j; nop`? The diff said insert mine[172:172] target[172:176] = 4 insns: beqz, nop, j, nop. So mine is missing a beqz+j pair (plus delay nops). The target's then arm has its own beqz+j; mine merged it.

What if I make the two comparisons use different *widths* so the branches differ? e.g. then arm tests `(u16)d >= 0x51`? That adds an andi. no.

What if the then arm's comparison is done on a copy in a different variable that after register allocation lands in v1 (the branch would be beqz v1)? Target shows beqz v0 both. no.

OK here's another idea: maybe we can prevent the unconditional-jump cross-jump by making the then arm's jump NOT a simple jump but a conditional one. The target's then arm ends `j 2bb8`. In RTL it's a simplejump. If the then arm's fallthrough path were conditional... no.

What about making the then arm's block end with the branch as the last insn (no jump), i.e. the then arm's fallthrough goes to the call. For that, the call must come right after the then arm in layout. Then the else arm must be elsewhere — e.g. after the skip code. Layout: then arm [slti; branch skip; call...] then skip code, then else arm somewhere. But target has else arm before call.

I keep coming back to needing a non-emitting RTL insn. Let's brainstorm what C produces a `(use)`/`(clobber)`/`(asm_input)`:
- `asm` (forbidden).
- A call to a builtin that expands to nothing? e.g. `__builtin_constant_p`? In GCC 2.7.2, `__builtin_constant_p` folds to a constant, no RTL.
- A `volatile` cast? no.
- `alloca(0)`? emits.
- A `(use)` insn arises from asm operands, or from `__builtin_apply`? 

Hmm, what about an inline function? no.

What about the `// !FAKE: do-while` marker with a do-while that has a *label*: `do { ... } while (0)` — the loop end label might survive as CODE_LABEL if the loop is marked. In v5 it didn't. But maybe with `break`/`continue`? e.g.

```
do {
    if (d >= 0x51) goto skip;
    break;
} while (1);
```
Hmm, do-while(1) with break: loop.c may convert. 

Alternatively use a `while (0)` loop: `while (0) { if (d>=0x51) goto skip; }` — the body is dead code, removed. But `while (0)` with a goto inside: the goto is dead → removed.

What about `if (d >= 0x51) goto skip; else { }` plus a label from an `else` block? Empty else block might leave a label? Usually deleted.

What about a `switch (d) { default: if (d>=0x51) goto skip; }`? The switch adds a jump table or compare. no.

Hmm, let me reconsider: maybe the barrier's role isn't the asm insn but the *volatile* nature: `__asm__ __volatile__("")` — a volatile asm is a `(set (mem:BLK ...) (unspec_volatile))`? No, an empty asm string produces `(asm_input ("")` as seen. But maybe if it's `volatile`, GCC treats it as having side effects and won't delete; also it may prevent certain optimizations like cse/combine but the dump shows asm_input.

The dump v0.jump2 shows `(insn 421 (asm_input ("")))` between the branch and the jump. So the asm insn is the only difference. Right.

So we need a non-emitting insn. Alternatively we can prevent the *jump* from existing: what if the then arm's code after the branch is not a jump but a call? Then the call would be duplicated and merged... 

Actually wait! What if the call is INSIDE the then arm, and the else arm's path jumps to the then arm's call? Consider:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
    goto docall;
}
docall: call;
```
Both arms jump. Cross-jump of unconditional jumps: then-jump (to docall) vs else-jump (to docall). find_cross_jump(insn=then-jump, JUMP_LABEL=docall, 1): code before then-jump = branch skip; code before docall = else-jump. Branch vs jump differ → break, minimum=1, last1=0 → no merge. Then the second loop "Try each other jump to this label": find_cross_jump(insn, target=else-jump, 2): i1 = prev_nonnote(insn) = branch skip; i2 = PREV_INSN(else-jump) skipping notes/labels = branch skip → equal (min 2→1); i1 = slti 81, i2 = slti 513 differ → break min=1 >0 → no merge. Hmm, but minimum is 2 there. So no merge! 

Then the layout: both arms jump to docall which is after the else arm. The then arm: slti 81; beqz skip; j docall. Else arm: slti 513; beqz skip; j docall. But target's else arm FALLS INTO the call (no j at 2bb4). If the else arm has a jump too, we'd get an extra j+nop = 2 extra insns vs target. Hmm, but wait: the else arm's `goto docall` where docall immediately follows → GCC turns it into fallthrough, no jump. Yes! The else arm's goto docall is a jump to the immediately-following label → becomes fallthrough. And the then arm's goto docall must jump over the else arm.

But that's exactly the v1 goto-docall variant I tried (only the then arm had goto docall; the else fell through). It gave 9. Because cross-jump of the then arm's jump matched [branch] with the else's [branch] and merged.

If BOTH arms have `goto docall`, then the cross-jump's "try each other jump to this label" comparison needs 2 matched insns (minimum 2), and the slti differ → no merge. But the else arm's goto is converted to fallthrough at jump1 (jump to next insn), leaving only the then arm's jump → back to the v1 case with minimum 1. Hmm.

Unless we make the else arm's goto NOT immediately next: put something between the else arm's end and docall? That something would be an insn.

Hmm, what if the else arm jumps to a label that is followed by a *barrier*... no.

What if we have THREE arms: then arm goto docall, else arm goto docall2, and docall2: docall: call; with docall2 a distinct label. The else arm's goto docall2 becomes fallthrough if docall2 is the next insn. If we put a label docall (unused?) no.

Alternatively, make the else arm's last insn a jump to a *different* label docall2 that is NOT immediately after (e.g., after some skip code), then a jump back? adds insns.

Let's think about the second loop in the unconditional cross-jump: "Try each other jump to this label. target = jump_chain[JUMP_LABEL]" — it compares the then-jump with other jumps to the same label. If the else arm also has a jump to docall that wasn't converted to fallthrough... but it will be converted.

What if the else arm's goto targets a different label docall2 that sits at the same position as docall (adjacent labels)? Then next_real_insn equal; find_cross_jump(insn=then-jump, JUMP_LABEL(insn)=docall, 1) — code before docall is the else-jump to docall2, still a jump, differs from branch → no merge (minimum 1). Then the jump_chain loop compares then-jump with the else-jump to docall2 (different label, so not in jump_chain for docall). So no merge! And the else-jump to docall2 is immediately followed by docall2 label → fallthrough conversion? The jump to docall2 where docall2 is the next label: jump1 would remove it and make it fallthrough, but the label docall2 might remain (used by the jump). After removing the jump, the label becomes unused and deleted.

Hmm. This is getting intricate. Let me just try the both-arms-goto variant and see what happens.

Actually, better: let's try to make the else arm's jump survive as a real jump by making docall NOT immediately after the else arm: put the skip code between the else arm and docall? Layout would change.

Alternatively, exploit the "jump to next insn" removal: if the else arm's goto is to docall and docall is next, it's removed. But if we insert a *label* between? no.

Hmm hold on — maybe there's a much simpler C-level way to break the branch match: make the two comparisons produce branches on *different* comparison codes. The MIPS branch_zero pattern is chosen by the condition. For `if (d >= 0x51) goto skip;` we get `slti v0,v1,81` then `beqz`. What if instead the else arm is `if (d < 0x201) { } else goto skip;`? GCC might generate `slti v0,v1,513` then `bnez v0, L` (branch to the empty then block) with the skip fallthrough... but then the block structure changes: the else arm would be laid out with the branch to the empty body. Hmm.

Actually, maybe the cleanest: make the then arm's branch be a `bnez` (branch-if-true) to the *call* instead of a beqz to skip, which is the v3 form. But target has beqz to skip.

Let me look at the actual target once more:
```
2b9c: slti v0,v1,81
2ba0: beqz v0,2bc8
2ba8: j 2bb8
2bb0: beqz v0,2bc8
```
Both beqz to skip.

OK let me try the "both arms goto docall" experiment and check.
