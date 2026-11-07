---
ts: 2026-11-06T14:08:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pl00nWY0LhqulfF3PCgP
---
Score 6 with asm removed. So the difference is register allocation of caller-saved temps ($9 src, $10 i, $11 dst, $12 n...). Let me see the diff. dt.sh gives diff tail. Let me run dt.sh on c1.c with more tail.
