---
ts: 2026-10-22T07:04:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_K3YXPJtjaJvQyscUZNKZ
---
cand22 and cand23 have the same diff (the li in the delay slot). cand24 is worse.

So the do-while fixes the move/li order but the li lands in the delay slot.

Now: how to keep the li out of the delay slot? The dbr's backward fill requires... hmm.

Let me think about the dbr's backward fill rule in gcc 2.7 branch.c: In `optimize_insn` (the dbr pass), for a call insn, gcc calls `fill_delay_slot` (forward) — but there's also code in `reorg_branch`/`make_delay_slot`...

Hmm, actually I recall in gcc's branch.c, the function `fill_delay_slot` handles the case where the delay slot is empty: it takes the insn FOLLOWING the branch. If the branch is at the end of the block, it may look backward.

In cand22, the call was at the END of the entry block (the loop body follows in a separate block). Hmm! In the tree, the call is also at the end of the entry block (the chain continues with the lui s1 etc. in the SAME block).

Wait, in cand22 the chain after the jal was: 51 (move s1 = lui) — the same block? The cand22 chain showed (insn 51 232 53 ...) right after the jal sequence — so the lui IS in the same block, after the jal. So the forward insn exists.

Hmm, so why did the dbr prefer the backward fill in cand22?

Maybe: the dbr's forward fill needs the following insn to be a single insn that can be moved into the delay slot. The following insn is the `lui s1` (set s1 = symbol_ref) — that IS a single insn. But it can't be moved into the delay slot? It could (it's just a lui). Hmm, but then the delay slot would hold the lui, not the sw s1. The tree's delay slot holds sw s1.

Hmm, so in the tree the dbr filled the delay slot with the sw s1 — which was inserted by the prologue right before the lui. So the forward fill took the sw s1 (the prologue's save).

In cand22, the sw s1 ended up BEFORE the jal. Why? Because the prologue inserted it before the jal?! Hmm, in cand22 the s1 use (the lui) is after the jal...

OH WAIT. Maybe in cand22 the prologue inserted the sw s1 before the jal because the LOOP restructuring changed which insn "uses" s1 first? Hmm.

Hmm, alternatively: in cand22, the dbr's forward fill took the sw s1 into the delay slot, and then... no, the sw s1 is before the jal in cand22's chain.

You know what? Let me look at the cand22 .sched2 dump chain (final) and compare with the tree's .sched2 chain, to see where the sw s1 is in each.

Actually, the .dbr dump IS the final-ish state (after dbr). The cand22 .dbr shows sw s1 before the jal, li in the delay slot. The tree's .dbr shows the li before sw ra, sw s1 in the delay slot.

Let me look at the pre-dbr state for cand22: the .sched dump chain for cand22 was: [4 (move s2,a0), 6 (move s4,a1), 15 (move s0,a2), 31 (li), 33 (call)] + notes. The prologue then inserted: addiu sp, sw s2 (before move s2,a0), sw s4, sw s0, sw ra, sw s3 (before the call), sw s1 (before the lui s1 — after the call).

So the pre-dbr chain (with prologue) = [addiu, sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, li, sw ra, sw s3, jal, sw s1, lui s1, ...].

The dbr then: the forward insn after the jal is sw s1 → fill the delay slot with it → [.., jal, sw s1(delay), lui s1]. But cand22's final shows sw s1 BEFORE the jal and li IN the delay slot. So the dbr did something different: it moved the li into the delay slot and left sw s1 before the jal?! That means the dbr's backward fill took the li and the sw s1... hmm, but then the sw s1 would still be after the jal (in the chain) — unless the dbr's backward fill ALSO moved the sw s1...

Hmm, actually maybe what happened: the dbr's backward fill moved the li INTO the delay slot (moving it later, past the jal). Then the sw s1 (which was after the jal) — the chain becomes [.., sw ra, sw s3, jal, sw s1, lui...] with the li moved into the delay slot. But the final shows sw s1 BEFORE the jal.

Hmm, unless the sw s1 was inserted by the prologue BEFORE the jal in cand22 (because the prologue pass ran after the dbr? or the dbr ran before the prologue?).

The .dbr dump shows PROLOGUE_END note → the prologue ran before the dbr. Hmm.

Wait, maybe the prologue inserted sw s1 before the jal because of the "first use" rule: in cand22, is there an earlier use of s1? The `jal` — no. Hmm, the loop? no.

Hmm, whatever the cause, the empirical question is: how do I get the sw s1 into the delay slot and the li before the sw ra?

The target: [.., move s0,a2, ASM, li, sw ra, sw s3, jal, sw s1(delay)].
cand22: [.., move s0,a2, sw ra, sw s3, sw s1, jal, li(delay)].

So in the target, the sw s1 is AFTER the jal (in the delay slot) and the li is before the sw ra.

Difference: in the tree, the ASM insn sits between the move and the li. In cand22, nothing.

**So the ASM's presence is what makes the li NOT adjacent to the call** — wait, in the tree the li IS adjacent to the call (chain: 20 (li) → 22 (call))! Hmm, but the PROLOGUE inserted sw ra and sw s3 between them! Why? Because the prologue inserts the saves right before the insn that uses them: ra is used by the call → sw ra before the call ✓; s3 is defined after the call (move s3,v0) → hmm, the sw s3 is before the call too.

So in the tree, the prologue put sw ra and sw s3 between the li and the call. That's why the li is not adjacent to the call in the final chain → the dbr's backward fill (which takes the immediately preceding insn = sw s3) didn't take the li.

And in cand22, the prologue put sw ra, sw s3, AND sw s1 before the call?! Hmm, why would sw s1 be before the call?

Hmm, maybe in cand22 the prologue's sw s1 was inserted before the jal because the jal's *sequence* contains...

You know what? Let me look at the .sched2 dump for cand22 to see the final chain, and also check whether the sw s1 in cand22 is before the jal because the dbr moved it there (the dbr's "backward fill" might have moved the sw s1 from after the call into the delay slot... no, the sw s1 is before the jal).

Alternatively the dbr might have done a "backward reorg" that moved the sw s1 before the jal and put the li in the delay slot.

Whatever. Practical approach: the target's structure requires an RTL insn between the move s0,a2 and the li. Since the prologue then inserts sw ra/sw s3 between the li and the call, the dbr's backward candidate becomes sw s3 (not the li) → the forward fill (sw s1) wins ✓.

So the ASM's role is just to occupy a slot between the move and the li.

Hmm, but why does that matter? In cand22, the chain (pre-prologue) is [move s2,a0, move s4,a1, move s0,a2, li, call]. The prologue inserts sw ra and sw s3 before the call → [.., move s0,a2, li, sw ra, sw s3, call] — the li is NOT adjacent to the call! So the dbr's backward candidate is sw s3, not the li. Then why did the dbr take the li into the delay slot?!

Unless the prologue inserted sw ra/sw s3 AFTER the dbr... i.e. the dbr ran BEFORE the prologue. But the .dbr dump shows the prologue's saves... The .dbr dump = the RTL after the "dbr" pass; if the prologue ran after the dbr, the dump wouldn't show the saves. It does show them (sw s2, sw s4, sw s0, sw ra, sw s3) → the prologue ran before the dbr.

Hmm, so in cand22, before the dbr, the chain was [.., move s0,a2, li, sw ra, sw s3, call, sw s1, lui...]. The dbr's backward fill candidate = sw s3 (immediately before the call). It can't take the li (2 insns away). So how did the li get into the delay slot?!

Unless the dbr's forward fill took sw s1 (the insn right after the call) — but the observed delay slot holds the li, not sw s1. And sw s1 appears BEFORE the jal in cand22.

I'm clearly misreading the chain. Let me print cand22's full .dbr entry block chain with the instruction meanings, to see exactly.

Actually, let me look at cand22's .sched2 (the final RTL) — simpler: the final assembly of cand22 was:
addiu sp; sw s2; move s2,a0; sw s4; move s4,a1; sw s0; move s0,a2; sw ra; sw s3; sw s1; jal; li a0,16(delay); lui s1; addiu s1...

So the delay slot = li, and sw s1 is before the jal. And the lui s1/addiu s1 come after the jal.

So the chain (final): [addiu sp, sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, sw ra, sw s3, sw s1, jal+li, lui s1, addiu s1, ...].

Interesting: the sw s1 was moved BEFORE the jal (from after it) — that's the dbr's "backward reorg" moving the sw s1 (the forward insn) backward past the jal? That doesn't happen normally.

Hmm, alternatively: the prologue inserted the sw s1 before the jal because in cand22's pre-prologue chain, the first use of s1 was...

OK. Honest assessment: I've spent 50 minutes on this item and I'm not converging. The mechanism is deep in gcc's dbr/reorg/prologue interaction.

DECISION: Let me do a final targeted attempt with a different idea, then move on.

**FINAL IDEA for item 3**: The tree's chain has the ASM between the move and the li. What if we get an insn there by using a *second copy of the value* that the local-alloc coalesces away but which survives until sched1 — e.g. the "copy then accumulate" pattern (C0458):

```
s32 t;
t = arg2;        /* copy: pseudo t born here */
rgb = t;          /* copy: pseudo 16 born here */
```
cand10 tested exactly this (with braces) → score 2, same as cand01. Hmm, so no.

**IDEA: use the `tag0` pin!** The tree has 2 pins: rgb→$16, tag0→$4. tag0 is assigned inside the if-block: `tag0 = *(u32 *)temp_v0;`. Hmm, the tree's target has `move a0,s1` hmm, tag0's use: `*(u32 *)temp_v0 = (tag0 & 0xFF000000) | ...`.

Not relevant to the entry block.

**IDEA: What if we change the ORDER of the C statements so that the call to func_80010A08 is NOT the second statement?** E.g., move the `*(u8 *)((u8 *)temp_v0 + 3) = 3;` before the call? Can't (temp_v0 comes from the call).

**IDEA: What if we call func_80010A08 twice?** No.

**IDEA: What if the do-while is placed between the move and the call but the loop body is empty, so the chain has the LOOP notes (not insns) between?** That's cand03 (empty do-while, score 4). Let me look at cand03's diff — maybe it's closer than cand22!

cand03 = `rgb = arg2; do { } while (0);` → score 4. Let me see its diff.

Let me check it quickly, then decide.
