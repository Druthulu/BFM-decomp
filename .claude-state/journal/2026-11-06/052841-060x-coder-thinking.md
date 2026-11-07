---
ts: 2026-11-06T12:28:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lcbKe08TkQN18d1kq6OG
---
Lever-free best stays 21 (v0.c), 32 tries.

Record item 2: WALL, best 21, wall tag: two mechanisms. The row format has ONE wall column: a tag or new `<pass>-<what>`. The dominant residual is the keepalive's register rotation (19). Tag: `global-pri-bank-order` (global-alloc priority order assigns the hard regs differently). Evidence mentions both.

Hmm, but the barrier's residual is `sched-store-sink` (2). Since the wall column is a single tag, I'll use `global-pri-bank-order` and mention the barrier in the evidence. Or use `sched-store-sink`? The bigger residual is the register bank. I'll go with `global-pri-bank-order`.

Now write notes.md, results row, moves.md line. Then item 3.

Time: ~06:45. Two items left (item 3: 312 ins!, item 4: 87 ins). Item 3 is 312 ins — big; likely WALL fast. Item 4 (87 ins) is the best MATCH candidate.

Let me hurry.
