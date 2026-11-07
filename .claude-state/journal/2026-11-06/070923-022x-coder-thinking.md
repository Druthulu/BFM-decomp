---
ts: 2026-11-06T14:09:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QtFg23Scc4l66BRBYw84
---
Function spans 4351-5642. The local-alloc dump probably shows the "Register dispositions" table at the end with n_refs? Let me grep in that range for "Quantity" or "n_refs" or the pseudo names. The RTL uses pseudo reg numbers (e.g., reg 78). Let me look at the beginning of the function's lreg dump to see what -dl prints.
