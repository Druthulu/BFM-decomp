---
ts: 2026-11-06T06:37:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HRzfgAroEOR40NYzLDnb
---
Now item 3: func_801919A0__ov_SC06_032_jr_801919A0 (307 ins) — big. Or the two 307/308 items in ov_SC06_018. Let me look at the remaining items:
- func_8019059C (308 ins) ov_SC06_018
- func_80191C50 (307) ov_SC06_018
- func_801919A0 (307) ov_SC06_032

All big. Let me extract one and see.

Strategy for the big ones: try the "drop each lever kind separately" test to find a PARTIAL quickly, then spend the remaining time trying to crack the other lever.

Let me do func_801919A0 first (307).

Actually, the two ov_SC06_018 items are in the same TU — maybe they share a pattern.

Let me extract func_8019059C first (I already saw its head at line 2787). It has pins $16,$3,$2 and launders.

Let me extract and score orig, then test the separate removals.

Note: for big functions, each score takes longer (maybe 10-20s). Let me be efficient.

Let me extract both ov_SC06_018 items and score their origs.
