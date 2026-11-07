---
ts: 2026-11-07T01:01:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L6E0mOtTY16VQ84VCXSJ
---
All ≥43. 45 tries now. Time: 18:00 → now ~18:06? Let me check. Started 17:57, need 20 min → until ~18:17.

Let me use the time to verify the wall evidence with alloc_table (ground truth for the priority claim), and maybe one more idea: what if the function's *return type* being void vs the caller's use matters? No.

One more idea worth testing: the target's prologue order is sw s3; move s3,a0; sw s0; move s0,a2; ... In mine: move s0,a0; move s1,a2; move s3,a3; move s2,a1. The save/restore order follows the alloc. Not fixable.

Let me look at whether `a` (param a_) could be made to rank differently — target a=s2 matches mine. Good.

So the only mismatch is the 3-cycle p,b,c. And p's priority is structurally the highest.

Let me get ground truth on priorities. Check tools/alloc_table.py usage.
