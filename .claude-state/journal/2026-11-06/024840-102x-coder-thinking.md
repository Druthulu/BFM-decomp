---
ts: 2026-11-06T09:48:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_skMeqCTz1t2f0gDFD5Fx
---
The same one-insn diff on all includers. Good — the WALL is stable.

Time 02:48:31. ~4.3 min to go. Let me write the results row now (that's an action), then notes, then the moves line, then the log. The writing will span the remaining time.

Actually, I realize I should double check the item-3 win.c: the brief says "write a lever-free body of func in G25x/<dir>/win.c (bare definition) that scores 0" — for a WALL, win.c is the best lever-free body (score 2). Fine.

Also clean up the dump dirs for item 3 (dump_o, dump_w) per the disk rule. Let me do that.

Results row for item 3:
dir func_8016432C__func_8016432C, file src/shared/ov/func_8016432C.h, func func_8016432C, kinds keepalive, result WALL, best 2, tries ~60, wall sched1-argcopy-hoist, evidence.

Tries count: orig, win, t1,t3,t4,t6,t7,t9,t10,t11 (10), u1,u2,u4,u5,u6,u7,u8 (7), v1-v7 (7), q1,q2 (2), w1,w6,w7,w9,w10,w11,w12,w13 (8), y1,y2,y7,y8,y9,y11,y12 (7), z1,z4,z5,z7,z8,z9,z10,z11 (8), aa1-aa6 (6), bb1-bb4 (4), cc1-cc4 (4), dd1-dd10 (10), ee1-ee8 (8), ff1-ff4 (4), allinc 6. Total ≈ 85+. Say 85.

Evidence ≤140 chars: "sched1 places the call-arg copy a0=s0 one cycle before the 0x188 store (volatile keepalive asm was the barrier); local-alloc then rewrites the store base to a0; lever-free 2 on 6 includers".

That's ~180 chars. Trim: "sched1 puts the arg copy a0=s0 before the 0x188 store once the volatile asm barrier is gone; local-alloc rewrites the store base to a0; lever-free 2". ~145. Trim more: "sched1 schedules the arg copy a0=s0 before the 0x188 store without the volatile-asm barrier; local-alloc then rewrites the store base to a0; best 2". ~145. Let me count precisely later; aim ≤140.

"volatile asm was the only barrier; without it sched1 puts the a0=s0 arg copy before the 0x188 store and local-alloc rewrites the base to a0; best 2" — count: let me estimate ~150. I'll trim to: "sched1: a0=s0 arg copy moves before the 0x188 store once the volatile-asm barrier is gone; local-alloc rewrites its base; best 2" (~135).

Let me write.
