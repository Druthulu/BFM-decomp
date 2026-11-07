---
ts: 2026-11-06T12:16:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HQxkKPyLjS5TV1s4SJDe
---
Target at 340: `srl v1,s1,0x18` = rec>>24 for q[0x1D] (addu v0,v0,v1 at 343, sb v0,29(s0) = q[0x1D]). So target DOES compute rec>>24 twice: once at 340 (into v1) and once at 373 (into a0). So hoisting is wrong. Good to know.

Mine (v3) at 340-343 presumably same. Yes since score diff only at 373+.

So cluster B needs: at the fill, vh = rec>>24 must land in a0 and be computed before vw's srl and before the v0.vx load; the stores ordered as target.

Currently in C:
```
v0.vx = p->unk8;      // load at 371 (target) / mine 371
vv2 = p->unkA;        // load: target 376 (a1); mine 375 (a0)
v0.vy = vv2;          // store 74: target 384, mine 384 (same slot, different reg order)
v0.vz = sz;           // 76: target 378, mine 379
vw = rec >> 16;       // target 375, mine 374
v1.vx = vw & 0xFF;    // 80: target 381, mine 377
vh = rec >> 24;       // target 373, mine 378
v1.vy = vh;           // 82: target 383, mine 382
v1.vz = sz;           // 84: target 379, mine 380
```
So mine's order is close but shifted: mine does vw at 374 (before the vv2 load at 375), target does vh at 373 first, then vw at 375, load at 376.

The difference: target schedules vh's srl earliest (into a0), mine schedules vw's srl earliest (into v0) and vh later.

Registers: target vh→a0, vw→v0, vv2→a1, v0.vx→a1?? no: 376 lhu a1,0(s3) then 384 sh a1,74(sp) = vv2 into v0.vy. And v0.vx load at 371 into v0 → sh v0,72(sp) at 374. So v0.vx's value dies at 374, freeing v0 for vw.

So the allocator: vh lives long (from 373 to 383), vw from 375 to 381, vv2 from 376 to 384, v0.vx from 371 to 374. Target gives: vh=a0, vw=v0, vv2=a1, v0vx=v0 (dies before vw computed — actually 371 loads into v0, dies at 374, then vw at 375 also v0). 

Mine: v0vx=v0 (371→373), vw=v0 (374→377), vv2=a0 (375→384), vh=v0 (378→382).

So the only real difference is which of vh/vv2 gets a0 vs v0, and the store order.

This is exactly what the keepalive asm does: it forces all three live at the asm point, so their priorities/conflicts are set: vh and vv2 both live past the fill end, so they need two different registers (a0, a1), while vw dies at v1.vx.

Without the asm, gcc computes vh later (just before its use at v1.vy) so it can reuse v0.

Real-C approach to extend vh's lifetime: use vh again AFTER the fill — but the only later uses are the gte_ldv3/rtpt and the q stores; there's nothing.

Alternative: reorder the C statements so that vh is computed before the vv2 load, e.g.:
```
v0.vx = p->unk8;
vh = rec >> 24;
vv2 = p->unkA;
v0.vy = vv2;
...
```
Statement order affects the initial sched1 order. Since target has vh at 373 before the vv2 load at 376, maybe writing vh earlier in C gives it.

But note the sched1 order is not the C order necessarily. Let's just try permutations. The number of orderings of these 9 statements is large; but the moves.md worked example says the ascending order (vx,vy,vz / vx,vy,vz) is what works WITH the asm. Without the asm we need a different C order.

Cheap experiment: try a set of hand-picked orders.

Ideas:
(a) Compute vh right after v0.vx:
```
v0.vx = p->unk8;
vh = rec >> 24;
vv2 = p->unkA;
v0.vy = vv2;
v0.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
v1.vy = vh;
v1.vz = sz;
```
(b) group as target's store order: v0.vx, v0.vz, v1.vz, v1.vx, v1.vy, v0.vy:
```
v0.vx = p->unk8;
v0.vz = sz;
v1.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
vh = rec >> 24;
v1.vy = vh;
v0.vy = p->unkA;   (no vv2 temp)
```
(c) drop vv2/vw/vh temps entirely: 
```
v0.vx = p->unk8;
v0.vy = p->unkA;
v0.vz = sz;
v1.vx = (rec >> 16) & 0xFF;
v1.vy = rec >> 24;
v1.vz = sz;
```
This is the natural C. Might give different allocation.

(d) make vh a u8/s32 width change; `s32 vh` is already s32.

Let me also consider: the target's `sh v1,76(sp)` (v0.vz = sz) at 378 and `sh v1,84(sp)` (v1.vz) at 379 are adjacent — sz is in v1 and stored twice consecutively. Mine has them at 379/380 also adjacent. Fine.

Let me generate ~8 order variants and score. Also include the no-temp variants.

Since cluster A is fixed by the do-while around the store (v3), all variants build on v3.

Let me write gen2.py with a parametrized fill block: I'll replace the FILL text with arbitrary text per variant.

Variants:
f1: (a) above
f2: (b) above
f3: (c) no temps
f4: c with v0.vy from p->unkA inline but vw/vh temps kept:
```
v0.vx = p->unk8;
vv2 = p->unkA;
v0.vy = vv2;
v0.vz = sz;
v1.vx = (rec >> 16) & 0xFF;
v1.vy = rec >> 24;
v1.vz = sz;
```
f5: reorder target's store order with temps:
```
v0.vx = p->unk8;
v0.vz = sz;
v1.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
vh = rec >> 24;
v1.vy = vh;
v0.vy = vv2;   // vv2 must be assigned before
```
Hmm vv2 assign must precede. Let me write:
```
v0.vx = p->unk8;
vv2 = p->unkA;
v0.vz = sz;
v1.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
vh = rec >> 24;
v1.vy = vh;
v0.vy = vv2;
```
f6: like f5 but v0.vy earlier.
f7: (a) but with vh assigned before v0.vx.
f8: temps but vh first:
```
vh = rec >> 24;
v0.vx = p->unk8;
vv2 = p->unkA;
v0.vy = vv2;
v0.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
v1.vy = vh;
v1.vz = sz;
```

Let me also consider that the do-while around the store (cluster A fix) adds loop notes which affect the ref weights of q, attr, tpage — those get +1 ref per loop depth. That may perturb other things later (it didn't: score 7, only cluster B).

Also, alternative cluster A fix: instead of a do-while around the store, maybe something cleaner, but v3 works; keep it. Though "do{}while(0)" with the !FAKE comment is allowed.

Let me generate and score f1..f8.
