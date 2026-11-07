---
ts: 2026-11-06T17:36:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uXKsasNbgLdLvOFaPSvV
---
`hard_reg_preferences` is built in global.c from... `reg_preference`? In global.c, hard_reg_preferences[allocno] is set by scanning the RTL: for each insn, if a pseudo is set from a hard reg or used in a copy, the preference is recorded. Let me look at `expand_preferences` and `record_one_conflict`/`set_preference`.

Actually, in global.c: `hard_reg_preferences[allocno]` gets hard regs via `record_preference`? Let me grep "hard_reg_preferences" usage.
