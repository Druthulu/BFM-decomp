---
ts: 2026-11-06T13:47:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_90IFuVVnZmk4yL3lKCDu
---
Interesting! w_d_base (B and C fixed, A barrier STILL PRESENT) scores 0. That means with B and C fixed, the A barrier is still needed... wait no: w_d_base has A present (the asm) — so it's not lever-free. Score 0 but keeps the barrier → not a MATCH.

The A-removed variants: v1 (do-while hh) = 8, v2 = 8, v3 = 12, v4 (order swap) = 2, v5 = 11.

Hmm, so with B and C fixed, removing A gives a different residual (8 for the do-while variants) than the earlier 2 (with B,C barriers present). Interesting: with B and C fixed, A's removal interacts.

v4 (swap ww/hh order) gives 2.

Let me look at v4's diff with B,C fixed.

Actually, let me think about A differently. In the target, the h load (lbu t7) is at index 11 right after lbu t6 (w), before the D_800A5E60 lui/lw. With A removed, the lbu sinks below the lui/lw.

The A barrier's effect: it's a memory clobber that orders the lbu (a memory load) with the D_800A5E60 load (also a memory load) — both are loads, so no ordering needed... but the barrier prevents the scheduler from moving the lbu past it.

Hmm, actually the barrier also orders the STORES: `*((u8 *)pkt + 3) = 9;` etc. come after.

What real-C construct can keep the lbu before the lui/lw? 

Idea: make the D_800A5E60 load depend on hh! E.g., use hh in the pkt pointer computation: `pkt = (FT4_801857A4 *)(D_800A5E60 + (hh & 0));`? folds.

Idea: since `pkt->v2 = pkt->v0 + hh;` is later, what if we move that computation earlier? No.

Idea: use a do-while around the pkt/D_800A5E60 lines (v5 in the A-only batch gave 8). With B,C fixed? Let me try.

Alternatively: what if we change where hh is used: the target code has `lbu t7,48(sp)` early. Maybe if hh were used earlier in the source (e.g., in the rgb computation), the lbu would be born earlier. But that changes code.

Hmm, what if we simply move the `hh = h;` line to be the FIRST of the group (before rgb)? Then the lbu might be scheduled earlier. Let me test: order hh, ww, rgb, cyy, zf, tpp. Actually v4 swapped ww/hh only.

Wait, maybe the issue is the *delay slot*: mine places the lbu after the lw (in its load-delay slot). The target has the lbu BEFORE the lw. The scheduler fills the lw's delay slot with the lbu. To prevent, the lbu must be scheduled earlier (higher priority) or the lw later.

What raises the lbu's priority? Its use is far away. Hmm.

What if we make hh used in the `ot = ...` computation? no.

What if hh is used in an expression right after the assignment that folds: e.g. `hh = h; rgb = rgb;` no.

OK, another angle: the barrier A is a *memory clobber*, so it orders ALL memory ops. The lbu is a memory op before it; the D_800A5E60 load is after it. A real-C construct that orders two memory ops: a store between them that may alias! E.g., if we put a store between `hh = h;` and `pkt = D_800A5E60;`, the scheduler couldn't move the lbu across the store (may-alias). But a store adds code.

Unless the store is part of the existing code: the `*((u8 *)pkt + 3) = 9;` store is AFTER the D_800A5E60 load. If we moved a store between... no.

Hmm, what about the order: `pkt = D_800A5E60; D_800A5E60 += 0x28;` — the increment is a load+add+store. The lbu could be ordered vs that store. If we move the `hh = h;` AFTER `pkt = D_800A5E60; D_800A5E60 += 0x28;` but before `*((u8*)pkt+3) = 9;`, then the lbu would be after the D_800A5E60 load (wrong: target has it before).

Wait, actually the target order: lbu t6 (w), lbu t7 (h), lui t0, lw t0 (D_800A5E60), addiu, lui at, sw (D_800A5E60 += 0x28). So the lbu's are before the D_800A5E60 load.

What if the source assigns hh *before* ww? v4 = 2. What if we assign hh first (before rgb)? Let me try several orders:
- hh first, then rgb, cyy, zf, tpp, ww.
- hh, ww at the very end (current).

Also, maybe make `ww` and `hh` assignments adjacent in source (they are) — the target has them adjacent in code (lbu t6, lbu t7).

Actually! Look: target `lbu t6,44(sp)` = w at index 8, `lbu t7,48(sp)` = h at index 9. Mine (A removed, B,C fixed): lbu t6 at 10, lui/lw at 11-12, lbu t7 at 13.

So mine put the D_800A5E60 load between the two lbu's. The barrier A is AFTER both lbu's, so it can't explain why the target has them adjacent... unless the barrier forces all memory ops before it to stay in order: lbu t6, lbu t7, then (after the barrier) the D_800A5E60 load.

Yes! The barrier forces the D_800A5E60 load (after the barrier) to come after ALL memory ops before it, including both lbu's. Without the barrier, the scheduler interleaves.

So we need a real-C construct that orders the D_800A5E60 load after the lbu's. Since both are loads, a *store* between them would do it, but there's no store.

Hmm — but what if we REORDER the source so that the D_800A5E60 lines come after a store? There's no store before `*((u8*)pkt+3)=9` (which needs pkt).

What if we make the D_800A5E60 load depend on hh through a real computation that's free? E.g., `pkt = (FT4_801857A4 *)(D_800A5E60 + (hh - hh));` — if fold doesn't eliminate hh-hh, we get a subu (extra insn). Fold does eliminate x-x for variables? Let me check: fold's "A - A -> 0" is done in fold() for non-volatile operands; yes, it's a standard simplification (`if (operand_equal_p (arg0, arg1, 0)) return const0_rtx` for MINUS). So it folds.

What about `hh & 0`? folds.

What about using hh in a way that the compiler can't prove: `(hh & (h - h))`? h is a memory load; fold might not fold h-h across the load (it could, since it's the same memory location and not volatile... but there's a load in between? no, adjacent). Fold's operand_equal_p on two identical MEM rtxs — it does fold x-x if no side effects; a MEM read is not side-effecting unless volatile. So it folds.

Hmm.

What if we use a *volatile* read of h? `hh = *(volatile u8 *)&h;` — then the load is volatile and can't be reordered across other memory ops! The volatile lbu would be ordered vs the D_800A5E60 load (also memory). That would keep it before... wait, volatile ordering: sched1 treats volatile mem refs as barriers relative to other memory ops (true_dependence returns 1 for volatile). So the volatile lbu can't move past the D_800A5E60 load, and the D_800A5E60 load can't move past it. That gives the target order: lbu (volatile), then the load.

But does making hh's load volatile change the code? The instruction is the same `lbu`. It might change other things (cse won't eliminate it; it's used once). Risk: the compiler might not be able to... Let's try!

Similarly, making the load of h volatile is a real C qualifier (not a lever? volatile is ordinary C, and the census counts `volatile` as... hmm. The lever_census AB_KINDS includes "launder" — a volatile cast can be a launder. The brief says no launder: "Lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm". The row kind is barrier only, so launder is not the row kind. But CONSTRAINTS say "identity-statement launders ... do NOT count as a crack" and "no new lever of any kind". Adding a `volatile` cast to change codegen would be a NEW LEVER (a volatile/launder). That's forbidden: "no new lever of any kind".

Hmm. Is a volatile read a "lever"? It's a codegen-affecting C qualifier used deliberately to control the compiler — yes, that's a lever (the census's launder/barrier class). The brief says lever-free = real C moves only (temps, decl order/scope, widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse). `volatile` is NOT in the catalog (C0505). So no.

So the A barrier needs a catalog move. The catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

"statement order" — reorder the source so the target's order emerges. The scheduler still reorders, but maybe a different source order changes priorities.

"loop shape" — do-while (tested).

Hmm, what about "temps": introduce a temp for the D_800A5E60 load? e.g.:
```
u8 *base = D_800A5E60;   // temp
pkt = (FT4_801857A4 *)base;
D_800A5E60 += 0x28;
```
Hmm.

Or a temp for hh: `s32 hh2 = h; hh = hh2;` — extra move.

What about making the D_800A5E60 load's result used later (so it's born later)? It's used immediately.

Let me try statement-order variants: move the `hh = h;` assignment to the very first line (before rgb). And move the D_800A5E60 lines around.

Actually, here's a thought: the target's lbu t6/t7 are the FIRST two memory ops. If the source order were `hh = h; ww = w;` before rgb/cyy/etc... the schedule might still interleave.

Let me try a batch of order variants with B,C fixed:
- e1: hh = h; first, then the rest.
- e2: hh = h; ww = w; first.
- e3: put `hh = h;` after `pkt = ...`? no (target has it before).
- e4: move the whole pkt group before the rgb group? Then pkt's load would be first — target has rgb's lui/ori first (indices 2-3), then moves, then the parameter loads, then the D_800A5E60 load. Hmm, the rgb lui/ori are at 2-3, before the parameter loads! Interesting: `rgb = 0x808080` is a constant, so it's lui/ori early.

Let me try e1/e2 and also `hh = h;` with a temp.

Actually, let me reconsider: maybe I can crack A by changing the *parameter* handling: hh = h where h is a u8 K&R parameter at 0x30(sp). The target loads it early because the barrier orders it. Without the barrier, it sinks.

What if hh is used in the *first* memory op after it? Hmm.

Let me try the order variants and a couple of temp forms. Time: 06:47. Item5 has taken 5 min. Budget is fine.

Let me generate e-variants on top of w_d_base (B,C fixed, A present) with A replaced by various forms.
