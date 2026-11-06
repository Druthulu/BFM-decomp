---
ts: 2026-10-22T20:47:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hNq8nH5IT6oEjsWyE5uH
---
The initial RTL (expand) for the else branch is already correct: `(set (reg 74) symbol)` then `(set (reg 73) (plus reg 74 const 25996))`. So the fold happens in cse1. Let me look at the cse dump at line 20486 (function section) to see the folded insn.
