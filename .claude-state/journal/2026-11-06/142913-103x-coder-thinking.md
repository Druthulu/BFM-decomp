---
ts: 2026-11-06T21:29:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NBAAFLSAX0YhHdx4VpSZ
---
Now I see: at 81c `bgez v0, 828` with delay slot `move s0,v0` (n=q), then at 824 `addiu s0,v0,3` (n=q+3). Then sra/sll/subu on s0. So n is in s0.

Note the DELAY SLOT: `move s0,v0` is in the bgez delay slot. This is a branch with delay slot. So the block: bgez, delay move s0,v0, addiu s0,v0,3, then merge at 828.

n crosses blocks (the bgez branch). So n is global-alloc. Target gives it s0.

Without the pin, mine gives n v1. Why? Global-alloc prefers caller-saved for non-call-crossing allocnos. To force s0... 

Hmm. But wait — mine's sequence:
```
68 move v1,v0
69 addiu v1,v0,3
70 sra v1,v1,2
71 sll v1,v1,2
72 subu v0,v0,v1
```
So mine uses v1 for n and v0 for q. Target uses s0 for n and v0 for q. Both valid.

The difference: register choice. The pin forced s0. Real C can't pin. Unless... the target's choice of s0 is because s0 is used for something else in the target (p, ent, etc. are in s1/s2). Let me look at the target's register usage: s0 = n, s1 = ent?, s2 = a0? Let me check.

Target prologue: `move a1,s0` at 55 (a1=s0 for the call arg). Hmm, s0 is used as the radius argument. Let me look at the whole target prologue.

Actually, in target, s0 is used for the rand() results/modulo AND for the call argument at 55 (`move a1,s0`). So s0 is a scratch that persists? Let me read the prologue.

Let me read target.s lines 1-55.
