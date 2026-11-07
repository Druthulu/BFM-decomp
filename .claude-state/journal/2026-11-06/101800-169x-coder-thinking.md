---
ts: 2026-11-06T17:18:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_genMMpNKEjBUpwZ721zJ
---
find_free_reg scans i from 0 upward (reg_alloc_order undefined → i). It excludes regs in `used` = fixed_reg_set (or call_used if crossing calls) ∪ regs_live_at[born..dead] ∪ non-class.

Crucially: `regs_live_at[ins]` is built during the block scan and includes the *hard* registers live, and also the qtys already allocated? No — regs_live_at tracks hard regs only. Since local-alloc allocates qtys one by one, previously allocated qtys have been converted to hard regs (via `reg_is_born` marking their hard reg live?) Hmm, after allocation, `qty_phys_reg[q]` is set but the RTL still has pseudos. find_free_reg for a later qty checks `regs_live_at` which was computed from the original hard regs, not the newly allocated ones. But there's a second loop: after the first allocation pass, local_alloc does `qty_phys_reg` and then a second pass "find a register for each qty that didn't get one" with conflict checks against other allocated qtys.

Actually the main loop (line ~1520) allocates each qty with find_free_reg, and find_free_reg's `used` set includes `regs_live_at` — the original hard-reg liveness. Two different qtys could get the same hard reg if their live ranges are disjoint. If they overlap, there's a separate check: `qty_phys_reg` conflicts? Let me read the loop after 1520.
