---
ts: 2026-10-22T06:58:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VRqb2TdlSNaHENL1XapJ
---
cand22: mine = [..., 7 ?, 8 ?, 9 ?, 10 jal, 11 li a0,16] — the li is in the jal's delay slot. The target has li a0,16 at 7 and the jal at 10.

So with the do-while, the move s0,a2 is now correctly before the li (the boost is killed!) — but the li moved into the delay slot (the dbr pass filled the delay slot with the li).

So now I need to prevent the dbr delay-slot fill. In the target, the li is NOT in the delay slot: the target's chain is [.., sw s0, move s0,a2, li a0,16, sw ra, sw s3, jal, sw s1(delay)]. Between the li and the jal there are 2 insns (sw ra, sw s3) — so the backward scan can't reach the li.

In cand22, the li ended up adjacent to the jal → the dbr fill moved it into the delay slot.

So the do-while changed the block's scheduling so that the li ended up right before the jal.

Hmm. Why? Because the do-while created a loop note → the block was split? Or because the ready-list order changed.

Hmm. So both aspects are scheduler/dbr-driven.

Let's look at the tree's structure again: the tree's chain in the entry block: [sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, ASM, li a0,16, sw ra, sw s3, jal, sw s1(delay)]. So the li is 3 insns before the jal.

In cand22: [sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, ?, ?, jal, li(delay)]. So the li is right before the jal.

The difference: in the tree, the li is scheduled EARLIER (before sw ra/sw s3). Since the chain = reverse launch order, "earlier in chain" = "later in launch order". So in the tree, the li was launched AFTER sw ra and sw s3, while in cand22 it was launched BEFORE them.

Hmm, why? The li (set a0=16) has no deps. The sw ra/sw s3 (prologue saves) are also independent. Their relative order is by LUID tie-break (higher UID first in the ready list?).

In the tree, the li (UID 20) vs sw ra/sw s3 (UIDs ~?, the prologue saves are usually high UIDs since they're added by the prologue pass later).

Ugh.

OK, alternative approach to the delay-slot problem: prevent the dbr pass from filling the delay slot with the li. The dbr fill moves an insn into the delay slot if it's "safe". For the li (set a0=16) before a jal, moving it into the delay slot is legal (the jal's args are set before the delay slot executes... wait, NO! On MIPS, the jal's delay slot executes BEFORE the call target. So `li a0,16` in the delay slot would execute after the branch is taken?? No — the delay slot instruction executes BEFORE the branch transfers control. So `li a0,16` in the delay slot of `jal` executes before the call → correct.

But gcc's dbr pass has a rule: it won't fill the delay slot with an instruction that sets a register used by the branch itself? Here a0 is an argument — fine.

Hmm, but why doesn't the tree fill it? Because in the tree there are 2 insns (sw ra, sw s3) between the li and the jal — the backward scan only looks at the immediately preceding insn.

So the question becomes: why in cand22 does the li end up immediately before the jal, while in the tree it doesn't?

Because in the tree, the ASM insn is between the move and the li, and the ASM... hmm, the asm is BEFORE the li, so it doesn't separate the li from the jal.

The separation in the tree comes from sw ra and sw s3 being scheduled between the li and the jal.

In cand22, those two insns got scheduled elsewhere (before the li).

Chain cand22 (reconstructed): [sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, X, Y, jal, li]. Hmm, positions 5,6 = sw s0, move s0,a2; 7,8,9 = ? (the diff says mine[7:7] insert target[7:8] li and mine[9:9] insert target[10:11] jal). Let me get the actual disassembly of cand22 to see.

Let me disassemble cand22's object.

Actually, let me think about it more cleverly. The two problems:
(A) the move's position relative to the li (needs the boost killed) — do-while works.
(B) the li's position relative to the jal (needs the li NOT adjacent) — currently broken.

For (B): in the tree, between the li and the jal there are sw ra and sw s3. In cand22 they're not there.

Hmm, maybe the do-while's loop note changed the block splitting, so the prologue saves ended up elsewhere.

Alternative idea for (A) that doesn't disturb the block: what if the second set is created WITHOUT a loop construct? E.g., the "copy then accumulate" pattern: `rgb = arg2;` then `rgb2 = rgb; rgb2 += 0;`? Hmm, that gives rgb2 2 sets (a copy and an RMW) but rgb still 1 set.

Hmm, what we need is for the PSEUDO 16 to have 2 sets. What if the pseudo that is boosted is not 16 but the copy source? Hmm.

Wait a moment. Let me reconsider: in cand22, was the boost actually killed? The move s0,a2 is at position 6 and the li at 11 → the move is before the li ✓ (as in the tree). So yes, the boost was killed (or the block structure changed).

Let me now think about what the do-while does: `do { rgb = rgb; } while (0);` — the self-copy inside the loop. gcc's loop.c: the loop is unrolled/removed? The RTL might keep a copy insn inside the loop body. Since the value is the same, cse might merge it with the outer copy → but the loop's insn is in a different "region" so cse (which is per-block) doesn't merge across blocks; but the loop body is a separate block → cse doesn't merge → the copy survives as a SET of pseudo 16 (no instruction? a copy `set $16, $16`... hmm, at RTL level it's `set pseudo16, pseudo16` → gcc's cse2/reload might delete it as a self-copy).

Anyway it survived as a second set (no extra instruction since it's a self-copy that got deleted later but the set count was computed earlier?). Hmm, reg_n_sets is computed in `regset`/`allocate` — the "reg_n_sets" is updated by the `set` count in the RTL... it's computed by `mark_reg_uses`/`mark_reg_sets` which walk the RTL at the time of the pass. If the self-copy was deleted before sched1, then no 2nd set. But empirically, the boost WAS killed → the 2nd set existed at sched1 time.

Hmm, but was the boost killed, or did something else change? Let me verify by dumping cand22's .sched trace and checking insn 15's priority. That's a solid diagnostic. Let me do it: build t_cand22.c and dump.

Actually, let's think about the bigger picture: maybe I should look for a lever that kills the boost WITHOUT changing the block structure. Candidates for "2nd set without a loop":
- The copy inside a loop (do-while) — changes block structure.
- An asm (not allowed).
- A volatile (a barrier lever).

Hmm, what about the second set coming from a *different function's* code? No.

What about: `rgb = arg2;` and then, later in the function, ANOTHER assignment to rgb that is used → e.g. the store uses rgb, and we could add `rgb = arg2;` right before the store → 2 sets, 2 moves (one extra insn) → no.

BUT: what if the second assignment is placed such that gcc's local-alloc coalesces the two copies? The two copies are both `set $16, a2`-ish. If they're in different blocks, the second is a real move.

Hmm, 99 ins is fixed.

OK, let me consider the reverse: instead of killing the boost on pseudo 16, what if we make the LI get boosted (so it launches earlier → lands later in the chain → hmm, we want the li to land EARLIER in the chain = launched LATER).

We want the li to be launched LATE (so it lands early in the chain, before the move). Currently (cand01) the li was launched at T-22 (late) → chain position 5 (early). Hmm wait, that contradicts: cand01's chain = [.., li(18), move(15), call(20)] → the li is BEFORE the move in the chain, meaning the li was launched AFTER the move. Hmm! So in cand01, the li IS in the right relative position vs the move?!

Hold on. cand01's chain: 4 (move s2,a0), 6 (move s4,a1), 18 (li), 15 (move s0,a2), 20 (call). The target's chain: 4, 6, 15 (move s0,a2), 17 (asm), 20 (li), 22 (call).

So in cand01, the li comes BEFORE the move s0,a2 in the chain; in the target, AFTER. And the assembly confirms (cand: li at 5, move at 7; target: move at 6, li at 7).

I earlier had this backwards. Let me redo: in the cand, the li is EARLIER in the chain; in the tree, LATER. Since chain = reverse of launch order: in the cand, the li was launched LATER than the move; in the tree, EARLIER.

So the boost (which makes the move launch early) → the move lands late in the chain → li lands early ✓ consistent with my earlier statement: cand's move lands after the li.

OK so to fix: the move must launch LATE → no boost → 2 sets. Consistent.

And in cand22 (do-while): the chain must be [.., move s0,a2, ..., li, ..., jal]? Let me get cand22's actual disassembly to see the full picture. The diff said: mine[7] missing the target's li at 7; mine[9] missing the target's jal at 10; mine[10:12] = jal, li.

So mine: [1-9: prologue etc.], 10 jal, 11 li a0,16 (delay slot). And the target: 5 sw s0, 6 move s0,a2, 7 li a0,16, 8 sw ra, 9 sw s3, 10 jal.

So in cand22 the li is in the delay slot, and the target has it 3 before the jal.

So cand22 fixed the move/li order but broke the li/jal distance.

Interesting. In cand22, what are insns 7,8,9? Probably sw ra, sw s3, and something. And the jal at 10 with the li in the delay slot.

Hmm! Wait: if the li is in the delay slot, then the jal is at 10 in both. And the target's li is at 7 while mine's is at 11 (delay slot). So the difference is just where the li sits: the target has it 3 slots before the jal; mine has it in the delay slot.

So the dbr fill moved it. To prevent the dbr fill, the li must not be the immediately preceding insn of the jal.

Hmm, so in cand22 the li ended up right before the jal (in the chain), and the dbr pass moved it into the delay slot.

In the tree, the li is 3 before the jal.

Why is the li adjacent to the jal in cand22? Because of scheduling.

Hmm, what if we add a dummy statement to keep the li away from the jal? E.g., a statement between the call and ... no, the li is created by reload for the call's arg.

Hmm, alternatively: what if the call is preceded by another instruction that's not the li? In the tree, sw ra and sw s3 are between. Those are prologue saves. In cand22 they got scheduled before the li.

So the scheduling difference: in the tree, [sw ra, sw s3] are between the li and the jal; in cand22, they're before the li.

The ready-list tie-break is by LUID: the li's UID vs the prologue saves' UIDs. In the tree, the li (UID 20) has a LOWER UID than the prologue saves → so in the ready list the higher UID (prologue saves) is preferred → they're launched earlier → they land LATER in the chain?! Hmm: launched earlier = later in chain. But the tree has the prologue saves AFTER the li in the chain (sw ra at 8, li at 7) → so the prologue saves land later → launched earlier ✓. So in the tree, the prologue saves are launched BEFORE the li (because they have higher UIDs and equal priority, the ready list picks the highest UID first).

In cand22, the prologue saves land BEFORE the li in the chain → launched AFTER the li. So the ready-list order differed: the li was preferred over the prologue saves.

Why? Because of the do-while! The do-while might have changed the UIDs or the block structure.

Hmm, in cand22 the chain is: [sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, X, Y, Z, jal, li]. Hmm, I need the actual disassembly.

Let me dump cand22's assembly.

Let me use --keep and objdump.
