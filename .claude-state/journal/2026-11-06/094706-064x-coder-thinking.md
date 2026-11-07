---
ts: 2026-11-06T16:47:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h2BUFVqDCqHWNVIlPMdz
---
n08 = 34 (better but still far). n02 compile error (duplicate decl probably).

Hmm. The pin gives 0; lever-free is 34-37. This looks like a WALL unless I find the right source shape.

Let me think about the target's register assignment more concretely. Target: $2=v0, $3=v1, $4=a0r, $5=a1, $1=at. That's a perfect descending assignment: the highest-priority local gets $2.

Unpinned: the shift temp takes $2, then v0 $3, v1 $4, a0r $5, a1 $6.

So the shift temp has the highest local-alloc priority. If I can make v0 have higher priority than the shift temp, or merge them...

local-alloc priority: let me read the actual code to understand. local-alloc.c around 1486-1507 (C0505 reference).
