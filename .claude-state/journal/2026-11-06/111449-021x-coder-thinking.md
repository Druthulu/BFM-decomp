---
ts: 2026-11-06T18:14:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aa0iHCG1ZSF3FUrque0U
---
No REG_ALLOC_ORDER in mips.h, so it's the default `i` order 0..31. So find_free_reg tries $0, $1, ... and $3 before $4. Why would a0 ($4) be picked instead of $3? Because $3 is live (used by something else) — v0? No, v0 is $2. Hmm. In block d30, at the load: live hard regs... v1 pseudo born at the load. $3 is not live from other pseudos? v0 is $2. a0 is $4 (live until the load). So $3 should be free and tried before $4 → chosen. But result: a0.

Wait, maybe combine_regs ties the load result to a0: the load pattern `set (reg) (mem (reg))` — may_save_copy? block_alloc calls combine_regs for each operand of the insn where `recog` gives constraints; for mips `lw` the "output" and "input" operands. The load's address reg a0 is an input operand with REG_DEAD. combine_regs(usedreg=a0, setreg=v1) — a0 is a hard reg, sreg pseudo: records `qty_phys_sugg` for the pseudo (since ureg < FIRST_PSEUDO_REGISTER, it records the hard reg as a suggestion and returns 0 "failure"). Then in the "try suggested" phase, the qty gets a0! That's the copy preference: "we just record the hard reg as the suggestion". may_save_copy is non-zero for "the input and output must share a register"? For a load, operand constraints "=r,m" — not tied. Hmm, but combine_regs is called from block_alloc when? Let me look at block_alloc's operand loop.

Actually, wait: qty_sugg_compare prioritizes copy suggestions. Let me check block_alloc where combine_regs is called.
