---
ts: 2026-11-06T16:34:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2w0UDfHBMR4w3GXdn81A
---
At jump1 (before jump2), v1 already has:
```
insn 412 slti 81
jump_insn 421 -> label 440 (unconditional jump!)
barrier
label 426
insn 430 slti 513
jump_insn 431 branch_zero -> 452
```
Wait, in v1 the then arm's beqz is already gone at jump1: insn 412 slti; 421 unconditional jump to 440. And 440 is the join (call). So the then arm's branch was eliminated at jump1 (the first jump_optimize pass) by cross-jump? Actually jump1 does cross-jump too. So the merge happened in the first jump pass.

In v0 (asm), the then arm retains: slti 412; branch_zero 413; asm 421; jump 423 -> 438.

So the asm prevents the first jump pass's cross-jump. That pass is before reload. The condition: the two branches match; without asm they merge.

Since both branches are identical, we need a real difference. Hmm.

Idea: Make the two comparisons non-identical at RTL while emitting the same instruction: the compare insns are `slti v0,v1,81` and `slti v0,v1,513`. They differ anyway. The merge matches the branch (label_ref skip) which is identical. With minimum 2 and a matched jump... Let's understand how the merge works here: e1 = the then arm's last insn, e2 = the else arm's last insn? For the then arm, the block ends with branch 413; the else arm ends with branch 430. They compare backward: branch vs branch equal (min 2→1), then slti vs slti differ (break, min=1 >0 → no merge). But the merge DID happen. Unless the blocks compared are the then arm (ending at branch 413) and the *join block*... 

Hold on, in v0 the then block ends [branch 413, asm 421, jump 423]. Why is there a jump 423 at all if the asm is there? Because the then arm's fallthrough after the branch goes to the asm then jump to join 438. And the else arm falls through to 438. So e1 = jump 423 (then arm's last insn), e2 = ? The join block's last? Cross-jump called at 1941/1978/1993/2024.

Without asm, the then block ends [branch 413, jump 423] where 423 jumps to the join. Backward compare e1=jump 423 with e2 = the else arm's block ending at branch 430: jump vs branch differ → break min=2 → no merge. Still no merge predicted, yet merge happened.

So maybe the merge is "jump-around-jump": at jump.c:1978 find_cross_jump(insn, JUMP_LABEL(insn), 1, ...). Hmm. Or the optimization that removed the branch is not cross-jump but jump threading: since the then arm's branch target is `skip` and the fallthrough is a jump to join... 

Wait, actually look at v1 jump1: `jump_insn 421 -> label 440`. The then arm's slti 412 is DEAD after? No, `(expr_list:REG_DEAD (reg/v:SI 3 v1)...)`.

Hmm, actually maybe in v1 the merge produced: then arm [slti 81, jump 440]; and the shared beqz branch at the else arm uses v0. That means the branch on v0 got moved to the join. This is cross-jump merging the two branches AND the tails: the then arm's block [slti, branch skip, jump join] vs the else arm's [slti, branch skip, (fall to) join]. The common suffix is [branch skip, jump join]? No, the else arm doesn't have a jump.

Hmm, but cross-jump can match the then arm's [jump join] with the else's fallthrough... no, cross-jump compares insns.

Let me just look at the full v1 jump1 function section around that.
