---
ts: 2026-11-06T04:42:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t86fFaUzxqUtpPrpvGw0
---
Let me use --keep to get the candidate object and dump asm. Actually simpler: write candidate variants and score.

The issue: target stores each result immediately (sb v0,0 right after), and uses v0 (result of subu) as the same register as the loaded byte. Mine uses v1 for subu and delays the store — that's because without barriers, gcc/cse sees the loads p[0], p[1], p[2] and stores can be reordered? Actually the target also loads p[1] after storing p[0]. Mine apparently batches the three loads? Let's see the mine listing with --keep.

Let me run --try --keep and inspect.
