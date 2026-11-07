---
ts: 2026-11-06T13:48:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FSMs1Def3wyH2E5Eprcd
---
With the ww/hh order swapped, the sinking one is now lbu t6 (w) instead of t7 (h) — the same issue: the last parameter load sinks below the D_800A5E60 lui/lw.

So the scheduler takes the last lbu and puts it after the D_800A5E60 load. To keep BOTH lbu's before the D_800A5E60 load, we need an ordering.

The barrier A (memory clobber) did it. Real-C: we need the D_800A5E60 load to be ordered after the lbu's.

Idea: make the D_800A5E60 load *depend* on ww or hh via the pointer arithmetic in a way that doesn't add code. What if the pkt pointer is computed as `(FT4_801857A4 *)(D_800A5E60 + 0 * (hh + ww))`? fold removes the *0? Let me think: `0 * (hh+ww)` → fold to 0 (multiplication by zero is folded regardless of side effects? fold does `0 * x -> 0` only if !TREE_SIDE_EFFECTS(x); hh+ww has no side effects, so yes).

What about `(D_800A5E60 + (hh & 0))`? folds.

Hmm, what if we use a comparison that's folded at RTL but not tree level... no.

Alternative: change the source order so the D_800A5E60 load is naturally after the lbu's AND the scheduler can't move it earlier. The scheduler moves the D_800A5E60 load up to fill the lbu's slot? Actually mine: lbu t6 at 10, lui t0 at 11, lw t0 at 12, lbu t7 at 13. The scheduler placed the lui/lw between. If the D_800A5E60 load had a dependency on something...

What if `pkt = (FT4_801857A4 *)D_800A5E60;` uses a temp that is set... no.

What if we use `D_800A5E60 += 0x28;` BEFORE `pkt = D_800A5E60;`? That changes semantics (pkt would be the new value). Unless we save: `u8 *base = D_800A5E60; D_800A5E60 = base + 0x28; pkt = base;` — same code, but the order of the load and the store... The store to D_800A5E60 is a memory op; the lbu's are memory ops. sched1 might order the store vs the lbu's? Loads can move above stores if no alias (D_800A5E60 is a global; the lbu is a stack read — no alias). So no.

Hmm, what about a store to the stack before the D_800A5E60 load? The lbu reads the stack params. A store to the stack would alias the lbu (same base sp, different offsets — the scheduler might still not alias). 

What about making the D_800A5E60 load *volatile*? Same problem (new lever).

What about reordering the source so that the two lbu's are used immediately? E.g., use ww and hh in the pkt->u/v computations which are later...

Hmm, what if we move `ww = w; hh = h;` to AFTER the D_800A5E60 lines but before the `*((u8 *)pkt + 3) = 9;` store? Then the lbu's are after the D_800A5E60 load in source. But the target has them before! Unless the scheduler hoists them above the D_800A5E60 load (it can, since no dependency). Would it? The lbu's would be born after the load in source; the scheduler might keep them there. Risky, but worth a try: the target's order could emerge if the scheduler hoists.

Actually — wait. Let me reconsider the target: is the D_800A5E60 load maybe scheduled after the lbu's because of the *store* `sw s0,16(sp)`? The prologue store. Hmm.

Let me look at the target head again:
```
8e50: addiu sp,sp,-24
8e54: move t1,a1
8e58: lui a1,0x80
8e5c: ori a1,a1,0x8080
8e60: move t2,t1
8e64: lw t5,40(sp)
8e68: move t3,a2
8e6c: sw s0,16(sp)
8e70: lw s0,52(sp)
8e74: lw t9,56(sp)
8e78: lbu t6,44(sp)
8e7c: lbu t7,48(sp)
8e80: lui t0, D_800A5E60
8e84: lw t0,0(t0)
```
The `sw s0,16(sp)` is the callee-save of s0 — part of the prologue, scheduled among the loads.

Mine (d_v4):
```
8e50: addiu sp
8e54: move t1,a1
8e58: lui a1
8e5c: ori a1
8e60: move t2,t1
8e64: lw t5,40(sp)
8e68: move t3,a2
8e6c: sw s0,16(sp)
8e70: lw s0,52(sp)
8e74: lw t9,56(sp)
8e78: lbu t6,44(sp)   ← (this is hh after the swap? w)
8e7c: lui t0
8e80: lw t0
8e84: lbu t7,48(sp)   ← the second one
```
So only the last lbu is displaced into the lw's delay slot.

What if we add a *third* parameter load? No.

What if the hh/ww assignments are moved so that both lbu's are born before the D_800A5E60 lines in the RTL and the scheduler has a reason to keep the second one early: e.g., if the second lbu's value is used by an insn scheduled before the D_800A5E60 load. The uses are `pkt->v2 = pkt->v0 + hh` and `pkt->u1 = pkt->u0 + ww` — both later.

Hmm, what if we reorder the pkt field stores so that the u/v computations come earlier? The target order is fixed.

OK — what about this: make the two lbu's part of one expression so they're adjacent? E.g.:
```
ww = w;
hh = h;
```
The scheduler treats them separately.

What if `hh = h; ww = w;` are written as `hh = h, ww = w;`? Same.

What if we compute both from a combined load: `*(u16*)&w`? The params w and h are at 0x2C(sp) and 0x30(sp) — adjacent! A single `lhu` would load both: `u16 wh = *(u16 *)((char *)&w); ww = wh & 0xFF; hh = wh >> 8;` — that's a different instruction sequence (lhu + andi + srl). Not target.

Hmm.

What about the A barrier's *other* effect: it also orders the `sw s0,16(sp)` (prologue) and the loads. 

Let me consider: maybe the real answer is to use a different barrier-free construct that the census counts as real C: a `&&`/`||` fold? The catalog mentions `&&`/`||` folds.

What if we write `pkt = (FT4_801857A4 *)(D_800A5E60);` vs with a conditional? no.

Honestly, maybe A is a WALL (the residual is a sched1-load-delay-fill: the scheduler fills the D_800A5E60 lw delay slot with the last param load). The moves table has `sched1-load-delay-fill` as a wall tag.

But wait — the item's kinds = barrier only. If I can't crack A, the item is not a MATCH. The result would be PARTIAL:<kept> only if I keep some levers; a WALL means the win.c keeps all row kinds. Since the row kind is "barrier" and A remains a barrier in the best body, the result is WALL with best = the score of the lever-free body... Hmm, careful: the definition: "WALL (best = lowest score of a lever-free body)". A lever-free body must have no barriers. The best lever-free body is 2 (with B,C fixed and A removed). So WALL best 2, wall tag sched1-load-delay-fill.

But before that, let me try a few more A ideas, since 2 is so close.

Idea: what if the D_800A5E60 load is moved after the `*((u8 *)pkt + 3) = 9;` store? No, pkt needs it.

Idea: what if `D_800A5E60 += 0x28;` is written as a separate statement after pkt's first use:
```
pkt = (FT4_801857A4 *)D_800A5E60;
*((u8 *)pkt + 3) = 9;
D_800A5E60 += 0x28;
```
Then the store to D_800A5E60 comes after the sb store. The lbu's are before... this changes the target order (the target has the D_800A5E60 store early at 8e98).

Idea: use `ot` computation as a dependency? no.

Idea: reorder so the D_800A5E60 group comes AFTER the gte macros? no.

Idea: What if the hh/ww assignments are placed inside the `if` that uses them? no.

Idea: since the scheduler fills the lw delay slot with the last lbu, what if we make the D_800A5E60 load's delay slot already occupied by something else? The delay slot is filled by the scheduler; if another insn depends on the lw... no.

Idea: what if we introduce a *use* of hh right after the assignment that the scheduler can place early, e.g.:
```
hh = h;
if (hh == hh) { }  // folds
```
no.

Idea: `ww = w; hh = h; rgb = rgb | (hh & 0);` folds.

Hmm, what about making the D_800A5E60 access via a *struct member* (MEM_IN_STRUCT) so the scheduler's alias analysis differs? The load address is a global; the lbu is a stack load. Alias analysis might treat the in_struct load as nonscalar and not move it across the stack load? Hmm, the stack lbu is a different address entirely (sp+44 vs a global) — no alias regardless.

Actually wait: why does the scheduler move the lbu AFTER the lw at all? It's filling the lw's load-delay slot (the MIPS sched1 has a "load delay" consideration). The lbu is independent and can fill it. To prevent, the lbu must be scheduled before the lw. The scheduler's priority for the lbu (a load with a distant use) is low.

What if hh is used SOONER in the source? E.g., if the first use of hh were within the same basic block right after, the lbu's priority would rise. The first use is `pkt->v2 = pkt->v0 + hh;` at the end of the block. What if we move the `pkt->v2` computation earlier? The target order of the pkt stores: u0, u1, v2, v1, u2, u3, v3 (from the source). Changing that changes the target bytes.

Hmm, but the u/v assignments are:
```
        pkt->u1 = pkt->u0 + ww;
        pkt->v2 = pkt->v0 + hh;
        pkt->v1 = pkt->v0;
        ...
```
The scheduler placed the loads early anyway.

What if we assign `pkt->v2 = pkt->v0 + hh;` FIRST among the v/u stores? That changes the store order → different bytes.

OK, I'll try one more family: "init at decl" — `s32 hh = h;` at the declaration point? No, the declaration is at the top (outside the block), and the assignment must happen after the prologue. Hmm, "init at decl" means `s32 hh = h;` in the declaration — that would move the lbu to the top of the function, before the other inits. The target has it at index 9, after the other param loads. Let me try `s32 hh = h;` and `s32 ww = w;` at the declarations (removing the assignments). The decls are:
```
    s32 ww;
    register s32 tpp __asm__("$25");
    s32 hh;
```
If we init at decl, the order of the inits follows the declaration order, which is: ... tpp, ww, hh, zz, cyy... The target's order of param loads: t5(cy), s0(tp), t9(zoff), t6(w), t7(h) — matches the init statement order (cyy=cy, zf=zoff, tpp=tp, ww=w, hh=h) but the declarations differ. If we init at decl, the order would be: zf (decl 18), z (25), cl(27), oz(29), tpp(33), zz(35), cyy(36)... and ww/hh declared at 32/34. Hmm.

Actually the assignment statements `cyy = cy; zf = zoff; tpp = tp; ww = w; hh = h;` in that order produce the target's load order (lw t5, sw s0, lw t9, lbu t6, lbu t7). Wait, t5=cy (lw 40(sp)), s0=tp (lw 52(sp)), t9=zoff (lw 56(sp)), t6=w (lbu 44(sp)), t7=h (lbu 48(sp)). Hmm, the source order is cyy, zf, tpp, ww, hh but the loads are t5(cy), s0(tp), t9(zoff)?? That doesn't match cyy=cy, zf=zoff, tpp=tp (would be cy, zoff, tp). The scheduler reordered.

OK. Let me just try a few: init at decl for hh/ww; and moving the hh assignment to the very end of the block (after the pkt stores)? No.

Actually, let me look at this from the "what would a human do" angle: the barrier stops sched from sinking the lbu h below the D_800A5E60 load. The known project wall tag `sched1-load-delay-fill` says "sched1 fills a load-delay slot with an independent store group the target leaves as nop" — here it's an independent *load* filling the lw delay slot. That's the same class: sched1-load-delay-fill.

Given the item has 3 barriers and I've cracked 2, the best lever-free body (A removed, B/C do-while) = 2. A WALL with best 2 is a decent result. But let me spend a few more tries.

Idea: make the D_800A5E60 load *later in source* than the lbu's AND give the scheduler no reason to hoist it: move the pkt group after the first sb store? Can't (needs pkt).

Idea: introduce a temp for the D_800A5E60 load that is assigned late: 
```
u8 *base;
...
base = D_800A5E60;
pkt = (FT4_801857A4 *)base;
```
Hmm, that adds a move unless coalesced.

Idea: use `pkt = (FT4_801857A4 *)D_800A5E60, D_800A5E60 += 0x28;`? no.

Idea: change the ot computation to come between the lbu's and the pkt group? The target has ot later.

Let me try the init-at-decl idea and a couple of orderings where the pkt group is moved before the ww/hh assignments:
- f1: init at decl for ww and hh.
- f2: move the pkt group (pkt, D_800A5E60+=, ot) BEFORE the ww/hh assignments but after rgb/cyy/zf/tpp.
- f3: hh assignment right before `pkt->v2 = pkt->v0 + hh;`? No — target has it early.

Actually, f2: if the D_800A5E60 load is before the lbu's in source, the scheduler might still move the lbu's before it (they're independent) or not. Target has the lbu's before. Risky.

Let me try f1, f2 and a variant where the two lbu assignments are swapped with the pkt group.

Time is fine (06:49). Let me do it.
