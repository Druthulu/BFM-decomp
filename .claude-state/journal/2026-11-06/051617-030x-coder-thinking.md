---
ts: 2026-11-06T12:16:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_135OTh8DGmUGjvrQwHpY
---
Compare:

Target:
```
371 lhu v0,-2(s3)     ; vv2 = p->unkA
372 lw  v1,212(sp)    ; sz
373 srl a0,s1,0x18    ; vh = rec>>24
374 sh  v0,72(sp)     ; v0.vy = vv2 (offset 0x48+2=74? wait sp+72 = v0.vx at 0x48)
375 srl v0,s1,0x10    ; vw = rec>>16
376 lhu a1,0(s3)      ; v0.vx = p->unk8
377 andi v0,v0,0xff   ; vw & 0xFF
378 sh  v1,76(sp)     ; v0.vz = sz (0x4C)
379 sh  v1,84(sp)     ; v1.vz = sz (0x54)
380 addiu v1,sp,72
381 sh  v0,80(sp)     ; v1.vx = vw&0xFF (0x50)
382 addiu v0,sp,80
383 sh  a0,82(sp)     ; v1.vy = vh
384 sh  a1,74(sp)     ; v0.vx = p->unk8 (0x4A)
```
Hmm wait: v0 at sp+0x48 = 72; v0.vx=72, v0.vy=74, v0.vz=76. v1 at sp+0x50 = 80; v1.vx=80, v1.vy=82, v1.vz=84.

Target: sh v0,72(sp) at 374 — that's v0.vx? But 371 loaded vv2 (p->unkA) into v0 and 374 stores v0 at 72 = v0.vx?? That would be wrong semantically... unless the store at 374 is v0.vy... no, 74 is vy.

Hmm, wait. Maybe at 374 the register v0 holds... 371 lhu v0,-2(s3) = p->unkA = vv2, stored at 72 = v0.vx? That's odd. Unless the compiler renamed. Let me re-read: maybe `sh v0,72(sp)` stores vv2 into v0.vy? offset 72 = 0x48 = v0.vx. Hmm.

Hold on: maybe I mis-assigned: perhaps v0.vx is loaded at 371 from -2(s3) = p+0xA... no, `v0.vx = p->unk8` (p->unk8 = offset 8), and `vv2 = p->unkA` (offset 10). The load at 376 `lhu a1,0(s3)` where s3 = p? If s3=p then 0(s3)=p->unk0... Hmm, s3 might be p+8. So lhu a1,0(s3) = p->unk8 = v0.vx, and lhu v0,-2(s3) = p->unk6? No, -2 from p+8 = p+6 = unk6.

Hmm. So s3 = p+8. Then -2(s3) = p+6 (unk6), 0(s3) = p+8 (unk8). Hmm but the code uses p->unk8 and p->unkA.

Wait — maybe s3 = p + 0xA: then 0(s3) = unkA = vv2, -2(s3) = unk8 = v0.vx.

Let's test: target 371 lhu v0,-2(s3) = unk8 = v0.vx → stored at 72 = v0.vx. ✓ consistent!
376 lhu a1,0(s3) = unkA = vv2 → stored at 74 = v0.vy (sh a1,74(sp) at 384). ✓
373 srl a0,s1,0x18 = vh → stored at 82 = v1.vy ✓
375 srl v0,s1,0x10 = vw; 377 andi 0xff → stored at 80 = v1.vx ✓
sz v1 → 76 (v0.vz) and 84 (v1.vz) ✓

Great, consistent. So target order of stores: v0.vx (374), v0.vz (378), v1.vz (379), v1.vx (381), v1.vy (383), v0.vy (384).

Interesting: v0.vx is stored FIRST at 374 (from the load at 371, before vh's srl), and v0.vy LAST at 384.

Mine v3 order: 371 lhu v0,-2(s3)=v0.vx; 373 sh v0,72(sp) [v0.vx]; 374 srl v0,s1,0x10 (vw); 375 lhu a0,0(s3)=vv2; 376 andi; 377 sh v0,80(sp) [v1.vx]; 378 srl v0,s1,0x18 (vh); 379 sh v1,76 [v0.vz]; 380 sh v1,84 [v1.vz]; 382 sh v0,82 [v1.vy]; 384 sh a0,74 [v0.vy].

So the differences are ordering of the stores and the fact that mine uses v0 for vh (at 378 srl v0) then sh v0,82. Target uses a0 for vh. That's a register allocation difference: vh in a0 vs v0.

Key: target computes vh (a0) EARLY at 373, before vw's srl at 375 and before the v0.vx load at 376. Mine computes vh at 378, after.

The keepalive asm forces vh, vv2, vw to be live simultaneously (all three are asm operands at that point) — giving them registers and forcing the computation order/priority.

Real-C alternative: make vh, vw, vv2 each have an additional use (so their lifetime/priority is like being held). Hmm, but a second use of vh at q[0x1D] (earlier) would compute it earlier — v4 did that and got much worse (100). Why? Because hoisting `vh = rec >> 24` to before q[0x1D] moved the srl earlier and reused it — target has a separate srl at 373... wait target 373 is srl a0,s1,0x18 = rec>>24. And q[0x1D] = q[0x0D] + (rec>>24) — where is that computed in target? Let's find. If target computes rec>>24 twice (once for q[0x1D] and once at 373), then hoisting to one use is wrong.

Let me dump the target region where q[0x1D] is stored (offset 0x1D in the primitive). That's around index 340-360.

Let me look at target 320-365.
