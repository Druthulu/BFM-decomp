---
ts: 2026-11-06T18:47:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lP522rwpZuOtFoKZCljd
---
The scratch TU is the includer with the shared header in shared/ov/. The body replacement happens in the header file, not the .c. My dump used the .c (which includes the header from the scratch's shared/ov/func_80146750.h). Let me check that header in the scratch — it should contain w1's body.

But the RTL showed a3 as a variable — meaning the scratch header still has the pin? Let me check.
