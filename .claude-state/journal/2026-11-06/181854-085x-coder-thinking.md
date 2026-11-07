---
ts: 2026-11-07T01:18:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kTQmEpeUI3MjXLWaJzQz
---
In bb, the pseudo numbering shifted (r75 = s0's pseudo) because the do-while created a new pseudo. Let me see the 516 store — the grep only showed up to line 68. Let me look further.

Note the do-while block created a separate EBB, so insn 26 (a0 = r75) is now at a different position.

Let me grep for 516 in the bb lreg dump.
