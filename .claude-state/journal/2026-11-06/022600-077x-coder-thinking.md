---
ts: 2026-11-06T09:26:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KZGhL1N1NUepo2khOfMQ
---
Same as item 1: the missing `move v0,s0` (rv = a0 copy coalesced). 

For item 5, we can force the copy by making rv's value not a pure copy of a0? Target needs `move v0,s0` where s0 = a0. The asm keepalive reads rv. If rv and a0 coalesce, no move.

To prevent coalescing: make rv's live range conflict with a0's. a0's pseudo is live... after `rv = (s32)a0`, a0 is dead (last use). So they can coalesce.

Idea: use a0 after the copy: e.g. `*a0 = rv; rv = (s32)a0;` — hmm. If we add a use of a0 after rv=a0, coalescing breaks, but the use must cost no instruction... Any use costs something.

What about making rv's source a different expression: `rv = (s32)(a0 + 0);` folds. `rv = (s32)(void*)a0;` copy.

What if rv is s32 and a0 is s32*: the conversion is a nop copy. 

Hmm — what if we assign rv from a *global*? No, target's value is a0.

What if the copy is `rv = (s32)a0;` but rv's live range starts before (it was set earlier: rv = sp20). rv has an earlier set! So rv's pseudo live range: from `rv = sp20` to `*a0 = rv` (dies), then re-born at `rv = (s32)a0` to the asm. Wait — in GCC, a pseudo reg (user variable rv) has ONE pseudo with multiple sets. Its live range is entry-to-asm (since it's live at the start of the second set... no, after `*a0 = rv` it's dead until the next set). Local-alloc splits by blocks.

Since `rv = sp20` and `rv = (s32)a0` are both sets of the same pseudo, the allocator might still coalesce the second range with a0.

Target: rv's first range (sp20) gets v0 (lw v0,32(sp); sw v0,0(s0)) and the second range gets v0 via move from s0. So the target has rv in v0 in both ranges, with a0 in s0.

Lever-free: rv's second range coalesced with a0 → no move. So we need a0 NOT to be in the same reg as rv. Why does a0 get s0? Because a0 (the pointer) is live across the call to func_8012B77C? a0's uses: *a0 = rv after the call → yes, live across the call → must be callee-saved s0. rv's second range is after the call → v0.

Coalescing: local-alloc's copy preference at `rv = (s32)a0` (a copy): it tries to make rv share a0's reg. But a0 is in s0 (global-alloc assigned) and rv's range is local. Hmm, in target (with the pin) it didn't coalesce because rv=$2. Lever-free it did.

To prevent the coalescing: make rv's second set not a copy. What if we write `rv = (s32)a0 + 0;`? folds to a copy. `rv = (s32)(a0[0])`? reads memory — no.

What if the second set is `rv = (s32)a0;` but we make rv live *across a call* after that (so it can't take s0's... no, coalescing is about matching regs).

What if a0 is used *after* the copy? E.g. `rv = (s32)a0; *a0 = rv;`? That changes the store order (target stores before). Hmm: target does `sw v0,0(s0)` (from rv=sp20) then `move v0,s0`. If we instead write `rv = (s32)a0;` then... no.

Idea: make the value copied be a *different variable* that's already in a callee-saved reg: e.g. `s32 keep = (s32)a0; ... rv = keep;` — adds a copy.

Idea: use a pointer type for rv: `u8 *rv;` then `rv = (u8*)a0;` — still a copy, same coalescing.

Idea: the copy is `rv = (s32)a0;` — what if we write `rv = (s32)a0;` where a0 is `s32 *` and rv is `s32`, and the compiler's copy coalescing happens in local-alloc's `block_alloc` with `qty_phys_copy_sugg`/`qty_phys_num_sugg`. The coalescing preference applies when the copy is a `(set (reg a) (reg b))` and b's qty... It sets a's preferred reg = b's reg. Then if a's block-local allocation prefers b's reg (s0), it takes it.

To break the preference, make the copy not a plain move: e.g. `rv = (s32)a0 + 1;` — changes value.

What if rv is a `u32` and we write `rv = (u32)a0;`? same.

Hmm, what if we make the second set `rv = (s32)a0;` happen in a *different block*? It's at the end, same block.

What if we reorder: `*a0 = rv; rv = (s32)a0;` is current. What if `rv = (s32)a0; *a0 = rv;`? Then rv's second set value is stored to *a0 — but that changes the stored value! Target stores sp20 to *a0. So no.

OK, so items 1, 4, 5 all hit "the pin is needed to force a copy". Hmm, but wait: for item 5, the target's move v0,s0 is the copy rv=a0. In lever-free, if rv's second set were assigned v0 and a0 s0, we'd get the move. The coalescing is local-alloc's copy preference. Can a real-C move break it? 

What if rv is assigned from a0 through an intermediate that's already in a *caller-saved* reg: e.g. `rv = (s32)a0;` where a0 is used... 

Hmm, actually, what about making rv a `s32` and the source expression `(s32)(a0)` vs `(s32)((void *)a0)`? Same.

What about making the copy happen before the call? `rv = (s32)a0;` before func_8012B77C? Then rv is live across the call → s0, and the move v0,s0 would be at the end... but target's move is after the call, and rv would then be in s0 (same as a0?) Hmm, if rv is live across the call and a0 too, they can share s0 (coalesced) → no move.

What if rv's second range must be in v0 because of the asm? The asm is `"r"(rv)` — any reg.

Honestly, these three (1, 5) are the classic "pin forces a copy" wall. The tag could be `lreg-copy-pref` (local-alloc copy preference ties the dying base reg). Existing tag: `lreg-copy-pref-dying-base local-alloc local-alloc copy preference ties a dying base reg to another pseudo (G24)`. That fits item 5: a0 dies at the copy, so rv is tied to a0's reg.

For item 1: found dies at the copy `rv = found` → rv tied to found's reg (s2). Same tag: `lreg-copy-pref-dying-base`. 

So items 1 and 5: WALL lreg-copy-pref-dying-base, best 1 each.
Item 4: WALL loop-giv-combine, best 8.
Item 2: WALL expand-void-return? Let me reconsider item 2 with the same lens: the keepalive-only gave 78/79 with flg in v0 and res in v1; target flg in v1, res in v0. That's local-alloc qty priority (flg shorter-lived wins v0). Real-C move: make res shorter-lived or flg longer-lived without extra insns. Hmm: res's life starts at `res = 0` and ends at the asm. flg's life starts at the load and ends at the test.

What if we set res *after* the flg test: 
```
flg = D_801F84AC;
if (flg != 0) {
    res = (s32 *)&D_801F832C;
} else {
    res = 0;
}
```
That's if/else — target's codegen would be different (branch to else). But maybe with the branch inversion it's the same? Target: beqz v1,L; move v0,zero; lui v0;addiu v0; L. Hmm, that IS if/else compiled with the else first? For `if (flg) res=&D; else res=0;` GCC would emit: beqz v1,Lelse; lui v0;addiu v0; b Lend; Lelse: move v0,zero. Not target.

What about `res = 0; if (flg) res = &D;` with flg loaded *after* res=0 (current). Target's order: load flg, test, res=0 in delay slot. So the source is res=0 then if(flg) — the res=0 is sunk into the delay slot by sched/dbr.

Priority: flg qty: refs 2, life (death-birth). res: refs 3 (0, &D, asm), life longer. flg wins.

To make res win, shorten res's life: assign res as late as possible. `if (flg != 0) res = &D; else res = 0;` makes res's birth at the branch but changes structure. Hmm.

What if we write `res = (s32 *)&D_801F832C; if (flg == 0) res = 0;`? Then target order would be: lui v0;addiu v0; lw v1; beqz v1,L; move v0,zero; L. That's different order (address computed first). Not target.

What if `res = flg ? (s32*)&D : 0;`? codegen: beqz v1,L; lui v0;addiu v0; b; L: move v0,zero. Different.

Hmm. What if we make flg longer-lived so res wins? E.g. declare flg and use it in the test only — can't extend without insns.

What if flg is *not* a separate variable: `if (D_801F84AC != 0)` — the load temp is created by the compiler; its life is from load to test (short). Same.

What if the load is hoisted earlier: `flg = D_801F84AC;` at the top of the function (before the calls)? Then flg is live across calls → callee-saved s-reg. Target has flg in v1, so no.

Hmm.

Alternatively, make res's life *start later* by assigning it inside the if only, with the 0 default via the other path... 

What about:
```
if (D_801F84AC == 0) {
    res = 0;
} else {
    res = (s32 *)&D_801F832C;
}
```
Compiled: beqz v1, Lthen; ... hmm.

Honestly, item 2's score 13 (keepalive-only) is close; maybe another real-C move flips it. Let me think about *how* local-alloc allocates v0: block-local quantities are allocated in priority order; the highest priority gets the first free reg. In the tail block, the free regs at that point: v0, v1, a0-a3, t regs... The first allocated gets v0 (lowest-numbered free reg). So the higher-priority qty gets v0.

flg: refs 2, floor_log2(2)=1, size 4 → 2*4? Wait size is in words? qty_size is the mode size. Both 4 bytes (word). pri = floor_log2(refs)*refs*size/(death-birth).

res: refs 3 → 1*3*4/life_res. flg: 1*2*4/life_flg.

If life_res = life_flg + delta, res wins when 3/life_res > 2/life_flg → life_res < 1.5*life_flg.

Currently res's life: res=0 (insn X) to asm (insn X+6?) ≈ 7 insns. flg: load (X-2) to beqz (X+2)? ≈ 4. 3/7=0.43 vs 2/4=0.5 → flg wins. Need res life < 6 or flg life > 4.5.

If we could move `res = 0` later... The asm is at the very end. res's life from res=0 to asm is fixed by the source order: res=0 then if then asm ≈ 6 insns (move, beqz, lui, addiu, [label], asm). Hmm.

What if the if-body sets res and the default 0 is set in a way that... e.g.:
```
res = 0;
if (flg) res = &D;
```
Already.

What if we remove the intermediate `flg` and load directly in the test — then the load temp's life is ~3 insns (lui, lw, beqz) → even shorter, so flg wins even more. a4 gave 13 too.

What if we make flg's life longer by loading it *before* the `res = 0`? a1 did that (flg = load; res = 0; if) → same 13. Hmm.

What if we add a *second use* of flg after the if that costs no insn? E.g. `res = flg ? ...` no.

OK, item 2 = WALL lreg-qty-priority (existing tag: "local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo (G22)"), best 13.

Hmm, wait. But actually let me reconsider: maybe the wall for item 2 is different. Let me look at the full diff again: besides the reg swap, there's the `li a0,11` scheduling difference (target hoists it into the first beqz delay slot). That's a consequence of the reg assignment? Possibly the sched1 order changes due to reg pressure. If res/flg swap, maybe the schedule fixes itself. The count difference (78 vs 79) is a real structural difference: target has 79, mine 78. Let me find where the extra insn is. From the earlier diff: "replace mine[44:45] target[44:46]" with target having `li a0,11` extra. So target has an extra `li a0,11`? That seems odd — maybe target's `li a0,11` appears twice (once in each path) while mine merges.

Hmm, target: 5b8 `li a0,11` (delay slot of first beqz), and later 5c8 `move a1,zero`... Let me recount target's insns around there:
```
5b4 beqz v0,5f4
5b8 li a0,11        <- delay
5bc addiu v0,s0,-310
5c0 sltiu v0,v0,70
5c4 beqz v0,5f8
5c8 move a1,zero    <- delay (Lshared path? no, this is the t2-false path -> goto Lshared which sets a0=11,a1=0,a2=0)
5cc lui a1,D_801F217C
...
```
and mine:
```
5b4 beqz v0,5ec
5b8 addiu v0,s0,-310
5bc sltiu v0,v0,70
5c0 beqz v0,5ec
5c4 li a0,11
5c8 lui a1,...
```
So in mine the `li a0,11` is at 5c4 (delay slot of the second beqz). Both have one `li a0,11`. The count difference must be elsewhere — maybe an extra nop or a duplicated `move a1,zero`. Target at 5c8 `move a1,zero` and later at 5e4 `move a1,zero`; mine at ... Let me not chase this.

The point: item 2's differences are scheduling + reg allocation, both downstream of the res/flg swap? Actually the li placement is dbr/sched1, independent.

Let me try a few more item 2 variants where res's life is shortened by moving the res=0 into the branch:

v5: 
```
flg = D_801F84AC;
if (flg != 0) {
    res = (s32 *)&D_801F832C;
} else {
    res = 0;
}
```
v6: use `if (!flg)`:
```
if (flg == 0) {
    res = 0;
} else {
    res = (s32 *)&D_801F832C;
}
```
v7: `res = 0; if (flg) res = ...` with flg as u32.

Let me try these.
