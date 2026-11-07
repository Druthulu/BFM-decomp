---
ts: 2026-11-06T08:50:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZmdTTOUe6LNJ9vLvifno
---
d3 (t3 store after h[1]) gives the right registers for the a0-copy (a2) and t3 (a3), but the t3 store is emitted late (at position 34) instead of at 21, and t4 is v0 not v1. So the store placement matters for the *emitted* code: the target stores t3 at insn 21 (right after the other stores), while d3's store moved to after h[1].

So the target's pre-alloc RTL has the store at position 21 but t3's live range extending to ~18 insns? That's impossible unless t3 is used later by something else — the keepalive asm was exactly that. And the store at 21 is where it is.

Hmm, so the target's real C must have t3 used *again* after insn 21 without emitting an instruction — that's what an asm does. Real C can't use a value without an instruction... unless the use is folded into an existing instruction's addressing.

AH WAIT. What if t3 is used as part of the *call*? No.

What if the fifth load's address uses t3? No.

Hmm, hold on: maybe the real C's t3 is not a temp but part of a struct/array assignment. Let's think: the five values are loaded from D_801A5460..5470 and stored to sp10[0..4]. What if the source does a *struct copy*: `*(SomeStruct5*)sp10 = *(SomeStruct5*)((char*)&D_801A5460 + off);`? That would generate 5 lw + 5 sw, possibly with different scheduling and register assignment! The move_by_pieces/struct copy path in gcc 2.7.2 (expand_assignment for BLKmode) emits loads and stores with its own temp registers. That could produce exactly this pattern: 4 loads, 4 stores, 5th load, 5th store... Hmm, move_by_pieces emits: for each chunk, load then store, i.e., load/store interleaved. The target has 4 loads then 4 stores then 1 load+1 store — that's sched1's doing perhaps.

But a struct copy of 20 bytes would be done by move_by_pieces with 4-byte chunks: load/store, load/store, ... 5 times. Then sched1 could reorder the stores after the loads. That's plausible! And the register assignment of such copies: move_by_pieces uses `gen_reg_rtx` temps per chunk. Hmm.

But actually the original body's levers comment doesn't mention a struct copy. It uses explicit temps. The "real C" the shard wants could be a different spelling though.

Let me try: `*(s32(*)[5])sp10 = *(s32(*)[5])((char*)&D_801A5460 + off);`? The globals are separate symbols but contiguous; a single struct copy would reference only D_801A5460 with an offset — but the target references all five symbols (5 relocations: D_801A5460, 464, 468, 46C, 470). A struct copy from `&D_801A5460 + off` would only reference D_801A5460 (one reloc) with displacements 0,4,8,12,16. The target listing shows separate HI16/LO16 relocs for each symbol (D_801A5460, 464, 468, 46C, 470). So the source references each symbol separately. Good — that constrains it.

So five separate loads from five symbols, stored into sp10[0..4].

What real C yields the t3 liveness? Only an extra use. Unless... the store order! What if the source stores sp10[3] = t3 LATER but sched1 hoists it back? In d3 the store stayed late (after h[1]) because sched1 couldn't move it up past the h[0]/h[1] stores due to anti-dependencies on sp10? Actually sched1 reorders within a basic block respecting deps; the store to sp+28 vs stores to sp+16/18: memory anti-deps. It could move but didn't.

What if the source's extra use is *reading* sp10[3]? Like `h[2] = h[2] + ...` where the h[] pointer is used... no.

Hmm, let me reconsider: maybe the target's t3 live range is short (5) but its priority is lowered another way: qty_size! pri = floor_log2(refs)*refs*size/(death-birth). If t3's mode is HImode? no, it's SI.

Or maybe the a0-copy's priority is RAISED. refs 6. How? The a0 copy is used at the three lhu's and the call. What if the source uses `a0` a fifth time in a way that doesn't add an instruction... 

Actually! What about the CAST_ALIAS macro? `CAST_ALIAS(u16, (s32)a0, 0xA)` — maybe the source uses a0 with different casts creating multiple uses. Hmm.

What about the call: `func_8012C51C(sp10, (s32)a0)`. What if the source passes `a0` as a pointer cast, e.g. `func_8012C51C(sp10, (s32)(Unkstruct*)a0)`? Same.

Let me look at the a0-copy's uses in the RTL: 3 lhu's (r72) + 1 move for the call. What if the h[] computations used the pointer to sp10 differently, e.g., `h[0] = h[0] + *(u16*)((s32)a0 + 6)`? Same.

New idea: make the a0 copy *die* and be re-created so it's two pseudos each with higher priority? E.g., if the a0 pointer is used, dies, then used again later — but it must stay in a2 throughout (the target uses a2 for all three lhu's and the call). Two pseudos could both get a2 if their ranges don't overlap... they do overlap (same value needed).

OK, alternative: maybe the real C uses a *different variable* for the pointer that also appears in the fifth load's address, making its live range shorter... no, we want higher priority = shorter live or more refs.

Hmm, what if the a0-copy's live range STARTS later? The param copy is at insn 4 (the `move`). If the copy were created later (after the loads), its birth would be later, live shorter → higher priority! The `move a2,a0` in the target is at insn 1 (first insn after sp adjust). So the copy is created at the top. Birth = insn 4.

Unless... the copy is created at the top but the pseudo is only *used* later; live length = death - birth where birth is the def. Fixed.

OK, let me try to get t3's live length to 6 by having the *fifth load* use t3 as its destination? No.

What about making t3 used in the store of t4: `sp10[4] = t4 + (t3 - t3)`? That's an identity launder (disallowed).

What if t3 is a pointer to something? no.

Let me try a completely different reading: maybe in the target, the h[] updates are done via t3? Like the code reuses t3 as a scratch in the h computation? The target's h computation uses v0/v1/a0/a1 (lhu v0, lhu v1, addiu a0, addu v0, sh). t3 (a3) is not used after insn 21. So no.

Hmm, so the target's t3 really dies at insn 21 (the store). Its live range: from load (17) to store (21) = 5 insns → pri 4000. And the a0-copy r72: live from 1 to 40 = 40 insns?? In the target's final code, the a0 copy (a2) is used at insns 28,33,38 and 39 (move a1,a2), so live from 1 to 39. That's a much longer live length than 27! In MY w1 RTL, r72's live length is 27. In the target's RTL it might be different (fewer/more insns between). But the live length is measured in the RTL *before* reload where the call setup etc. differ.

Wait, actually the live length of r72 in w1 is 27 (from insn 4 to the call insn ~96). The "27" is the number of insns where r72 is live (incremented per insn in the live set). The final target has the same insn structure, so r72's live would also be 27 → pri 3703. For the target to give r72 a2, t3's pri must be < 3703 → t3 live ≥ 6.

Unless t3's *refs* differ: if t3 were used 3 times (e.g., store to sp10[3] twice?) pri = floor_log2(3)=1, 1*3/live. With live 5: 6000. Worse.

If t3's size were... no.

Hmm, so how could the target's RTL give t3 live ≥ 6 while the final instruction order has it 5 insns apart? Because local-alloc runs on the RTL after sched1, and sched1's output order might have t3's store later than the final (sched2/reorg reorders). In d3, sched1 kept the store late and it stayed late in the final code. But maybe the target's source has the store in the original (early) position while t3 is used again later by a *scheduling barrier*... no.

WAIT. Maybe I've got it backwards: maybe the target's t3 pseudo is live from an EARLIER point. What if t3's load happens earlier in the source (before t2's)? Then the live range from its load to its store would be longer, and its store position in the final code is still 21. E.g., source order: t3 loaded first, then t0,t1,t2. After sched1, the loads could be ordered t0,t1,t2,t3 (as target) but the pseudo t3's live range... no, the live range is determined by the RTL order, not the source order. If sched1 reorders the loads to t0,t1,t2,t3, then t3's load is at position 17 regardless.

Unless sched1 does NOT reorder loads (it may keep source order) — but the target's final order IS t0,t1,t2,t3,t4 loads. If the source order were t3 first, sched1 would have to reorder. Hmm.

OK here's another thought: the live length counts insns where the reg is live, and *sched1's order* is the final order (modulo sched2). What if the target's t3 store is NOT at insn 21 in sched1's order but sched2/reorg moved it? sched2 can reorder within blocks too (it's a second scheduler). The final order has it at 21. So sched2 could have moved it up.

In d3, sched1 left it late and sched2 didn't move it. Maybe a different source position lets sched2 move it. Hmm, unlikely.

Let me try: keep the store early (target position) but add a *real* later use of t3 that the compiler removes... no.

Alternative: maybe the a0-copy is not one pseudo in the target. What if the source uses a *fresh cast* of a0 for each lhu, and the compiler's CSE doesn't merge them into one pseudo because of the intervening call? There's no call between. Hmm.

Let me try the most promising remaining idea: reuse t0 for the fifth load AND extend t3's live range via d3's store-after-h[1], but with the store position... 

Actually, d3's diff showed the t3 store at position 34 (after h[1]) and the correct regs a3/a2. If I could get the store back to position 21 AND keep the long live range... The long live range came from the store being late. So no.

Let me reconsider (b) t4→v1 with the early t3 store (w2 variant score 2). What if we make the fifth load use a temp that is also used by an earlier store (copy preference)? E.g.:

```
t4 = *(s32 *)((char *)&D_801A5470 + off);
sp10[4] = t4;
```
The store to sp10[4] has no preference.

What if we write the fifth load into sp10[4] via a variable that was used before: `t0 = *(s32*)((char*)&D_801A5470 + off); sp10[4] = t0;` (d1). In d1, the pseudo's reg was a3 at the end, not v1.

Hmm, what if instead: `sp10[4] = t4 = *(s32*)(...);`? Same.

What if we declare t4 and use it in the h computation? no.

Let me look at the actual difference between target and w2 (score 2): only t4 v0 vs v1. What if the address temp r84's live range were extended by ONE insn (past the fifth load) via a real use of `off` in the h[2] computation? Like:

h[2] = h[2] + ((Unkstruct*)a0)->unkE;  — no off.

What if the source uses off to index h? `h[2] = h[2] + *(u16*)((char*)&D_801A5470 - ... )` no.

Hmm, what if the fifth load's address expression is *reused* for something else later, e.g. the h[2] load could be written via the same base? no.

What about this: since the address temp r84 = off*4, if the source computes `off = a1 * 20` and uses `off` in the h computations via `(u16*)((char*)sp10 + off - off)`? identity launder, disallowed.

OK let me try yet another structure: what if the five loads are done with `off` computed as `a1 * 5` and then `*(s32*)((char*)&D_801A5460 + off*4)`? The multiply-by-4 could be folded differently (e.g., off*4 via sll each time or the address scaled). Might change live ranges: `off*4` as a separate expression per load → each load's address computation independent, and off (a1*5) live across all loads. Hmm, the target's v0 = a1*20 computed once (sll/addu/sll) and reused in all 5 addresses. So off*4 is CSE'd once. Same.

I think I should try the simplest remaining structural idea: five separate `s32` locals for sp10 (not an array), or the array but stores written as `*(s32*)((char*)sp10 + 4*i)`. Unlikely to change liveness.

Let me instead try to get t3 live 6 via sched1 order. The live length counts insns in the *sched1 output*. If the source has an extra dependency that makes sched1 place t3's store after t4's load (position 24) while sched2 moves it back to 21... Let me test c1 again: c1 had the store after the t4 load in source; final code kept t3 at position 35 (sw a2,28(sp) at line 35) — wait c1's listing showed `sw a2,28(sp)` at line 35 (after lw v0,0(at) at 33). So sched1 moved it after the load (position 35) and sched2 didn't move it back. The diff was score 10 with 46 insns.

So sched2 doesn't reorder much.

Hmm, so how does the real target achieve t3=a3 with a store at position 21? Maybe local-alloc's ordering isn't purely pri — there's also `qty_phys_reg` preferences. Let me look at local-alloc.c's `alloc_qty`: it tries `reg_preferred_class` first, then `qty_phys_reg`... Let me read the relevant part to see if a preference could give t3 a3 and the copy a2.

Actually, here's a cleaner idea I haven't tried: **give the a0-copy a copy preference for a2**. If the a0-copy's preferred register is a2, local-alloc would try a2 first. Copy preferences come from copies (`move`). The a0 param copy is `(set r72 (reg a0))` — hard reg a0. Hmm, `set_preference` for a copy from a hard reg? local-alloc sets `qty_phys_reg` preference when a pseudo is copied to/from another pseudo. From a hard reg, the preference is the hard reg itself (a0)? But r72 got a3 in w1, so no preference or a0 was taken.

What if the source has a copy involving a2? E.g., an intermediate pointer `p = (u16*)a0;`? That's still the param copy.

Hmm, what if the a0 copy is used as the destination of a copy from something in a2? No.

Let me try: `u16 *p = (u16*)a0;` used for the three lhu's, and pass `(s32)p` to the call. Then p is a pseudo copied from a0. Same.

Time check: ~30 min on item 1. The brief says budget 20-30 min wall per item; past 30 min stop and record a wall (WALL needs ≥20 min and ≥30 scored tries). I have maybe 15 scored tries. Let me push a few more high-value tries, but I must not sink the whole task. Actually, the budget is per item and "do not stop between items". Let me spend ~10 more minutes max on item 1, then move on.

Let me try a batch of ~8 candidates quickly:

e1: w2 (t3 keepalive equivalent) but with t4's load using the same address temp trick: put the fifth load's store before the load? no.

e1: reuse t0 for fifth load + early t3 store (target order).
e2: same but with `sp10[4] = t0` written as `*(sp10+4)`.
e3: declare off inside a block; use `s32 off = a1 * 20;` init at decl.
e4: move `h = (u16*)sp10;` before the loads.
e5: compute h[0..2] via `sp10[...]` instead of h.
e6: use `((u16*)sp10)[0] = ...`.
e7: split the h computation with a temp.
e8: make the fifth load into t1 (a0).

Hmm, e8: target's fifth is v1, not a0.

Wait, actually, maybe I should look at whether the target's fifth load being v1 could come from the *store target* preference: `sp10[4] = t4;` where sp10[4] is also read by the call... no.

Let me look at the problem from the angle of the *first* keepalive: it was on `off`, and it produced the t4→v1 fix (score 7, only the a0/t3 swap). The second keepalive (t3) fixed the a0/t3 swap (score 2, only t4). The real C needs both effects.

For the off effect: the asm used r84 = off*4 (the CSE'd address temp), keeping it live past the fifth load. A real C use of the *address temp* after the fifth load: the address temp is `(char*)&D_801A5470 + off` — the same value as `&D_801A5460 + off + 0x10`. If the h[2] computation used a global at that address... no.

Hmm, but what if the source computes the five loads through a *pointer variable*:
```
    s32 *p = (s32 *)((char *)&D_801A5460 + off);
    t0 = p[0]; t1 = p[1]; ...
```
Then the target's relocations would be D_801A5460 only, but target has five separate symbols. Unless the TU declares them as an array `D_801A5460[5]`? Then referencing p[1] would emit D_801A5460+4 relocation, displayed as D_801A5460 with offset. The objdump shows five distinct symbol relocs (D_801A5464 etc.), so no.

OK, what if off is used to index a *second* array in the h computation? The h[0] value is at sp10[0] = the first loaded word. h[0] = h[0] + a0->unk6. No global.

I'm stuck on a clean mechanism. Let me try the batch and then decide on WALL/PARTIAL.

Actually — hold on. Let me reconsider the possibility that the fifth load is done via a *separate* variable declared later, e.g. `s32 t4` declared inside a nested block or initialized at declaration. "init at decl" is a listed real-C move! What if:

```
    s32 t4 = *(s32 *)((char *)&D_801A5470 + off);
```
at the declaration point (after the stores)? That's a C89 mixed declaration — gcc 2.7.2 might allow it? The project's style is C89; `s32 t4 = ...` after statements would be an error.

What about declaring all temps with initializers at the top? `s32 t0 = ..., t1 = ...;` — the loads would be emitted at declaration order, and the stores later. That's the c2 structure (all loads first, then stores) → 46 insns.

Hmm, but wait: maybe with declarations `s32 t0 = load0; ... s32 t4 = load4;` the loads are all emitted first, then the stores — but sched1 might interleave them into the target order. c2 (loads then stores) gave 46 insns and score 16. Not good.

Let me try: the five loads into sp10 via a temp, but with the fifth load declared/emitted *after* the fourth store:

```
    t0 = load0; t1 = load1; t2 = load2; t3 = load3;
    sp10[0]=t0; sp10[1]=t1; sp10[2]=t2; sp10[3]=t3;
    t4 = load4; sp10[4]=t4;
```
= orig (w1). The RTL order is target's order and allocation gives t3 a2. 

The asm's effect on t3's liveness: the asm at position after h[1] used t3, extending its live range to insn ~71 while the store stayed at 51. For real C, we need a use of t3 at insn ~71 that costs nothing. What existing instruction at ~71 could use t3? The h[2] computation at insn 83 uses r72 (a0 copy) and r96 (lhu). If the source wrote h[2]'s update using t3 somehow... but the target's code doesn't have t3 there.

Conclusion: no real C use of t3 after its store can exist without adding an instruction. Therefore the t3 fix must come from a different allocation-order effect. Let me look at local-alloc's allocation loop for preferences. Maybe a copy preference could give the a0-copy a2 directly.

Let me read local-alloc.c around the allocation decision.
