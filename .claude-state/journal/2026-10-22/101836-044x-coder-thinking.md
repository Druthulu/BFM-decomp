---
ts: 2026-10-22T16:18:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HreDGJ5iRWxWsrtUN2Tl
---
r1/r2 still 1. So the declaration order doesn't change the beq order. r5 got 2 (16 ins? no, 19 ins, MIXED) — hmm r5 = q9 + `return 0` instead of goto zero + declaration swap → 2. Interesting: maybe r5 differs in a different way. Let me check r5's diff — 2 could be closer or different.

Let me look at r5's diff and also check whether the beq order changed.

Actually r5 has `if (it == p) return 0;` and no zero label. Score 2 (MIXED, 19 ins). Let me diff.

Also let me think about the beq order more: the cse2 EQ is (p,it). Maybe it's cse's `fold_rtx` that swaps because the second operand (it) has a REG_EQUAL symbol and the first (p) has a REG_EQUAL plus? In cse.c's fold_rtx, for a comparison it does:
```
      /* Put the constants on the right... */
```
Hmm.

Let me check the .cse dump (after cse1) to see if the swap happens in cse1 or later. If cse1 swapped, then the mechanism is fold_rtx. Let me grep the .cse dump.
