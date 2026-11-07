---
ts: 2026-11-06T11:09:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3bWDmv36tHCrbxMkoVgf
---
Both wins contain only asm-label aliases (symbol names), no register pins, no asm insns, no barriers.

Let me verify the win.c files score 0 with a fresh dt.sh run.

Also I need to double-check the do-while tag `// !FAKE: do-while` is present.

Let me run dt.sh on both.
