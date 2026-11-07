---
ts: 2026-11-06T12:34:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7RZHTMq2xGV7SGrU7m65
---
Key: `regs_someone_prefers` and `hard_reg_copy_preferences`. Copy preferences come from copies (reg-reg moves) — from local-alloc's `reg_equiv`/copy propagation. A `set v0 = pseudo` is a copy → the pseudo has a copy preference for v0!

But `hard_reg_copy_preferences` is set from local-alloc's `reg_pref`? Let me look at how hard_reg_copy_preferences is computed in global.c. Search.
