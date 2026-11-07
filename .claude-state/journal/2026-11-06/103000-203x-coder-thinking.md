---
ts: 2026-11-06T17:30:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TUmD1BdZVvHLP9bC3mpS
---
Target:
```
bc04 move a0,v0        ; angle saved to a0 (angle = func_80029D3C(...))
bc08 sh v0,242(s0)     ; p[0x79] = angle  (v0 = angle)
bc0c lbu v1,73(s2)     ; r[0x49]
bc10 li v0,5
bc14 beq v1,v0,bc38
bc18 sll v0,a0,0x10    ; delay slot: sh16 = angle << 16  (angle in a0, result v0!)
...
bc2c lhu v0,242(s0)
bc34 sll v0,v0,0x10    ; sh16 = p[0x79] << 16 (v0)
bc38 sra v1,v0,0x10
```
So the target: angle is in a0 (saved from the call), and the sll result goes to v0.

Interesting: the target's `sll v0,a0,16` uses a0 as the source and v0 as the dest. In mine, the sll is `sll v1,?,16` — let me check mine's asm around there.

Mine's flow: the angle pseudo is in some reg; the sll output 75 prefers the input's reg (v1). In the target, the input (angle) is a0 and the output is v0 — so the preference wasn't followed (the pin forced v0).

Lever-free, to get the sll output in v0, the *input* should be in v0... but the input `angle` is also stored to p[0x79] (`sh v0,242(s0)` at bc08) — the store uses v0. In the target, the angle value is in v0 at bc08 (the store), and a0 holds the angle for the sll.

So the angle value: v0 (call result) → stored; a0 (copy) → used in the sll. Hmm, the target has `move a0,v0` (angle saved to a0), then the sll uses a0.

Lever-free, gcc might do the same if the copy preference works out.

In mine, let me look at the same region of the nopin asm.
