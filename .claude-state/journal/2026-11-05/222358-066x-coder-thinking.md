---
ts: 2026-11-06T05:23:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iE4wkkeroD9O2mYr419n
---
Structs match. So why does the real TU produce frame 16?

Wait — maybe the real TU's function at line 4105 is NOT the one from the header include; maybe the header include is inside a larger function, and the spliced body appears at a different place. Let me check where the body appears in the TU: grep for `func_80175820` in the TU source.
