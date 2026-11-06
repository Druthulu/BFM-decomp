---
ts: 2026-10-22T21:42:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zwjGugiVuxGUSMfoNIH6
---
The dump is truncated in my view. Let me see more lines to find where sw ra (which insn?) and the li are scheduled.

Note the ready list at T-2: "30 (2) 33 (1)" — priority 2 insns. Hmm.

The block's insns are 81, 83, 85, 4, 11, 14, 16, 22, 25, 27, 30, 33, 34.

Let me see the rest of the schedule (lines 19995-20020).
