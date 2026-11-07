---
ts: 2026-11-06T17:36:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TqMqJtTEr2QahriFBdoe
---
`set_preference` builds hard_reg_preferences from insns where an operand is a hard reg (e.g., a copy to/from a hard reg). For allocno 75 (sh16), a preference for v1 means some insn involving 75 (or its coalesced group) has a hard-reg operand v1.

Hmm, but 75 is a pseudo; the RTL before global has no hard regs except the call-clobbered v0/ra etc. `set_preference(reg, pref)` is called for REG_NOTES (REG_NO_CONFLICT) and for insns with a hard reg operand.

Actually, `set_preference` is called from `mark_reg_store`/`mark_reg_clobber`? Let me look at set_preference and its callers.
