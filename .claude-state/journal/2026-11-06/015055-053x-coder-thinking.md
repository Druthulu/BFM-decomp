---
ts: 2026-11-06T08:50:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iwq4wsM5FT81bGmXmEpW
---
`find_free_reg` with `qty_min_class` etc. The `0, 0` args are `insn` and `?`; let me look at find_free_reg's signature and whether it uses preferences. In gcc 2.7.2 local-alloc, `find_free_reg (class, mode, qty, insn, last_insn_used, birth, death)` — the "preferred" handling was in global.c. Hmm, local-alloc in 2.7.2 has `qty_phys_reg` and `find_free_reg` which scans `regs_live_between` masks and picks the first free reg in `reg_alloc_order`? Let me check find_free_reg.
