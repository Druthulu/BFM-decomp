---
ts: 2026-11-06T11:05:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LCZfTuOoFgA5X7TTNTpD
---
Mine's loop start is at fc0; the target's at fc0 too but the target has an extra insn at fb8/fbc? Let me compare:

Target:
```
fb4 beqz v0,1010
fb8 move s1,zero
fbc move s3,v0
fc0 sll v0,s1,0x10
...
fdc beqz v0,ff8
fe0 addiu v0,s1,1     <- delay slot
fe4 move a0,s0
fe8 jal
fec move a1,s2
ff0 move s0,v0
ff4 addiu v0,s1,1
ff8 move s1,v0
ffc sll
1000 sra
1004 slt
1008 bnez v0,fc0
100c addiu s2,s2,32
```
Mine:
```
fb4 beqz v0,100c
fb8 move s1,zero
fbc move s3,v0
fc0 sll ...
...
fdc beqz v0,ff0
fe0 ??? (probably nop or something)
```
Let me see mine's fdc-ff8. The diff said mine[83] beqz v0,ff0 vs target ff8, and mine lacks the addiu at 84. Let me dump mine's fc0-ff8.
