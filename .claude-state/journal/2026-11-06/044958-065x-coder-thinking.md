---
ts: 2026-11-06T11:49:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v4bmQojnlv14QlckAL3E
---
Target loop body:
- fd4 lw a1,-4(s1) = zz
- fd8 lw v0,-8(s1) = xx
- fdc srl a2,a1,0x10 = wv
- fe0 lw v1,0(s7) = ? (s7 = 288(sp) — some spilled pointer; v1 = part->prim?)
- fe4 lw s7,264(sp) = vtx?
- fe8 sh a1,36 = box[0].vz = wz
- fec sh a1,44 = box[1].vz = wz
- ff0 sh a2,52 = box[2].vz = wv
- ff4 sh a2,60 = box[3].vz = wv
- ff8 move t2,v1 ; ffc srl t1,v1,0x10  → that's `wy` handling? v1 = part->yy; t2 = wy (low 16), t1 = wy>>16
- 1000 addu a3,v0,s7 → mn? = wx + dy? Hmm, v0 = xx, s7 = 264(sp) = dy?
- 1004 srl v0,v0,0x10
- 1008 addu t0,v0,s7

So `s7` (264(sp)) = dy. And a3 = mn + dy = mny; t0 = mx + dy.

So the order: zz, xx loads; wv; wy load; box stores; mny/my computations.

In mine (v2), the order is: xx, zz, then lw v1,0(s7), lw s7,264(sp), then srl a2,a1,0x10 (wv), then the box stores.

So the difference is only where `srl a2,a1,0x10` sits: target right after the loads; mine after the two other loads.

Hmm, in mine, the srl moved later. Both are in the same basic block; sched1 decides. The launder's presence apparently forces the srl early.

Actually, wait: maybe it's not sched1 but the *order of the tree/RTL expansion*. In the target, `wv = wz >> 16;` is expanded right after the zz load (source order: wz, wv). In mine, the srl is emitted later. Hmm.

Hmm, but mine has the loads swapped (xx first) which suggests sched1 is reordering.

Let me try: put `wv = wz >> 16;` immediately after `wz = part->zz;` in the source (it already is). 

Wait, in v2 the source order is:
```
wx = part->xx;
mn = wx;
mx = wx >> 16;
wz = part->zz;
wv = wz >> 16;
wy = part->yy;
```
So wv is right after wz. But the emitted order is xx load, zz load, [wy load?], ..., srl.

The `mn = wx;` is a copy that gets folded. `mx = wx >> 16` — hmm, where's the srl for mx? `srl v0,v0,0x10` at 1004.

So sched1 is moving things around. The two loads at fd4/fd8: sched1 picks the order.

Let me try a targeted C change: make `wv` used before `wy` is loaded? It already is (box[2] comes after). 

Alternative: since it's one insn, maybe try making `wz` and `wv` computations adjacent by using a single expression: `wv = part->zz >> 16;` and `wz = part->zz;`? Then two loads of the same address → cse merges into one load + srl. Let me try:
```
wz = part->zz;
wv = wz >> 16;
```
→ change to:
```
wv = part->zz >> 16;
wz = part->zz;
```
Hmm, the order of the srl vs the load.

Let me try several sched-perturbing variants in a batch:
- s1: `wv = wz >> 16;` moved after `wy = part->yy;`
- s2: `wv = part->zz >> 16;` (separate load, cse merges)
- s3: reorder wz before wx (v7 already, no change)
- s4: move `wy = part->yy;` before wz.
- s5: `box[2].vz = wv; box[3].vz = wv;` moved right after wv.
- s6: compute wv at the box stores: `box[2].vz = wz >> 16;`

Let me batch these.
