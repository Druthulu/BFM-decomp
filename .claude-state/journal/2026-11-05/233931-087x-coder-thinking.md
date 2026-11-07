---
ts: 2026-11-06T06:39:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LGSu5xPUz9fXZGLKddlA
---
c2 (dead-reset after each call) = 22 with 711 ins (one extra). That's a big improvement from 43! But one extra insn and 22 diff.

The extra insn is probably one `sw zero` from a dead reset that wasn't deleted.

Hmm, 9 dead resets; only 1 extra insn — so 8 were deleted and 1 survived.

Let me look at the diff of c2.

Actually, the C0414 trick: "dead reset x=0 after the store; cse1 drops the value so the 2nd load is not forwarded, delete_dead_from_cse removes x=0". So most get deleted.

Let me see the diff to find the residual.
