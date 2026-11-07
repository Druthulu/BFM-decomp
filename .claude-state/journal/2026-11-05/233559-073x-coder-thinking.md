---
ts: 2026-11-06T06:35:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9iow46JRjM1GTXL2jqcS
---
Order: 73 76 72 74.
- r73: pri 27857, 13 refs, live 14 → takes $2 (v0)? But mine has the working value in v1...

Hmm. r73 (13 refs, live 14) is probably the `t` in the middle block... no wait. Let me identify:
- r72: 8 refs, live 26, pointer → a0 (the param, a pointer).
- r74: 3 refs, live 4, 2 bytes → the lhu/unk2 read?
- r73: 13 refs, live 14 → the address `&D_80126B62` or the constant?
- r76: 2 refs, live 2, ST_REGS → the `s16` compare temp?

Order: 73 first → $2; 76 → $3 (but ST_REGS); 72 → $4 (a0 is already in a0, and it's the param, so $4 preferred); 74 → $3?

Hmm, the final assignment in mine: the middle working value is in v1 ($3). 

The target (with the pin) would have t as a hard reg $2, so everything else moves.

Since the pin held `t` in $2 for the whole function, and lever-free r73 (13 refs/live 14 = 27857) takes $2.

What is r73? 13 refs in 14 insns — very dense. Likely the address/constant pseudo for `&D_80126B62` + the two `D_801D094C`/`D_801D093C` addresses? Hmm, 13 refs.

Let me look at the RTL: grep for reg 73 in the .lreg section of this function. Let me find the function's section first.

Alternatively: the middle section (14-28) computes the value. In mine, the value is v1. In the target, v0.

Hmm, the target's t = $2 = v0.

Since t is a *global* allocno (used across blocks: assigned in the if arms, used after), it competes with r73.

To make t take $2, t's priority must exceed r73's 27857, or r73 must conflict with $2.

What is r73? Let me check.
