---
ts: 2026-11-06T20:48:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FMOS5F8Y8NReklgBv69b
---
So after cse1, insn 92 (ent = a0) SURVIVES and the uses use 87. So cse1 did NOT propagate the copy! The copy survives cse1.

So where does it disappear? Let me check the .combine and .lreg dumps. The combine pass may merge the copy into its uses (`try_combine` propagates a copy into a single use). Let me check the .combine dump.

In the .combine dump, is insn 92 still there? Let me search within our function's section for reg/v:SI 87.
