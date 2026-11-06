---
ts: 2026-10-22T20:57:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZdMPvahp80ApAR8mzB4s
---
v1 = 6 (worse). Others 4.

The residual is stubbornly sched1's by/ax order and ay's placement. Let me check the sched dump to see sched1's decisions. Maybe I can find the exact lever.

Actually, wait: the target's ay is placed *after* the index chain, and mine before. In the target, the index chain is computed between bx and ay. The chain computes `op` for the call. In the source, `op` is computed inside the block after bx and before ay (the launder line position!). In gen_o3, `op` is declared in the block and used in the call — the chain is scheduled where?

In mine: by, ax, bx, ay, chain, stores, call.
Target: by, ax, bx, chain, ay, stores, call.

So the only difference is ay vs chain. If the chain were scheduled before ay, we'd match. The chain's insns (sll/addu/sll/addu) have a dependency chain; sched1 puts them together. In mine, ay is placed before the chain.

What if I move the `ay = ay + 0x75;` statement *after* the op computation in the source? It already is after (the block declares op, then ay += ...). Hmm, in gen_o3:
```
{
Gline_801372B0 *op = (Gline_801372B0*)&D_800A6518[(u32)aD800B9A02 * 0x14];
ay = ay + 0x75;
prim.x0 = ay; ...
aGsSortLine(&prim, op, 0);
}
```
The op computation is an initializer. Maybe moving the op computation *later* (right before the call, after the stores) would schedule the chain after ay — the opposite. The target has the chain BEFORE ay.

What if I compute op *before* bx = bx - 0x57? Then the chain would be scheduled earlier (before bx), but the target has bx before the chain.

Target: by, ax, bx, chain, ay, stores.
Source order (orig with the launder): by, ax, bx, [launder op], ay, stores. The launder is between bx and ay, and it's an asm → a scheduling barrier that keeps the order! In gen_o3 the op computation (a pure address calc) can be moved by sched1.

So the target's order by, ax, bx, chain, ay is exactly the source order; sched1 in the target's build kept it because... hmm, the target's source presumably had no launder either (we're cracking the launder). The chain in the target is between bx and ay — sched1 respected the source order there. In mine, sched1 moved ay before the chain.

The difference could be that in mine the chain's result (op) is used only at the call (after the stores), so sched1 deferred the chain; in the target the chain is earlier. Sched1 priority: the chain's first insn (lui v0, D_800B9A02) is at 1504 — before the adds! In mine: 1504 lui v0, 1508 lhu v0 — then the adds, then the chain's sll/addu at 1530-153c. In the target: 1504 lui, 1508 lhu, then adds at 1520-1528, then sll at 152c-1538, then ay at 153c.

So in the target the chain's sll starts right after bx; in mine the sll starts after ay.

What if I write the op computation as a *statement* after the ay add (i.e., declare op without an initializer, assign it after ay)? Then the source order would be: ..., bx, ay, op = ..., stores, call → the chain after ay (like mine). Not what we want.

What if I write `op = ...` *before* `ay = ay + 0x75`? The current code has op's initializer before ay. But sched1 still moved ay before the chain. Hmm.

What if the op computation is *split* so it can't move as a unit? no.

What about making ay's add *depend* on the chain? e.g. `ay = ay + 0x75;` unchanged — can't create a dependency without changing semantics.

Alternatively, make the chain's insns higher priority by using them earlier: e.g. pass `op` to the call as the *first* argument? No, the signature is fixed.

Hmm, what if the launder's real purpose here was just to be a scheduling barrier; the target's source may have had `op` computed with a *function call* or something. No.

Let me look at the target's insns 70-85 vs mine in the .sched dump? That's a lot of work.

Alternative: maybe the `op` launder can be replaced by a real-C 2nd set that keeps op's computation where it is: e.g. 
```
Gline_801372B0 *op = (Gline_801372B0*)&D_800A6518[(u32)aD800B9A02 * 0x14];
op = op;   // dead
```
No.

What about declaring op as `register`? no.

Let me try moving the ay add *after* the prim stores? Not possible (x0 = ay needs it).

What if I compute `prim.x0 = ay + 0x75;` directly (no ay update) and then `ay = prim.x0;` after? Then:
```
prim.x0 = ay + 0x75; ay = prim.x0;
```
The add is scheduled right before the store (which is what the target has: addiu s1 then sh s1,36). And the target's order: addiu s1 at 153c, then sh s1,36 at 1540. So `prim.x0 = ay + 0x75;` (the add) is immediately before the store. In mine, the add is earlier (at 152c) because it's `ay = ay + 0x75;` and ay is also used later (the second block's prim.x1 = ay), so its live range extends → sched1 hoists it early.

In the target, ay is updated too (the second block uses the updated ay: sh s1,40 = prim.x1 = ay). So ay's updated value is used later; still, the add is late.

Hmm, what if the target's source computes ay's update as `prim.x0 = ay + 0x75;` and the *second block* uses `ay` (the old value)? Let me check the target's second block: at 1574-1580: sh s0,36 (x0=ax), sh s4,38 (y0=by), sh s1,40 (x1=ay), sh s2,42 (y1=bx). s1 at that point = the updated ay (0x75 added). If the source used the old ay there, the target would store out.vx — but the register s1 was updated in place, so the second block's s1 is updated. So ay is updated in place.

OK, let me try a couple of variants:
w3: `prim.x0 = ay + 0x75; ay = prim.x0;` (reorder the add and the update)
w4: `{ s16 t = ay + 0x75; ay = t; prim.x0 = t; }` — the add feeds both the store and ay.
w5: move the ay update to just before the second GsSortLine (after the first call)? No, semantics: the first line's x0 uses the updated ay.

Actually, what about writing the first block's stores with `prim.x0 = ay + 0x75;` and the second block's `prim.x1 = ay + 0x75;`? That computes the add twice (or cse merges). Hmm.

Let me look at the prior coder's gen_o1/gen_o4/gen_plus0 (25-27 scores) to avoid repeating.

I'll try w3/w4 and a variant where ay is updated with a temp.

Also, for the by/ax swap: try declaring by before ax in the declaration list? Declarations don't affect scheduling.

Actually, the by/ax swap might be a *local-alloc* artifact: sched1's order depends on the register assignment and the "death" info. by is pinned ($20=s4), ax is s0. Hmm.

What if `ax` is assigned later in the source? v4/v6 tried.

Let me try w3/w4 and also: make `by` a plain s16 (no pin)? The pin $20 is allowed to stay but could be dropped — dropping a pin is allowed (pins "may stay", not must). If dropping the by pin changes the schedule... but the target needs by in s4, and the pin is what puts it there (probably needed). Let me test removing the by pin to see.

Actually — the target needs by in s4 ($20). The pin is doing that. Without it, by might get another reg → more diffs.

Let me try:
w3: prim.x0 = ay + 0x75; ay = prim.x0;
w4: { s16 t = ay + 0x75; ay = t; prim.x0 = t; }
w5: prim.x0 = ay + 0x75; (no ay update) + second block prim.x1 = ay + 0x75;
w6: ay += 0x75 written after prim.y0? The stores order x0,y0,x1,y1 — x0 must be first.

Let me run.
