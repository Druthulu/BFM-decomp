---
ts: 2026-10-22T11:12:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BSQbPyAQG4HSEBc2Kiw8
---
The dump is verbose. Let me instead grep for the load pattern `lw` of 32(s0) near the call in the sched dump, and also look at the pre-sched (.cse / .jump2) RTL.

Actually, a cleaner approach: search the .sched dump for "(call_internal)" / "call " and for " (set (mem (reg ...32) ...)".

Let me try a different approach: extract the region of the sched dump between the func's start and end. Let me find lines with "func_8017E780" region markers.

Alternatively, use `tools/alloc_table.py`. Hmm.

Actually maybe simpler: let me look at the `.jump2` and `.cse2` dumps (pre-sched RTL) around the call, and the `.sched` dump around it, to see the block boundaries and instruction order.

Let me search for "func_8001D0E8" in the dumps.
