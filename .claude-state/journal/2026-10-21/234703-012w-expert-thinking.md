---
ts: 2026-10-22T05:47:03.551Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a933331c6d154adc4
model: claude-opus-5-5[1m]
effort: medium
turnId: d25270b4-e42b-432f-9435-484b642c2966
---
I'm noting that results.tsv only has the header line, while G15 has a header plus two rows. I'm thinking through a way to split larger unstarted shards into sub-shards (like G16a/G16b) while leaving smaller partially-done shards like G15b alone since they only have a few items left.

For splitting, my approach is to move item directories rather than copy them, partition list.tsv between the new sub-shards, keep a fresh results.tsv with just the header, and generate a new brief by renaming the original. I'm also confirming that RM1/RM2 already have empty results.tsv files with only headers.

Before working out the splitting details further, I want to kick off the B3 coder since it gates the shards, which means I need to check what shards B3 actually covers and look at bank_B2.txt to see how prior substitutions were filled in and which shards were already banked in B1/B2.
