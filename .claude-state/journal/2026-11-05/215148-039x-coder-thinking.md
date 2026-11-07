---
ts: 2026-11-06T04:51:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QpEcnDRzAKNPmlQYofvH
---
Priority = longest path to end of block via dependencies, computed with insn_cost. So the store's address insns (lui/addiu) lead to the store; the store leads to the block end? The store is not dependent on anything, so priority path: address->store->(block end). The store is a "block boundary" thing? Let's read priority() to see if stores get boosted.
