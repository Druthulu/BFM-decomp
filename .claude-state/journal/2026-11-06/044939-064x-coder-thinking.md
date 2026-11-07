---
ts: 2026-11-06T11:49:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0C2dHQf5aXX3Vx9ZReOk
---
Same diff. So the scheduler always puts the load later. Target: `lw a1,-4(s1)` at position 61 (first), mine at 62.

Let me look at the exact positions:
Target: fd4 lw a1,-4 ; fd8 lw v0,-8 ; fdc srl a2,a1,0x10
Mine:   fd4 lw v0,-8 ; fd8 lw a1,-4 ; fdc lw v1,0(s7) ; fe0 lw s7,264(sp) ; fe4 srl a2,a1,0x10

Wait, the diff says mine[61] is missing lw a1,-4 and mine[62] has it, target[63] has srl a2. So target order: [61]=lw a1,-4, [62]=lw v0,-8?, [63]=srl a2,a1. Mine: [61]=? , [62]=lw a1,-4, ..., [65]=srl a2,a1.

Hmm, the numbering might be 1-based over the whole function. Let me look at the actual listing again:

Target (from fd0):
fd0: lw s7,288(sp)
fd4: lw a1,-4(s1)
fd8: lw v0,-8(s1)
fdc: srl a2,a1,0x10
fe0: lw v1,0(s7)
fe4: lw s7,264(sp)
fe8: sh a1,36(sp)

Mine:
fd0: lw s7,288(sp)
fd4: lw v0,-8(s1)
fd8: lw a1,-4(s1)
fdc: lw v1,0(s7)
fe0: lw s7,264(sp)
fe4: srl a2,a1,0x10
fe8: sh a1,36(sp)

So in mine, `srl a2,a1,0x10` is at fe4 instead of fdc. The scheduler (sched1) placed the two loads and the srl differently: target has the srl right after the loads; mine delays it after the two other loads.

Hmm, this is sched1 ordering. The v7 swap didn't change anything because sched1 reorders based on dependencies/priorities.

Actually wait: in mine, `srl a2,a1,0x10` (wv = wz>>16) is at fe4. In the target at fdc. The target computes wv earlier.

What is `wv` used for? `box[2].vz = wv; box[3].vz = wv;` later. In mine, wv is computed later.

This looks like sched1's birth ordering. The target computes zz>>16 early because of the launder (which forces wz to be materialized at that point).

Hmm. So the launder affects scheduling: it acts as a use of wz forcing the srl.

What real C would produce `srl a2,a1,0x10` early? Maybe if `wv` is used earlier. `box[2].vz = wv; box[3].vz = wv;` are at lines 2837-2838. The target's sh for box[0].vz = wz is at fe8 (right after). So the target's order: loads, srl, then the box stores.

Mine: loads, other loads, srl, box stores.

Hmm, what are `lw v1,0(s7)` and `lw s7,264(sp)` at fdc/fe0? s7 was loaded at fd0 from 288(sp) — that's `part->prim`? and `part->nprim`? No wait, this is the outer loop over parts (j). The body starts: wx, wz, wy loads.

Hmm, s7 at fd0 = lw 288(sp) — a reload of something. `lw v1,0(s7)` then `lw s7,264(sp)`. These look like the `part->xx`/`part->zz`... no.

This is getting deep. Since it's a sched1 ORDER issue, maybe a real-C reordering of the *statements after* the loads could change the birth order. Let me look at the C again:

```
wx = part->xx;
mn = wx;
mx = wx >> 16;
wz = part->zz;
wv = wz >> 16;
wy = part->yy;
mny = wy + dy;
<launder wz>
my = (wy >> 16) + dy;
box[0].vz = wz;
box[1].vz = wz;
box[2].vz = wv;
box[3].vz = wv;
box[0].vx = mn; box[0].vy = mny;
...
```

In the target, the order of loads: zz (-4) then xx (-8). Then srl (wv). Then `lw v1,0(s7)` — hmm.

Let me think about what `lw v1,0(s7)` is: s7 = 288(sp) = ? Maybe `part->prim` (loaded earlier into a stack slot). And `lw s7,264(sp)` = `vtx`? So these are loop-invariant reloads from the stack (spilled).

Anyway, the residual is a single sched1 ordering. Let me try a few real-C moves:
- Move `wv = wz >> 16;` to after `wy = part->yy;`.
- Move `wv` computation into the box stores.
- Compute `wv` later (e.g., `box[2].vz = wz >> 16;`).

Actually, in the target, wv is computed at fdc, early. In mine, at fe4, later. To make the compiler compute it earlier, maybe write it earlier in the source (it already is) or make it depend on the load directly.

Hmm, maybe the difference is that sched1 in the target has an extra insn (the launder) which changed the birth. Removing the launder changes priorities.

Alternatively, maybe the fix is to add a real-C *use* of wz/wv that forces the srl early. E.g., `box[2].vz = wv;` moved earlier? The box stores are after.

Let me look at the target's full loop-body start to see where the box stores are. Let me dump the target from f00 to f60.

Actually, let me try a batch of reorderings:
- w1: move `wv = wz >> 16;` after `wy = part->yy;` / after mny/my.
- w2: move the box[2]/box[3] stores earlier (right after wv).
- w3: `box[2].vz = wz >> 16;` inline.
- w4: reorder to: wz, wy, wv...

Let me first see the target's code from the loop start to understand. Let me dump f00-f40 of the target.
