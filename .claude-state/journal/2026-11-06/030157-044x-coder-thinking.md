---
ts: 2026-11-06T10:01:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QbE06aESBxhKDLyb1TSY
---
Empty. The -dl dump writes to the .lreg file (RTL after local-alloc). Let me look at the lreg RTL for the relevant block to see which pseudo got which reg, and maybe find the qty debug (GCC 2.7.2 -dl prints ";; Register dispositions:" etc.). Let me search for "disposition" or "qty".
