---
ts: 2026-11-06T21:11:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PklIXDb8yXBx71q2ORcx
---
Interesting! 
- l_only (launder kept, barrier dropped): score 4 ORDER — so dropping the barrier causes an ORDER difference.
- b_only (barrier kept, launder dropped): score 4 REG-caller — same a0/a1 swap.

Wait, that contradicts: b_only keeps the barrier but drops the launder → still 4 (the swap). And l_only keeps the launder but drops the barrier → 4 (ORDER). So BOTH are needed together (score 0), and each alone gives 4 but different diffs. Hmm.

So the launder is needed to fix the a0/a1 swap. b_only (no launder) has the swap → confirms launder fixes a0/a1. And the barrier is needed for the ORDER difference (something else). Wait but l_only has launder and no barrier → ORDER diff, no REG diff. So launder fixes REG (a0/a1), barrier fixes ORDER.

Hold on, that means the barrier and launder each fix a different residual. So I need real-C moves for both:
1. A move that raises e's refs (replaces launder) → fixes a0/a1.
2. A move that replaces the barrier → fixes the ORDER diff.

Let me see the ORDER diff in l_only. Let me get the full diff.
