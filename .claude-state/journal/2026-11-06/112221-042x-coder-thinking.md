---
ts: 2026-11-06T18:22:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bY0YJHFETuhAynervojf
---
No prior notes. Let me try a couple of quick experiments in parallel (one batch of candidates, one sc.sh run):

w2: use `void *p = a0;` and use p in the three loads and the store? The store uses v1. Just the loads.
w3: make 72 live-out by using a0 after the load: e.g., move the store's base computation... Hmm.
w4: hoist the load out of the if (single load).
w5: swap `v0 = 1; v1 = load;` order? Already.
w6: `s32 v1 = ((Unkstruct*)a0)->unkCC;`? no.

Idea w3 concretely: the store `*(s32 *)(v1 + 0xB0) = v0;` → what if we write `*(s32 *)((char *)a0 + 0xB0) = v0` — no, wrong value.

What if the final store address is computed as `v1 + (s32)((char*)a0 - (char*)a0)`? launder — forbidden.

New idea: **change the C so that a0's copy 72 is live into block 5 (the store block)**. If block 5 used a0, 72 would be live-out of the arms → conflict with 76 → pref not merged. What free use could block 5 have? The store itself: `*(s32 *)(v1 + 0xB0) = v0;` — no a0.

Alternatively, restructure the branches so the store is inside the arm (target's block 5 is shared; if we duplicate the store in each arm, jump2 merges identical arms!). Interesting: if each arm ends with the store, then jump2/cross-jump may merge the identical arms into a shared block — exactly the target's structure! But in the target, the store is in a separate block (d38) reached by a jump from d24 with a delay slot. Actually the target's d24 `j d38` + delay `nop`; d30 falls through to d38. So the store block is shared. If the C duplicated the store in each arm, gcc's cross-jump could merge two identical arms (that's how d24 and d30 became identical: they were two source arms merged by jump2). Hmm, but the load is also in those arms.

Hmm OK, let me think about what actually differs between the pinned version and mine: ONLY the register of 76. In the pinned version, does 72 exist and have pref 4? Yes. The pin makes 76 a hard reg $3 from the start (global-alloc's reg_renumber[76] = 3 pre-set), so no pref applies.

So any real-C change must make global-alloc pick $3 for 76. The cleanest: make 72 allocated before 76 (order swap) OR remove the pref.

Since pref comes from expand_preferences (merge at insn 32 where 72 dies), one more idea: **make insn 32's load have a REG_DEAD of a different allocno with a pref for $3**. expand_preferences merges prefs from ALL dying allocnos at the insn that sets 76. If we add a dying pseudo at the load with pref $3... e.g., a temp that is $3? no.

**Another angle: make 76's preferred class not include $4.** No.

**Make $4 conflict with 76**: hard_reg_conflicts[76] gets $4 if hard reg 4 is live during 76's live range. Hard reg 4 (a0) is live only at insn 4 (the prologue copy). If the prologue copy didn't exist (param used directly), hard reg 4 would be live through the arms → conflict with 76 → $4 excluded → $3! 

How to avoid the param copy? The copy exists because PARM_DECL a0 is a pseudo. Hmm, but wait: in the pinned version, is there a copy at insn 4? Let me check the .lreg of the *pinned* version... I'd need a dump of the orig. But the orig scores 0 (byte-identical to target), and the target's asm has no `move` from a0 to another reg at the start (d04 is lui v0). So in the target, a0's value is used directly as the base (no prologue copy in the asm). But that's after the register allocator assigned 72→$4, making the copy `(set 72 (reg 4 a0))` into `move $4,$4` which is then deleted (or coalesced). So the copy is coalesced away in the target too.

In our build, 72→$4 as well, and the copy is coalesced. Fine.

So the copy is not visible in the final asm; it just creates the pref.

Hmm! What if the copy 72→$4 is deleted *before* global-alloc by cse (copy propagation)? Then there'd be no allocno 72 and no pref. cse could delete `(set 72 (reg 4 a0))` by substituting $4 for 72... but cse doesn't substitute hard regs for pseudos (it only propagates constants/regs). Actually cse can: `(set (reg 72) (reg 4))` → makes them equivalent and replaces uses of 72 with $4? cse avoids substituting hard regs? It does record equivalences; using $4 in place of 72 would be fine if 72 dies... but 72 is live across the whole function, so no.

OK. Let me now consider the *local-alloc* angle: maybe if 76 were block-local, local-alloc's suggestion mechanism would give it $4 anyway (as analyzed). Hmm, in block-local case the load base 72 is a global ($4), so the suggestion would be $4 again. Bad.

Hmm, what if the base of the load is a *local* pseudo? E.g., in each arm, load from a local copy of a0? That adds a move.

Let me try yet another angle: **make the loaded pointer 76 not the one used in the store; instead store via a copy**. e.g.:
```
v1 = a0->unkCC;
...
*(s32*)(v1 + 0xB0) = v0;
```
what if instead:
```
s32 w = v1;
*(s32*)(w + 0xB0) = v0;
```
Adds a move at the join (target has none) — but maybe combine coalesces. Then 76's live range shortens (dies at the copy), and w (the new pseudo) is block-local to block 5 → local-alloc. 76's refs increase (5), live shorter... The copy might be deleted by coalescing; but the live range change could reorder priorities. Worth a try? It adds a `move` in the final asm likely (target has `sw v0,176(v1)` directly).

OK, time check: I've spent ~20 min on analysis. The budget is 20-30 min per item with ≥30 scored tries for a WALL. Let me generate a batch of ~10 candidates quickly and score them all. Then continue with more ideas. Let me write them as w2..w11.

Candidates for item 3:
w2: `void *p = a0;` use p in loads (expect same as w1, but tests coalescing).
w3: reorder branches in source: put the `v0 < a2` arm first (swap if/else structure).
w4: hoist `v1 = a0->unkCC;` once before the ifs, store at the end. (structure differs)
w5: `s32 v1; v1 = ((Unkstruct*)a0)->unkCC;` in each arm but with the store inside each arm (duplicate store).
w6: use a struct pointer variable `Unkstruct_80184B70 *p = a0;` and `v1 = p->unkCC;`.
w7: use `u32 v1` and `u32 v0`.
w8: `s32 t = ((Unkstruct*)a0)->unkCC; v1 = t;` in each arm (extra copy coalesced?).
w9: make the store `*(s32 *)(v1 + 0xB0) = v0;` → `((Unkstruct*)v1)->unkB0 = v0;`
w10: reverse the order of the two if arms.
w11: compute v1 in the common else only... 

Actually, wait. Let me reconsider the source order. The target's block order: A: v0=1; lw v1; j. B: lw v1; v0=2. Then C: lw v1; v0=2. Blocks B and C are identical and merged by jump2. The source order in orig.c: if (!(v0<a1)) { if (v0<a2) {v0=1; v1=load;} else {v1=load; v0=2;} } else {v1=load; v0=2;}

The target block A (v0=1; lw v1; j) is the `if (v0<a2)` arm. Blocks B and C (lw v1; v0=2) are the other two.

If I reorder statements within an arm, e.g., `v1 = load; v0 = 1;` instead of `v0 = 1; v1 = load;` → block A would be `lw v1; li v0,1; j` — target has li v0,1 first then lw. So no.

Hmm.

What about making 76's live length 8→longer by moving the store into an arm? no.

**Big idea**: what if we make the store block *use v1 from only one arm* — i.e., make the value loaded in each arm be stored into a variable that is *block-local* per arm, and then... no, the join needs one value.

**Idea: swap which value is 76**: use the loaded pointer as the *last* arm's value only... no.

Let me look at the priority numbers again: 75 pri 11666 (v0), 76 pri 10000 (v1), 72 pri 8000 (a0 copy), 74 pri 5000 (a2). Order 75,76,72,74.

If 76's pri were < 8000, order 75,72,76,74 → 72 takes $4 first → 76 takes $3. 

76: refs 4, live 8. 72: refs 4, live 10. pri = floor_log2(refs)*refs/live *10000 * size. 76: 2*4/8=1 → 10000. 72: 2*4/10=0.8 → 8000. To make 76 < 8000, need refs/live ratio < 0.8 → live > 10 (with refs 4). 76's live length is 8 (in "insns"). If 76's live range extended to 11+ insns, pri drops below 8000. 

How to extend 76's live length without changing the final code? The live length is computed from the RTL: 76 is born at the first load (insn 32) and dies at the store (insn 61). The span is ~8 insns (in "insn numbers"? 32→61 but live length counts real insns in between?). In the table: r76 live 8, refs 4. Hmm.

If we add code between the load and the store... no.

Alternatively, reduce 76's refs: refs 4 (3 defs + 1 use). If one def were removed (e.g., only 2 loads), refs 3 → pri = floor_log2(3)*3/8 = 1*3/8 = 0.375 → 3750 < 8000! Then order: 75(11666), 72(8000), 74(5000), 76(3750). 72 would be allocated second → $4. Then 76 gets $3 (since $4 used and pref 4 excluded by regs_used_so_far). And 74 → $6? Then 76 → $3? Wait order: 75→$2; 72→$4 (pref); 74→$6 (pref a2=$6); 76→$3. That matches the target EXACTLY (v0=$2, a0copy=$4, a2=$6, v1=$3).

But how do we get only 2 loads? The target has 2 loads after jump2 merges two identical arms. The RTL before jump2 has 3. Hmm, but jump2 runs AFTER global-alloc, so global-alloc sees 3 loads. So refs must be 4 in the target's compilation too. Unless the target's source had a different structure where two arms shared the load before global-alloc!

Wait: target's asm has the load in the merged block d30 (shared by two paths) and in d24. The merge at d30 could come from cross-jump (jump2, post-reload) OR from the source having a shared else block:
```
if (!(v0<a1)) {
   if (v0<a2) { v0=1; v1=load; }
   else { v1=load; v0=2; }   // arm X
} else {
   v1=load; v0=2;            // arm Y (identical to X)
}
```
Cross-jump merges X and Y at jump2 (post-reload), so pre-global there are 3 loads. But if the source were written with a shared block:
```
if (v0 < a1) { v1 = load; v0 = 2; }
else if (v0 < a2) { v0 = 1; v1 = load; }
else { v1 = load; v0 = 2; }
```
same thing.

Could the source be written so the two identical arms are merged at the C level? E.g.:
```
if (!(v0 < a1) && (v0 < a2)) { v0 = 1; v1 = load; }
else { v1 = load; v0 = 2; }
```
Then there are only 2 loads! The condition `!(v0<a1) && (v0<a2)` compiles to: slt a1,v0,a1; bnez a1, else; slt v0,v0,a2; beqz v0, else; then arm. That's EXACTLY the target's compare sequence (d10 slt a1; d14 bnez; d18 slt v0; d1c beqz)! And with only 2 loads in the RTL: one in the `&&` arm and one in the else. Then refs(76) = 3 (2 defs + 1 use) → pri lower → order swaps → $3!

That's a very promising real-C move: fold the nested ifs into a `&&` (the catalog mentions "`&&`/`||` folds"). The branch structure: `if (!(v0<a1) && (v0<a2))` — note the target's first test is `bnez a1` where a1 = (v0<a1): branch to else when (v0<a1) is true, i.e., `if (!(v0<a1))` falls through. Then `slt v0,v0,a2; beqz v0, else` → falls through when (v0<a2) true. So the then-arm is `!(v0<a1) && (v0<a2)`. 

So write:
```
v0 = D_80078EB1;
if (!(v0 < a1) && (v0 < a2)) {
    v0 = 1;
    v1 = ((Unkstruct_80184B70 *)a0)->unkCC;
} else {
    v1 = ((Unkstruct_80184B70 *)a0)->unkCC;
    v0 = 2;
}
*(s32 *)(v1 + 0xB0) = v0;
```
This gives 2 loads (refs 3) and the same compare code. This might crack it! Note: `&&` in C evaluates left-to-right with short-circuit → exactly the two tests.

Let me test this as w2. Great idea.

Similarly for the other items, this kind of restructuring may help.

Let me write w2 and score it.
