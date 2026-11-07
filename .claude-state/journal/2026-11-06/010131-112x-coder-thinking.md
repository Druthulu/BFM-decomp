---
ts: 2026-11-06T08:01:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Gp39btk7EbCAQqcX2Zv6
---
`func_800174DC()` isn't defined in the TU or headers (extern). Let me check the gte macros: `gte_ldv0(r0)` at line 219, `gte_stsv(r0)` at 869. Maybe `gte_stsv` has a variant that takes a pointer and the source uses a different macro. But the source calls gte_stsv((u16*)w3c).

Let me look at the gte_stsv macro to see if it clobbers registers (which would affect a0's liveness).
