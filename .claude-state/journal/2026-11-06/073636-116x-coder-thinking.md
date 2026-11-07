---
ts: 2026-11-06T14:36:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aXLjwJhQPbRiF5dSBA1a
---
All still 4. So moving the assignment doesn't help; the scheduler reorders regardless.

Let me look at the sched2 dump to see the final order. If sched2 is the one moving the la, then the fix must affect sched2. Let me check the .sched2 dump's block 3 order for c1 vs orig.

Let me print the block 3 launch order for both. The order in the dump: "ready list at T-1 ... now X" means X is launched at T-1. The final order is T-N ... T-1. Let me extract the launched insn per T for block 3.

Actually, let me just look at the .sched2 dump's block 3 for c1 and see which insn is launched at each T, and map 47 (a1) to a T.

Let me read the full block 3 of the sched2 dump.
