---
ts: 2026-11-06T21:52:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4l0ZGGE9jNrJD5oFEoOk
---
Now item 2: func_801919A0 (ov_SC06_032), kinds pin, PARTIAL:pin best 0. The launder is already cracked (src holds the cracked body). Remaining: $3 (dst) and $2 (tmp) pins.

From notes: "Dropping $3 (dst) and $2 (tmp) from the cracked body (e1.c) = 135: 709 ins and dst lands in a2 instead of v1 ($3), plus the whole dst-chain register bank shifts."

Twin func_80191C50 same.

Let me look at the current src and prev_win for 801919A0. First regenerate orig.c fresh and diff with prev_win.

The body is 308 lines. Let me find the function in src. The notes say src:2960-3267. Let me diff prev_win vs that range.
