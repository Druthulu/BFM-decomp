---
ts: 2026-10-22T07:01:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_uSumrCV8Yj3iFsqiFEP1
---
Very interesting! The .dbr dump is the RTL AFTER the prologue pass (it includes the prologue's addiu sp and the saves).

TREE's chain: addiu sp(203), sw s2(211), move s2,a0(4), sw s4(207), move s4,a1(6), sw s0(215), move s0,a2(15), ASM(17), li a0,16(20), sw ra(205), sw s3(209), jal(217 = sequence), ...

C22's chain: addiu sp(216), sw s2(224), move s2,a0(4), sw s4(220), move s4,a1(6), sw s0(228), move s0,a2(15), sw ra(218), sw s3(222), sw s1(226), jal(232 = sequence)...

And where's cand22's li a0,16? In cand22's chain, insn 31 (the li) should be before the jal. Hmm, I see "(insn 232 229 51 (sequence[" = the jal. The li (31) isn't visible in this excerpt — it must be inside the sequence (232) as the delay slot! Yes: the dbr moved the li into the delay slot of the jal sequence.

TREE's jal sequence (217) probably contains sw s1 in the delay slot.

So confirmed: the dbr pass put the li into the delay slot in cand22 but not in the tree.

In the tree, the ASM (17) is between the move (15) and the li (20). So the li is preceded by the ASM. In cand22, the li (31) is preceded by the move (15) (with loop notes).

So the dbr's backward fill took the li in cand22 but not in the tree. Why? The dbr's backward fill ("fill_delay_slot" with a preceding insn) — in gcc's dbr (branch.c), the "backward" fill happens in `reorg_branch`/`optimize_insn`: it can move the insn BEFORE the branch into the delay slot if the branch is a "jump" style (i.e., there's no fallthrough or the fallthrough is empty).

The key: `sequence` — the jal became a sequence with the delay slot insn.

In the tree, the backward candidate (the ASM) is not movable → the dbr used the forward fill (sw s1).

In cand22, the backward candidate was the li (movable) → the dbr used the backward fill.

Hmm, why would the dbr prefer the backward fill in cand22 but not in the tree? Because in the tree the backward candidate (the ASM) is not movable, so it fell back to the forward fill.

So: to reproduce the target, we need an RTL insn between the move and the li that is NOT movable into a delay slot. In the tree that's the ASM (an asm insn is never moved into a delay slot).

In plain C, what insn is not movable into a delay slot?
- A call/branch.
- An insn with a volatile memory operation (mem/v) — the dbr won't move a volatile op into the delay slot? Hmm, actually volatile insns CAN be in a delay slot (they execute once).
- An insn that has a "slow" operation.

Hmm! But what about the *order*: the li is created by reload right before the call. The insn before the li is whatever precedes the call in the chain. In the tree, the chain is [move, ASM, li, call] — so the ASM was BEFORE the li in the chain even though the li was created by reload. Interesting: reload inserted the li before the call, but the ASM was already there.

So in cand22, the chain is [move, li, call] — nothing between.

To get something between the move and the li, we need an insn that sched1 places between them. Hmm.

But hold on: in the TREE, the ASM's presence between the move and the li is what makes the li NOT adjacent to the move. In cand22 the li is adjacent to the move.

But the dbr's issue is about the li's adjacency to the CALL (the li is immediately before the call in BOTH). So in the tree, the backward-fill candidate for the call's delay slot is the li — and it wasn't stolen! Hmm, so my theory is wrong.

Let me look at the tree's jal sequence (insn 217) to see what's in the delay slot, and the cand22's (insn 232).

Let me print those.
