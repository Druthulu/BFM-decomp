---
ts: 2026-11-06T16:36:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UwZYykM4EmuE71lHQqsJ
---
Key: `note_stores (PATTERN (insn), reg_is_set)` is called AFTER the tie loop for that insn. So at insn 65, when the tie loop runs, reg 75 (set in this insn) has not yet been given a qty by reg_is_set for THIS insn... but the condition requires `reg_qty[sreg] == -1` → if 75 is not yet born, reg_qty[75] is -2 (not born). The condition is `reg_qty[sreg] == -1` (ignore), so -2 passes. Then combine_regs does `if (reg_qty[sreg] == -2) reg_is_born(...)` in the hard-reg case only... For pseudo-pseudo, it checks `if (reg_qty[sreg] >= -1) return 0;` — -2 is < -1, so OK. Then ties.

Hmm so why no tie in r16? Let me look at the actual andi insn: `(insn 65 64 69 (set (reg/v:SI 75) (and:SI (reg:SI 77) (const_int 32768))) 92 {andsi3} (nil) (expr_list:REG_DEAD (reg:SI 77) (nil)))`.

The tie loop condition: `insn_code_number >= 0 && insn_n_operands > 1 && insn_operand_constraint[code][0][0] == '=' && [0][1] != '&'`. Let me check andsi3's operand 0 constraint in mips.md.

Let me grep mips.md for andsi3.
