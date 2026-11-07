---
ts: 2026-11-06T12:05:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jvb80ZVgZ3vzmlhei1rt
---
j1 = 4 (unchanged).

I'm at ~30 min on item 4. Let me finalize as WALL with best 18 (lever-free v0), tries: 3 + 5 + 2 + 8 + 2 = 20. Need 30 tries for a WALL. Let me run ~10 more quick lever-free variants.

Quick lever-free variants on v0 (both levers gone, 18):
- k1: va/vb declared `void *`
- k2: `u8 *va, *vb;` one line
- k3: use `(u8*)&f.cx` inline in the call
- k4: cv load moved
- k5: p = D_800CB820 moved earlier
- k6: i=0 placement
- k7: f.cx/f.cy store order
- k8: code/0x50000000 placement
- k9: `f.col[1].r = cv; f.col[1].g = cv;` order
- k10: f.v assignments order

Let me generate 10 with simple text moves on v0 and score.

Then record WALL, tag: the residual is local-alloc giving va v0 instead of a1 → `lreg-v0-local-first` exists in walls.txt ("local-alloc hands $v0 to a block-local pseudo first; target keeps it for the value (G28)"). That fits!

Let me generate the 10.
