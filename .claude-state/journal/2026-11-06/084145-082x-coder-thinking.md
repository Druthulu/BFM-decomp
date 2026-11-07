---
ts: 2026-11-06T15:41:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rctlHCXopswb53SBAope
---
Target:
```
894: addiu a2,v0,8       <- n = q+8, a2 = $6 (pinned n)
898: lui v0,0x0          <- load D_80126950 into v0
89c: lw v0,0(v0)
8a0: nop
8a4: addiu v0,v0,500
8a8: mult a2,v0
```
So the constant load goes into v0, and `mult a2,v0`.

Mine: the load goes into v1 and `mult a2,v1` — the register choice differs (v0 vs v1). Score 9 (a few position/reg differences).

Since n is pinned to $6=a2, the launder's effect must be on the cse/alloc of the constant temp.

Let me see mine's asm.
