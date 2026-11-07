---
ts: 2026-11-06T18:25:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BvuvdctxTh8VNdOsNytV
---
w3 (temp split) still score 3 — the copy was likely coalesced or the pref still merged. Let me check w3's greg to see whether t survived. Actually, the score is 3 with the same 15 insns, so t was eliminated (combine/cse) and 76 got $4 again.

Let me think differently.

The pref is merged at the load because 72 dies there. What if 72's death is NOT at the load? Make 72 live past the load in the arm block. The arm block contains only `li v0,1; lw v1; j`. If the source put a *real use* of a0 after the load in that block, the target's asm would change... unless the use folds.

Hmm, what if we reorder the arms so the load and a use of a0 land in the same block? E.g.:

```
if (!(v0 < a1)) {
    if (v0 < a2) {
        v1 = load;       // load first
        v0 = 1;
    } else {
        v1 = load;
        v0 = 2;
    }
} else {
    v1 = load;
    v0 = 2;
}
```
Still a0's last use is the load.

What if a0 is used in the condition? E.g., the store... no.

New angle: the target's registers: $3 for v1. What if we can make the allocno order put 72 before 76? 72's pri 3333 (refs 3, live 9), 76's 6000 (refs 3, live 5). To raise 72's pri above 6000: refs up or live down. 72's live length 9 spans from insn 4 to the last load. If 72's live range were shorter (e.g., the loads closer together), pri rises: e.g., live 6 → pri = 3/6*... floor_log2(3)=1, 1*3/6=0.5 → 5000. Still < 6000. live 4 → 7500 > 6000! Then order: 75(12000), 72(7500), 76(6000), 74(5000). 72 → $4 (pref), then 76: $4 used (regs_used_so_far) → pass 0 gives $3; pref $4 is in used → pruned → $3. MATCH!

But shortening 72's live range means fewer insns between the prologue and the loads — not controllable without changing the code (the loads are in the arms).

Alternatively raise 72's refs: refs 3 = the 2 loads + the prologue copy. Hmm, if a0 were used 3 times in the loads (3 arms as in orig) refs 4, live 10 → pri 8000 (from the earlier dump). And 76 refs 4 live 8 → 10000. Order 75,76,72,74. So no.

Hmm, in the orig structure (3 loads): 76 refs 4, live 8 → pri 10000; 72 refs 4, live 10 → 8000. If 76's live length increased to 11: pri = 2*4/11 = 0.72 → 7272 < 8000 → order 75,72,76,74 → 72 → $4, 76 → $3. How to increase 76's live length from 8 to 11 without changing the code? Live length counts insns from first def to last use. 76's defs are at insns 32,40,53 and the use at 61. Live length = total insns in [32,61]? The table says 8. Hmm, insn numbers 32→61 but live length counts "insns" not numbers (real insns between, excluding notes/labels/barriers): let me count: 32,34(jump),40,43,47(jump),53,56,61 → 8. To get 11 we'd need more insns between the load and the store.

Alternatively, decrease 76's refs to 2? Only if there were one load.

Hmm, what about making the *first* load earlier so 76's live range starts earlier (longer)? E.g., hoist one of the loads to before the branches (w5 = single load before → 12-13 insns, wrong).

OK here's another thought: what if 76's live length is computed to be longer because the store is *later*? The store is at the end. No.

What about refs: if the source has 3 loads (orig structure), refs=4. If 2 loads, refs=3 (w2). In w2 the order was 75,76,74,72 with 76 pri 6000 > 72 3333. Hmm, 74 (5000) is between. So in w2, 76 still allocates before 72.

If we could make 76's pri < 3333 (72's), then order 75,74,72,76 → 72→$4, 74→$6, 76→$3. w2's 76: refs 3 live 5 → 6000. Live 6 → 5000; live 8 → 3750; live 9 → 3333 tie (lower allocno wins → 76 vs 72: 76 > 72, so 72 wins the tie? "TIE (lower allocno wins)" means the lower allocno number is allocated first — 72 < 76, so 72 first!). So with live ≥ 9, 72 goes first → 76 gets $3.

w2's 76 live 5. How to lengthen 76's live range to 9+? Between the load and the store, w2 has: load, jump, li v0,2, store? Let me see w2's .lreg. Actually w2: 2 loads. 76's defs at the load in arm A and arm B; use at the store. Live length 5.

Hmm, to lengthen: add insns between the load and the store — not possible without changing the target's asm.

OK, so the global-priority route seems hard.

Let me reconsider: maybe the target's register assignment isn't global-alloc's pref at all — maybe the target's source had a slightly different structure where 76 gets $3 naturally. Since this function's current src uses the pin to get $3, maybe the *original* (target) code had a structure that naturally produced $3.

What structure? Let me think about what C would produce `lw v1,204(a0)` twice with v1=$3 and v0=$2. 

What if the pointer variable v1 is NOT the same variable in both places? E.g., in the target, the two loads might be two *different* pseudos, both allocated $3 (they don't conflict). In the orig structure with 3 loads, 76 is ONE pseudo (one C variable). What if the C used two separate variables (one per arm)? Then each arm's load result is a separate pseudo, and the store uses... both? The store needs one value; the C would need a merge.

Unless the store is duplicated too: each arm loads into its own variable and stores. Then each arm's code is `lw t; li v0; sw v0,176(t)` — but target has `j` + shared store. Hmm, jump2 merges identical tails: the two `lw v1; li v0,2; sw v0,176(v1)` arms would be identical if they use the same register... but different pseudos might get different regs. Risky.

Alternatively, the target's two loads could be the same pseudo 76 allocated $3. Our job: get 76 to $3.

Let me look at the actual global-alloc code for the "pref" pruning once more: prune_preferences removes prefs that conflict with `temp = hard_reg_conflicts[allocno] | fixed_reg_set | complement(class)`. $4 isn't conflicted.

What if we could make $4 appear in 76's hard_reg_conflicts? That happens if hard reg 4 is live during 76's range — i.e., if the *parameter hard reg* a0 is live. The parameter hard reg dies at the prologue copy (insn 4). Hmm, but what if the parameter is NOT copied (used directly)? Then hard reg 4 would be live until the last use (the load) and conflict with 76. Is there a way to make GCC use the hard reg directly? In 2.7.2, `assign_parms` copies a parameter into a pseudo only if `reg_parm_stack_space`... Let me check function.c assign_parms for the copy logic.

Actually, maybe the copy exists because the parameter is *not* the last... Let me look at the .rtl: insn 4 `(set (reg/v:SI 72) (reg:SI 4 a0))` with REG_DEAD 4. This is the standard "parameter copy" — in GCC 2.7.2, function.c's assign_parms does:

```
      /* If the parameter is not in a register, or if it is in a register
         but we don't want to use that register, copy it to a pseudo.  */
```
Hmm. Let me grep function.c around assign_parms for "copy".

Actually — in many PSX decomp functions, the arg is used via `a0` directly and no copy appears. When does the copy appear? Looking at the RTL: the param pseudo 72 is used as the base. The copy exists because the param is referenced 3 times and the register allocator wants it in a pseudo. This is the standard behavior for any parameter used more than once? Actually GCC 2.7.2's assign_parms always creates a pseudo for each parameter unless the parameter is unused. The move from the hard reg to the pseudo is then coalesced by global-alloc (the copy pref) or local-alloc. Yes: every parameter has a pseudo; the prologue copy is coalesced away. So the copy is always there.

Hmm, so how did other functions with a parameter base get a pseudo in $3? By the priority order: e.g., if the param copy allocno is allocated BEFORE the load-result allocno, it takes $4 (its pref) and the load result takes $3.

In our case the load result (76) has higher priority than the param copy (72). To flip: raise 72's priority or lower 76's.

72's pri = floor_log2(refs)*refs/live. In orig: refs 4 (3 loads + prologue), live 10 → 8000. 76: refs 4 (3 defs + 1 use), live 8 → 10000.

If 72's refs increased to 5 (e.g., 4 uses of a0): floor_log2(5)=2, 2*5/10=1 → 10000 = tie with 76; tie → lower allocno (72) wins → 72 first! Then 76 gets $3. 

So: add ONE more use of a0 without adding an instruction? Hmm, refs counts REG references in the RTL. If a0 were used in the store block... e.g., if the store's base expression used a0 in a way that folds. Hmm.

OR: 72's live length decreases → pri rises. If 72's live length were 8 instead of 10 → pri = 2*4/8 = 10000 = tie → 72 wins (lower allocno). How to shorten 72's live range? Live length is from the prologue copy (insn 4) to the last load. If the last load happened earlier... the arms are spread out. Hmm.

OR: 76's refs 4 → 3 by having 2 loads (w2): pri 6000 vs 72's 3333 (72's refs 3, live 9). Hmm, in w2, 72's pri also dropped because refs 3.

So we need to decouple: reduce 76's refs (fewer loads) WITHOUT reducing 72's refs. That means: 2 loads but 3+ uses of a0. Add a use of a0 elsewhere. E.g., use a0 in the store block? 

Hmm, what about the `D_80078EB1` load: `v0 = D_80078EB1` — no.

What if we use a0 in the first comparison? Like `if (v0 < a1)` where a1... no.

What if we add a dead use that flow keeps? Dead code is removed.

OK, radical idea: what if the C computes the load address from a0 in one place and passes the pointer... 

Actually, let me revisit: **maybe use the `&&` fold (2 loads) and ALSO keep a third use of a0 by loading unkCC into a temp in the condition?** No.

Alternatively: make the store use `((Unkstruct_80184B70 *)a0)->unkCC` again? That's a second load.

Hmm, let me look at the problem from the "what does the target's source look like" angle. Perhaps the original source was:

```
void func_80184B70(void *a0, s32 a1, s32 a2) {
    s32 v0;
    s32 v1;
    v0 = D_80078EB1;
    if (!(v0 < a1) && (v0 < a2)) {
        v1 = ((Unk*)a0)->unkCC;
        v0 = 1;
    } else {
        v1 = ((Unk*)a0)->unkCC;
        v0 = 2;
    }
    *(s32*)(v1+0xB0) = v0;
}
```
That's w8/w2 with 2 loads — score 3.

Maybe the original had `s32 v1; ... v1 = ...;` but the pin in the current src is a *deliberate* workaround because the natural allocation gives $4.

So the shard expects us to find a real-C move that flips it. Since the pin exists, maybe the intended crack is a different one. Let me think about the local-alloc "copy preference" instead: maybe the intended solution makes 76 block-local (not global), so local-alloc allocates it. If the store were in the same block as the load... e.g., the else arms each store directly:

```
if (v0 < a1) { v0 = 2; ... }
```

Hmm, what if the C is:
```
v0 = D_80078EB1;
if (!(v0 < a1)) {
    if (v0 < a2) { v0 = 1; v1 = load; }
    else { v1 = load; v0 = 2; }
} else { v1 = load; v0 = 2; }
*(s32*)(v1+0xB0) = v0;
```
The store block is shared. For 76 to be block-local, the store would have to be inside each arm.

What if we write the store inside each arm and let jump2 merge? The target's shared store block is the result. Let me test:

```
if (!(v0<a1)) {
   if (v0<a2) { v0=1; v1=load; *(s32*)(v1+0xB0)=v0; }
   else { v1=load; v0=2; *(s32*)(v1+0xB0)=v0; }
} else { v1=load; v0=2; *(s32*)(v1+0xB0)=v0; }
```
Each arm is block-local; local-alloc would allocate each load result... the three arms' variables are the same C variable v1 but in different blocks → 76 would be... hmm, if v1 is only live within a block, it's local. But it's one pseudo used in 3 blocks — local-alloc assigns per-block if the pseudo is not live across blocks. Since v1 dies at the store in the same block, it's block-local! Then local-alloc assigns each use.

But the target's asm has a shared store block, which suggests the source had the store once. Hmm, but maybe jump2 merged the identical tails, producing the shared store block. If the three arms become identical after the compare... The arms have different v0 values (1 vs 2), so the tails aren't identical (li v0,1; lw; sw vs lw; li v0,2; sw). Cross-jump could still merge? It merges identical instruction sequences (after the branch); the sequences differ (li v0,1 vs li v0,2). So no.

Hmm. So the target's source likely had the shared store.

OK, let me look at this from the *actual target's* perspective: the target asm shows `j d38` with delay `nop` — a jump to the store block with a NOP delay. And d30 falls through into d38. If the store were shared in the source, the natural code would be: arm A: li v0,1; lw v1; j join; arm B: lw v1; li v0,2; fallthrough join: sw. Yes, matches.

So the source is as we have. The pin is the only way? But the shard's premise is that a real-C move can crack it. Let me look at what a "real C move" could be that changes the register allocation: statement order, decl order, temps, widths, loop shape, init at decl, &&/|| folds, pointer reuse.

**Init at decl**: `s32 v1 = 0;`? adds insns.

**Decl order**: irrelevant in GCC 2.7.2 (pseudo numbering follows first use/def order, not decls).

**Pointer reuse**: Hmm! What if v1 is reused as something else? Like the store's address? 

**Widths**: s16/u8 — the value is a pointer.

What about making v0 s16? The compare results are s32.

Hmm, let me try the "3 loads but different variable for the load in the third arm" idea... 

Actually — wait. What about **using a pointer variable p = a0->unkCC's base**, i.e., `Unkstruct *p = (Unkstruct *)a0;` used in all arms, and then `v1 = p->unkCC`. That's w7 → score 3.

What if p is declared as `void *p = a0;`? Same.

Let me think about the *other* preference source: maybe if 72's pref were pruned for 76 because $4 is in `regs_someone_prefers[76]`. That requires a CONFLICTING lower-priority allocno preferring $4. 72 is lower priority (3333 < 6000 in w2) and prefers $4, but doesn't conflict. If 72 conflicted with 76, then regs_someone_prefers[76] would include $4 AND expand_preferences wouldn't merge. So again: conflict is the key.

How to make 72 conflict with 76 in w2's structure? 72 is live in both arm blocks; 76 is born at the load in each arm and live to the store. In arm A: 72 used at the load; 76 born at the load; 72 dies at the load (last use in that block, since block 5 doesn't use it). If 72 were live at the end of the arm block, it would conflict.

So: make block 5 (the store block) use a0 (72). How? The store: `*(s32 *)(v1 + 0xB0) = v0;`. 

What if we write the store using a0 as the base and v1 as an offset... launder, forbidden.

What if the C has `v0 = ...` where the stored value depends on a0? The target stores v0 (1 or 2).

Hmm, what if the arms don't jump to a shared store but the store is duplicated *in the else arms only*? Then... no.

What if we add a use of a0 in the *last* arm after the load, where the load is not the last use? E.g., the else arm:
```
else {
    v1 = ((Unk*)a0)->unkCC;
    v0 = 2;
}
```
The load is the last use. If we wrote `v0 = 2; v1 = ((Unk*)a0)->unkCC;` — same.

Hmm what if the else arm's store uses a0? No.

OK, let me step back and check how much time I've spent: started 11:11, now maybe 11:40. Item 3 alone is over budget already. The brief says 20-30 min wall per item, and a WALL needs ≥20 min and ≥30 scored tries. I've done 8 tries on item 3. Let me time-box: continue item 3 with a few more tries until ~30 tries total, then decide WALL vs continue.

Actually, wait. Let me reconsider the problem: maybe I can make the load result 76 be allocated by *local-alloc* (block-local) by making the store's value not cross blocks. What if the store's value is v0 only and the pointer is... no.

Hmm, here's an idea: **swap the roles of v0 and v1 in the store**: `*(s32 *)(v1 + 0xB0) = v0;` — what if the pointer value is loaded into v0 and the flag into v1? No.

Another idea: **make the pointer value live across a call** — no calls.

Let me look at the .lreg table for the *pinned* orig to see what global-alloc does there (the pin's effect). Not needed.

Let me try the "conflict" route concretely with a use of a0 in the store block that costs no insn. What if the store is written as:

```
*(s32 *)(v1 + 0xB0) = v0;
```
and we make v1's computation use a0... 

What about storing `v0` into `((Unkstruct*)v1)->unkB0` where the struct's unkB0 offset is 0xB0 — same.

Hmm, what if the store block recomputes the pointer: `((Unkstruct *)((char *)a0 + 0xCC))`? No.

Let me try a different tack: what if v1 is *not* loaded in each arm but computed as `(s32)a0 + 0xCC` and then dereferenced in the store block? No, the target loads in the arms.

OK, time to consider the possibility that item 3 is a WALL. But before that, let me try a few more promising things:

1. w9: store duplicated in the arms (tests the block-local route).
2. w10: `v0` declared after v1 (decl order).
3. w11: use `u32` types.
4. w12: the `&&` fold with the load first in each arm (w8-like).
5. w13: `if (v0 < a1) {...} else if (v0 < a2) {...}` with explicit structure (w4 did that).
6. w14: make the else arm `v1 = load; v0 = 2;` and the first arm `v0 = 1; v1 = load;` — that's orig.

Also: what about making the *first* comparison use a temp (slt dest) that changes priorities? The temps r78/r79 are block-local.

7. w15: `s32 v1; ... v1 = ((Unkstruct_80184B70 *)a0)->unkCC;` but with `v0 = D_80078EB1 & 0xFF;`? changes insns.

Hmm, let me think about the refs count of 72 again. In w2 (2 loads): 72 refs 3, live 9 → pri 3333. 76 refs 3, live 5 → 6000. If I could make 76's live length 9 → pri 3333 tie → 72 wins (lower number). How to make 76's live length 9 in w2? The RTL span from the first load to the store. w2's structure: arms are close together; the span is 5 insns. If the loads were farther from the store (more insns in between), live length grows. Adding insns = wrong.

BUT: what if the *first* def of 76 is earlier (hoisted into the compare region) while the store stays at the end? That's w5 (single load hoisted) — 13 insns.

What about hoisting the load into the first comparison block? E.g., 
```
v0 = D_80078EB1;
v1 = ((Unk*)a0)->unkCC;   // one load early
if (...) { ... } else { ... }
store
```
That's w5/w6 — 12-13 insns (missing one load).

Hmm, target has 2 loads. To have 2 loads with one early: e.g., load in the `&&` arm AND one before? No.

Let me look at the actual target's source possibilities once more. The target has exactly: slt a1; bnez; slt v0; beqz; li v0,1; lw v1; j; nop; lw v1; li v0,2; jr; sw.

Note: after `beqz v0` the delay slot is `li v0,1`, then `lw v1`, then `j d38` with delay `nop`. The `j` delay slot being a nop suggests the jump target's first insn is the store and the delay slot couldn't be filled. Fine.

OK — maybe the intended lever is elsewhere: what if v1 is loaded via a *u32 pointer* with a cast that changes the load's mode to HImode? no.

Let me try a completely different idea: make the two loads use *different source variables* so that only ONE of them is the global 76 and the other is block-local, changing refs/priority. E.g.:

```
if (!(v0<a1)) {
   if (v0<a2) { v0=1; v1 = load; }
   else { v1 = load; v0=2; }
} else { v1 = load; v0=2; }
```
v1 is one pseudo.

What if the third arm uses a temp then assigns v1? `t = load; v1 = t;` — combine merges (w3, score 3).

What if the third arm uses `v1 = (s32)load`? same.

Hmm, let me check w3's dump to see if 76's refs changed. Actually, let me test whether the tie-break/order can be shifted by making the param copy 72 higher priority through *refs*: add a fourth use of a0 that doesn't add an instruction. What use? 

The store `*(s32 *)(v1 + 0xB0) = v0;` — could be written as `*(s32 *)(v1 + 0xB0) = v0` — no a0.

What if we write `*(s32 *)((char *)v1 + 0xB0) = v0;` — no.

What if the *load* address is written as `(char *)a0 + 0xCC` and the store as... no.

What if we use a0 twice in the same load expression: `((Unkstruct *)((s32)a0))->unkCC` — does the RTL reference 72 twice? The cast is a no-op, so one reference.

What about `((Unkstruct *)((char *)a0 + 0))->unkCC`? The +0 folds; one ref.

Hmm.

**New idea**: change the *first* parameter's use in the comparison. `v0 < a1` uses a1. What if the comparison used a0 in a way that's free? No.

**Another angle**: the target's v0 (r75) has pri 12000 in w2 and conflicts with a1,a2,sp. 76 conflicts only sp. If 76 conflicted with more, no.

Let me try making the store's pointer value be `v0` and the flag `v1`... no.

OK, let me try the "duplicate store" and a few others, then move to other items if no luck.

Actually WAIT. A thought: what if the source *doesn't* use a pointer variable for the store but writes through the loaded value directly in each arm? Then the store block... hmm.

Alternatively: what if the loaded pointer is stored to a *global*? no.

Let me look at the moves.md W48 line: "cse-copy-canonical | cse | cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg (W48)". Maybe this shard's items are known to be WALLs? The shard is "singleton crack shard" — each item has one lever kind left. The goal is to try to crack them.

Given the time budget, let me do a broader sweep of statement orders (the moves.md mentions "found by statement-order permutation sweep (30/120 hit)"). I can script a permutation sweep over the arms' statement order and the store's placement. But each score is a compile (~seconds?). Let me time one: dt.sh takes maybe 2-5s. A sweep of 20-30 candidates is feasible via sc.sh (sequential). That's a good use of time: the brief says ≥30 scored tries for a WALL.

Let me create a generator script (under my item dir) that writes candidates: for each of a few structural templates, permute the arm statement orders and the store position, and the branch condition forms. Then sc.sh them all.

Templates:
A. 3 arms, orders of (v0=const) and (v1=load) within each arm: 2^3 combos (but the first arm must have v0=1; others v0=2).
B. 2 arms via && fold: orders within arms.
C. Nested ifs with else-if.

Let me write a Python script to generate w_*.c files. Since this is scratch, under my item dir. Then run sc.sh on all and look for score 0.

Actually, note the target requires: arm1 (v0<a2 true): li v0,1 THEN lw v1. Arms 2,3: lw v1 THEN li v0,2. Since sched1 may reorder, both orders could produce the target. Let me sweep.

Also sweep the *condition* forms: `if (!(v0 < a1))`, `if (v0 >= a1)`, `if (v0 < a1) ... else`, and `&&`.

Let me write the generator.
