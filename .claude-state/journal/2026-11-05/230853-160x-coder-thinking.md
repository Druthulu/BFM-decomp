---
ts: 2026-11-06T06:08:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yGd8luR3EpYbtU6Cc3Et
---
p1's global allocnos: 72 in 16 (s0), 73 in 17 (s1), 74 in 2, 76 in 4.

So reg 72 (in $16) and reg 73 (in $17). Both are cross-call allocnos. 72 is probably the `s0` variable, 73 is... another pointer-ish value? The `move s1,s0` at the prologue copies 72→73.

What is reg 73? Maybe the `a0` parameter used after the first call? Hmm.

In the target (pinned), s0 is a hard reg, so there's no allocno for it; pa0 (the launder copy) is an allocno.

Hmm, so in p1 there are two allocnos (72, 73) both crossing calls. In the target, the pinned s0 is hard, and pa0 is the only cross-call allocno.

Wait — but p1 has no pa0. So why two?

Let me look at the RTL to identify reg 73. Let me grep the greg/rtl for reg 73.

Actually — maybe reg 73 is `loc`'s address or the `v0` in the last block? No, those are local.

Hmm, reg 73 conflicts with 5 as well (a1). It's used across calls. Let me look at the rtl.

Actually, let me try a different approach: keep the `pa0 = s0` copy (a plain C copy) — that's what n2 was (score 25, 67 ins). n2 had the same issue.

Hmm.

Let me look at the target's greg to see the allocnos. Let me dump the orig.

Actually, the target's asm has only s0 saved (frame 48). So only one callee-saved allocno.

Let me look at the orig's greg dump.
