---
ts: 2026-11-06T07:22:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uQyypxIKT2QFvGkTcwBw
---
Now I understand the shapes. The keepalive asm keeps a value live in a register. Removing it should be replaced by "real C" that keeps that value alive naturally (e.g., using the variable in a later computation, or a dead store that flow doesn't delete). The catalog C0505. Let me look at the cookbook entries C0505, C0535, C0414 and the moves entries for keepalive MATCH cases.

Let me check the cookbook index for C0505.
