---
ts: 2026-11-06T14:52:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pvc0xlPfB9gTObc1GGS2
---
The cse dumps differ only by numbering (and the "sets" counts differ by 1 due to the asm). So cse1 did NOT fold the branch either! The structure is the same.

So where does the fold happen? The jump_insn counts: rtl 72, cse 62, cse2 62, jump 62, jump2 58. Same for both. So the fold (beq vs bne) happens... hmm.

Wait, maybe the fold happens in the FINAL assembly (the assembler's branch relaxation or reorg)? Or maybe my normalized diff missed it.

Let me directly compare the cse2 dumps for the case 5 region. Let me find the `const_int 5` comparison and the following branches in both.

Actually, the jump_insn counts are identical, and the normalized diffs show only numbering. So the RTL is structurally identical (modulo the asm). Yet the final asm differs in the branch structure. So the difference is introduced in a LATER pass: combine, sched, reload, sched2, or reorg.

Hmm, but combine doesn't change branches much. Let me check the .dbr (post-reorg) dump structure. Let me diff the .dbr dumps normalized. If they differ structurally, reorg did it.

Actually, wait — the .jump2 dump (after reload) has 58 jump_insns. Let me diff the .jump2 dumps normalized.

Let me do that.
