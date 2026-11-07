---
ts: 2026-11-07T01:09:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H09dm5YDBocX73RmVkd1
---
Interesting! My candidate's generated code:
```
subu sp,sp,24
sw $16,16(sp)
sw $31,20(sp)
jal func_8017EE68
move $16,$4        <- s0 = a0 (in the delay slot, AFTER the call starts)
li $2,8
sw $2,512($16)
li $2,0x100000
move $4,$16
...
```
So the copy `move $16,$4` is in the jal's delay slot. The target probably has:
```
jal func_8017EE68
move $16,$4
...
```
Hmm, same? But the score says mine[10] = sw v0,516(a0) vs target sw v0,516(s0).

Wait, my dump shows `move $4,$16` before the second store... let me see the rest.

Hmm, my scratch dump may differ from the actual candidate scoring (which uses the real TU context). Let me see the full function.
