---
ts: 2026-11-07T00:15:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_trcNIXpDDMoi40r984na
---
Interesting! This header has only 2 includers (not 34; the list.tsv's last column must be something else). Good — verification is cheap.

Baseline: score 22, mine 82 insns vs target 79. So 3 extra insns. That's the launder/pin removal effect.

Register pairs: s1->s2 x4, s4->s3 x4, s2->s1 x3, s3->s4 x2.

So mine: s1↔s2 and s3↔s4 swapped relative to target. Target: tp=s3 (pinned $19). 

Let me get the full diff.
