---
ts: 2026-11-06T20:48:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oc0GYRn99eSBw0Ml69ma
---
Pseudo 87 is reused in other functions (the dumps are per-TU). Let me look at line 37101 in the cse dump: `(insn 57 55 60 (set (reg/v:SI 87) ...` — hmm, insn 57 in our function is `a0 = 80`. Not ours.

Let me search within our function's cse section (starting at 75656) for "reg/v:SI 87".
