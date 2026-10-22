---
ts: 2026-10-22T06:59:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_n1kVhSBP0ct3NlLK4ofd
---
cand22's chain: addiu sp; sw s2; move s2,a0; sw s4; move s4,a1; sw s0; move s0,a2; sw ra; sw s3; sw s1; jal; li a0,16(delay).

Target: addiu sp; sw s2; move s2,a0; sw s4; move s4,a1; sw s0; move s0,a2; li a0,16; sw ra; sw s3; jal; sw s1(delay).

So the target's chain has the li between the move s0,a2 and sw ra, and the delay slot holds sw s1. cand22 has the li in the delay slot and sw s1 before the jal.

So the difference between tree and cand22 is just the position of the li among the prologue saves: the target has it right after the move s0,a2 (position 7), cand22 has it in the delay slot (position 11).

So: the li must be launched EARLY (so it lands late in the chain?) hmm. Let me recompute: chain = reverse of launch order. Target chain: [..., move s0,a2, li, sw ra, sw s3, jal, sw s1]. So the launch order (reverse): sw s1 first, jal, sw s3, sw ra, li, move s0,a2, ... So the li is launched AFTER sw ra and sw s3 (i.e., later in launch order → earlier in chain ✓).

In cand22's chain: [..., move s0,a2, sw ra, sw s3, sw s1, jal, li] → launch order: li first, then jal, sw s1, sw s3, sw ra, move s0,a2. So the li was launched EARLIEST (before sw ra/sw s3) → it lands last in the chain → the delay slot.

So in the target, the li is launched LATE (after sw ra/sw s3) → lands early in the chain.

Now, in cand01 (no do-while): chain [.., move s4,a1, li, sw s0, move s0,a2, sw ra, sw s3, jal, sw s1] → launch order: sw s1, jal, sw s3, sw ra, move s0,a2, sw s0, li, ... → the li was launched quite early (before sw s0/move s0,a2) → lands late in the chain.

So the li's launch position varies: in the target it's launched after sw ra/sw s3; in cand01 before move s0,a2; in cand22 first.

The ready list tie-break: at each step, among ready insns, the one with the highest priority wins; ties broken by... in gcc's sched1, the ready list is sorted by priority, and for equal priority, by the "UID" order? Actually sched1's ready list is a linked list sorted by priority; new insns are inserted at the front if the priority is >= the current front? In gcc's sched1, `ready` is sorted descending by priority, and for equal priorities, the most recently added goes first? Hmm, gcc's sched1 uses `insert_to_ready_list` which inserts before insns with LOWER priority, i.e., equal priority → inserted after existing ones? Let me recall:

```
static void
insert_to_ready_list (insn_t insn)
{
  ...
  if (!ready) { ready = insn; ... }
  else if (priority (insn) >= priority (ready)) { /* insert at front */ }
  else { /* insert after all with >= priority */ }
}
```
I believe gcc's sched1 inserts an insn at the FRONT of the ready list if its priority >= the front's priority. So for equal priorities, the LAST inserted goes first → the ready list order is reverse insertion order for ties.

And the initial ready list is built by scanning the block's insns in order → so the first-inserted ends up LAST. So for equal priority, the LATER insn in the block (higher UID) is launched first.

In the target, the li (UID 20) vs the prologue saves (sw ra, sw s3 — what UIDs?). The prologue pass creates the saves late → high UIDs. So the saves (high UID) are launched before the li → they land later in the chain → chain: li, sw ra, sw s3 ✓ (the target!). And the li is launched before move s0,a2 (UID 15, lower) ✓ → chain: move s0,a2 before li ✓.

So the target's chain is fully explained by UID ordering with NO boost:
- launch order (descending UID among equal priority): the saves (high UID) first, then the li (UID 20), then the move s0,a2 (UID 15), then the earlier ones.

Chain (reverse): ..., move s0,a2 (15), li (20), saves, jal, ...

Hmm, but the target's chain has the li AFTER move s0,a2 ✓ and BEFORE sw ra ✓ — consistent with descending-UID launch order: saves (UID ~40+, launched 1st) → land LAST in chain; li (20) → next; move (15) → next; ... and the jal (22) → hmm, the jal's UID is 22 > 20, so the jal would be launched before the li → the jal lands after the li in the chain ✓ (the jal is after the li in the target ✓).

OK! So the target = plain UID ordering, no boost effect at all (the asm's 2nd set killed the boost, but even with the boost the UID ordering would... hmm, no: with the boost, the move is launched EARLIER than the li (boost wins over UID) → the move lands after the li ✗).

In cand01: the move (15) got the boost → launched before the li (20) → lands after the li ✗ (that's the bug).

In cand22: the li was launched first (before the saves!) → the do-while changed the block structure/UIDs. Hmm, why would the li be launched first? If the li had a boost?? Hmm, or if the do-while made the li's UID higher than the saves'... no, the do-while is at the top.

Hmm, whatever: in cand22 the li landed in the delay slot, which is a different problem.

So the ideal: kill the boost on the move (so the move launches after the li → lands before it ✓) WITHOUT disturbing the rest.

cand22 did kill the boost but also moved the li's launch position to the front. Hmm, why? Maybe because the do-while made the entry block split into two blocks (the loop body is a separate block), and the scheduler handles them separately: the loop body block is scheduled first (it's the "inner" block), then the rest.

Hmm! In cand22 the chain shows the do-while has NO instructions (a self-copy) but the block structure changed.

What if I use a do-while that doesn't split the block... e.g., `do { rgb = rgb; } while (0);` — the loop body is a separate block regardless.

Hmm. What if the 2nd set is created by a do-while placed LATER (e.g. at the end of the function)? cand25 (`do { rgb = rgb; } while (0);` at the end) gave score 2 — the same as cand01 (no improvement). So the do-while at the end didn't kill the boost (because the self-copy inside the loop was folded/removed since rgb's value doesn't change? or because the loop is in a different block and the copy was deleted).

Hmm, cand25 = score 2 = same as cand01 → the boost wasn't killed.

So cand22's do-while right after `rgb = arg2;` DID kill the boost. But it also messed up the li's placement.

Let me try more variants around cand22:
cand29: `do { rgb = arg2; } while (0);` (cand24 = score 8).
cand30: `do { rgb = (s32)rgb; } while (0);` (cand23 = score 4).
cand31: `do { rgb = rgb; } while (0);` but placed before the `rgb = arg2;`?
cand32: `for (;;) { rgb = rgb; break; }` — a loop with a break.
cand33: `do { if (arg2) { rgb = rgb; } } while (0);` — hmm, adds a branch.

Let me look at cand23's diff (score 4) and cand03's diff (score 4) to see the pattern.

Actually, let me think about what's needed: the li must land at chain position 7 (right after move s0,a2) and the jal at 10 with sw s1 in the delay slot.

In cand22, the li landed in the delay slot (position 11). What if the do-while's copy in the block causes the *delay-slot fill* to choose the li? The dbr pass fills the delay slot with the preceding insn if it's safe. In cand22 the insn preceding the jal was the li → filled. In the tree, the insn preceding the jal was sw s3 → filled with sw s3? But the target's delay slot has sw s1! Hmm, so the target's delay slot was filled by sw s1 (a prologue save) from the OTHER direction.

In the tree's chain: [.., li, sw ra, sw s3, jal, sw s1] — the delay slot holds sw s1, which comes AFTER the jal in the chain (i.e., it's from the "forward" part of the block). So the dbr pass filled the delay slot from the insn following the jal.

In cand22: [.., sw ra, sw s3, sw s1, jal, li] — the delay slot holds the li (the preceding insn).

Hmm, so in cand22 the dbr chose the backward fill (the li) while in the tree it chose the forward fill (sw s1).

The dbr (delayed branch) pass: it first tries to fill the delay slot by moving the FOLLOWING insn into the delay slot? No — the standard MIPS dbr pass: for a branch, the delay slot is filled by the insn that FOLLOWS the branch (if it can be moved) — no wait. On MIPS, the delay slot instruction executes before the branch takes effect. The instruction AFTER the branch in program order executes AFTER the branch completes... so it can't be moved into the delay slot (it would execute too early). Hmm, actually the standard MIPS convention: `jal func; sw $ra, 8($sp)` — the sw is in the delay slot and executes before the call. So the instruction AFTER the jal in the listing is the delay slot insn, which was moved from later in the block.

GCC's dbr pass: "fill the delay slot" — it moves an insn from AFTER the branch into the delay slot (if safe), or leaves a nop. Also "reorg" may steal an insn from BEFORE the branch into the delay slot ("delay slot fill" from the backward direction).

In the tree: the delay slot holds sw s1 (from after the jal) ✓ standard.
In cand22: the delay slot holds the li (from before the jal) — that's the "backward" fill, which the dbr pass does when it can't move the following insn? Hmm, the dbr pass's "fill" prefers the forward insn; the backward "steal" is done by `reorg` (dbr's "delay slot fill" backwards is done in dbr's optimize_insns: it can move the preceding insn into the delay slot if the branch is a "jump" etc.).

Hmm. In cand22, the chain before the jal is [sw ra, sw s3, sw s1] — the insn immediately before the jal is sw s1, and the delay slot holds the li. So the dbr moved the FORWARD insn (sw s1) BEFORE the jal and put the li in the delay slot? That doesn't make sense either.

Hmm, actually, wait: in cand22's chain the sw s1 appears before the jal (position 9) and the li in the delay slot (position 11). In the tree, sw s1 is in the delay slot (position 11) and there's no sw s1 before the jal.

So in cand22, the dbr pass filled the delay slot with the li (backward fill) and moved sw s1 before the jal. In the tree, it filled with sw s1 (forward fill).

The dbr pass's rule: for a `jal`, the delay slot can be filled with the following insn if it's safe (not a branch, etc.). Both cases have sw s1 available after. Hmm, so why the difference?

Maybe because in cand22 the li was adjacent to the jal (in the pre-dbr chain) and the dbr's backward fill grabbed it (dbr's fill_insn prefers... hmm).

Honestly, the difference might be: in the tree, the ASM insn is between the move and the li, so the li isn't adjacent to the jal; the dbr's backward fill (which can only take the immediately preceding insn) couldn't take the li (2 insns away: sw ra, sw s3 are between... wait no, in the tree the li is BEFORE sw ra and sw s3, so the insn immediately before the jal is sw s3).

So in the tree, the dbr's backward fill would take sw s3 — but it took sw s1 (forward) instead. Hmm, maybe because sw s3 is a store to the stack and the dbr prefers... whatever.

In cand22, the insn immediately before the jal was sw s1 — and the dbr moved sw s1 before the jal?? and put the li in the delay slot? That's weird.

Hmm, hold on. Maybe the pre-dbr chain in cand22 was [.., li, sw ra, sw s3, sw s1, jal] and the dbr filled the delay slot with the li?? No, the li isn't adjacent.

I'm over-analyzing. Let me get empirical: try variants of cand22 with a slightly different structure and see if any gives 0. E.g.:

cand29: `do { rgb = rgb; } while (0);` + change the store order? no.
cand30: `do { rgb = (s32)rgb; } while (0);` (cand23 = 4)
cand31: `do { rgb = arg2; } while (0);` (cand24 = 8)
cand32: `do { rgb = rgb; } while (0);` with the do-while placed AFTER the call but before the store?

Let me look at cand23's and cand03's diffs to see how the li/jal relate. Let me dump cand23's disassembly.

Actually, let me reconsider the whole approach. This is one of 5 items and I've spent ~25 min on it. The shard has 5 items and I should manage time. Let me set a budget: continue on this item until ~40 min total, then decide.

Hmm, but the brief says 20-30 min per item and a WALL needs ≥30 scored tries. We've done ~24 tries so far (9+9+7 = 25 scored). Let me count: batch1: cand01-cand09 = 9; batch2: cand10-cand18 = 9; batch3: cand22-cand28 = 7. Total 25 scored tries.

Time: started 00:31, now ~01:05. 34 minutes on item 3 (including setup). Hmm.

Let me think about which lever is most promising and test a focused batch.

Key insight so far: the boost on the move (pseudo 16's birth) must be killed, AND the li must land right after the move (chain position 7) with sw ra/sw s3 between the li and the jal.

The tree's chain: [sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, ASM, li, sw ra, sw s3, jal, sw s1].

Note: the ASM is between the move and the li! So the ASM occupies the slot right after the move. If our do-while trick (cand22) produced a no-op in that slot, the chain would be [.., move s0,a2, <nothing>, li, sw ra, sw s3, jal, sw s1] — exactly the target!

But cand22 gave [.., move s0,a2, sw ra, sw s3, sw s1, jal, li]. So the li moved to the end.

Why? Because the boost kill changed the launch order globally? Hmm.

Wait. In cand22, is the boost actually killed? Let me verify with a dump: check whether insn 15 (the move) has the 7f000001 boost in cand22's .sched trace. If the boost is still there, then the difference is elsewhere.

Let me do that dump — it's cheap and decisive.

Let me build t_cand22.c and dump it.
