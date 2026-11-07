---
ts: 2026-11-06T21:52:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gY0dXqMqsoIR6QQEsYka
---
No reg 100 in the combine dump — so after combine, reg 100 is gone (the copy was absorbed). Confirms combine.

So the trick must defeat combine. Combine works on consecutive insns in a basic block, max 3 insns (i1,i2,i3), and it stops at a CODE_LABEL.

If the copy is in a different basic block than the compare, combine can't merge. The target's copy is in the same block though (label at 27 = the copy). But wait — the target's RTL: after allocation, the copy is at the join. At RTL/combine time, was there a code_label between the copy and the compare? The `one = 1` is a pinned asm-register variable assignment — it's a plain set.

Hmm, so in the target's own build, combine saw:
```
iv2c = iVar2        (i1)
asm("=r"(iv2c):"0"(iv2c))   (i2)
one = 1
if (iv2c != one)
```
and the asm blocked it.

So we need a C construct that emits a real insn between the copy and the compare, or a block boundary, with zero net instruction cost.

Zero-cost block boundary: impossible in general... BUT: what about a block boundary that jump1 does NOT merge because the label is a jump target from elsewhere? E.g., if the copy is at a label that is the target of the else-arm's jump (i.e., the copy is placed after the then-arm's goto). Hmm, that's exactly what the join is: the join label is a jump target (from the then arm), so the join starts a new EBB. The copy is IN the join block along with the compare. No boundary between them.

What if we place the copy at the END of the then arm AND at the end of the else arm? Then each arm's copy is in a different block from the compare (join). Cost: an extra move in the then arm... but maybe the then arm's copy gets folded: then arm sets iVar2 = 1, so `iv2c = iVar2` → combine folds to `iv2c = 1`, i.e., `li v1,1`, and then the join compares v1 with v0. But the target's then arm has `li a0,1` and the join `move v1,a0`. So we'd produce `li a0,1; ...; li v1,1`? Hmm, wait: if in the then arm we do `iv2c = iVar2` where iVar2 was just set to 1, combine folds to `li v1,1` and possibly removes `li a0,1` (a0 = iVar2 is dead until later use at sll a0<<3 — it IS used later, so `li a0,1` stays). So then arm: `li a0,1; li v1,1` = 2 insns vs target's 1. Bad.

Hmm. Unless the then-arm's copy can be made free: assign iv2c = 1 directly? Same problem.

So the copy must be at the join. Combine will merge it into the compare... unless something blocks.

What if we put the copy BEFORE the join label, i.e., at the end of the else arm only, and in the then arm... the then arm jumps over. Then the copy executes only on the else path — but the compare at the join uses iv2c on both paths. Wrong.

Unless the then path's iv2c is set differently... 

Wait, actually let's reconsider the whole structure. What if we move the compare into the else arm too? Semantics: the then arm sets uVar5=0 already; the compare would be false there (iv2c=1). So we can restrict the compare to the else arm:

```
if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
else {
    t = ...; iVar2 = t + 1; param_2 <<= 4;
    { int iv2c; iv2c = iVar2; one = 1; if (iv2c != one) uVar5 = 0; }
}
```
But the target's compare is in the join block shared by both paths, so this would produce different code (the then arm would jump past the compare → different layout). Not matching.

OK, so we're stuck with the copy at the join, adjacent to the compare, and combine merges it.

Therefore we need the copy to be something combine can't merge: a non-copy RTL that produces a `move` after combine. Options:
- SIGN_EXTEND that combine folds to a copy but can't merge into the compare (because the folding produces a copy in a later pass?). Hmm: combine folds and merges in one step.

Wait — actually how does combine merge a copy into a compare? It needs i1 = copy, i2 = ?, i3 = compare, with at most 3 insns. Between the copy and the compare there's `one = 1` (li). So i1=copy, i2=li, i3=compare: 3 insns. Combine tries combining i1,i2,i3. It substitutes the copy's dest in i3. It requires i2's dest (v0) not be needed... it works.

Now: if I put ANOTHER insn between the copy and the compare, combine's window (3) would not reach: copy at i1, X at i2, li at i3, compare at i4 → the window [i2,i3,i4] doesn't include the copy. But adding an insn costs one instruction (57 vs 56).

Unless the extra insn is one the target already has elsewhere... no.

Hmm, what about combine's `prev_nonnote_insn` — it can look at i1,i2,i3 where i1 and i2 are non-jumping. There's also the restriction that i3 must be the last insn of the combination.

What if the copy is *not* immediately followed by the li, but the li comes BEFORE the copy? Target: move(27), li(28), beq(29). If we reorder to li first then copy then beq: `li v0,1; move v1,a0; beq v1,v0`. Combine would still merge (i1=li, i2=copy, i3=beq) — substitute v1→a0. Yes, still mergeable.

What if the compare is `if (iv2c != one)` where one is the pinned $2... 

Hold on — maybe we can exploit combine's rule about hard registers: after cse, `one` is a pseudo assigned to $2? No, `one` is declared `register int one __asm__("$2")` so it IS hard reg 2 at RTL. Combine has `HARD_REGISTER_NUM_P` checks: it will not delete an insn that sets a hard register? Let me check: combine refuses to substitute when the destination is a hard register in some cases. Hmm.

Actually in the w2 RTL, insn 105 sets `(reg/v:SI 2 v0)` — a hard reg (v0). Combine's try_combine has a check: `if (GET_CODE (SET_DEST (PATTERN (i2))) ... && ! dead)`. Also `HARD_REGISTER_P` matters for `i2dest`: combine says "If I2DEST is a hard register, we can't delete it" — hmm, but the merge here is of i1 (copy) into i3 (compare), with i2 = li v0 (hard). Combine requires that i2's destination isn't used in i3? No — i3 (beq) uses v0!

So combine must handle: i2 sets v0 (hard), i3 uses v0. It can't delete i2 (hard reg, and i3 needs it). Combine's try_combine only combines i1,i2,i3 when i2's result feeds i3 or can be merged. Here the substitution is about i1's dest (iv2c) used in i3.

So the pattern is: i1 = copy (iv2c = iVar2), i2 = li v0, i3 = beq using iv2c and v0. Combine merges i1 and i3, keeping i2? Hmm, that's the "combine 1 and 3 with 2 in between" case, which combine handles (i2 must not use i1's dest or modify the source). Since i2 (li v0) doesn't touch a0 or v1, it's fine.

So combine merges.

To block: make i2 use or clobber the copy's source (iVar2/a0)? If i2 modified iVar2, the copy couldn't be merged — but iVar2 is needed later anyway.

Hmm, what if the copy source is a *memory* location? Then combine can't... no, memory.

New idea: what if the copy's source is a register that combine can't prove unchanged across i2 — e.g., if the copy is `iv2c = *(some global)`? no.

Let me look at combine.c's conditions to find a legitimate C shape that blocks it. Maybe the condition involves `i2` modifying the destination register iv2c... 

Actually, simplest: what if i2 (the li v0,1) sets a register that is *the copy's source*? E.g., if `one` were assigned before the copy... no.

Let me flip: put the copy AFTER the li but make the copy's source register be v0? no.

What about making the compare use iv2c in a way combine can't fold: e.g., compare `iv2c != one` where the comparison is done on the *narrowed* value... 

Alternatively — maybe avoid the copy entirely by getting `beq v1,v0` where v1 is a real different variable: what if iv2c is computed as `iVar2` via a *second assignment in the else arm*, and the then arm sets iv2c = iVar2 too, but the join's compare... we discussed.

Hmm hold on. Let me reconsider the then-arm copy idea more carefully with actual target code:

Target:
```
19 bne v1,v0,63b8    ; if (iVar4 != 6) goto else   [delay slot 20: sra v0,a1,0x10]
21 li a0,1           ; then: iVar2 = 1
22 j 63c4
23 move t3,zero      ; delay: uVar5 = 0
24 andi v0,v0,0xf    ; else (63b8)
25 addiu a0,v0,1     ; iVar2 = t+1
26 sll a1,a1,0x4
27 move v1,a0        ; 63c4: iv2c = iVar2
28 li v0,1
29 beq v1,v0,63d8
```

If I put `iv2c = iVar2` at the end of the then arm (after iVar2=1, uVar5=0), the then arm becomes: `li a0,1; move v1,a0; j; move t3,zero` — one extra insn (56+1=57). The join would then be just `li v0,1; beq v1,v0`. Total 57. Not matching (target 56).

Unless the then-arm's `li a0,1` disappears because iVar2 is dead... no, it's used later.

So the copy must be at the join.

OK. What about making combine's window miss by having the copy be i1 and the compare i4 (with 2 insns in between)? We'd need an extra insn — unless the `li v0,1` could be split... no.

Hmm, wait. What if the copy and the compare are in different blocks but the copy is at the join label and the compare... no.

Let me reconsider: maybe use a real second set of iv2c that cse/combine keeps, making the value different... 

Actually here's an idea: **assign iv2c in the then arm and in the else arm, but let the else arm's copy be the only one at the join**... no.

Alternative idea: **use a variable that combine cannot substitute because it's a hard register**. `one` is a hard register ($2). What if iv2c is ALSO pinned to a hard register... that's a pin (forbidden kind). 

BUT: the item's kinds file says `launder` only. The pins ($8/$2/$4/$3/$2/$2/$3/$2) are "levers of other kinds the def already had" — they may stay, never added. Adding a new pin = adding a lever of a kind the row lists? The row kinds = launder only, so adding a pin is "a new lever of any kind" → forbidden by "no new lever of any kind".

Hmm.

OK, let me think about what real C produces a copy that combine keeps. Combine refuses to combine when the source register is used/modified... 

What if the copy's destination is used in the compare AND the copy's source is also used in the compare? no.

What if the copy is from a *HImode* source that combine can't fold because the value's high bits are unknown? Let's find such a value equal to iVar2: 

What if we store iVar2 into a `short` and read it back? memory (lui/sh) — no.

Hmm, what about making the sign-extend source a `s16` *global*? no.

What if we change the comparison to `if (iv2c != one)` where iv2c is `short` and `one` is int: the RTL would be sign_extend(iv2c) vs one — the sign extend is on iv2c (which we know is 1..16 from... hmm, iv2c is a variable assigned iVar2; combine tracks that iv2c = iVar2 (a copy), so it knows the range).

Unless iv2c is assigned from a value combine can't track: e.g., iv2c = iVar2 where iVar2 was computed in a different block (the else arm). At the join, combine sees iv2c's value as... the copy insn is there; combine knows iv2c = iVar2 at the join. It doesn't know iVar2's range across blocks? nonzero_bits is global (per-register, computed by reg_scan? no, nonzero_bits uses REG_NONZERO / known values tracked by combine within the block).

Hmm! In the join block, iVar2 (reg 77) is live-in from the else arm (fall-through) or from the then arm (jump). The andi/addiu happened in the else block. Combine works per block and doesn't know iVar2's range at the join (it only sees what's in the block). Wait, but combine also has REG_EQUAL notes. In the else block, `addiu a0,v0,1` has no note about range.

So if the sign-extend is applied at the JOIN (in the same block as the copy), combine might not be able to prove the sign-extend is a no-op → it would emit sll/sra (2 insns). That's what we saw? No — w2's sign-extend was in the same block as the andi (the sign extend was at insn 99-101, in the join block, but combine folded it anyway).

Hmm, why? Because combine's nonzero_bits on reg 77 uses `reg_nonzero_bits`? It might know from the earlier block via REG_NONZERO... uncertain.

Alternatively, maybe the sign extend was folded because of the REG_EQUAL note on insn 101: `(expr_list:REG_EQUAL (sign_extend:SI (reg/v:HI 102)))` and insn 99 sets 102 = subreg(77). Combine folds sign_extend(subreg(x)) → x when it can prove... 

Let me just test a variant where the sign-extend source is a value computed in the *then* arm too... 

Honestly, let me try a batch of candidate shapes and score them. Cheap experiments:

w4: `iv2c = (s16)iVar2;` but with iv2c declared `s16` and compared to `one`:
```
s16 iv2c;
...
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
w5: same but with an int iv2c and `iv2c = (s16)iVar2;` (already w3=5).

w6: copy in both arms (see the count).

w7: use a `union`? skip.

w8: separate the copy from the compare with a real C construct that emits nothing but a NOTE... notes don't block.

Hmm, what about `if (iv2c != one) uVar5 = 0;` written as:
```
uVar5 = (iv2c != one) ? 0 : uVar5;
```
or `if (iv2c == one) ; else uVar5 = 0;` — the empty then-arm might produce a block structure... probably same.

Another idea: the target's compare is at the join; maybe I can make the copy the FIRST insn of the join block and the compare the third, but insert a *NOTE_INSN_BLOCK_BEG* — notes don't stop combine (prev_nonnote_insn).

OK, let me look at combine.c to see the exact conditions for merging a copy into a user. Maybe there's a specific check: "if the source of the copy is a register that is set between i1 and i3, don't". Or "if i1's source is a hard register and i2 sets a hard register..." Let me grep for the relevant check.
