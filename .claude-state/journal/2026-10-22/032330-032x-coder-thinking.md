---
ts: 2026-10-22T09:23:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_DYBNSAKY1o5wf5IMUYy8
---
So the shift is insn 184: `(set (reg:SI 118) (ashift:SI (reg:SI 88) (const_int 3)))` with REG_EQUAL (mult (reg 88) 8).

Now I need the insn that uses 118: the address add. Let me find insns referencing reg 118 in the cse dump, and the tree.

Let me grep for "118" in the function section ofcse.
