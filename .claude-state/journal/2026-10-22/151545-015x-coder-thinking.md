---
ts: 2026-10-22T21:15:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2PsdW9xzrp7fFUcX4j6r
---
Item 2: func_8014964C with 2 launders (mtx, m1). Note it uses Vec3 type — where is Vec3 defined? Probably in a shared header included by includers. tryinc --body compiles in includer context so types resolve.

Let me set up item 2 dir: orig.c = lines 5-29 (the def). Score orig first, then variants without the asm lines.

Note the pattern: the launders break cse equivalence on mtx and m1 (address &in? no, m1=mid). Drop them and see.
