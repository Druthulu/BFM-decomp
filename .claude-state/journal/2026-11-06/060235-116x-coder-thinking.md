---
ts: 2026-11-06T13:02:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Po4vanOVptecdL93W0kr
---
Mine (p2):
```
la $4,D_80127548
lw $3,0($4)      ← dcount = v1
addu $4,$4,4     ← dp++ 
li $2,0x24       ← c36 = v0
subu $2,$2,$3
...
```
Target:
```
lui a0,0
addiu a0,a0,0
lw v1,0(a0)
li v0,36
addiu a0,a0,4
subu v0,v0,v1
```
So the difference: `dp++` (addiu a0,a0,4) is before the `li` in mine, after in the target. Both 159 insns; just order.

This is sched1 ordering within the block. The `li` (constant) vs `addiu` (dp increment): sched1 chose differently.

In the target, `dp++` comes after `li v0,36`. In mine, before.

Hmm, why? The target has the c36 keepalive asm before `df = c36 - dcount;` which is after `dp = dp + 1;` in the C:
```
dp = D_80127548;
dcount = *dp;
c36 = 0x24;
__asm__ keepalive;
df = c36 - dcount;
tmp = ...;
dp = dp + 1;
ba = ...;
```
So in the C, `dp = dp + 1;` comes AFTER `df`/`tmp`. The RTL order: lw, li, subu, sll, addu, sll, addiu(dp++), addu(ba).

Target asm: lw v1; li v0; addiu a0,a0,4 (dp++!); subu v0,v0,v1; sll... 

Wait, the target has dp++ at fe4, right after li v0,36 and before subu. So sched1 moved dp++ up (it's independent). In mine it's after the sll chain? No, mine has it at 210 (right after lw) — even earlier.

So both moved it, differently. The target: lw, li, dp++, subu. Mine: lw, dp++, li, subu.

sched1's ordering of the li vs the addiu. Hmm.

Lever-free ideas: change the order of the C statements so the RTL order differs:
- Move `dp = dp + 1;` before `c36 = 0x24;` in the C? Then RTL: lw, addiu, li, subu. sched might keep it.
- r2 moved `c36` before `dp = D_80127548` — no change.

Let me try:
- s1: move `dp = dp + 1;` to right after `c36 = 0x24;` in the C.
- s2: move `c36 = 0x24;` after `df = ...`? can't.
- s3: `df = c36 - dcount;` → compute `tmp` first?
- s4: make `c36` a literal in the expression: `df = 0x24 - dcount;` and keep c36 assigned elsewhere... but c36 must exist (it's not a lever; I can change it).

Hmm, actually: what if `c36` is removed entirely and `df = 0x24 - dcount;`? Then `li v0,36` still emitted. But then the "keepalive" variable disappears... we're already in the PARTIAL:launder state where the keepalives are gone. c36 is just a variable. Removing it is a real C change. But careful: c36 also... it's only used in `df = c36 - dcount`. So `df = 0x24 - dcount;` is equivalent.

Let me try:
- s1: `dp = dp + 1;` moved right after `c36 = 0x24;`
- s2: `df = 0x24 - dcount;` (drop c36)
- s3: `df = c36 - dcount;` written as `df = -dcount + c36;`? Hmm, that changes subu operand order.

Let me test s1, s2.
