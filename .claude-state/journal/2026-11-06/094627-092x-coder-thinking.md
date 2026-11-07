---
ts: 2026-11-06T16:46:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Sth4mpK2yuXDodfALOnS
---
The target: `move t0,v0` after RotTransPers → cnt in t0. Interesting: the source `cnt = RotTransPers(...)`. Target uses t0 for cnt. Then `sll t0,t0,2`.

Mine (nopin all): `move t1,v0`? From the earlier diff: mine[53] `sll t1,t1,2` vs target `sll t0,t0,2`, and mine `div zero,a1,t1`. So in the fully-unpinned body, cnt landed in t1 instead of t0. With no_t0c (ot, fp pinned), the score was 5 and cnt was in t0 (the diff didn't mention it). So the ot pin ($9=t1) keeps t1 occupied, forcing cnt into t0.

So the ot pin's function: reserve t1 so cnt goes to t0. Without it, cnt=t1.

Hmm, the target has ot in t1 (pin $9) and cnt in t0. To get cnt in t0 without pinning ot, we need the allocator to prefer t0 for cnt. cnt's live range is long (across the div and loop). t0 is caller-saved; t1 also. The allocation order/priority decides.

This is a hard register-allocation puzzle across a 265-ins function. The fp pin (s0) is even more structural (score 47).

Given the budget (20-30 min per item) and that this is one of 4 items, maybe this is a WALL. But let me try some things. The 3-pin removal is 52; the biggest is fp ($16=s0).

Let me look at the fp residual: score 47, 268 vs 265 (3 extra insns). See its diff.
