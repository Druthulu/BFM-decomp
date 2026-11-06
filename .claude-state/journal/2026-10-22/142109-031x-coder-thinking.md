---
ts: 2026-10-22T20:21:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fSNmRVEMSrGMFdDhojJQ
---
In c_struct: "Register dispositions: 72 in 18 (s2), 76 in 4, 80 in 17 (s1), ...". So r80 got s1 at local-alloc. And the address r80: let me find its definition in the greg dump. Search for "(reg:SI 80" and "reg/v:SI 80" in the c_struct greg section.
