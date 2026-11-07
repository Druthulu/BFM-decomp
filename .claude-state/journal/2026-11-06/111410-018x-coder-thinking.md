---
ts: 2026-11-06T18:14:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2KKxxzeeusjBmAu9cI19
---
This is combine_regs for `set` patterns. For a load `set (reg) (mem (reg))`, the `usedreg` is inside the address, not directly a REG operand — so combine_regs isn't called for the address reg? Actually block_alloc calls combine_regs for operands where "may_save_copy" if the pattern is a simple copy or "the input and output must share a register". For a load, no.

So why does the load result get a0? Because find_free_reg finds a0 free (a0's liveness ends at the load). The hard reg a0 is live at 2*insn_number... Let me check: `regs_live_at[2*insn_number]` is "registers live after INSN_NUMBER"? Comment says "Set the registers live after INSN_NUMBER" and IORs into both 2*n and 2*n+1. The load result is born at the load: qty_birth = 2*n - 1. Hard reg a0 dies at the load (REG_DEAD note): wipe_dead_reg removes it from regs_live after processing. find_free_reg checks regs_live_at at birth..death range.

Let me look at find_free_reg (search line).
