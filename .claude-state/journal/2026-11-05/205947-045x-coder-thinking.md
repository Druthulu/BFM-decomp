---
ts: 2026-11-06T03:59:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RfkvMPtOB7oW8uUntkRD
---
Hmm, cse_around_loop is about moving invariant values; a do-while(0) creates a loop but the body executes once; cse's loop handling may still invalidate. In practice, the moves.md shows do-while(0) "splits cse1 EBB" (C0535) — likely because the loop creates a basic block and cse processes per-EBB, flushing at block boundaries. Let's just test it.

Let me create candidates for item 2:
c1: wrap the x2 block in do-while(0).
c2: wrap the diff block in do-while(0).
c3: wrap both.

Let me read nopin.c lines to build.
