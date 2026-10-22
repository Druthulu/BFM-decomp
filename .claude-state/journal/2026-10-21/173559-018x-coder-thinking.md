---
ts: 2026-10-21T23:35:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cEZtO9Wh6KKv3zBfeOi1
---
Now I understand the target for func_80180D54 (and func_801815D4 is nearly identical).

The C source I have produces 120 ins vs target 119. The difference: mine has `sw s0,32(sp)` at 4 instead of `addiu a1,sp,24` — so mine saves s0 later and keeps sp+24 in s0. Target: computes a0=sp+16, a1=sp+24 directly, no s0 for the address. s0 holds param_1 (a0).

So in the target, the address sp+24 is NOT held in a register across the call — it's recomputed. That means the launder in the original forces a *different* behavior than what I assumed.

Wait, but the original src has the launder and presumably scores 0. Let me verify: score the original.

Hmm, but mine (a1 = launder removed) has 120 ins with s0 = sp+24, and target has 119 with s0 = param_1. So actually removing the launder made gcc MORE aggressive. But then how does the original with launder give target's code?

Let me score the original to check.

Actually wait — maybe a1.c is not the original minus launder correctly. a1.c removed both launders and kept p0/p1. And b1.c removed p0/p1 entirely (using sp10 directly).

Hmm, and mine(a1) has 120 ins and target 119. And the "register pairs s1->s0 x13, s0->s1 x8" indicates a systematic register swap, which is just how the diff tool maps.

Let me score the original first.
