---
ts: 2026-11-06T23:57:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gHGIL2Jt9Y5YVbRBEDu6
---
p14_store_first: score 14, 161 insns! That's interesting — `*q = val; p = q;` (store first, then p=q) gives 161 insns (the copy!) with score 14 = REG-callee only (the s3/s4 swap).

So p14 produces the copy correctly! Let me check its diff: if it's exactly the same as G_nopin (only the reg swap), then the copy problem is SOLVED by `*q = val; p = q;`.

Wait: G_nopin also scored 14 with 161 insns. So p14 == G_nopin's residual? Let me diff p14.

If p14 is byte-identical to G_nopin except the s3/s4 swap, then the launder is cracked (lever-free copy) and only the reg order remains.

Let me check.
