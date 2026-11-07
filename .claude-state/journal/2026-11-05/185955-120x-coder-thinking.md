---
ts: 2026-11-06T01:59:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BvtdepBzkVkqGBBMeS2z
---
No rtl.def in the reference copy. But the cc1 binary has `rtx_name` array; I can get the code value at runtime: `p rtx_name[24]` etc. Let me just query gdb for the array entries: `p rtx_name[0]` ... or print the whole array. Let me use gdb to print rtx_name indices.
