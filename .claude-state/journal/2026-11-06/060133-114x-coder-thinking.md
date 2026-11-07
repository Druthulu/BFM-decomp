---
ts: 2026-11-06T13:01:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iYtfvgEn860FGkNZqosS
---
p2 = score 2, 159/159 ins, only the `li v0,36` position (mine at 125, target at 124) — a 1-insn ordering difference in the c36/dcount block.

That's the same issue as before (the c36/dcount swap is now just an ordering).

Let me fix it: the target has `lw v1,0(a0)` (dcount) then `li v0,36` (c36); mine has `li v0,36` then `lw v1,0(a0)`? Let me look:
diff: insert target[124] `li v0,36`; delete mine[125] `li v0,36`. So mine has one more insn before the li.

Let me look at the actual region in both. Target:
```
fd4: lui a0,0
fd8: addiu a0,a0,0     ← dp = D_80127548
fdc: lw v1,0(a0)       ← dcount
fe0: li v0,36          ← c36
fe4: addiu a0,a0,4     ← dp++
```
Mine (p2) presumably:
```
lui a0; addiu a0,0; lw v1,0(a0); addiu a0,a0,4; li v0,36 ...
```
So the `li v0,36` is 1 insn later. sched1 ordering: the `dp++` moved before the li.

Lever-free fix: a do-while(0) block split between `dcount = *dp;` and `c36 = 0x24;`? Or reorder the C statements.

Let me try:
- r1: `do { c36 = 0x24; } while (0);` after dcount.
- r2: `c36 = 0x24;` moved before `dp = D_80127548;`.
- r3: `dp = dp + 1;` moved after `df = ...`.
- r4: `do { dcount = *dp; } while (0);`

Let me test a few.
