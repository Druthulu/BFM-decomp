---
ts: 2026-11-06T20:18:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vvx8lw56mmWXUcCGIS59
---
Key: `REGNO (SET_DEST) < FIRST_PSEUDO_REGISTER` → live_insn = 1. So a set to a HARD register is never deleted. So `pv = 0;` at the end → `li $3,0` survives (1 extra insn).

But note: "delete insns that ... copy a register to itself" — `SET_DEST == SET_SRC` (same rtx) is deleted regardless of hard/pseudo. So `pv = pv;` (a self-move to the same hard reg) would be deleted by delete_dead_from_cse. But if deleted, reg_n_sets at sched1 wouldn't include it.

Hmm, but wait: the launder asm is `asm("" : "=r"(pv))` — an asm with an output operand. It's a SET in RTL? asm with output is a SET of the output reg to an unspecified value (usually `(set (reg) (asm_operands))`). Not a self-copy.

So we need a set of $3 to something that is (a) not a self-copy, (b) not deletable, (c) emits no instruction. Impossible in plain C: any set of a hard reg to a different value emits an insn.

UNLESS the set is dead *at the end* but survives because the dest is a hard reg... it survives WITH an instruction.

Hmm, so maybe there's another route: prevent the birthing boost by making $3 live at block entry differently, or by changing the pseudo structure.

Wait, actually re-read birthing_insn_p: `if (bb_live_regs[offset] & bit) return (reg_n_sets[i] == 1);`. bb_live_regs is the live set at the start of the basic block. $3 (=v1) is a call-clobbered temp; is it live at block entry? The block here is the tail block after the last call (func_80016638 is after; the tail block starts after the last RotMatrixZ/ApplyMatrixSV calls?). The tail block (from the last ApplyMatrixSV) — at its entry, $3 might be live because... hmm.

Alternatively `reg_n_sets[3] == 1` — if $3 is set earlier in the function (e.g., by the earlier calls' returns or other code), reg_n_sets[3] > 1. Since $3 is used as a scratch throughout, reg_n_sets[3] is probably > 1 already... unless reg_n_sets counts only... Hmm, but empirically the launder changes the schedule, so reg_n_sets[3] must be 1 before.

Wait — maybe reg_n_sets is per pseudo, and hard regs aren't counted. Let me check reg_scan: it counts REG_N_SETS for regs >= FIRST_PSEUDO_REGISTER only? Let me check reg_scan_mark_refs.
