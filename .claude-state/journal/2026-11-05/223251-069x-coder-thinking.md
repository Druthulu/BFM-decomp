---
ts: 2026-11-06T05:32:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ioPJwCqYehtnqZCeCQMY
---
b1 uses `lh v0` and merged. So the HImode declaration didn't keep the copy.

Hmm. Let me look at b1's cse2 RTL for the copy.

Actually, I've spent a lot on this. Let me consider the time: it's probably ~22:55 now (25-30 min on item 2). I have 19-20 tries. The WALL criterion: ≥20 min and ≥30 tries. I could do 10 more quick ones.

But hold on — let me reconsider the whole approach. What if the copy should be from a *different* variable: the source might have `tmp` assigned from `iVar2` where iVar2 is a *signed 16-bit load into an s32 variable*, and the launder is replaced by... 

Actually, let me revisit the moves.md catalog for this exact wall class. Line 96: "pin | func_8017E614 | WALL lreg-v0-local-first — local-alloc gives cmp const 14 v0 (call v0 dies at andi) before global ok". Line 41: "pin | func_8017D924 | WALL lreg-v0-local-first". Line 143: "pin | func_800D02D0 | WALL lreg-qty-order — target puts the D_800D3768[arg0] load in $v1 and the &D_800C7C60 pointer in $v0; lever-free p makes the load take $v0 (best 8 of 38)". 

Hmm, our situation: target wants iVar1 in $3, lever-free iVar2 takes $3. That's "lreg-qty-order" / "greg-pri-refs".

But maybe there IS a crack. Let me think about the qty priorities once more, focusing on iVar1: 8 refs/18 insns. 

Hmm, what if iVar1's live range is *shorter* because we move the unk20 load later? E.g.:

```c
func_80181B00(a0);
func_801820F8(a0);

iVar2 = CAST_SIGN(s16, ((Unkstruct_800B5CB8 *)a0)->unk20, 0x10);
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
```
Hmm, that's 2 loads but gcc CSEs them. The order in asm: the target has `lw v1,32(s0)` then `lh a0,16(v1)`.

What if the source computes iVar2 from a direct memory expression and iVar1 from a separate one? gcc's CSE would merge the two loads into one pseudo. The pseudo's live range starts at the first load.

Alternatively, what if iVar1 is used only in the arms and the CAST_SIGN uses the direct expression? Then iVar1's def would be... 

Hmm, here's a thought: what if we *eliminate* iVar1's long live range by reloading it in each arm from `*(s32*)(a0+0x20)`? The target's arms use v1 (already loaded). If gcc CSEs, it keeps one load. But the *pseudo* might have a shorter live range if each arm uses a separate expression and gcc doesn't CSE across branches? It would CSE (same address, no intervening stores to that address... actually there ARE stores: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = ...` stores through iVar1, which might invalidate the memory CSE for `*(s32*)(a0+0x20)`? No — a0+0x20 is a different address, but cse can't prove it (iVar1 is an unknown pointer) → the store invalidates the cached load of a0+0x20! 

Oh interesting. So if the arms use `((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 = ...` (reloading unk20 after the store), gcc must reload. That would add `lw` instructions. Target has `sh v0,16(v1)` without reloading between arms. Hmm, in the target, the two stores in the arms use v1 directly (iVar1 held in a register).

OK.

Let me now consider: is the WALL tag "lreg-qty-order"? Or maybe I should try harder with the *first* idea: make iVar2's qty longer.

Actually, here's a thought I haven't tried: make iVar2's live range extend past the arms by *using* it in the arms in a foldable way. For example, the condition `if (0 < tmp * 0x10000)` could be written as `if (iVar2 < 0 && 0 < tmp * 0x10000)`? That changes control flow.

What about the store: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — could be `(s16)(tmp + 0 * iVar2)`? Folds to tmp but might count as a use of iVar2? gcc folds 0*iVar2 to 0 early (fold_const). Hmm, but maybe not if iVar2 is a variable: `tmp + iVar2 - iVar2`? gcc might not fold that. It would add instructions though (subu/addu).

What about `tmp * 1`? folds.

Hmm.

OK — actually, let me revisit the possibility that the target's structure is achievable with `tmp` being assigned NOT from iVar2 but from the *memory* via iVar1, e.g., `tmp = CAST_SIGN(s16, iVar1, 0x10);` — a second load. That'd be an extra lh. No.

Let me just try a handful more and then WALL. Actually, let me reconsider the qty formula with `qty_size`: for a pointer qty, is size 4? Yes.

Hmm, wait — what about `-f` options? No.

Let me try one more clever thing: what if iVar1 is used in the *condition* `if (iVar2 != 0)` in a way that folds? E.g., `if (iVar2 != 0)` — the branch tests iVar2.

What if we write `if (*(s16*)(iVar1+0x10) != 0)` directly (using iVar1) and then `iVar2 = ...`? That adds a load.

I'll do a final batch of ~10 with different structures, then record the WALL if none works.

Final batch ideas:
g1: `iVar2` s16 + copy `tmp = (s32)iVar2;` + second test `if ((s16)tmp < 0)`? no.
g2: iVar2 declared `s32`, tmp `s32`, copy `tmp = iVar2;`, and the second test written `if (tmp < 0)` (test on tmp).
g3: copy placed after the second test in the then-arm: `if (iVar2 < 0) { tmp = iVar2; tmp += 0x80; ...}` and in the else arm too.
g4: iVar1 declared as `s32`, `(Unkstruct_800B5CB8 *)(iVar1)` casts.
g5: `tmp = iVar2;` where tmp is declared `s32` but the arms use `(s16)tmp`.
g6: the copy through a `s16` *pointer*? no.
g7: `tmp = iVar2;` + `iVar1 = iVar1;` (dead) — might boost iVar1's refs before cse deletes it? cse would delete it. But maybe the dead set survives to local-alloc and adds a ref! moves.md line 199: "dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL)". So dead sets can survive if they're not trivially deleted (e.g., a copy between different variables). `iVar1 = iVar1;` is a self-copy, likely deleted. What about `iVar1b = iVar1;` (dead)? That's a copy to an unused variable → deleted.

Hmm, but what about a *store* through iVar1 that's dead? E.g., `((Unkstruct_800B5CB8 *)iVar1)->unk10 = ((Unkstruct_800B5CB8 *)iVar1)->unk10;`? Adds instructions.

g8: use `iVar1` in the second test: `if (iVar2 != 0 && iVar1 != 0)` — changes branch.

g9: make the `tmp = iVar2` copy an HImode *store/load* through a local array? Adds insns.

g10: `tmp = iVar2;` with iVar2 declared `int` and tmp `long`? Same size.

Let me try g2 and g3 and a few others. Actually g2 is interesting: if the second test uses tmp, then iVar2's last use is the copy → its live range is shorter, priority HIGHER (worse). No.

g3: copy inside the arms — the copy would be after the bgez, so the target's delay-slot move is lost.

Hmm.

Let me think about "what could make iVar1's priority higher" one more time. nrefs for iVar1 = 8. If we could get 16 refs... 

The arms: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — the cast `(s16)tmp` and the store. What if we write the store value as `(s16)(tmp + iVar1*0)`? folds.

What if the address uses iVar1 twice: `((Unkstruct_800B5CB8 *)(iVar1 + 0))->unk10`? folds.

Hmm, what if iVar1 is `u8 *` and the store is `*(s16 *)(iVar1 + 0x10) = (s16)tmp;`? Same refs.

OK. Let me accept a likely WALL for item 2 but do the required ≥30 tries. I'm at ~20. Let me do 10 quick variants in one batch, then record WALL with best 8.

Actually wait — before that, let me reconsider ONE promising direction: the *frame*. a1's score is 18 with iVar1/iVar2 swapped. If I could make iVar1 win... 

What about declaring iVar1 as a `register` variable? No — `register` keyword isn't allowed ("no `register` vars"). And without an asm pin it doesn't force a register anyway.

What about `-f`? No.

Hmm, one more idea: **swap the roles**: make iVar2 the pointer-ish long-lived one? No.

What about making the two tests use *different* variables so iVar2 dies early, and the copy is from iVar2 before it dies? E.g.:
```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
tmp = iVar2;          // copy before the if (hoisted)
if (iVar2 != 0) {
    if (iVar2 < 0) {
```
That's e1 (score 8, merged? e1 was 8 = same as n1). Hmm, e1 scored 8 (MIXED, v0->a0 x6) — so merged still.

What if we hoist the copy AND cast: `tmp = (s16)iVar2;` before the if? Let me try that (h1).

And also: `tmp = (s16)iVar2;` before the if with tmp s32.

Let me also try the copy AFTER the second test (inside the arm heads) — h2.

Let me do a final batch:
h1: hoisted `tmp = (s16)iVar2;`
h2: copy at the start of each arm (`if (iVar2 < 0) { tmp = (s16)iVar2; tmp += 0x80;`)
h3: `iVar2` s16 + hoisted copy `tmp = iVar2;`
h4: `tmp = iVar2;` + second test `if (tmp < 0)` (test on tmp)
h5: declaration order: tmp declared before iVar2
h6: iVar1 declared before iVar2 but tmp after pad
h7: `iVar1` as `s32` with explicit casts
h8: `iVar2 = (s16)CAST_SIGN(...)` 
h9: `tmp = iVar2;` and the arms use `iVar2` for the store value: `((...)iVar1)->unk10 = (s16)iVar2;`? changes semantics (iVar2 unmodified).

Let me run h1-h5, h8.
