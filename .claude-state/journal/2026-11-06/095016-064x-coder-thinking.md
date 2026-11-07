---
ts: 2026-11-06T16:50:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mSeGaWs5T9KlIU5cSkJR
---
Same swap. Let me think about the tie group priority again, and what actually determines the allocation of the FIRST free reg.

Actually, maybe the issue isn't priority but the ORDER in which hard regs are tried. In local-alloc, `find_free_reg` tries registers in an order influenced by `reg_preferred_class` and possibly by `reg_alternate_class`, plus it prefers registers not live. Let me look at find_free_reg.

Actually — key insight: maybe the allocation is fine (t gets $2 in the target because of the *copy preference* from something?). Hmm.

Let me look at find_free_reg to understand the hard reg order.
