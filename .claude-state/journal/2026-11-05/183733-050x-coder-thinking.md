---
ts: 2026-11-06T01:37:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b6ojt0Rn8lPIxf9krdJa
---
Now I see: the merged structure at jump2:
- dec jumps to label 383, which is between `sh zero,244` and the final `sw v0,28(s0)`. So zero's block is split: label 383 sits right before the store, i.e., the store is a *shared tail* outside both blocks, and zero's block also falls into label 383.

So the merge happened before jump2? The label 383 was created by do_cross_jump in an earlier pass. But earlier passes had cross_jump=0... unless the pass at 2929 (after cse2, before loop?) also has cross_jump... wait the args: jump_optimize (insns, 0, 0, 0) at 2870 and 2929. The second arg is cross_jump. So 0.

Hmm, but maybe the merge is from `cse2`? No.

Wait, maybe I misread the dump: this is the .jump2 dump which is printed AFTER jump2 runs. So the merge could be from jump2 itself, and the label 383 is created by do_cross_jump. Yes! jump2 ran and merged. That's exactly it.

Now let me confirm the mechanism: e1 = jump_insn 323 (dec's jump to label 383?). Wait, jump 323 already targets 383 which is the created label. At the time of the merge, e1's target was the epilogue label. find_cross_jump(insn=jump 323, JUMP_LABEL=epilogue label, minimum=1). i1 = prev_nonnote_insn(323) = insn 319 (addiu). i2 = prev of epilogue label = ? Before the merge, zero's block: ... insn 364 (li v0,29), insn 361 (sh zero,244), then the store `sw v0,28(s0)`, then the epilogue label. So i2 = the store. Compare addiu (insn 319) vs store → differ. Match length 0. minimum 1 → no merge via first call.

Then the jump_chain loop: other jumps to the same label. zero's block: does it end with a jump to the epilogue? No (falls through). So no other jump. So how did it merge?!

Unless the first call's i1 = prev_nonnote_insn(323) is insn 319? Hmm, but wait, where did the store in dec's block go? In the merged RTL, dec's block has no store. Let me look at the RTL *before* jump2 (the .jump dump, which is the pre-jump2 state? The .jump dump is after the earlier jump_optimize pass; the .jump2 dump after the final). Let me check nopin.i.jump (pre-jump2) tail.

Actually the dumps: -dj = jump (first jump pass), -dJ = jump2. Let me look at .jump.
