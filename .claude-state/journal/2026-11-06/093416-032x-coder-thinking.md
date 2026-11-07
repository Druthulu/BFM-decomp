---
ts: 2026-11-06T16:34:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h957C0YXDaCwvDeLHfPg
---
Same merge again. Cross-jump at jump2 merges [slti? no] — the shared block is the beqz + call. Interesting: in v3, then arm = slti 81; branch-if-true to call; false falls to... the else arm? The merge found the common tail.

Fundamental: cross-jump merges the two blocks' common tail. To stop, we need the two blocks' RTL to differ in the last insns. The target's RTL (with asm) shows the then block ends [asm, jump join] vs else [branch]. 

Wait, in v0 (with asm), the then block ends with a jump to the join (438) — because the join label is after the else arm. And the asm was just before that jump, and cross-jump compares [jump 423] vs [branch 430] → differ → no merge. Hmm but if we remove the asm, the then block is [slti, branch, jump 438]. Comparing backward from e1... e1 is what? The merge candidates are blocks ending at the same point. The then block's last insn is jump 438, the else block's last insn is branch 430. Different → no merge. But mine merged anyway. So maybe the asm isn't what prevented the merge; rather, the asm changed the *layout/threading* earlier.

Hmm. Let's look at the .jump (first jump pass) dumps for v0 and v1 to see when the then arm's branch disappears.

Actually, maybe the cross-jump in question is at the first jump pass (jump.c:1941 etc.) and the asm prevented jump optimization threading. Let's grep .jump dumps.
