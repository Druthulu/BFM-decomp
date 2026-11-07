---
ts: 2026-11-06T06:10:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_scNwuyCY4RPldCfi6dMi
---
To dump my candidate body, I need a TU with the body substituted. The --try with --keep prints the candidate object path and keeps the per-call scratch — that scratch likely has a spliced t.c I can dump. Let me use --keep and get the scratch TU path.

But careful: --keep scratch must be removed after use. And dumps go under my item dir, then rm -rf.

Let me run with --keep.
