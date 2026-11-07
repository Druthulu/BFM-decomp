---
ts: 2026-11-06T05:28:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bOX5kx4O5f3raXh7Xc6k
---
Priority = floor_log2(n_refs) * n_refs * size / (death - birth).

For n1: reg 73 (iVar1): n_refs=8, floor_log2(8)=3, size=4, live=18 → 3*8*4/18 = 5.33 → 53333.
reg 74 (iVar2?): 6 refs, floor_log2(6)=2, size=4, live=6 → 2*6*4/6 = 8 → 80000.
reg 75 (tmp): 20 refs, floor_log2(20)=4, size=4, live=16 → 4*20*4/16 = 20 → 200000.

So order: 75 (tmp) → v0; 74 (iVar2) → v1; 73 (iVar1) → a0. But n1's asm shows iVar1 in v1! Contradiction.

Hmm, so maybe in n1, reg 74 isn't iVar2. Let me identify: reg 72 = a0 (arg, 12 refs/46 insns). Reg 73: 8 refs/18 insns, dies in 4 places. Reg 74: 6 refs/6 insns, dies in 2. Reg 75: 20 refs/16 insns, dies in 4.

Hmm, in the source: iVar1 is used at: unk20 load, CAST_SIGN load, store in then arm, store in else arm, reload, then block 2... many. iVar2: test, copy, and the test in each arm... tmp: many.

Wait, reg 73 (8 refs) could be iVar1; reg 74 (6 refs) iVar2; reg 75 (20) tmp.

If priority 75 > 74 > 73, then allocation: tmp→$2, iVar2→$3, iVar1→$4. But n1's asm has iVar1 in $3. So maybe in n1, iVar2 and tmp were merged into reg 75, and reg 74 is something else (like the sign-extend temp).

Actually if cse merged iVar2 into tmp, then reg 74 might be a leftover.

The lreg dump is the *input* to local-alloc (after global-alloc?). Hmm, n1.i.lreg is the lreg pass dump which shows qtys.

OK let me take the empirical route: I need iVar1's priority > iVar2's priority, so iVar1 gets $3 and iVar2 gets $4.

Formula: pri = log2(nrefs)*nrefs*size/live.
iVar1: 8 refs, live 18 → 3*8*4/18 = 5.33
iVar2: 6 refs, live 6 → 2*6*4/6 = 8
So iVar2 wins. But in n1, iVar1 got $3... so maybe iVar2's qty is merged with tmp's (pri 20) and there's no separate iVar2 qty. Right! In n1 they're merged, so no conflict: tmp(merged) gets $2, iVar1 gets $3.

In a1, the copy keeps them separate: tmp (pri 20) → $2, iVar2 (pri ~8) → $3, iVar1 (5.33) → $4. That's what we see (iVar2 v1, iVar1 a0).

Target wants: tmp $2, iVar1 $3, iVar2 $4. So we need iVar1's priority > iVar2's.

iVar1: 8 refs, live 18 → 5.33. To beat iVar2 (8), we need either more refs or shorter live. With 9 refs: floor_log2(9)=3, 3*9*4/18=6. With 10: 3*10*4/18=6.67. With 16 refs: 4*16*4/18=14.2. Hmm, need > 8: 3*x*4/18 > 8 → x > 12. So 13+ refs, or shorten live range.

Alternatively reduce iVar2's priority: iVar2 has 6 refs over 6 insns. If its live range were longer (death-birth bigger), priority drops. E.g., 6 refs over 12 → 4. 

Interesting! The live length of iVar2: in a1, iVar2 is used for the copy and the branch tests. Hmm.

How to increase iVar1's refs without adding instructions? Adding a "dead use" that folds... e.g., using iVar1 in an expression that gcc can eliminate. Like `if (iVar2 != 0)` — no.

Hmm, this is the "greg-pri-refs" class of wall. But maybe there's a real C move: declare iVar2 as a *different width* so its live range/refs change. Or make tmp's copy from iVar2 not extend iVar2's live range.

Wait — actually, maybe we don't need the copy `tmp = iVar2` at all. What if instead the target's `move v0,a0` is `tmp = iVar2` where tmp and iVar2 are separate because... hmm.

Let me reconsider the target asm once more:
```
2a4c lh a0,16(v1)     iVar2
2a54 beqz a0, 2aa4
2a58 move v0,a0       tmp = iVar2
2a5c bgez a0, 2a80
2a60 nop
2a64 addiu v0,v0,128  tmp += 0x80
```
So in the then-arm, the store value is v0 (tmp). iVar2 (a0) is used for the tests.

Now, what if the source's `tmp` is not a copy of iVar2 but the result of a *sign extension* that happens to be free? Like `tmp = (s32)(s16)iVar2`? That's a1 (18).

Alternatively, what if iVar2 itself is the one in a0 because it's used in the branch tests, and tmp is a *separate value* computed from the loaded s16 in a different way... 

Hmm, let me try to nudge priorities. Options:
1. Add a reference to iVar1 that folds: e.g., `iVar1 = iVar1;`? deleted.
2. Change iVar2's live range: declare it later (at first use)? `iVar2` is assigned then tested.
3. Make iVar2 HImode (s16) — b1 didn't keep the copy.

Hmm wait, maybe there's another way to keep the copy that doesn't add a qty: make `tmp` and `iVar2` the same pseudo but with an extra def... 

What about this: `tmp = iVar2;` and then re-set iVar2 from tmp somewhere? No.

Let me look at what the launder actually did in the original: `tmp = iVar2; __asm__("=r"(tmp):"0"(tmp));`. The asm is a set of tmp. So tmp has 2 defs and iVar2 is copied. With the asm, tmp's priority/liveness changed too. And the pin fixed iVar1 to $3 regardless of priority.

So the original needed the pin because the launder changed priorities. Our job: find a lever-free body where priorities land right.

Idea: make iVar2's live range LONGER (lower priority) by moving its load earlier or using it later. Hmm.

Idea: make tmp's qty take $2 and iVar1 $3 by ensuring iVar1's priority > iVar2's. Since iVar2 (6 refs/6 insns) has priority 8 and iVar1 (8/18) 5.33, we need iVar1 to have more refs. 

Where does iVar1 get 8 refs? Uses: 
1. `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` (def)
2. `CAST_SIGN(s16, iVar1, 0x10)` (use)
3. then-arm: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` (use)
4. else-arm: same (use)
5. `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` (def, reload)
6. `CAST_SIGN(s16, iVar1, 0x12)` (use)
7. then-arm2 store (use)
8. else-arm2 store (use)
Maybe 8 refs counts defs+uses.

To increase refs without adding instructions: use iVar1 in a way that folds into an existing instruction. E.g., in the then-arm, the store `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — could write `((Unkstruct_800B5CB8 *)iVar1)->unk10 = ...` twice? That'd add a store.

Hmm.

What about shortening iVar1's live range? Its live range spans from the unk20 load to the reload (18 insns). If we split iVar1 into two variables (iVar1 for the first part, reload into iVar1b), the first iVar1's live range would be shorter... but it still spans the arms. And the target has ONE v1 holding it across both blocks (2a44 lw v1; ... 2aa0 lw v1).

Hmm, actually, look at the target: at 2aa0 `lw v1,32(s0)` — the reload. So iVar1's first live range: 2a44 to 2a9c (the store in the else arm) and then 2aa0 reload. So live across the whole first if. That's ~22 insns.

If we made it shorter, priority would rise. But the structure is fixed.

Alternatively, reduce iVar2's priority by extending its live range: e.g., use iVar2 after the arms? It's dead after the branch test.

Hmm, hold on. Let me reconsider: maybe I don't need `tmp = iVar2` to be a copy at all. What if `tmp` is computed directly from the load in a way that reuses iVar2's register? E.g., the target's `move v0,a0` could be produced by `tmp = (s32)iVar2` where iVar2 is s16 — the sign-extend is free (move) and cse doesn't equate (a1). But a1's priority problem.

Let me try to combine a1 with a tweak that raises iVar1's priority: e.g., add a dead-ish use of iVar1. What folds away? 

Idea: change the then-arm store to use iVar1 *and* the else-arm... they already do.

Idea: the reload `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` at the end of the first if — maybe make it earlier/later to change live range.

Alternatively, change iVar2's live range by reordering the copy and the test:
```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = (s16)iVar2;
    if (iVar2 < 0) {
```
iVar2's live range: from the load to the last test. If we could compute the copy AFTER the second test... but the copy must be before the arms.

What if the copy is inside each arm (two copies)? Then iVar2's live range is the same.

Hmm, what if we reorder the two tests:
```c
if (iVar2 != 0) {
    tmp = (s16)iVar2;
    if (iVar2 < 0) {
```
The tests both use iVar2.

OK, different idea: what if `tmp` is assigned from a *different* expression that involves iVar2 but isn't a pure copy, so cse doesn't merge and the qty count stays low? For example `tmp = iVar2;` where tmp is used as an s32 and iVar2 is s16 — a1.

Let me look at a1's actual asm: `lh v1,16(a0)` — wait, a1 has iVar2 in v1 and iVar1 in a0. If I could just swap those two registers... The asm is otherwise identical? Let me check a1's full diff: it showed a0->v1 x8, v1->a0 x2, plus the copy placement (mine had `move v0,v1` at 14 instead of `move v0,a0` at 12). Actually a1's copy is at a different position (insn 14 vs 12) — in the delay slot of bgez instead of beqz. Hmm, that's because the copy `tmp = (s16)iVar2` is a sign-extend that got scheduled differently.

Hmm.

Let me try yet another idea: use the *do-while* to split the EBB at the right place so that cse can't propagate but the qty structure stays like n1. In n1, the copy merged. What if we do:

```c
tmp = iVar2;
do { } while (0);   // split
if (iVar2 < 0) {
    tmp += 0x80;
```
a4 did exactly this (do { } while (0) after the copy) — score 8, same as n1 (merged). So the split didn't stop cse.

Hmm. Maybe cse's propagation is global (not EBB-based) in 2.7.2. Actually gcc's cse is a global pass over the function using `reg_eqv`; it invalidates at basic block boundaries only for memory, not registers? In cse.c, `cse_basic_block` processes an extended basic block; at the end it calls `flush_hash_table`? Let me check: cse_main loops over basic blocks; `cse_basic_block` returns the next block; equivalence classes are reset per block (`reg_eqv` reset in `new_basic_block`). Yes, `new_basic_block` clears reg_eqv. So across a basic block boundary, equivalences are cleared.

The copy `tmp = iVar2` and the use `tmp += 0x80` are in different basic blocks already (the then-arm is a separate block). So cse can't propagate across the branch... but it did (the copy disappeared). Hmm, unless the merge happened at combine or elsewhere.

Wait, maybe the copy disappeared at *combine*, not cse. combine merges `tmp = iVar2` with the use if adjacent. Hmm.

Let me look at n1's cse2/combine dumps around the copy. Let me grep the n1 dump for "tmp" — hard. Let me look at the RTL after cse2 for the first block.

Actually, let me look at n1.i.cse2 around the function start.
