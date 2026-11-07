---
ts: 2026-11-06T05:14:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WDkUD4N2eTwMuBONItV2
---
Let me find includers of the header. `grep -rl 'func_80175820.h' src/`. That's a targeted search within src. But "never ls/find outside the project" — grep inside src is fine.

Actually, the important question: is this item a WALL (asm-artifact frame)? Let me verify by dumping the RTL. Let me find an includer.
