---
ts: 2026-11-06T21:14:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HhcopfA5Q2cOdTtA5INh
---
Line 421-423: allocno_n_refs sums reg_n_refs over the pseudos in the allocno; allocno_live_length = max reg_live_length.

So allocno 79: n_refs=2, live_length=4. allocno 95: n_refs=3, live_length=8.

pri_e = floor_log2(2)*2/4 = 0.5
pri_off = floor_log2(3)*3/8 = 0.375

e > off. So e should be before off in allocno_order. But the list has 95 before 79. Contradiction. Unless allocno numbers != pseudo numbers. Let me check: allocno_reg maps allocno→pseudo, and the print uses allocno_reg[allocno_order[i]]. So the numbers printed ARE pseudo reg numbers. Hmm.

Unless there are multiple allocnos for the same pseudo? allocno_reg[allocno] = i where i is pseudo. If two pseudos are tied (copies) they share an allocno, and allocno_reg points to one of them. So the printed number could be the "representative" pseudo. E.g., if 79 and some other pseudo are tied, they share an allocno whose representative is, say, 79. The n_refs would be summed.

But the order: 95 before 79. Let me recompute with possible ties: maybe 95 is tied with another pseudo, raising n_refs.

Hmm, this is getting too deep. Let me use a more direct experimental approach: find a real-C change that moves e up in the order. Since the launder gives e n_refs=4 (doubling floor_log2 to 2 → pri = 2*4/4=2), it jumps above off (0.375).

If I can get e to n_refs=3: floor_log2(3)=1, pri=1*3/4=0.75 > 0.375. Still above off! So even +1 ref should fix it. Wait, but if e is last with pri 0.5 > off 0.375, the ordering is inconsistent with my calc, so maybe the calc is wrong.

Let me test empirically: add a single extra reference to e that produces no code and see if it flips. A single extra *use*: e.g., use e in a `(void)e;` statement — does that generate a ref? `(void)e;` with e a variable — the C front-end might drop it (no side effect). Let me test: does `(void)e;` create a USE in RTL? Probably not (it's a no-op expression statement, discarded).

What about `if (e) {}`? That creates a compare/branch on e → extra code.

Hmm. What about using e in the lim load in a way that produces the SAME instructions? We saw `((s16(*)[2])e)[idx][0]` gives 146 (one less). What if we use e for lim AND keep the symbol-based address somewhere? 

Actually, let me reconsider the 146 result: using e for lim shares the address e+off, saving one addu. But target has TWO addu. What if we make the two addresses different so they don't share? The lim is at e+off (offset 0) and the condition at e+off+2. If we compute lim from e but with a DIFFERENT base expression that cse can't unify... e.g., `lim = *(s16*)((u8*)e + idx*4);` vs condition `*(s16*)((u8*)e + off + 2)`. cse computes idx*4 = off, so same. 

What if lim uses `((s16*)e)[idx*2]` and condition uses `*(s16*)((u8*)e + off + 2)`: lim address = e + (idx*2)*2. cse might compute idx*2 then *2 = idx*4 = off. Same base → shares.

OK. Let me try the simplest single extra ref: add `e = e;` — flow removes. Add a redundant load through e that cse removes.

Alternatively, raise e's n_refs by making it used in the `if (idx >= 0)` block in a way that folds into an existing instruction. E.g., `p = D_801E8F98[idx];` — what if we write `p = D_801E8F98[idx] + (e == e);`? folded.

Hmm.

Wait — maybe I should reconsider: the moves log has entries like "launder->real 2nd set pv &= 0xFF000000". The pattern is: replace the asm launder with a real arithmetic 2nd set that is *part of the program's semantics* (e.g., the target actually does `pv = pv & mask`). In our case, the target's e is a constant address; there's no arithmetic to do.

But maybe there's a different real-C structure. Let me look at the target more: is `e` actually used as a pointer, or could it be that the "launder" was masking a genuine need? 

Let me try: `e = (s16 *)D_801E8F78;` replaced by loading e from a global pointer? No.

Alternatively, use `e` for the lim load and ALSO keep off separate by writing the lim load as `D_801E8F78[idx][0]` — no.

Let me try something: what if we compute `lim` via `e` and the condition via the SYMBOL? i.e., swap:
```
e = (s16 *)D_801E8F78;
lim = ((s16(*)[2])e)[idx][0];
...
if (*(s16*)((u8*)D_801E8F78 + off + 2) == 0 || ...)
```
Then e is used for lim (born early), and the condition uses the symbol (REG_EQUIV of e? no, uses symbol directly). This gives e n_refs=2 (def+lim use) but the condition doesn't use e. The address for the condition = sym+off (at), and lim = e+off. Target has lim=sym+off (at) and condition=e+off. So this is the mirror — wrong.

Hmm.

Let me step back and consider the budget: started 13:58, now ~14:20. I've spent 22 min on item 1. Budget 20-30 min per item; past 30 min stop and record a wall (needs ≥20 min and ≥30 scored tries). I have maybe 8 min. Let me count tries: I've scored ~15 candidates. Not yet 30.

Let me try a batch of more ideas quickly, then decide. Ideas:
1. `(void)e;` extra use.
2. `e = (s16 *)D_801E8F78;` then inside `if (t < lim)`, before the condition, reassign `e = (s16 *)D_801E8F78;` — makes first dead, but maybe combine keeps both? Test.
3. Use `e` twice in the condition by writing `*(s16*)((u8*)e + off + 2) == 0 || (((s32(*)(s32))func_80029178)(((s16*)((u8*)e + off))[1]) & 0xFF) == 0` — the second is a different expression but same address; cse might or might not merge. Test.
4. Make off a separate variable assigned from e? no.
5. Reorder: `lim = ...; e = ...; off = idx*4;` (off born later).
6. Compute `off` from `e`: no.

Let me test 1,2,3,5 and also `e[idx*2+1]`.

Actually, let me reconsider idea 3: if cse does NOT merge the two loads (because the expressions are structurally different in RTL?), then e has 2 uses and there would be 2 loads (extra instruction). But maybe cse merges. Let me test.

Let me also try making the condition use a `s16` temp `v` loaded through e, then `v` twice. c.c tried that (v2) → 4, same REG. So the temp didn't help.

Let me try the two-expression version.
