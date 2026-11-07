---
ts: 2026-11-06T14:21:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6Y9Drg5hthpFGVl5brFz
---
The dead-store deletion is in `life_analysis`/`propagate_block`? Let me look at where the "only effect is to store a value never used" deletion happens. It's probably in `mark_used_regs`/`propagate_one_insn`. But importantly, the ref counting happens during the same pass. If a dead store `i = 0` is deleted, is its ref counted? The deletion happens after counting? Hmm.

This is a promising route: add a dead store of i inside the loop. It would be deleted by life_analysis, but the ref might be counted (flow's propagate_block counts refs as it scans, and deletes dead stores). If the deletion happens in the same scan, the ref might still be counted (or not).

But careful: even if the dead store is deleted by flow, the extra ref is counted (if counted before deletion). Let me look at the deletion code to see the order. Let me find where insns are deleted for "only effect is to store a value never used". Search for "REG_UNUSED" or the code around line 1560/1009.

Actually, the deletion is likely in `propagate_block`'s scan: for each insn, if it's a SET of a dead reg with no side effects, delete it. But the ref counting in `mark_used_regs` happens for the insn's operands... A dead SET's dest is not "used", so it wouldn't count as a use; but it counts as a set (reg_n_refs += loop_depth at line 2067). So a dead store adds a ref (as a set) and then the insn is deleted. That's exactly what we want!

Wait, but if it's deleted, the ref count remains from the scan. Let me verify: the dead-store deletion likely happens in a separate loop after mark_used_regs. Let me look.

Let me search for the code that deletes a dead SET. In flow.c, `propagate_one_insn` or `mark_used_regs`. Let me look around line 1500-1600.
