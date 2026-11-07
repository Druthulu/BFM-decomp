---
ts: 2026-11-06T16:35:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Z2Xi1Fat6ALGWjQdOYl2
---
Key: tying happens at the andi only if `reg_qty[ureg]` exists (the used reg already has a qty) and `find_regno_note (insn, REG_DEAD, ureg)`.

In w1_r16, the andi's input is reg 77 which has a REG_DEAD at insn 65. And 75 (m) is a pseudo without qty. So it should tie... unless the andi insn code has operand constraints that block it, or `MODES_TIEABLE_P` fails (both SI, fine).

Hmm wait, but maybe reg 77's qty is assigned later? The tie loop processes insns in order; at insn 65, reg 77 has qty (born at insn 53). So it should tie. But the result shows no tie. Let me check the .lreg output AFTER allocation — the lreg dump shows the RTL before allocation? Actually the -dl dump is printed after local-alloc. The RTL still shows pseudos because the lreg dump prints register numbers as pseudos? Let me check the .greg or the final .s to see actual allocation.

Actually the diff already told us: `andi v0,v1,0x8000` — ret(77)=v1, m(75)=v0. So no tie.

Hmm, why? Maybe because `reg_meets_class_p` fails? No.

Wait, maybe the andi pattern `andsi3` operand 0 constraint isn't '=' plain; maybe it's `=r` with an earlyclobber? Let me check mips.md andsi3. Actually in the tie loop, the condition requires `insn_operand_constraint[code][0][0] == '='` and `[0][1] != '&'`. If andsi3's operand 0 constraint is "=d" or similar, fine.

Hmm, but wait: the AND might have been converted from `(and:SI (reg:SI 77) (const_int 32768))`. The andsi3 pattern might be defined with the output and input tied? Let me look.

Actually, hold on. Let me reconsider: maybe the tie DID happen in the natural build (win0) because 74 and 75 tied, and in w1_r16 no tie because reg 77's qty was already *allocated* by then? The tie loop runs during the same scan as birth/death computation, before allocation. Hmm.

Let me actually check the lreg dump for the register assignments. The -dl dump prints the RTL with pseudo regs (before/after?). Let me look at the final .s (r16.s) to confirm, and look at the .lreg tail for "Register 77 in ..." messages.

Actually, let me look for the assignment table in the lreg dump: it prints lines like "Register 75 in 2." Those are the "reg in block" lines. Let me grep for "Register 77" and "Register 75" in r16.i.lreg.
