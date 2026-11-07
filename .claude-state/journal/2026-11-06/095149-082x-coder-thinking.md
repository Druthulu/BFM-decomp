---
ts: 2026-11-06T16:51:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D3h78H4AigolW6FyCm6L
---
TARGET_GP_OPT is probably off for PSX (-G0). So SYMBOL_REF_FLAG = 0, cost 2. Both our build and the target build use the same flags, so this isn't a source-level difference.

Hmm. So how did the target's original source avoid cse merging? Let's think again about cse's merge condition: fold_rtx replaces a constant with an equivalent register if the register's cost is lower. The register's cost for a pseudo is 0? Actually REG_COST... In cse, the replacement happens in `fold_rtx` when it finds `qty_const[regno]` equal to the constant and the register is "not cheap"? Let me read the relevant code around line 1359.
