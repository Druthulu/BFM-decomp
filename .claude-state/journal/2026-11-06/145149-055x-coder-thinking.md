---
ts: 2026-11-06T21:51:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2Zz79OqRgWg2c9a0kO9B
---
Very informative. After cse (w2), the code is:

- insn 95: `(set (reg/v:SI 100) (reg/v:SI 77))` — this is `iv2c = iVar2`! reg 77 = iVar2, reg 100 = iv2c.
- insn 99: `(set (reg/v:HI 102) (subreg:HI (reg/v:SI 77) 0))` — the s16 tmp (reg 102), taken from iVar2 (not from iv2c!).
- insn 100-101: sign extend back into reg 100 (iv2c) — so `iv2c = tmp` became sign_extend(tmp), i.e., cse substituted tmp with iVar2 in the sign_extend.
- insn 105: one = 1 (v0)
- insn 108: compare iv2c (100) with v0.

So the copy insn 95 IS present after cse (it's `iv2c = iVar2`). Then combine presumably folds the sign-extend (101) into a copy and merges 95 into the compare. So the RTL after cse has:
- 95: iv2c = iVar2
- 99: tmp:HI = subreg(iVar2)
- 100: shift
- 101: iv2c = sign_extend(tmp)

Note the sign-extend path recomputes iv2c from tmp — so 95's copy is dead (overwritten by 101). Combine should kill 95.

In the final asm we saw no extra instructions: so combine folded 99/100/101 into nothing and then 95 into the compare.

Key: cse DID substitute `iv2c = tmp` → `iv2c = sign_extend(iVar2)` (reg 100 = sign_extend of reg 77, not of tmp 102!). So cse propagated tmp → iVar2 in the sign_extend (they're equal since tmp = subreg(iVar2)). And iv2c's copy at 95 remains a separate insn.

So if I remove the `iv2c = iVar2` line and just use `iv2c = (s16)iVar2;`... same.

The sign-extend is what combine then folds. Since iVar2 (77) is known sign-extended? combine sees `iv2c = sign_extend(subreg(iVar2))` — for a SImode reg, subreg:HI then sign_extend:SI is exactly a no-op → folds to a copy. Then combine merges the copy into the compare.

So the mode trick doesn't survive here because combine can prove the round-trip is a no-op.

What if the sign-extend source is a HImode *variable* whose SImode value is unknown? i.e., tmp:HI = ... and then iv2c = sign_extend(tmp). Combine folds sign_extend(subreg(x)) only when the subreg is of a register of the same mode — always a no-op semantically? `(sign_extend:SI (subreg:HI (reg:SI x) 0))` is NOT generally a no-op: it's a no-op only if x is known sign-extended in HI. Combine uses REG_EQUAL/sign-extension info: in func_80182ED4 the load was `lh` (sign-extending load) so combine knew.

Here, iVar2 comes from addiu — combine knows bits 16+ ... hmm, actually `(sign_extend:SI (subreg:HI (reg:SI x) 0))` for a random x would require sll/sra. But the final asm shows no sll/sra, meaning combine proved the sign bit of the low half is 0 (from andi 0xf, +1). Yes: iVar2 = (x & 0xf) + 1 ∈ [1,16], so sign_extend is a no-op.

So the value range is what kills it. If I make the copy from a value whose range is unknown... but it must equal iVar2.

Idea: make iVar2's *known range* go away by computing it differently while producing the same asm. E.g., in the else arm, instead of `t = param_2 >> 0x10 & 0xf; iVar2 = t + 1;`, write `iVar2 = (param_2 >> 16 & 0xf) + 1;` — same asm (sra, andi, addiu) and same known range.

What if we compute `iVar2` through a variable of type `unsigned` or with a cast that hides the range? The andi 0xf result is inherently 0..15 — any expression `& 0xf` gives that. Unless we write it as `t % 16`? GCC would emit andi and know range too.

Hmm, what if the sign-extend source is a *different* HImode variable that holds the same value but with unknown range... e.g., `s16 tmp = iVar2;` — tmp:HI = subreg(iVar2), combine knows subreg.

What if the copy is `iv2c = (s16)(iVar2 | 0x8000)`? changes value.

OK, so what else could produce a `move v1,a0`?

Let me reconsider: the copy at insn 95 (iv2c = iVar2) IS in the RTL after cse. It's combine that merges it into the compare. Can I block combine? Combine looks at up to 3 consecutive insns, and it only combines insns in the same basic block, and it stops at a CODE_LABEL or a jump. There is a note NOTE_INSN_BLOCK_BEG/END between insns 92/95/97/99/101/102 — notes don't block combine.

What if there's a `use` insn or a clobber between? A `(use (reg))` doesn't block.

What if the copy is in a different basic block than the compare — combine can't cross a code_label. The target has the copy at the join (same block as the compare).

Hmm, but wait: maybe I can arrange for the copy to be at the END of both arms in a way that produces the target's exact code! Let's look at the target's structure again:

```
19 bne v1,v0,63b8     ; if (iVar4 != 6) goto else
20 sra v0,a1,0x10      ; delay slot: (else-arm's first insn! it's in the delay slot of the bne)
21 li a0,1             ; then-arm: iVar2 = 1
22 j 63c4
23 move t3,zero        ; delay: uVar5 = 0
24 andi v0,v0,0xf      ; else arm
25 addiu a0,v0,1       ; iVar2 = t+1
26 sll a1,a1,0x4
27 move v1,a0          ; <-- join: iv2c = iVar2
28 li v0,1             ; one = 1
29 beq v1,v0,63d8
30 nop
31 move t3,zero        ; uVar5 = 0
```

So the copy is at the join, after the else arm falls through (the then arm jumps to 63c4 which is insn 27? The j at 22 jumps to 63c4 = address of insn 27; delay slot is 23). So the join label is at insn 27 (the copy). Both paths reach it.

So the copy must be at the join block start. Combine merges it into the compare (2 insns later).

Wait — does combine actually merge it? In w2's final asm, the compare used a0 directly and there was no move. Yes, merged.

But hold on: why does combine merge `iv2c = iVar2` into `beq iv2c,v0` when it also has `li v0,1` in between? Combine's try_combine(i1=95, i2=99?, i3=...) — the insn sequence after cse is 95, 99, 100, 101, 105, 108. Combine might first combine 99+100+101 (the sign extend) into a copy, then 95 becomes dead, then combine 95 into 108.

Alternatively, maybe combine isn't needed: perhaps the copy at 95 is deleted because iv2c is re-set at 101 (dead store elimination in flow/combine). Then 101 (sign_extend) folds to a copy `iv2c = iVar2`, and then combine merges that into the compare.

Either way, the copy gets absorbed.

What real C would keep the copy? A copy that combine cannot merge into the compare because the compare's operand isn't the copy's destination... 

Hmm! Wait. What if we make the compare use a *different* register by making `one` not a register? `one` is pinned to $2, so `li v0,1` then compare reg-reg.

What if the copy is needed by *two* uses, one of which combine can't fold? E.g., use iv2c twice. Adding a second use changes the code (target has one use).

What if the copy's source (iVar2) is modified between the copy and the use? No.

Combine will always fold a copy whose dest dies at the next use. Unless the dest is *not* dead (used later) — then combine still substitutes the first use and keeps... no: combine substitutes only if the register is dead after the use (`reg_dead` check? In try_combine, i2 must not be needed after i3). Actually combine's `try_combine` requires that the insn i2's destination is dead after i3 OR it re-adds a copy. Specifically, combine checks `dead` and if i2's dest is used later, it doesn't combine (or adds back the insn). Yes! In combine.c, when substituting, if the register set by i2 is used after i3, it inserts i2 back (it can still combine by keeping the set). Hmm.

But here iv2c is used only once, so combine merges freely.

What if iv2c has a second use *after* the compare that we can justify? Adding a use would add instructions... unless the second use replaces an existing one. Hmm: uVar5? No.

What if we make the *destination* iv2c live-out in a way that costs nothing: e.g., `if (iv2c != one) uVar5 = 0;` — the target computes uVar5 = 0 in the branch. What if we write the condition using iv2c twice: `if (iv2c != one && iv2c != one)`? fold removes.

OK, radically different approach: maybe make the copy come from a different source register. In the target, `move v1,a0` where a0 = iVar2. What if we copy `iVar2` into a *new variable* that is then used in the compare, but the copy is separated from the compare by an insn that combine can't see through — like a *volatile*? no.

Hmm, what about the `one = 1` pinned assignment: it's `register int one __asm__("$2"); one = 1;`. The pin is a hard reg. What if we make the copy's destination also hard-reg-pinned? That's a pin (forbidden).

Let me reconsider the problem: maybe I don't need the copy at all if I can get `beq v1,v0` differently. The target's compare is between v1 (iv2c) and v0 (one). Mine is between a0 (iVar2) and v0. What if I make iVar2 live in v1 instead of a0? Then no copy needed! The difference: mine `beq a0,v0`, target `beq v1,v0` plus a move. If iVar2 were in v1 and the copy in a0... no, the target's iVar2 is in a0 (used later at `sll v0,a0,0x3`).

So the target genuinely has a copy.

Think about **combine's limit of 3 insns**. The target has: 27 move v1,a0; 28 li v0,1; 29 beq v1,v0. Combine examines i1=27, i2=28, i3=29. It can combine all three? It tries: i2 (li v0,1) sets v0; i3 uses v1 and v0. Combining i1 into i3 would need to substitute v1→a0, and then i3 is `beq a0,v0` with i1 deleted — that's 1 insn saved. Combine does this if v1 is dead after i3 (yes) — but it must also ensure the substitution is valid: a0 must not be modified between i1 and i3 — it isn't.

So combine would ALWAYS do this. Unless... v1 is a hard register? In the target, v1 is a hard reg ($3). Combine refuses to substitute a hard register? Hmm — combine typically won't substitute a *hard* register because the value must be recreated... Actually here the copy's SOURCE is a0 (hard) and dest v1 (hard, after allocation? no, combine runs before allocation, so these are pseudos; v1/a0 are allocated later).

Right — at combine time these are pseudo registers. So combine sees pseudo->pseudo copy. It merges.

But wait: in the target build, the same compiler with the same passes produced a surviving move. How? Because the target's source had something that made combine not merge — the asm! The launder is an asm that reads/writes the pseudo, so the copy isn't adjacent to the compare... Actually with the launder, the RTL is:
```
iv2c = iVar2
asm("" : "=r"(iv2c) : "0"(iv2c))    ; a real insn (unspec/asm_operands) that reads iVar2 and writes iv2c
one = 1
if (iv2c != one)
```
The asm blocks combine (combine doesn't combine asm_operands).

So the target's move comes from the copy that's *before* the asm; the asm's output is a new pseudo (or the same). Hmm.

Anyway — we need a real-C construct that makes combine not merge the copy into the compare, while emitting the same instructions.

Combine's merging of a copy into a compare: it happens in try_combine for i1 = copy, i3 = compare? The classic combine pattern "reg = reg; ... if (reg)" — combine requires that the intermediate i2's dest is not needed. Let me look at combine.c for the condition that prevents substituting a register that is *live* after.

Key: if iv2c is used LATER (after the compare), combine cannot delete the copy. It would then... combine can still substitute into the compare and keep the copy (but that's not profitable? It doesn't delete an insn, so combine's `added_sets`/cost check may reject).

So: give iv2c a second use after the compare that costs nothing? Impossible without an instruction.

Hmm, unless the second use is in a *dead* code path that flow removes but combine sees... too hacky.

What about making iVar2 not equal to iv2c by making the copy a *widening from a HImode variable that is itself the thing compared*... 

Let me look at this from another angle: how did other shards crack "launder" items where the launder's role was anti-coalescing? moves.md line 23: "launder gone via in-place pv chain; pv pin dropped too". Line 17: reassignment kills the cse sym class.

The "reassignment kills the cse sym class" trick: write the variable twice, so cse can't equate it. For our case:

```
iv2c = iVar2;
iv2c = iv2c;   // dead self-assign — that's a launder (identity statement) — forbidden.
```

What about a real second set: since the compare is `if (iv2c != one) uVar5 = 0;` — what if we restructure to:

```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
What real second set could iv2c have? None.

OK, what about making `one` the variable that gets the copy... Let's see: target `li v0,1` (one) and `move v1,a0`.

Alternative: What if we assign `iv2c = iVar2` where iVar2 is a *parameter-like* value that combine refuses... no.

Let me look at combine.c to see the exact condition for merging a copy into a following compare. Perhaps the copy is merged only because it's `(set (reg) (reg))` with same mode; if the copy were a different mode (e.g., HI→SI with a real sign extend that combine can't fold), it wouldn't merge. Our problem is combine CAN fold it due to known range.

So: make the sign-extend source's range unknown! Where can we get a value equal to iVar2 with unknown high bits? 

What if we change iVar2's type/declaration so GCC doesn't track its range? The range comes from the RTL (andi 0xf + addiu 1). Combine uses `nonzero_bits` on the RTL, not the C type. So it knows regardless of the C declaration.

Unless the sign-extend source is a *memory load*: `lh` from a local? no.

Hmm — what if the copy is `iv2c = (s16)iVar2` where iVar2 has been passed through something opaque... 

Actually wait. What about the reverse: make the sign extend NOT foldable by combine, and accept the extra sll/sra? The target has 56 insns; mine 55. Adding 2 → 57. Unless one of the existing insns disappears.

Hmm.

Let me reconsider: is combine really the pass? Let me check the .combine dump for our function to see the state after combine. If the copy is gone after combine, it's combine.
