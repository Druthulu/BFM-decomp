---
ts: 2026-10-22T20:56:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QfmuNZgc9JL8J7J2eNgj
---
Identical residual: by's add is one slot late (target 72, mine 73) and ay's add is 4 slots early (mine 75, target 79).

Hmm wait, the diff says:
- insert at 72 (target has addiu s4 at 72, mine doesn't)
- delete at 73 (mine has addiu s4 at 73)
- delete at 75 (mine has addiu s1 at 75)
- insert at 80 (target has addiu s1 at 80)

But the actual disasm I saw had by at 1524 (insn 73?) and ax at 1520 (72). So the target's insn 72 = addiu s4 (by) and insn 73 = addiu s0 (ax); mine's insn 72 = ax, 73 = by. So it's the by/ax swap.

And ay: mine at 75, target at 79 (after the chain).

To fix the by/ax swap: sched1 orders by before ax. In mine, ax is first. Both depend only on their loads. sched1's priority for each insn: it's the same pattern. The tie-break may be by *uid* (later uid = ...). In the source, by's statement comes first (uid lower), so sched1 should keep by first. But it didn't — so something gives ax a higher priority: maybe ax's result (s0) is used by a store that's scheduled soon, while by's (s4) is used later? Both stores are adjacent.

Wait — maybe it's not sched1 but the *order of the loads*: in mine, ay (s1) is loaded at 1500 before the block; bx (s2) is loaded earlier. The insns by = bx-0x5D and ax = ay+0x7B. If sched1 schedules based on the "birth" of the operands, ax's operand (s1=ay) was loaded at 1500 (recent), by's (s2=bx) loaded earlier. GCC's sched1 `priority` = insn length + sum of dependent insns... The `birth` boost: an insn that consumes a just-born value gets scheduled early. Hmm, that's the sched1-birth-boost tag in walls.txt!

Actually, the walls list has `sched1-birth-boost`: "sched1 vs local-alloc birthing-insn priority boost against a local-alloc constant". Different.

Let me look at the RTL/sched dump to see the sched1 decision. But this is a scheduling residual; the prior coder spent a lot. Given the time budget (started 14:50, now ~14:57), I have ~20 min. Let me try a few more structural variants:

The target's ax (s0) is used by the store sh s0,40 (prim.x1) and the second block's store sh s0,36. In mine, ax's add is earlier.

Idea: reorder the *stores* or the prim assignments to change the priorities. The target's store order: sh s1,36 (x0=ay); sh s4,38 (y0=by); sh s0,40 (x1=ax); sh s2,42 (y1=bx).

Idea: make by's value used *earlier* than ax's (e.g., swap prim.y0/prim.x1 in the source? the stores are in struct order: x0,y0,x1,y1). The target's source probably writes them in struct order.

Hmm, sched1's order by vs ax: both are "simple" adds with 1 use each (a store). The store order is y0(by) before x1(ax)? The stores are x0, y0, x1, y1 → by's store (y0) comes before ax's (x1). So by's consumer is earlier → by should be scheduled earlier. In mine, ax is earlier despite its consumer being later. That's the sched1 priority quirk.

What if I change the *source order of the prim stores* to x0, x1, y0, y1 (so ax's store comes before by's)? That changes the store order in the asm (target has y0 before x1). No.

What if I write `prim.x0 = ay; prim.y0 = by;` before computing ax... no, ax is computed before.

Idea: make ax's add depend on by's add (a false dependency) — e.g., `ax = ay + 0x7B + (by - by);` — folded.

Idea: compute by via a temp that's scheduled differently: `s16 t = bx - 0x5D; by = t;` — probably coalesced.

Idea: change the *loads*: `bx = out.vy; ay = out.vx;` — if the loads are swapped (`ay = out.vx; bx = out.vy;`), the operand birth order changes → sched1 might order by/ax differently. Worth a try.

Let me also try: compute `by` before loading `ay` (so by's insn is born earlier).

Batch:
v1: swap the load statements (ay first, then bx).
v2: `by = out.vy - 0x5D;` with bx loaded after (u4 was 34 — no).
v3: move `ay = out.vx;` after `by = bx - 0x5D;`:
```
bx = out.vy;
by = bx - 0x5D;
ay = out.vx;
ax = ay + 0x7B;
bx = bx - 0x57;
```
v4: move `ax = ay + 0x7B;` after `bx = bx - 0x57;` (then sched1 might place ax after bx — target wants ax at 73, bx at 74? target: by 72, ax 73, bx 74 (insn indices). Hmm target insn 72=by, 73=ax, 74=bx? The diff shows target 72: addiu s4; and mine 75 = ay. Let me get the target's insn indices around 70-80 to know exactly.

From the target disasm: 1520 by, 1524 ax, 1528 bx, 153c ay. The insn index 72=by, 73=ax, 74=bx, then chain 75-78, 79=ay, 80=store? The diff says target has addiu s1 at 80 and mine at 75. Hmm.

Let me just try the variants and see the score.

Also: what about making `bx = bx - 0x57` not depend on the old bx (e.g., `bx = out.vy - 0x57;`) — then by and bx both use the load; sched1 order may change. But that may add a second load (cse reuses).

Let me run 6 variants.
