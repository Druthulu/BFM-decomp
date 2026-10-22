---
ts: 2026-10-22T07:04:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cwBhFMWql1UN6QKdXVAN
---
cand03 (empty do-while) has the SAME diff as cand22: the li in the delay slot.

So the do-while (empty or with a self-copy) fixes the move/li order but the li lands in the delay slot.

Now: the target has the li 3 slots before the jal. The difference now is only the dbr's delay-slot choice.

In cand03/cand22, the dbr put the li in the delay slot. In the tree, it put sw s1 there.

Why? In the tree, the chain before the dbr (post-prologue) is [.., move s0,a2, ASM, li, sw ra, sw s3, jal, sw s1, lui s1...]. The dbr's forward fill takes sw s1 ✓.

In cand03: [.., move s0,a2, li, sw ra, sw s3, jal, sw s1, lui...]. Why doesn't the dbr take sw s1 (the forward insn)?

Hmm! Maybe because in cand03, the forward insn after the jal is NOT sw s1. Maybe the prologue inserted sw s1 elsewhere (e.g. before the jal).

Let me check cand03's .dbr dump. But cand03 wasn't dumped. Hmm.

Alternatively, maybe the dbr's forward fill takes the FIRST insn after the call: in cand03, if the first insn after the jal is the `lui s1` (a symbol_ref set) — the dbr might refuse to move a `lui` into the delay slot? Hmm, in the tree the first insn after the jal was the sw s1 (the prologue's save) — so the dbr took it.

So the question is whether the prologue's sw s1 is before or after the jal in cand03's chain. In the tree it's after (the prologue inserts the save right before the first use of s1 = the lui). Hmm, but in cand03 the sw s1 ended up BEFORE the jal in the final assembly.

So in cand03, the prologue inserted sw s1 before the jal! Why? Because... the prologue inserts the saves in the prologue "region" — maybe the rule is: the save is inserted before the LAST use? or in the order of the register bank?

In the tree: sw ra and sw s3 are before the jal (they're the last uses: ra by the call, s3 by move s3,v0 after the call hmm).

Hmm, in the tree: sw s3 before the jal but s3 is defined AFTER the call (move s3,v0 at position 15 in the chain). So the prologue inserted sw s3 before the jal even though s3's def is after the call. That means the prologue inserts the saves in the "prologue region" — i.e., all the callee-saved saves go near the top of the function (in the entry block, before the first call), in the order of the register bank.

Hmm, but the observed order in the tree is: sw s2 (before move s2,a0), sw s4 (before move s4,a1), sw s0 (before move s0,a2), then sw ra, sw s3 before the jal. So the saves are inserted right before their defining insn for s2/s4/s0, but ra/s3 are inserted before the jal.

Hmm, s3's def (move s3,v0) is after the jal — but the sw s3 is before the jal. So the prologue inserts the saves in a specific order relative to the block: all saves go before the first call? Hmm, the jal is the first call.

So: the prologue inserts the callee-saved saves before the first "call" in the entry block? And s1's save (sw s1) is inserted... in the tree it's in the delay slot (after the jal) — so s1's save was NOT inserted before the jal. Why? Because s1's save is inserted before s1's first use (the lui after the jal) — since the lui is after the jal, the sw s1 lands after the jal ✓.

And s3's save is before the jal even though s3's def is after the jal — hmm, that contradicts "before the first use".

Ugh, unless: the saves are inserted before the first use, and for s3 the "first use" is... the `move s3,v0`? That's after the jal. Hmm.

Whatever the rule, the empirical difference between the tree and cand03 is where the sw s1 lands. Let me look at cand03's .dbr dump to see the chain. Let me dump cand03 — it's cheap.

Actually, let me think about it via the MIPS prologue pass: it inserts the saves for all the callee-saved regs used, in the order: it walks the function and inserts each save just before the insn that first uses the register (in the entry block). For s1: the first use is the `lui s1` after the jal → sw s1 before the lui ✓ (after the jal). For s3: the first use is `move s3,v0` (after the jal) → the sw s3 should be before that, i.e. after the jal. But the target has sw s3 BEFORE the jal!

Hmm, so my rule is wrong. Let me look at the target's assembly again:

```
d2cc: addiu sp,sp,-48
d2d0: sw s2,32(sp)
d2d4: move s2,a0
d2d8: sw s4,40(sp)
d2dc: move s4,a1
d2e0: sw s0,24(sp)
d2e4: move s0,a2
d2e8: li a0,16
d2ec: sw ra,44(sp)
d2f0: sw s3,36(sp)
d2f4: jal
d2f8: sw s1,28(sp)   (delay)
d2fc: lui s1,0x0
d300: addiu s1,s1,0
d304: move a0,s1
d308: move s3,v0
```

So: sw s2 before move s2,a0; sw s4 before move s4,a1; sw s0 before move s0,a2; sw ra and sw s3 before the jal; sw s1 in the delay slot (after the jal).

The MIPS prologue pass inserts each save immediately before the insn that DEFINES the register (for s2/s4/s0: the moves) — and for ra/s3 (defined later, after the jal): hmm, sw ra before the jal (ra is defined by the jal!). ✓ So the rule is "before the defining insn":
- s2 defined by move s2,a0 → sw s2 before it ✓
- s4 defined by move s4,a1 ✓
- s0 defined by move s0,a2 ✓
- ra defined by the jal → sw ra before the jal ✓
- s3 defined by move s3,v0 (after the jal) → sw s3 should be before move s3,v0 → but it's before the jal! ✗

Hmm. Unless the dbr/prologue moved it. The .dbr dump for the tree showed: (insn 205 20 209) sw ra, (insn 209 205 217) sw s3, (insn 217 ...) jal. So both sw ra and sw s3 are before the jal in the RTL.

Hmm, and sw s1 (213) is inside the jal's sequence (the delay slot) — the dbr moved it there from after the jal.

OK so the prologue inserted sw s3 before the jal (maybe the rule is: the saves are inserted in the entry block before the first call, in bank order, and the dbr then moves sw s1 into the delay slot).

Hmm, whatever.

DECISION TIME. I've spent ~55 min on item 3. The brief says to stop at 30 min and record a wall. But a WALL requires ≥30 scored tries (I have 25). Let me do a final batch of 5-8 tries exploring the delay-slot issue, then decide.

Final batch ideas (all plain C, keeping the do-while):
1. cand22 + move the `li a0,16` situation: what if we prevent the dbr from stealing the li by making the li NOT the call's arg setup... no.

2. **What if the call's argument is a variable that is NOT a constant, so the arg setup is a `move a0,sz`?** Then the instruction differs (move vs li) → the target has li a0,16 → no.

3. **What if we make the do-while's LOOP notes sit between the move and the li (as in cand22) AND the sw s1 lands after the jal?** The sw s1's placement is determined by the prologue/dbr. Hmm.

4. **What if we add a `pad` variable to change the frame?** The frame is 48 in both.

5. **What if the do-while is placed between the call and the store?** The boost/loop notes would then be after the call → the entry block's chain would be [move s2,a0, move s4,a1, move s0,a2, li, call, ...loop...]. That's cand01-like (score 2)? cand25 (do-while at the end) = score 2.

6. **What if we combine: do-while right after rgb=arg2 AND ALSO make the li not adjacent by adding another statement between the move and the call?** e.g.
```
rgb = arg2;
do { rgb = rgb; } while (0);
temp_v0 = func_80010A08(0x10);
```
that's cand22.

7. What if we add a SECOND do-while or a different loop shape: `for (rgb = rgb; 0; )` hmm.

8. What if the loop has a real body that emits an instruction we can use? E.g. `do { rgb = rgb; } while (0);` emits nothing.

9. **What if we could make the dbr's forward fill work by ensuring the insn after the jal is a single movable insn?** In the tree it's sw s1. In cand03 the sw s1 ended up before the jal.

Hmm, why would the prologue insert sw s1 before the jal in cand03 but after in the tree? The prologue inserts the save before the first use of s1. In cand03 the first use of s1... is the same (the lui after the jal). Unless the loop restructuring moved the lui? No.

Hmm, unless in cand03 the dbr moved sw s1 from after the jal to before the jal (a "reorg" backward move) — the dbr's `reorg_branch` can move insns across a branch in some cases.

Honestly, let me try a few empirical variants where the dbr might behave differently:

cand29: `do { rgb = rgb; } while (0);` + reorder the C so that the call is NOT immediately after the do-while but after another statement. E.g., insert a statement between the do-while and the call that emits an instruction... that would change the count. Unless the statement is the `*(u8*)((u8*)temp_v0+3) = 3;`? Can't (temp_v0 undefined).

cand30: `do { rgb = rgb; } while (0);` and ALSO change `func_8004914C(&D_800AF648)` — no.

cand31: `do { rgb = rgb; } while (0);` placed after `temp_v0 = func_80010A08(0x10);` but before the stores:
```
rgb = arg2;
temp_v0 = func_80010A08(0x10);
do { rgb = rgb; } while (0);
*(u8 *)((u8 *)temp_v0 + 3) = 3;
...
```
Hmm, the loop notes would be after the call → the entry block's chain [.., li, call, LOOP notes...] and the li's position relative to the move would be like cand01 (score 2). Probably no good.

cand32: TWO do-whiles?

cand33: `do { rgb = rgb; } while (0);` + the `*(s32*)...` store moved? no.

Honestly, maybe the answer is a WALL for item 3. But before that, let me try ONE more idea that could be the winner:

**What if we keep the do-while but place it so that the LOOP notes come between the move and the li, and additionally the sw s1 issue is fixed by making the s1 address a single instruction?** The `lui s1,0x0; addiu s1,s1,0` comes from `&D_800AF648` where the symbol is at address 0?? Hmm, that's weird: `extern u8 D_800AF648;` and the address is 0x00000000? That means the TU's symbol D_800AF648 is a common/absolute symbol with value 0? Whatever, the target has it.

Hmm, what if the delay slot in the target holds sw s1 because the dbr's forward fill took it, and in cand03 the sw s1 was before the jal because the dbr did a backward move of it. If I could make the dbr's forward fill succeed in cand03, the delay slot would hold the sw s1 ✓ and the li would stay before the sw ra ✓ → MATCH.

What does the dbr need for the forward fill? The insn right after the call must be movable into the delay slot. In cand03, what's right after the jal? Let me check cand03's .dbr chain. Let me dump cand03 (cheap, 1 min).

Let me do that, then decide.
