---
ts: 2026-11-06T11:55:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DjwjxmLCuErVwfhzaoMF
---
All 35. The lever-free body is stuck at 35 with 133 insns. That's a WALL: `sched1-load-delay-fill` (the target leaves 6 nops; sched1 fills them once the barrier fences are gone).

Tries for item 2: 3 (v0,p1,p2) + 7 + 4 + 2 + 12 = 28. Close to 30. Let me do one more batch of a few (e.g., 4 more: barrier-removal subsets lever-free won't count; must be lever-free bodies). Let me generate 4 more lever-free variants (e.g. store order of the yr group, idx computation position) to cross 30, and confirm.

Actually, is `best` 35? Yes.

Hmm, wait. Before finalizing a WALL, let me consider the PARTIAL option for item 2: p1 (barriers kept, launder gone) = 13, not 0. p2 = 22. Neither is 0. So no PARTIAL. Unless another real-C move on p1 gets 0 — the mask swap is the residual. I tried several. Could try more (e.g. writing the masks as `& 0xFF000000` inline and `m24` var; or `pv = *p` moved after ot). Let me do 4 more p1 variants + 4 lever-free = 8 tries → total 36.

Actually, the mask swap (a0/a2) might be fixable by changing the if branch too, since both branches share the mask variables' allocation? The if branch has its own m24/mFF. Hmm.

Let me try a couple of quick p1 variants:
- i1: else with mFF declared but m24 inline (only mFF var)
- i2: else with m24 var but mFF inline (only m24 var) — same as base (base uses inline 0xFF000000 and m24 var).
- i3: m24 var declared after pv/ot decls (I tried m24after = 13).
- i4: pv = *p moved after the first mask load: `*(u32*)p = ...` requires pv, so no.

Let me instead try moving the `ot = ...` line to right after `pv = *p` (so the ot lookup is between pv and the first store):
```
pv = *(u32 *)p;
ot = (u32 *)D_800AE7BC[D_800B9A02].a;
*(u32 *)p = (pv & 0xFF000000) | (*ot & m24);
*ot = (*ot & 0xFF000000) | ((u32)p & m24);
```
and
```
ot = (u32 *)D_800AE7BC[D_800B9A02].a;
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (*ot & m24);
*ot = ...
```
(otfirst with *ot in the first store was 27 in the lever-free context; in p1 context I didn't try it.)

Let me do 6 p1 variants quickly.

Actually, time: item 2 is at ~25 min. Let me do one final batch of 8 (4 p1 + 4 lever-free), then finalize.

For lever-free extras, vary: `*(s16 *)((u8 *)p + 0x10)` vs `*(s16 *)((u8 *)p + 0x10)` no change; use `p` as u32* for the tag; or reorder the four corner groups.

Let me just do 4 lever-free variants by reordering the corner groups (xr before xl? no, values differ) — simpler: swap the two stores in each group (cswap did that for xl only). Let me apply cswap to all four groups, and a variant with `idx = a1;` (no &0xFFFF? no, needed).

OK: 4 lever-free variants:
- l1: all four corner groups lo-then-hi
- l2: idx assignment moved to the top (before the corner groups)
- l3: idx as u16
- l4: all four groups swapped + idx early

Let me write them.
