---
ts: 2026-11-06T07:36:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8wl6UWITlzIFbhzlCCXX
---
That compiles. So K&R is fine. The difference must be that in the real TU, the function's type is somehow `(void)`. Let me check the cpp output around the declaration. Maybe a macro in common.h redefines? Let me preprocess the TU and grep.
