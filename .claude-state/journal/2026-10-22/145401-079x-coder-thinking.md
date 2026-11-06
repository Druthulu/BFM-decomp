---
ts: 2026-10-22T20:54:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JTgvgVFvNCm7k2l075en
---
gen_o3's order: ax (1520), by (1524), bx (1528), ay (152c) — vs target: by (1520), ax (1524), bx (1528), ..., ay (153c).

So mine has ax first then by; target has by first then ax. And mine's ay is at 152c (right after bx), target's ay is after the index chain.

The source order is by, ax, bx, ay. sched1 reordered mine to ax, by, bx, ay. The target keeps by, ax, bx and pushes ay later.

This is a sched1 ordering issue; the prior coder tried many variants. The residual is only 4 with ORDER. Since the diff is only order, maybe a small source change (e.g., declaration types, the order of the prim stores) can fix it. But this is the prior coder's territory; they got 4.

Let me look at what's different between gen_o3 and gen_o2/gen_o4/gen_plus0_axby (all tried). The prior work is extensive.

Time budget: item 3 fresh, started 14:50. I have 20-30 min. Let me try a handful of ideas around the ordering:

The target's `addiu s4,s2,-93` (by = bx - 0x5D) is FIRST, before ax. In the source, `by = bx - 0x5D;` comes before `ax = ay + 0x7B;` — matches the source. So sched1 in mine swapped them. Why? sched1 prioritizes by dependency/priority. To keep by first, maybe declare `by` with a higher priority (e.g., more uses) or make ax depend on by? 

Alternatively, reorder the source statements: put `ax = ay + 0x7B;` *after* bx = bx - 0x57:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
bx = bx - 0x57;
ax = ay + 0x7B;
```
Then sched1 might put by, bx, ax — target has by, ax, bx. Hmm.

Or put ax before by in the source: `ax = ay + 0x7B; by = bx - 0x5D;` → sched1 might keep that order (ax, by) — but target is by, ax.

The sched1 order depends on insn priorities (uid). Since the target has by, ax, bx and mine has ax, by, bx — the target's source order (by then ax) is natural; sched1 in mine reordered. Something in mine's RTL makes ax's insn higher priority.

Since both ax and by are simple addiu with the same priority, sched1's tie-break uses the insn's "priority" = length + something, or the dependency structure (bx's use in by and bx's re-set). Hmm: `bx = bx - 0x57` reads bx (the old value). `by = bx - 0x5D` also reads bx. So both depend on bx's load. sched1 can order by and the bx re-set in either order? No: `bx = bx - 0x57` *sets* bx, so by must read the old bx → by must come before bx's set (anti-dependency). So by must be before `addiu s2,s2,-87`. Target: by at 1520, bx-set at 1528. Mine: by at 1524, bx-set at 1528. OK.

ax depends on ay (the load), no dependency with by. sched1's order between by and ax: target by then ax; mine ax then by. The prior coder's gen_o* tried order variants; gen_o3 got the closest (207 ins, ORDER 4).

Let me try source reorders:
t1: `by = bx - 0x5D;` then `ax = ay + 0x7B;` (already) — mine swapped.
t2: split: `by = bx - 0x5D; ax = ay + 0x7B; bx = bx - 0x57;` (already).
t3: move the ay load later: `bx = out.vy; by = bx - 0x5D; ay = out.vx; ax = ay + 0x7B; bx = bx - 0x57;` — the ay load after by might push ax later.
t4: compute by from out.vy directly: `by = out.vy - 0x5D;` — but the target loads out.vy once into s2 (bx) and uses it for both. If by = out.vy - 0x5D, gcc loads out.vy twice? cse would reuse the load → same value, but the add might be scheduled differently.
t5: make ax a u16 (gen_o3 has u16 ay, bx; ax u32). Try ax u16 too.

Let me look at gen_o3's declarations: u32 ax; u16 ay; u16 bx; register u32 by. Hmm, gen_n1 had u32 ay/bx + `by = (u16)by`.

Let me try a few declaration/type combos and source orders. But first, let me see the whole gen_o3 body (the differences from orig beyond decls). Let me diff orig vs gen_o3.
