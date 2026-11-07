---
ts: 2026-11-06T12:28:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BaeeqjBgafkKaMCRLF9s
---
The struct alias fixed the tail store (score 8 → 4). Remaining: the beqz delay-slot fill (2 diffs + offsets).

Now the delay-slot issue. Let me try the do-while(0) ideas.

Idea A: wrap the if in do{}while(0).
Idea B: wrap the increment in do{}while(0).
Idea C: wrap the call statement in do{}while(0).

Let me look at C0535 in the cookbook for the exact technique.
