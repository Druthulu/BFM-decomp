---
ts: 2026-11-06T12:45:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dkrdFrLBTOCzmTVowGXj
---
Key insight: the first diff (delete mine[236:241]) is the *scheduling* of the ua/ub computation: mine has it 11 insns earlier than target. Target computes `andi v1,a3,0xffff; andi v0,a1,0xf; sll v0,v0,0x6; subu v1,v1,v0; sllv v1,v1,s7` at 242-247, mine at 236-240 with `sllv a0,v1,s7`.

So with the barrier, sched1 keeps that computation after the prim[7] store; without, it hoists it. And the register a0/v1 difference follows from the birth order.

So the mechanism: the barrier prevents sched1 from hoisting the ua computation above the `prim[7] |= ...` store. Real-C: make the ua computation depend on the store. E.g.:

```
prim[7] |= (attr & 0x40) >> 6;
...
ua = ub = (sx - ...) << sh;
```
The store `prim[7] |= ...` reads prim[7] and writes prim[7]. The ua computation depends on sx (which comes from x, which comes from pxv + (dxv>>sh)) and tpage, sh, s7.

Target order: the ua computation comes AFTER the store. Mine hoists it before. Why? sched1's rank_for_schedule. To stop hoisting in real C: introduce a dependency on the store's value, e.g. compute ua from `prim[7]`? No, changes semantics.

Alternative: make the store's value feed into ua's computation in an identity way — that's a "launder"/identity trick, which does NOT count as a crack ("identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack").

Hmm. But we can use a real dependency: e.g., `prim[7] |= ...; ` then `ua = ub = (sx - ...) << sh;`. There's no real dep.

Real C moves that change scheduling: put the ua/ub computation in a separate basic block, e.g. inside the `if (id & 0x100)` arms? No, ua/ub are computed before.

Or: use a temp variable to lengthen the chain so the insns are born later. E.g. compute `tpage`-derived things later.

Alternatively: sched1's rank_for_schedule tie-break uses LUID (source order) for equal priority; the store is a "store" and may have lower priority. The barrier prevents the load/compute from moving above it. Hmm.

What if I move the `prim[7] |= ...` statement *after* the ua/ub computation in source? Then sched1 might still put things in a different order. Actually target has store first then compute. Mine has compute first then store? Let me check mine's order: mine[236:241] has the compute at 236-240; where's the store? Let me dump mine's 230-250.

Actually the diff says "delete mine[236:241]" — mine has 5 extra insns at 236 that target has at 242. So mine's order: ..., 236-240 compute, then (241) store? and target: 236-241 store + others, then 242-246 compute.

So target: store first, compute second. Mine: compute first, store second.

If I move the `prim[7] |= ...;` statement *before* the ua computation in source — it already is before! Source order: `prim[7] |= (attr & 0x40) >> 6;` then barrier then `ua = ub = ...`. So target respects source order; mine (no barrier) reorders. sched1 moved the compute above the store because of priorities.

To prevent: make the store's address/value computation later? Hmm, the store is `sb` to prim[7]; `prim[7] |= (attr & 0x40) >> 6;` = load byte prim[7], or with (attr>>6)&1, store. That's a load-store pair.

Idea: write the store differently so it has higher priority, e.g. `prim[7] = prim[7] | ((attr & 0x40) >> 6);` (explicit) — same RTL.

Idea: split into a temp: `u8 t7 = prim[7]; t7 |= (attr & 0x40) >> 6; prim[7] = t7;` — a temp adds a set that sched1 may schedule differently. Worth trying.

Idea: the store to prim[7] is a store to a byte; sched1 usually won't move a load above a store to the same address (alias). Actually the ua computation includes `sx` which is a u16 loaded earlier. Hmm.

Wait — actually the real reason might be that the ua computation reads `sx` (a local var) and `tpage`, and sched1 hoists it because of the "birth" of insns. In the target, the barrier's asm forces a block boundary. Without it, all in one block.

Practical approach: try a `do { } while (0)` (C0535) around the ua/ub block — that splits cse1 EBBs, and maybe sched1 blocks too. Let me try:
- e1: `do { ua = ub = ...; ub += rec->w; ub -= 1; } while (0);` + the `if ((u16)ub >= 0x100)` outside.
- e2: `do { prim[7] |= ...; } while (0);` then ua block.
- e3: temp t7 variant.

Also consider: maybe the block split should be between the store and the compute — a do-while(0) around the store. Let's try both.

Let me also consider reordering source: move `prim[7] |= ...` to after the ua/ub computation? No, target wants store first.

Let me try variants.
