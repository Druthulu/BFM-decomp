---
ts: 2026-11-07T01:22:59.346Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: af5fe0128a7f156b5
model: claude-opus-5-5
effort: medium
turnId: 74626616-a269-4e2f-a92f-db10c97d5aad
---
I'm tallying the 572 singleton rows by kind, which breaks down as pin 186, launder 156, barrier 124, keepalive 79, and instruction 27, so I can set up the before/after comparison. Once c112 is done I'll count the rows again by kind and wall tag and total how many were dropped. I'm also writing a read-only script to add up MATCH, PARTIAL and WALL across the T11 shard results.tsv files.

The before-counts show 572 singleton rows, led by pin at 186, and I'm writing the after-count script while c112 runs.
