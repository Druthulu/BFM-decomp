---
ts: 2026-10-22T05:46:50.484Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a933331c6d154adc4
model: claude-opus-5-5[1m]
effort: medium
turnId: d25270b4-e42b-432f-9435-484b642c2966
---
I'm thinking through the sequencing — whether to bank B3 first since it needs no shards running, versus running the MiniMax shards now and banking later, given that banking triggers a clean build that would break any active shard scorers. The barrier rule favors banking first, but that costs time against the developer's push to scale up, and B3's 24 functions are already overdue.

While banking happens, I want to prepare shard splits for batches over 5 functions — writing a splitting tool that partitions list.tsv and moves item dirs for shards like RM1 and RM2, and checking how briefs differ across shards (like G16 vs G20) to confirm it's just name substitution before automating the split.
