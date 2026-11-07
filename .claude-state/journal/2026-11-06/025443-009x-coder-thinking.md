---
ts: 2026-11-06T09:54:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5L7xsyqyb4MNaQLCnWpS
---
This function is a big one — 281 insns, with barrier fences needed. The comment says the barriers are load-bearing for the allocation. Removing 13 barriers with "pure §47 live-length arithmetic"... The alternative is something that changes live lengths without a barrier. Hmm.

But wait: these functions are currently MATCH in src. The point of this shard is to find lever-free spellings. The barrier kinds here are `__asm__ __volatile__("")` fences which are asm. The pin is `register u32 base __asm__("$3")`.

The task: write a lever-free body that scores 0. That's very hard for these — that's why they're in a "crack shard". Let me first establish baseline: what does the current src body score? Actually delever_search compares the function in build/ — build/ has the current object. The src body with levers scores 0 presumably (it's the banked body). Let me verify with dt.sh using orig.c.

Let me first copy orig.c for each item and run the baseline. But careful: I should first diff orig.c against the src def (FRESH instruction). orig.c doesn't exist yet for these dirs, so I create it from src.

Let me plan the workflow:
1. For each item: copy current def to <dir>/orig.c, run dt.sh with orig.c to confirm baseline 0 (or whatever).
2. Then strip levers: create nopin.c (remove pins/barriers), measure.
3. Then try moves to recover.

Given the scale (4 items, 20-30 min each, potentially 2 hours), this is a big task. Let me start.

Let me first check the tools: delever_search.py usage, and dt.sh. Also sc.sh.

Let me look at the other items' functions too, to size them up.

First item func_80023BF0: 281 insns — big and complex. The 13 barriers are needed. Hard.

Let me look at the others.
