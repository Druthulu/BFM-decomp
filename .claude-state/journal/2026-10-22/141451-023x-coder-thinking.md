---
ts: 2026-10-22T20:14:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GFx12t4nw7UWfV9zLDBY
---
The alloc tables are identical (as expected pre-reload). So the difference appears later — reload/local-alloc. The .lreg stage table is the same because the RTL is nearly the same? But the final code differs: score-0 rematerializes the call address, c_struct keeps s1.

Wait — both dumps identical at .lreg? But the C differs. Let me diff the dumps to find where they diverge.
