---
ts: 2026-11-06T18:32:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PVXMwZfzaGMdMkPLjo0q
---
That's the first call's region. Let me find the second symbol_ref D_801A15AC insn in the scheduled RTL and its position/number. Line 160 in the offset view = n+145+15 = n+160. Let me print n+150..n+175.

Actually the grep showed line 160 (offset from n+140) has `(symbol_ref:SI ("D_801A15AC")) 159 {movsi_internal2} (insn_list:REG_DEP_ANTI 49 (nil))`. That's within the a1 insn. Let me see its number and neighbors.
