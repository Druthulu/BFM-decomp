---
ts: 2026-11-06T12:58:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QpoLXl5lSkjSzWsVhhrA
---
While that runs (~4 min), let me start item 4: func_80177EA4.h, kinds keepalive,launder.

The body has many pins ($8, $2, $4, $3, $2, $2, $2, $3, $2) which may stay. Levers to remove:
1. `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));` — launder (line ~40)
2. `__asm__ __volatile__("" : : "r"(iVar2) : "memory");` — keepalive

Let me score the baseline first and then remove them.

Note: the header has `uint` and `int` types — fine.

Let me do the baseline + c1.
