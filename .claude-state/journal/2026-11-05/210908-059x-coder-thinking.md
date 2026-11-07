---
ts: 2026-11-06T04:09:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9kjQsTGXFW4HBU0ArF0o
---
The key: `lookup (src, hash, mode)` — lookup walks the bucket and validates. Let me read lookup's validation of the value register. The entry for a load has `p->exp` = the MEM? Actually for a load, the src is MEM; when it's inserted, the table entry is the MEM with its "value" being... In cse, when an insn sets a register to an expression, the expression itself is inserted into the table, and the destination register is linked as an equivalent value (the table element for the expression has `first_same_value` including the destination register? Actually `insert_regs`/`insert`). Let me read `lookup` and how a load is forwarded. Search for "src_elt" usage after lookup where src is replaced.

The forwarding happens: `sets[i].src_elt = elt;` then later `src = ...`? Let me look further after line 6520 to see the "replace src with a cheaper equivalent" part.
