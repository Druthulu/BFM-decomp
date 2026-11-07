---
ts: 2026-11-06T22:27:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GaX489ivXVIaans6dU13
---
The TU is the header path itself (src/shared/ov/func_8012B8E4.h), and recs_for expands to all includers from a mapping. For hdump, I need a specific includer TU. Let me pick src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c.

Let me run hdump for w0 and prev_win, and look at alloc tables. hdump.sh signature: <includer TU> <header basename> <body.c> <outdir> <tag>.

Disk: dumps go under item dir and deleted after. Good.

Let me run for w0 and prev_win. Actually hdump for prev_win (pin kept) is the baseline. Let me do both in one command sequentially.
