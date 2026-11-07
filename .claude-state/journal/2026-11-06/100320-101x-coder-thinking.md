---
ts: 2026-11-06T17:03:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9p6KNioo46wO6Y1n8lYN
---
ah04 = SCORE 0! Wrapping the struct assignment in `do { m = D_800AE620; } while (0);  // !FAKE: do-while` splits the cse EBB, preventing the &m cache!

Let me verify ah04:
- No launder, no keepalive asms (only the a0 pin remains).
- Score 0, 73 ins.

Let me grep for asm and make win.c.
