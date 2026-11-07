---
ts: 2026-11-06T22:12:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qJghd4UBs6RDNNCBao2F
---
i2 (do-while around `otp = ...; *otp = ...;`) = 3 remains the best. j1 (only the store) = 20, j2 = 13.

So i2's structure is special. The residual is a 3-position ORDER: the mask materialization is 2 insns early.

Let me get the full instruction listing for i2 to understand. Use --keep to get the object and objdump. Let me do that.
