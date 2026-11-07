---
ts: 2026-11-06T10:20:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Bf81Afp5t5obV5zAGPR2
---
Now div is in s0 (good!). The remaining residual is an ordering/scheduling difference:
- mine[5:6] has `andi s1,s1,0xfff` early (at position 5), target doesn't.
- mine[14] `sll v1,s0,0x10` (div sign-ext uses temp v1), target[14] `sll s0,s0,0x10` (in-place).
- mine[16:18] lacks the andi at 16-17; target has `sll s0,s0,0x10; andi s1,s1,0xfff`.
- mine[18] `sra s0,v1,0x10`, target `sra s0,s0,0x10`.

So mine moved `andi s1,s1,0xfff` (a mask) EARLY (position 5), and the div sign-ext uses a temp v1 instead of in-place.

The target order (positions 13-18): sll s0,s0,0x10; andi s1,s1,0xfff; andi a0,v0,0xfff; bne s1,a0; sra s0,s0,0x10.

Mine: andi s1,s1,0xfff at position 5 (too early), then sll v1,s0,0x10 at 14, sra s0,v1,0x10 at 18.

The `a = a & 0xFFF` moved early (before the call). Because the do-while changed scheduling? Hmm, the `andi s1,s1,0xfff` at position 5 means a's mask was hoisted before the call. That's wrong (target has it after the call).

Also the div sign-ext uses a temp v1 instead of in-place because... `sll v1,s0,0x10; sra s0,v1,0x10` — gcc needs v1 because s0 is both the source and dest, and the sll/sra pair for sign-extension can't be in-place? Actually, `sll s0,s0,16; sra s0,s0,16` IS in-place and valid. Why does mine use v1?

Hmm, because `div = (s16)div` might be compiled as: sll v1,s0,16 (temp), sra s0,v1,16 (dest). The target has sll s0,s0,16; sra s0,s0,16. This is a combine/regmove difference.

Wait, in the target the sequence is `sll s0,s0,0x10; sra s0,s0,0x10` — the sll writes s0, then sra reads s0. In mine, `sll v1,s0,0x10; sra s0,v1,0x10` — the sll writes v1 (a temp), then sra reads v1 and writes s0. Both are 2 instructions; the difference is the temp register. This is because gcc's sign-extension pattern uses a temp when the destination is a pseudo (not a hard reg). With the pin, div is a hard reg so the sll can be in-place.

Hmm, this is the same "pin" effect: the sign-extension of a pseudo uses a temp. Interesting.

Actually, this might be fixable: the target's in-place `sll s0,s0,16; sra s0,s0,16` requires the destination to be the same register. For a pseudo, gcc emits `sll temp, src, 16; sra dst, temp, 16` where temp is a new pseudo. If combine merges temp and dst... 

Hmm. Actually, the target's in-place suggests the ORIGINAL used a hard reg (the pin) OR a different C construct.

Wait, but the target is the ORIGINAL game's code, which presumably didn't have a pin. So how did the original get `sll s0,s0,0x10; sra s0,s0,0x10` in-place? Maybe the original's `div` was a hard register because... hmm.

Actually, maybe the sign-extension is not `div = (s16)div` but the division uses `(s16)div` and the sign-extension is hoisted by cse into an in-place form. Or the original had `s16 div` and the sign extension at the use.

Hmm. Let me look at the current residual more carefully:
- mine[5:6] andi s1,s1,0xfff (a mask early)
- mine[14] sll v1,s0,0x10
- mine[18] sra s0,v1,0x10

Target:
- position 14: sll s0,s0,0x10
- position 16: andi s1,s1,0xfff
- position 18: sra s0,s0,0x10

So the differences:
1. a's mask is too early in mine (position 5 vs 16).
2. div's sign-ext uses temp v1.

For #1: the do-while caused a's mask to hoist. Hmm, or the a mask's position depends on sched1. The target has it after the call, between the div sll and the cur andi. Mine has it before the call.

Wait, why would `andi s1,s1,0xfff` be before the call in mine? a = arg2, and `a = a & 0xFFF` is after the call in the source. Sched1 could hoist it before the call (a is available from arg2). The target has it after the call. So in the target, something anchors it after the call (like the keepalive anchored ang).

Hmm! The keepalive in item 3 is on `ang`, not a. So the keepalive's removal might cause this ordering.

Let me re-add a real anchor: the keepalive anchored `ang` after `ang = ang - 0x400`, which is after the call. That would keep ang's addiu in place, and maybe the sll/andi follow.

Since I removed the keepalive, sched1 hoists a's andi.

So I need a real-C substitute for the keepalive too.

OK so item 3 has two sub-problems: pin (solved by do-while ref boost!) and keepalive (ordering).

Let me now focus on the ordering. Let me add the keepalive back temporarily to see if f1+keepalive scores 0. If yes, then I just need a real-C anchor.

Let me test f2 = f1 + keepalive on ang.
