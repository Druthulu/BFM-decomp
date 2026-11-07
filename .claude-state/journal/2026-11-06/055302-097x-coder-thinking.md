---
ts: 2026-11-06T12:53:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GcVjSoqgOR90kHD52iXe
---
Differences:
1. The prologue: mine `sw s3,36(sp); move s3,a2` at insn 5-6, target `addiu a1,sp,16` then `sw s3,36(sp)` at 8. So the frame save placement differs and mine uses s3 for something the target keeps in a1 (the local[4] array address = sp+16!).

Actually target: `addiu a1,sp,16` — a1 = &local (the local array passed to func_8013914C). Mine: `move s3,a2` (s3 = param_3 = pb).

Hmm, in mine, a1 = sp+16 is emitted later (insn 11). So the ORDER differs (sched1) and a2 vs a1 for pb.

2. The copy loop: target uses a2 for dst (the pinned $4 is dst... wait, `register u16 *dst __asm__("$4")` = a0). Hmm, target: `addu a1,v1,a0; move a0,a1; lhu v0,0(a2)`. So dst = a0 (pin $4) and src = a2? Let me look at the target's tail asm in full.

Let me dump the target asm.
