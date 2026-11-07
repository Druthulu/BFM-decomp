---
ts: 2026-11-06T15:08:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m1Wo4JbpOtA8Bj8kqky4
---
At RTL, insn 19 is the ashift and insn 21 moves it to a0. So `a0 = s0 << 10` becomes ashift into a temp then move. Interesting — the pinned a0 forces a move.

Wait, the target's `sll a0,s0,0xa` — in the tree's own (launder) body, it would be ashift into a0 directly maybe.

Let me look at the same region in the .cse and .combine dumps to see the fold.
