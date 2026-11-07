---
ts: 2026-11-06T04:48:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pSO4nI2JviG1fXoYwKLJ
---
b10 is otherwise exactly target except the ori position and a3 setup position. Target:

```
138 lui v1,0xffff
13c ori v1,v1,0xfff
140 lui v0,currentLocationId
144 lh v0,0(v0)
148 lui a3,D_800C7C60
14c addiu a3,a3,0
150 sw ra,16(sp)
154 and v0,v0,v1
...
```

Mine:
```
138 lui v1,0xffff
13c lui v0,currentLocationId
140 lh v0,0(v0)
144 ori v1,v1,0xfff
148 sw ra,16(sp)
14c and ...
...
16c lui a3
170 addiu a3
```

So target has: ori right after lui (mask fully formed before load), a3 setup right after lh, sw ra after a3. Mine: lh before ori, a3 setup after the two loads, sw ra before and.

This looks like sched1 scheduling order differences driven by insn priority/birth. Hmm, the a3 setup (p = &D_800C7C60) in target is scheduled early, in mine late. 

What determines sched1's placement? The `p` pseudo's birth: `p = &D_800C7C60` is a set. Its use is the store `*p = val` inside the do-while block (a different basic block maybe!). If the do-while creates a separate block, then p's setup can't be in the same block... wait it is in the same block (the store moved). Hmm.

Actually maybe in target, `p` is in a0? No, a3.

Let me think differently: maybe the do-while isn't needed if we prevent the D_800A2E20 hoist another way. The real problem in a1 was the store to D_800C7C64 and its address being hoisted above the loads, causing register pressure change (mask in a0, D_800A2E20 addr v1).

What if we make the D_800C7C64 store depend on the `val` load in a genuine way? Target's store value is &D_800A2E20, no dependence. But maybe we can reorder source so the store is naturally after the loads and sched1 can't hoist because of a memory dependence: D_800C7C64 store vs the loads from D_800D34AC/D_800D34AE — different symbols, so no dependence. The barrier stopped it.

Hmm, what if we store through a pointer whose address comes from a computation using idx? No.

Alternative: change the *order* of the source so that the D_800A2E20 store appears textually after `id = raw & 0xFFF;`. b3 tried that → score 17, same as a1. Because sched1 still hoists.

So the do-while is the only real-C blocker. The residual 5 is a sched1 ordering of ori/a3. Let me try to nudge:
- Put the mask computation as `s32 mask; mask = ~0xF000;` separate statement? Same.
- Compute mask via `s32 mask = -0xF001;`? constant same.
- Declare idx first, then mask? Order of declaration might affect insn order (birth order). C0535: do-while splits cse1 EBB; sched1-birth-order moves reorder source.

The ori issue: mine's ori is after the lh. That's a pure sched1 order. Target's ori immediately after lui. To change, maybe make the mask's first use the `and` (which is after lh) — same in both. The scheduling priority: sched1 sorts ready insns by priority. lui/ori pair: ori depends on lui. The lh depends on the lui of currentLocationId. All ready at cycle 0 except ori needs lui. Hmm.

Try variants where the mask is used earlier: e.g., compute `idx` with mask before the loads (source order already: idx = currentLocationId & mask before raw load). The lh must happen before and. So source order: mask const, lh, and, ...

Target order: lui v1, ori v1, lui v0, lh v0, lui a3, addiu a3, sw ra, and. So the mask is fully formed first, then load, then p setup, then ra save, then and. Mine: lui v1, lui v0, lh, ori, sw ra, and, ... a3 later.

Notice target's a3 setup (p init) is right after the lh and before sw ra. Mine's a3 setup after loads. In a1 (no do-while), a3 setup was at 150-154, early. So the do-while is moving p's setup later. Why? Because p's only use is inside the do-while block? If the do-while's store is a separate basic block, then p's live range starts at the block... but global/local alloc assigned a3 and the move is placed... Hmm, actually the p init is an insn in the entry block; sched1 places it. If p's use is in a later block, sched1 may still place it anywhere in entry block.

Maybe the difference is that in target, the `sw ra` is after a3 setup; in mine sw ra before and. These are all sched1 ties.

Let me try to perturb with more real-C moves:
- Move `s32 *p = &D_800C7C60;` to be the first declaration/initializer (before mask)? The prologue emits initializations in some order (moves/address loads are scheduled anyway).
- Use `s32 *p;` then `p = &D_800C7C60;` as a statement after the loads (would make it late).
- Different: make the D_800C7C64 store part of a do-while AND p init statement inside? No.

Actually maybe try making both stores inside the same do-while but with `p` assignment inside: 
```
do {
  p = &D_800C7C60;
  D_800C7C64 = &D_800A2E20;
  *p = val;
} while (0);
```
Then p init is inside the same block as its use. Let's test.

Also try declaring `s32 *p = &D_800C7C60;` after the loads? No.

Let me also try wrapping each load+store group differently: do-while around `D_800C7C64` store and keep p init in the same do block.

Let me test a batch.
