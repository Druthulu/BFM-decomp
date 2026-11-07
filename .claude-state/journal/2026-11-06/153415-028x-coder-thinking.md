---
ts: 2026-11-06T22:34:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oH5FlulCH1BnzL37sMKC
---
Key: "Try to put each quantity in a suggested physical register, if it has one" — `qty_phys_num_sugg` / `qty_phys_num_copy_sugg`. These suggestions come from `find_free_reg`'s suggested regs, computed in `block_alloc` from copy insns and from insn constraints (e.g., `alloc_qty_for_scratch` and `qty_sugg` from operands). For an `lh` load, the destination has no suggestion. But if the value is *copied* from another pseudo with a suggested hard reg...

`qty_phys_copy_sugg` is filled by `reg_is_set`/`wipe_dead_reg` and the `copy` handling. Let me look at where qty_phys_copy_sugg gets set: in `block_alloc`, there's code around line 1123-1460. Let me look for "qty_phys_copy_sugg" assignments.
