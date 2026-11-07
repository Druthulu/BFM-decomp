---
ts: 2026-11-06T16:55:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9aqNPzcCAdprhGU2QzbM
---
30 tries reached (19+11=30). Best lever-free = 52 (nopin and several variants). Time now ~10:16 (32 min).

Item 2: WALL, best 52.

Write win.c? The brief says "each MATCH/PARTIAL has its win.c scoring 0"; for a WALL, best = lowest score of a lever-free body. The interface says win.c should be a lever-free body scoring 0 for MATCH/PARTIAL. For a WALL, do we write win.c? The CHANGE says "write a lever-free body of func in O05x/<dir>/win.c (bare definition) that scores 0". For a wall, best is recorded. I'll put the best lever-free body (nopin.c) in win.c and note it's best 52.

Hmm, but the check script chk.sh rescores MATCH/PARTIAL rows only. So a WALL row doesn't need win.c to score 0. I'll still keep nopin.c as win.c (the best lever-free body) — that seems consistent with "best = lowest score of a lever-free body".

Now record:
- notes.md for item 2
- results row: dir file func kinds result best tries wall evidence
  result WALL, best 52, tries 30, wall `global-pri-bank-order`, evidence: "3 pins dropped: fp(s0)->s5+s0 extra base, table/cbase shift, +8 frame (global-alloc priority); ot: block-local load takes t0, cnt t1 (lreg-qty-priority); t0c copy combine-merged (combine-copy-merge)" ≤140 chars.

Let me write it.
