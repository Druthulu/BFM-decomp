---
ts: 2026-11-06T19:01:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9Nkqu3K54kamsVJXiAQ7
---
The loop block 2: the scheduler picks by priority: 98 (8), 96 (7), 91 (7), 89 (6), 84 (6), 82 (5), 77 (5), 75 (4), 70 (4), 68 (3), 63 (3), 61 (2), 58 (2), 56 (1).

The final order (reverse): 56, 58, 61, 63, 68, 70, 75, 77, 82, 84, 89, 91, 96, 98, 101...

Hmm, the priorities: the two increments must be among these insns. Let me map the RTL insns. Let me look at the RTL for the loop block in the .sched dump.

Actually, the priorities are the "length of the longest path to the branch" — the increments have different priorities because of their dependencies. To get the a7 increment scheduled before the v1 increment, the a7 increment must have a HIGHER priority (longer path to the branch) or be chosen by a tie.

Let me find which insn is which in the RTL. Let me grep the .sched dump's RTL for the loop block.
