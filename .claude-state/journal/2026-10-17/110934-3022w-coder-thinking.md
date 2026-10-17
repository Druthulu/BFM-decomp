---
ts: 2026-10-17T17:09:34.223Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm noting that with three or fewer quantities the sort isn't a full comparison sort, but with four it falls back to qsort, which isn't stable—so ties like the one between r73 and r75 at priority 5000 get resolved by the secondary quantity comparison.

Still, r73 ending up at a1 is odd unless regs_live_at already accounts for previously allocated quantities, or constants sorted ahead of r73 affect the tie-break order. I need to actually trace through qty_compare_1 to see how it resolves this.
