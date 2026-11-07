---
ts: 2026-11-06T06:09:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Otzv7a2md7dNlm5kkTHs
---
The orig has only ONE global allocno (74, in $2). So in the target, s0 is hard $16 and pa0 is reg 74 in $2? Hmm, but the target's asm shows `move a0,s0` and uses a0 (pa0 = $4). Hmm, reg 74 in $2 — that doesn't match.

Wait, the dispositions: 74 in 2, 108 in 4. Hmm, 108 might be pa0.

Hmm, "1 regs to allocate: 74" — only one cross-block allocno. So pa0 (the launder's output) is a local qty (allocated within a block) — 108 in $4.

OK so in the target: s0 = hard $16, pa0 = $4 (local-alloc, block-local).

In p1 (no pin, no pa0): 72 in 16 (s0 var), 73 in 17 (another), 74 in 2, 76 in 4.

So removing the pin created a SECOND cross-call allocno (73). What is it?

Hmm, reg 73 in p1: "conflicts: 72 73 74 76 2 3 4 5 29". Let me identify it from the RTL. In the orig, reg 73 is `(reg/v:SI 73)` at insn 6 — that's the s0 variable (hard $16). In p1, reg 72 is $16 and reg 73 is $17.

Wait, in p1 the RTL register numbers differ. Let me look at p1's rtl for reg 73.

Actually, maybe p1's reg 72 = s0 (the source variable) and reg 73 = a *second* pseudo created by the `(s32)a0` cast or by the copy.

Hmm, let me grep p1's rtl for reg 73.
