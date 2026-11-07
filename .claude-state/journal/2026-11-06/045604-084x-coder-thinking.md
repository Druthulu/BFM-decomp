---
ts: 2026-11-06T11:56:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fHa8UTSoDxgYiPIcBweD
---
30 scored tries now (26 + 4 = 30). Best lever-free = 45.

Item 2: WALL, best 45, tag `sched1-birth-order`? The header attributes it to sched2 order + a global-alloc priority tie. The wall tag should describe the *blocker*: the barrier is a global-alloc priority tie (`global-pri-bank-order`), the launders are sched order (`sched1-birth-order` / sched2). I'll pick `sched1-birth-order` as primary? Hmm.

The result line has one wall column. Let me use `global-pri-bank-order` since removing the slider (barrier) is what costs the 2 insns and the launders only cost the order. Actually the best 45 comes from removing everything: the 2 extra insns come from the slider removal (mechanism 1), and the order from the launders (mechanism 2).

The header explicitly says mechanism (2) "Statement order cannot reach the target shape... 470+ orderings". And mechanism (1) needs zero-byte insns.

I'll tag `global-pri-bank-order` and mention sched order in the evidence.

Wait — but "best = lowest score of a lever-free body" = 45. Hmm, the WALL evidence should mention both.

Now: win.c. For a WALL, what goes in win.c? "each MATCH/PARTIAL has its win.c scoring 0" — a WALL doesn't need a win.c scoring 0. But the results row needs a best. I'll keep win.c = the best lever-free body (v1/q2/t1 = 45).

Let me set win.c = v1 (the base lever-free, 45) and write the row.

Actually, let me double check that v1 has zero asm. v1 = both launders + barrier removed. Let me grep.

Then write the results row: dir, file, func, kinds, result=WALL, best=45, tries=30, wall=global-pri-bank-order, evidence.

Evidence ≤140: "header (2770-2744) documents it: slider is a global.c priority tie (&g.sz0 vs &g.sz1) needing N zero-byte insns; re-ties split wz's live range for sched2 order; 470+ orderings bottom at 5"

Let me count ~190. Shorten: "slider = global.c pri tie &g.sz0/&g.sz1 needing N zero-byte insns; re-ties split wz live range for sched2 order; src header: 470+ orderings bottom at 5" ≈ 150. Trim more: "global.c pri tie &g.sz0/&g.sz1 needs N zero-byte insns; re-ties split wz's range for sched2 order; src header 2744: 470+ orderings bottom at 5" ~145. OK, close enough (≤140 is a guideline; let me trim to be safe).

"global.c pri tie sz0/sz1 needs N zero-byte insns; re-ties split wz range for sched2 order; src hdr 2732-2743: 470+ orderings bottom at 5" = 133 chars. Good.

Let me finalize.
