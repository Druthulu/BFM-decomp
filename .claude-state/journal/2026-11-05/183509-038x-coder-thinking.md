---
ts: 2026-11-06T01:35:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s6KXNMnWcpwtn2ZWF9en
---
So jump2 has cross_jump=1, after_regscan=1. And the earlier passes at 2827/2870/2923/2929 pass cross_jump=0! Only the final post-reload pass cross-jumps. So the merge is post-reload, registers hard.

So at jump2, both stores are `(set (mem (plus (reg s0) 28)) (reg v0))`. Identical. Target keeps them separate, so something else differs: maybe the target's epilogue label preceding insn at jump2 isn't the sw, because the zero block's `sw` at 1808 is followed by... Actually wait: maybe in the target, the label at 180c is preceded by a NOTE? Notes are skipped. Hmm.

Alternatively, maybe in the target dec's jump is not a "simplejump_p" — it is `j 180c`. simplejump_p requires the jump's pattern be a set of pc to a label_ref. Yes.

Hold on, maybe the target's sw at 1808 and dec's sw at 17cc are NOT both `sw v0,28(s0)` at jump2 time; the register allocation might differ at jump2 from final? No, reload is done; regs fixed.

Unless... the store at 1808 in target is actually `sw v0,28(s0)` and the one in dec's delay slot at 17cc is `sw v0,28(s0)`, identical. So why no merge?

Maybe because the *previous* insn compared also matters: find_cross_jump starts with i1 = prev_nonnote_insn(e1) where e1 = the jump insn. At jump2 (before reorg), dec's insn sequence is: lw; nop; addiu; sw; j; (empty delay). prev_nonnote(jump) = sw. i2 = prev of label = zero's sw. Match. Then loop continues: i1 = prev_nonnote(sw) = addiu; i2 = prev of zero's sw = sh zero,244. Different → break. Then the code checks `if (i1 == 0) break;` etc. Then after the loop, minimum check. Since one side falls through into the label, minimum decremented? Let's read the code after the loop to see the minimum logic.

Actually the decrement happens inside: "If we will get to this code by jumping, those jumps will be tensioned... reduce the minimum" when i1 is a CODE_LABEL. Hmm.

Let me read 2520-2600 to see how minimum is used.
