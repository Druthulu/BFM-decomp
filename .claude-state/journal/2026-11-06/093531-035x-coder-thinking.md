---
ts: 2026-11-06T16:35:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XblKVPPICNmKmXcWKl4Z
---
Wait, this v1 is from the earlier `goto docall` variant? No — v1.fn.jump is from the dump of the TU in dumptu, which at that time was... I dumped v1 right after generating v1 (goto docall) — yes the dumptu t.c was the v1 candidate. Hmm, then later I overwrote dumptu with orig for v0. So v1.fn.jump is the goto-docall variant.

Interesting: in v1 jump1, the then arm retains its branch 413! and has jump 421 -> 440 (docall). And the else arm 430/431. So at jump1 there's no merge; the merge happens at jump2. In v1 jump2 (shown earlier), the then arm became [slti, jump->523] with the branch gone and shared.

So the merge is at the second jump pass (jump2, after reload). Post-reload, the branch insns have hard regs; cross-jump compares patterns.

OK so what can differ post-reload? In v1 (goto docall), jump1 shape: then [slti 81; branch_zero -> skip; jump docall], else [slti 513; branch_zero -> skip; fall to docall]. At jump2, cross-jump matched the then arm's branch (413) with the else's branch (431) and the call tail, merging. To prevent: make the then arm's tail differ from the else's. In the target (with asm), the then arm's last insn is jump to join, and the asm sits before it; cross-jump comparing e1 = jump 423 vs e2 = ... prevented.

Wait, in v0 jump2 (post-reload), the shape is: then [slti; branch skip; asm; jump join]. So the asm is between the branch and the jump. Without the asm, jump2 shape is then [slti; branch skip; jump join]. Cross-jump then matched branch+... 

Hmm, why would the presence of an asm change whether the branch matches? Because cross-jump's backward scan from e1 (the then arm's last insn, the jump to join) vs e2 (else arm's last insn, the branch). Wait no — the asm isn't the last insn; the jump is. So e1 = jump 423 in both cases.

Unless without the asm, the first jump pass (jump1) removed the then arm's jump to join by... no, v1 jump1 shows the jump still there.

Hmm, but v1 jump1 was the goto-docall variant, not the plain no-asm variant. The plain no-asm variant (win.c) — I didn't dump it. In win.c (no goto), the source is `if (d>=0x51) goto skip;` inside then, call after if. At jump1, the then block would be [slti; branch skip] and the join after else. There's no explicit jump in the then block (fallthrough to else arm? no, the then block falls to... hmm).

I'm going too deep. Practical: the merge is at jump2 (post-reload). Cross-jump matches hard-register patterns. Let me try to make the two arms' post-reload branch patterns differ via C, keeping instructions identical.

Post-reload branch: `(if_then_else (ne (reg:SI 2 v0) (const_int 0)) (pc) (label_ref skip))` — identical for both.

Idea: make one arm branch on a different register! E.g. in the else arm, make the comparison result land in a different register (v1) by using a different expression order: `if (0x201 <= d)`. Still v0.

Or: in one arm use a comparison that the machine emits as `slti v0` but with the operands swapped: `if (0x51 > d) goto skip;`? Hmm — `d >= 0x51` → slt d,0x51 then beqz; `0x51 <= d` → slt 0x51,d then bnez? Not same.

What if the then arm's condition is `if (d - 0x51 >= 0)` → addiu+bltz — different insns.

OK, different angle: maybe we don't need to prevent the merge at all. Maybe the intended crack is to accept the merge but compensate by making the *rest* of the function differ... no, score 9 vs target 201 ins means the target has 4 extra insns in that region; we must reproduce them.

Another angle: make the else arm not share the same skip label. If the two arms `goto skip` to different labels, cross-jump can't match the branch pattern (label refs differ) — but GCC will merge identical labels at jump1. Unless the labels are separated by code that prevents merging. Hmm.

Alternative: make the else arm's branch target the skip label via an intermediate label with a real instruction between? No.

What about avoiding the shared skip: restructure as:

```
if (d <= 0) {...}
else if ((...&1)==0) {
    if (unk70 == 0) {
        if (d >= 0x51) goto skip;
    } else {
        if (d >= 0x201) goto skip;
    }
    func_801822A4(param_1);
    return;
}
skip: ...
```
same.

Hmm, maybe the target's RTL differs because the then arm's compare insn is in a different position: the target's slti 81 at 2b9c comes AFTER the bnez (in the fallthrough), and the slti 513 sits in the delay slot of bnez. Both as expected.

Let's reconsider: maybe the target's then arm's branch is `beqz v0,2bc8` — i.e. branch when NOT(d<81). Mine's merged branch at 2ba0 is also `beqz v0,2bb8` branching to skip. Same insn.

So the only difference is the merge; we need RTL difference. Since both C arms must be identical RTL for cross-jump to merge... What if we make the two comparisons use different C types that still emit slti? For example, else arm: `if (d >= 0x201)` where d is s32. Then arm: `if ((s32)(s16)(d) >= 0x51)`? d is computed as `CAST_WIDTH(s16, param_1, 0xDC) - D_801C7748` which is s32 already sign-extended. A cast to s16 could add sll/sra — extra insns (not in target).

What if the then arm's comparison uses an unsigned constant comparison with a variable? e.g. `if ((u32)d >= 0x51u)` → sltiu v0,v1,0x51; beqz. Emits `sltiu` — target has `slti`. No.

What if one arm's compare is `if (d > 0x50)` → slti v0,v1,0x51? `d > 0x50` = `d >= 0x51` → same slti. RTL: `(lt (reg) (const_int 81))` same. No difference.

Hmm. What about making the two arms' branches target skip from different *blocks*, so the label_ref numbers differ but rtx_renumbered_equal_p treats them equal anyway (renumbered equal ignores register numbers, but labels? `rtx_renumbered_equal_p` — it compares label refs by label number? Let me check. If it compares LABEL_REF by pointer, then two branches to the same label are equal. Both branch to the same skip label → equal.

If we could make them branch to different labels that both lead to skip: e.g. `goto skip1` / `goto skip2`, with skip1 and skip2 being distinct labels. At jump1, jump optimization may merge them. But maybe if we place a statement between them... The skip code must be shared.

Idea: `skip2:` label placed after the then arm? No.

Alternative: make the then arm's branch a `bnez` to a label that jumps to skip, i.e. invert:
then arm: `if (d < 0x51) goto docall;` — hmm we tried v3 which has `if (d < 0x51) { call; return; }`. That produced `bnez v0,docall`? In v3 the emitted branch at 2ba0 was `beqz` shared.

Hmm, let me try writing the then arm as: `if (d < 0x51) { } else { goto skip; }`. Ugly but real C. RTL: branch if d<0x51 taken (to the empty then), else goto skip → post-reload: slti 81; bnez v0, skip? no: `if (d < 0x51) {} else goto skip;` compiles to `slti; beqz v0, skip` (branch when false). Same.

What about using a `while` or `do{}while(0)`? C0535: do-while splits cse1 EBB. But the merge is at jump2 cross-jump.

Think about what would make the then block's tail differ: the target's then block has an unconditional jump to the call block. That's the goto-docall variant, which at jump1 kept the jump. At jump2, cross-jump merged. If the then arm's jump is to the *call* block while the else falls through, cross-jump's backward compare starts at e1 = the then block's last insn (jump to call) and e2 = the else block's last insn? For the merge to match, it must find [branch skip] common. It can because the jump is skipped in the backward scan? Look at find_cross_jump: `i1 = prev_nonnote_insn(i1)` where i1 starts at e1. e1 is the last insn of block 1. If e1 is the jump to call, then i1 = branch skip (prev nonnote). i2 starts at e2 (the else block's last insn = branch skip) and moves back skipping notes/labels. So i1=branch, i2=branch → match! Then i1 = slti 81, i2 = slti 513 → differ → break with minimum=1 (started 2, decremented once) → minimum>0, no merge.

But minimum also gets decremented by jump-around-jump: `if (GET_CODE(i1)==JUMP_INSN && JUMP_LABEL(i1) && prev_real_insn(JUMP_LABEL(i1)) == e1) --minimum;` — at the mismatch break. Here i1 is the branch (a JUMP_INSN) with label = skip; prev_real_insn(skip) == e1? e1 is the jump to call, not the insn before skip. No.

Hmm, so minimum should be 1 and no merge. But merge happened. Unless e1/e2 are chosen differently, e.g. find_cross_jump(insn, target, 2) where e1 is a label or something.

Let me actually read jump.c around 1941-2030 to see how it's called and what e1/e2 are.
