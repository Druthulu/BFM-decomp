---
ts: 2026-10-17T16:54:42.725Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
Looking back at func_8001BBBC, I notice the residual discrepancy is about register tagging (v1 vs t2) and the placement of the sw at offset 4(a3), plus the li v0,4 positioning between the lui/ori pair for t1 — that's the known LUID ordering issue. My version placed the sw storing t2 earlier than the target, which keeps the constant tag alive longer than the source order implies.

I'm trying alternate variable orderings now: making tag0 a top-level assigned variable, treating the mask construction as a multi-step operation that CSE can't simplify, and experimenting with ways to make the "4" value go through a temp with multiple sets to avoid birth-boosting it. I'll test a few of these combinations to see which matches the target scheduling.
