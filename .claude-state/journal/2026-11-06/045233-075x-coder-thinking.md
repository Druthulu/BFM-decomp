---
ts: 2026-11-06T11:52:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZhKYzWe9oRmoJqcZwyTc
---
engine_types.h defines Part as {xx, yy, zz, nprim, prim} — 0x14 bytes. But the loop increments s1 by 0x20. So s1 ≠ part. Maybe s1 is a different variable, and the loads at -8/-4 are `part->yy` and `part->zz`? If s1 = part+0x10 (prim), then -8 = zz (offset 8), -4 = nprim (0xC)? Hmm.

Wait: maybe s1 = &part->zz + something. Let's compute: if s1 = part + 0xC, then -8 = part+4 = yy, -4 = part+8 = zz. Hmm, -8 would be yy.

Let me look at the surrounding code: after the loads,
- v0 (from -8) → mn = v0? and addu a3,v0,s7 = mny
- a1 (from -4) → wz

C: mn = wx (so v0 = wx), mny = wy + dy (a3 = v0 + dy?? no, v0 = wx).

Hmm, `addu a3,v0,s7` where v0 = the -8 load and s7 = dy. But mny = wy + dy, and mn = wx. So a3 = wy + dy → v0 = wy. And mn = wx...

Wait: `mn = wx` then `mny = wy + dy`, `my = (wy>>16)+dy`. And `box[0].vx = mn; box[0].vy = mny;`. So `mn` = wx (low half) and mny = wy+dy.

Hmm, in the target: `addu a3,v0,s7` → v0 = wy? and `srl v0,v0,0x10` then `addu t0,v0,s7` → my = (wy>>16)+dy. So v0 = wy! And where's wx (mn)?

Look: `sh t2,32(sp)` (t2 = v1 from lw v1,0(s7)) → box[0].vx = mn. So v1 = wx, loaded from `lw v1,0(s7)` where s7 = 288(sp). Hmm, that's a reload from a spill slot.

So the actual loads: v1 = wx (spilled), v0 = wy (-8), a1 = wz (-4). And s1 = part+4? Since wy is at 4 and wz at 8: if s1 = part+0xC, -8 = part+4 = wy, -4 = part+8 = zz. Hmm, then -4 = zz ✓ and -8 = yy ✓. So s1 = part + 0xC? But then the increment 0x20 doesn't match Part size 0x14.

Hmm, maybe the loop's `part++` uses a different Part type (0x20 stride). Whatever — the offsets confirm: -8 = yy, -4 = zz.

So the two loads are `wy = part->yy;` and `wz = part->zz;`. Target order: zz then yy. Source order: yy then zz (`wy = part->yy;` comes before `wz = part->zz;`).

Wait, source:
```
wx = part->xx;
mn = wx;
mx = wx >> 16;
wz = part->zz;
wv = wz >> 16;
wy = part->yy;
mny = wy + dy;
<launder #2>
my = (wy >> 16) + dy;
```
So source order: xx, zz, yy. Target: zz(-4), yy(-8) → zz before yy. Mine (v2): yy(-8) before zz(-4).

Interesting! So in the target, zz is loaded before yy, even though the source has zz before yy (yes! wz = part->zz comes before wy = part->yy). So the target's order MATCHES the source (zz then yy), and mine (v2) has them swapped (yy then zz)!

Wait, mine: fd4 lw v0,-8(s1) = yy first, then fd8 lw a1,-4 = zz. So mine swapped relative to source.

Hmm, so sched1 reordered in v2 but not in the target. So the launder (which is between `mny = wy+dy` and `my = (wy>>16)+dy`) affects the scheduling.

Hmm, wait: in v2 the source order for the loads is still xx, zz, yy. But mine emits yy before zz. That's sched1 moving yy up.

Hmm, but sched1 ties by INSN_LUID. Both loads have priority 1. The "class" depends on the last scheduled insn. So the order can change.

In the target, zz comes first (source order). In mine, yy comes first. So something makes sched1 prefer yy in v2.

The launder is a use of wz (zz's value). Without it, wz's death is at the box stores. With it, wz lives longer.

Hmm, why would that change yy's position? 

Alternatively, maybe it's not sched1 but the *RTL expansion order*: `mny = wy + dy;` is a use of wy. Without the launder, `my = (wy>>16)+dy;` follows immediately. Hmm.

Hmm, maybe the launder changes local-alloc: without it, wz's register... but the register assignment is the same (a1).

OK let me try a real-C move that mimics the launder's *effect* on wz's live range without an asm: make wz used after the box stores. E.g., move `box[4].vz = wz;` (currently at line 2850, after the gte calls) — no, that's a real store, changes order.

What about using wz in a *dead* real-C expression that the optimizer removes but which affects liveness? For example:
```
wv = wz >> 16;
...
box[2].vz = wv;
box[3].vz = wv;
```
What if I write `box[2].vz = wz >> 16;` and `box[3].vz = wz >> 16;`? That uses wz twice (two srl → cse merges). The liveness of wz extends to the last box store. Currently `wv` is used at box[2]/box[3], and wz at box[0]/box[1]. The launder extends wz's use past all of them.

What about writing the stores as `box[0].vz = wz; box[1].vz = wz; box[2].vz = wv; box[3].vz = wv;` — same as now.

Hmm, what if I use `wz` in computing `wv`: already.

Let me try: assign `box[2].vz = wv;` where wv = wz>>16 — the launder is between `mny` and `my`, i.e., before the box stores. So its position is BEFORE the stores. Wait:

```
2832: mny = wy + dy;
2833: <launder wz>
2834: my = (wy >> 16) + dy;
2835: box[0].vz = wz;
...
```
So the launder is before the box stores. It extends wz's liveness backward? No — it's a *use* of wz before the stores, so wz must be live from the load to the launder (and to the stores). Without it, wz is live from the load to the box stores. Similar.

Hmm, the launder is a *read-write* of wz. So wz is redefined at the launder: the value from the load is used, and a new (same) value is defined. That splits wz's live range into two: [load, launder] and [launder, stores].

Hmm.

Alternatively, maybe I should attack this from the "what real C produces the target's order" angle: since sched1 ties by source order, and the target has zz before yy (matching source), maybe the target's RTL is in source order and sched1 didn't reorder; mine reordered because the *priorities* differ.

Let me try to make wz's value used immediately after the load, e.g., `wv = wz >> 16;` — already.

What if I move `wy = part->yy;` AFTER the box stores? That would change the source order to xx, zz, [stores], yy. Then the loads would be zz then yy... but the box stores use wy (mny, my).

Hmm.

Let me try a completely different tactic: use the `&&`/`||` fold or `do{}while(0)` to split the EBB? No.

Honestly, let me try a batch of ~10 real-C permutations of the loop head and see if any hits 0. The space: order of the statements wz/wv/wy/mny/my and the box stores.

Let me enumerate:
- p1: move `wy = part->yy;` before `wz = part->zz;` (xx, yy, zz).
- p2: move the box[0..3].vz stores before `wy = part->yy;`? They use wz/wv only.
- p3: split `mny`/`my` computation after the stores.
- p4: `wz = part->zz; box[0].vz = wz;` early.
- p5: use `mn`/`mx` after.

Let me write a generator that permutes the head block.

Actually, let me reconsider: the ORDER diff in v2 says mine[61] vs target[61]. Target insn 61 = `lw a1,-4(s1)` and mine has it at 62. And target[63] = srl. So mine's insn 61 is `lw v0,-8(s1)`. So the only difference is the swap of the two loads plus the srl position follows.

Wait, if only the two loads swap, the srl would still be after both in mine. The diff shows mine's srl at 65 vs target 63 — because mine has 2 extra insns before it? Let me re-read the v2 diff:

```
insert  mine[61:61] target[61:62]
     61  --            | lw a1,-4(s1)
replace mine[62:63] target[63:64]
     62  lw a1,-4(s1)  | srl a2,a1,0x10
delete  mine[65:66] target[66:66]
     65  srl a2,a1,0x10 | --
```
Hmm, so target: [61]=lw a1,-4, [62]=?, [63]=srl a2. Mine: [61]=?, [62]=lw a1,-4, [63]=?, [64]=?, [65]=srl.

This is the diff algorithm's alignment. From the actual listings:
target: fd0 lw s7,288; fd4 lw a1,-4; fd8 lw v0,-8; fdc srl a2,a1; fe0 lw v1,0(s7); fe4 lw s7,264; fe8 sh...
mine:   fd0 lw s7,288; fd4 lw v0,-8; fd8 lw a1,-4; fdc lw v1,0(s7); fe0 lw s7,264; fe4 srl a2,a1; fe8 sh...

So in mine, srl is at fe4 (after the two loads v1 and s7); in target at fdc (before them). So the difference is: the target computes `srl a2,a1,0x10` (wv) right after the loads; mine delays it until after `lw v1,0(s7)` and `lw s7,264(sp)`.

Since sched1 ties by LUID, the srl's position should be source order (right after wz). In mine it moved later. So sched1 reordered it (priority difference).

Hmm, `wv` is used by box[2]/box[3] stores. The srl has priority 1 too. 

OK. I've spent a lot on this. Let me do a quick batch of permutations and if none hits, wall it.

Let me write a python script generating ~12 variants by reordering the head statements.
