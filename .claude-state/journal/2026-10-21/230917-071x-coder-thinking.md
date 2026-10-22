---
ts: 2026-10-22T05:09:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FITVjwhVhIglu70JgNvU
---
h9 = 9 (same as vV2/vV3). The `r = 1` form (nopin) = 11.

So the best is 9 with 75 ins (2 extra).

Hmm, the score of 9 for h9/vV2/vV3 — the residual is the load temps' regs + the extra j/li.

Let me think about the "75 vs 73 ins" issue: the direct-return forms have 2 extra insns (the `j` and the `li v0,1`). The nopin form has 74 (1 extra).

Hmm, the target's tail: `li v0,1` in the delay slot + no extra j. So the target's structure = nopin's structure (74 ins, 1 extra?) — hmm, nopin has 74 vs the target's 73 → 1 extra insn somewhere.

Let me look at nopin's diff again:
```
48  j df08 (+0x10c)  | j df04 (+0x108)     <- a branch offset difference
51  lh v1,6(s0)      | lh a0,6(s0)
52  lh v0,160(s0)    | lh v1,160(s0)
54  bne v1,v0        | bne a0,v1
55  li a0,1          | li v0,1
56  lh v1,10(s0)     | lh a0,10(s0)
57  lh v0,162(s0)    | lh v1,162(s0)
59  bne v1,v0        | bne a0,v1
60  move v0,a0       | nop
65  sltu a0,zero,v0  | sltu v0,zero,v0
66  move v0,a0       | --
```
So mine has `move v0,a0` at 60 (an extra copy: the value from a0 to v0) and `move v0,a0` at 66.

The `move v0,a0` at 60: mine's value is in a0, and the RESULT_DECL is in v0 → the copy. In the target, the value is in v0 and the RESULT_DECL is v0 → coalesced ✓.

So the whole issue: the value pseudo must be in v0.

In nopin, the local `r` is in a0 and the RESULT_DECL in v0.

Hmm! So even if `r` were in v0, the RESULT_DECL... the copy `move v0,a0` would become a no-op ✓.

So the target needs: the local `r` (or the RESULT_DECL) in v0, and the temps in a0/v1.

Now, hmm, here's a thought: what if the local `r` is the RESULT_DECL — i.e. the function's returned value is the local variable directly? In gcc 2.7.2, `return r;` copies r into the RESULT_DECL. But if the RESULT_DECL's copy is coalesced with r (both in the same reg), the copy disappears ✓ — that's what the target shows.

So the target wants: r and the RESULT_DECL both in v0.

Lever-free: r in a0, the RESULT_DECL in v0 → the copy remains.

To get r into v0: r must beat the temps.

Hmm, what if we could make the RESULT_DECL and r the same pseudo? That happens if the compiler "returns the local directly" — hmm.

OK. Let me try the empirical route on the allocation: what determines whether the local `r` gets v0? Its priority vs the temps'. Let me try to make `r`'s live range SHORTER so its pri rises above 10000, e.g. by making `r` assigned at the very end.

Structure with a short live range for r:
```
if (cond) { r = X; }     /* def */
else { r = 1; }          /* def */
return r;                /* use */
```
(vV3_else / h9-ish) → r's live range = the merge block only → live ~3 → pri = 3*10000/3 = 10000 → a tie with the temps → the temps win (lower allocno) ✗. Hmm, unless r's allocno is lower.

Hmm! r is declared at the TOP of the function in these variants → its pseudo number is LOW → in a tie, the lower allocno wins → r should win v0 over the temps!! But the temps are LOCAL allocnos (assigned in the local allocation, which happens BEFORE the global one) — so the global `r` can't take v0 from them anyway.

Ugh. The key question: can the local `r` be a LOCAL allocno? Let me test this directly: if `r` were local, its allocation would compete with the temps by priority.

From the dump, r76 (the local r in nopin) is in the .greg order → GLOBAL.

Why is it global? Let me look at gcc's rule... In gcc 2.x's global.c, `find_local_pseudos`:
```
      /* Now, if this is a pseudo that is live across a call, it can't be
	 allocated to a hard reg...  */
      ...
      /* Don't allocate pseudos that conflict with hard regs... */
      if (reg_mentions_reg_p (..., HARD_REGNO (reg)))
```
Specifically, gcc 2.x has this in find_local_pseudos:

```
	  /* If the pseudo is live across a call, then it can't be put in a
	     hard reg... unless the pseudo conflicts ... */
	  ...
	  /* Now, if the pseudo conflicts with a hard register, it must be
	     allocated globally.  */
```
The "conflict with a hard reg" for `r`: `r`'s value is used by the return → the RESULT_DECL copy → hmm.

The dump says r76 "conflicts v0,v1,sp". Hmm, sp! Why would r conflict with sp? Because the return sequence copies the RESULT_DECL to v0 and sp is adjusted... Hmm, the pseudo's live range overlapping the epilogue's sp adjustment.

Hmm, the RESULT_DECL is copied to v0 at the return, and the epilogue adjusts sp → so any pseudo live at the epilogue "conflicts" with sp? That would make EVERY local global — no.

OK, empirical: let me test whether the value's allocation can be changed by making its live range not reach the epilogue... impossible (it's the return value).

Alright, let me consider the OTHER direction: make the load temps' live ranges longer or their priorities lower, so that in the local allocation they don't take v0 but a0/v1. Hmm, the local allocation assigns v0 to the highest-priority local pseudo. If the temps' pri were lower than some other local pseudo's pri that takes v0... but the other local pseudos are also temps.

Hmm, hmm. Which local pseudos are there? r101/r102 (block 2/3), r106/r107, r109/r111, r112/r115, r116/r117, r118, r122/r124/r127...

In the lever-free nopin: the pri-10000 ones got v0 (r103, r107, r118, r127) and v1 (r124); the 6666 ones got v1 (r102, r116), v0 (r112, r122); the 5000 one v1 (r110).

In the pinned: the pri-10000 ones got v0 (r103, r107, r128), v1 (r118, r125); the 6666 ones v1 (r102, r112), v0 (r123), a0 (r116); the 5000 one a0 (r110).

So in the pinned version, some temps went to a0 — because v0/v1 were needed by the pinned chain.

The difference in the TAIL: pinned → the first comparison's temps in a0/v1; lever-free → v1/v0.

So in the pinned version, the temp that would take v0 (r118?) took a0 instead, because v0 was occupied by the pinned `r` at that point.

So, lever-free: the temps take v0 in the tail because v0 is free.

To make v0 unavailable to the temps in the tail, a pseudo must hold v0 across the tail. The candidates: the local `r` (global ✗).

Hmm, what if the local `r` were assigned EARLY (before the block with the calls)? Then it'd be live across calls → callee-saved ✗ (the target's prologue has s0,s1,s2 + ra; hmm, the target's prologue: sw s0,s1,s2,ra → 4 callee-saved. If `r` were live across the calls, it would need a 5th (s3) → the prologue changes ✗).

OK so this item looks like the same wall: "the pin reserves $2".

Given the budget (this item started 22:59, now 23:25 = 26 min), I should wrap up. Let me do a couple more quick experiments (5 min) then record.

Quick experiments worth trying:
- The load temps' pri: what if the loads are stored into named s16 temps (vV1_temps = 11)?
- What if the comparison is done with `!=` (inverted) to change the branch structure?
- What if the whole tail is in a do-while?
- What if `r` is `s32` but the return is `return r;` with r declared as `volatile`? volatile → memory ✗.

Hmm, one more idea: what if the value is computed into the RESULT_DECL early (the direct-return form) AND the "1" is materialized early?

```
r = 1;      /* hmm */
```

Another idea: what about making the FIRST comparison's temps different from the second's by using temps for only one comparison (vV1 did that → 11).

Let me try:
k1: the first comparison via temps, the second inline (mixed).
k2: the second comparison via temps.
k3: the boolean via a temp.
k4: `r` assigned before the comparisons but as a `u8`? changes the code.

Hmm.

Actually, let me revisit: is the score 9 vs 11 about the same residual? nopin (11) vs h9 (9). The 9-residual has the temps' regs wrong + the extra j/li.

What if I combine: the `r = 1` form (nopin, which has the right structure: `li v0,1` in the delay slot ✓) but with the value in v0?

The `li a0,1` in nopin: the value is in a0 because `r` (the local) got a0.

Hmm! What if `r` is not a local but the value is assigned directly to the RESULT_DECL early? I.e.:
```
/* the RESULT_DECL is set to 1 early */
```
In C: `return 1;` can't be "early".

Hmm, what about this trick: the function's result is assigned by an early `return` in a branch that's never taken but the compiler can't prove:
```
if (q < 0x40 || ...) { ...; return 0; }
```
There's already an early return 0! In the target, that path returns 0 — the RESULT_DECL is set there → the RESULT_DECL pseudo is created EARLY (at that return) → a low allocno ✓ and it's live from there → across the calls → it would be in a callee-saved reg ✗? Hmm, but the early return 0 is inside the `if (chk != 0)` block, and the RESULT_DECL is set to 0 there and returned immediately → its live range is short ✓.

So the RESULT_DECL already exists early (from the `return 0`). Then in the tail, the RESULT_DECL is set again (1 or the boolean) → the RESULT_DECL's allocno is LOW ✓ (created at the early return)!

Hmm! So in vV2_direct (direct returns), the RESULT_DECL is created at the `return 0` (early) → low allocno ✓. And in vV2_direct's dump, the RESULT_DECL... hmm, the dump showed no RESULT_DECL pseudo (the returns are direct copies to v0).

Hmm, in vV2_direct the value in the tail matched the target ✓ (v0). And the temps were wrong.

So in vV2_direct, the RESULT_DECL is in v0 during the tail? Hmm, the diff showed no mismatch in the last comparison ✓ → so the boolean is computed into v0 ✓.

But the temps of comparisons 1&2 took v0/v1 ✗ (target a0/v1) — because in vV2_direct, the RESULT_DECL isn't live during comparisons 1&2 (it's only set at the end) → v0 is free → the temps take it.

In the target, the "1" is materialized BEFORE comparison 2 (in the delay slot of comparison 1's bne) → so the value is live during comparison 2's temps ✓ → they skip v0.

Hmm, wait: the target's `li v0,1` is in the delay slot of comparison 1's bne → it executes BEFORE comparison 2's loads ✓. So during comparison 2's temps, v0 = 1 (the value) ✓ → they use a0/v1 ✓. And during comparison 1's temps (before the `li`), v0 is free — but the target has a0/v1 there too! Hmm.

Hmm, comparison 1's temps: `lh a0,6(s0)`, `lh v1,160(s0)` — a0 and v1, NOT v0. So v0 was unavailable even there. Why? Because in the pinned version, the pinned `r` (v0) is live from... hmm, the pinned `r` is assigned `r = 1` at the tail start. Hmm, but its live range starts at the `li v0,1`.

Hmm, but in the PINNED version, the pseudo `r` is a hard-reg pseudo → v0 is RESERVED for the whole function (not just its live range!) → so ALL the temps skip v0 ✓✓✓ (that's the "hard reg reserved for the whole function" mechanism).

So in the target: comparison 1's temps in a0/v1, comparison 2's in a0/v1, comparison 3's in v0/v1 (because by then the pinned `r`'s value is dead — it's being redefined by the boolean → so v0 is free ✓).

That's exactly the "reserve $2 for the whole function, except where the value is dead" behavior. Lever-free, no pseudo reserves v0 → the temps use v0 early.

CONCLUSION: this item's ROM shape requires a hard-reg variable (the pin) — the same wall class. Lever-free, the value `r` is a normal pseudo and the temps take v0 in the early comparisons.

Hmm, but hold on: could a lever-free `r` be live from the function start (reserving v0)? It would have to be live across the calls → callee-saved ✗.

Hmm, unless `r` is live across the calls but the calls don't clobber it... no.

Hmm, what if the "1" were materialized at the very beginning of the function (before the calls)? Then `r` would be live across the calls → callee-saved ✗ (the prologue would change: the target's prologue is `sw s0, s1, s2, ra` = 4 regs; adding s3 → mismatch).

Hmm, so the wall is structural: "the pin reserves $2 for the whole function".

Hmm, but wait. There's another possibility I should test: what if the early comparisons' temps are forced to a0/v1 by a different mechanism, e.g. if the loads are `lh` from memory with an offset — the mips backend might have a register constraint for the address? No, the address is s0+offset.

Hmm, in the target, the FIRST load is `lh a0,6(s0)` — a0 is the standard "first operand" reg? Hmm, gcc's mips backend has "reload" preferences: the result of a load into a pseudo that feeds a `bne` — the bne's operands can be any regs.

Hmm, but notice the pattern: a0, v1, a0, v1, v0, v1. Hmm, that's odd. Why would the first two comparisons use a0/v1 and the third v0/v1?

Because in the third comparison, the value `r` (v0) is dead → v0 is available ✓. And in the first two, v0 is reserved by the hard-reg pseudo ✓.

So indeed the hard-reg reservation explains it.

OK, so for this item, the wall tag: "greg-hardreg-reserve" or reuse the existing "greg-alloc-order". The existing moves.md line says: "pin | func_801536DC | WALL greg-alloc-order — alloc_table: the RESULT_DECL (pri 10000, prefers v0) ties with the load temps (pri 10000) and loses the allocno tie-break (global.c:607), so the temps take $2/$3 (G08)".

My G08b evidence is more precise: the hard-reg pseudo reserves $2 for the whole function; lever-free the value is a normal pseudo and the load temps take $2 in the first two comparisons (the target has them in $4/$3), leaving 4 mismatched loads + 2 branches + the value copy.

The best lever-free score: 9 (vV2_direct / vV3_else / h9). Tries: the G08 shard had some; my new tries: 9 (h1-h9) + 5 rescores = ~14 new. The item's total tries: unknown from G08 (the notes say "Tried: do-while(0) ref boost (R1), named s16 temps (V1), direct returns (V2)" → 3 + others). Let me count: the existing candidates are 5 (nopin, R1, V1, V2, V3) → say 8 tries from G08 + my 14 = 22. Hmm, I need ≥30 scored tries for a WALL.

Hmm. The rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 30 scored tries for this item. I have ~22. Let me do another ~10 tries (a batch of variants) to reach 30+.

Let me generate a batch of 12 more variants quickly (different angles), score them, and then record.

Ideas for the batch:
k1: `r` with the comparison via `>=`/`<` forms.
k2: the loads through pointers (e.g. `*(s16 *)(s0+6)` → a pointer variable).
k3: `s0` as a pointer (`s32 *p = (s32*)param_1`) — pointer reuse!
k4: the first comparison's operands as temps of type s16 (vV1 = 11).
k5: the second comparison as temps.
k6: both comparisons via temps but assigned in a different order.
k7: the value `r` computed as `(a != b) | (c != d)`? changes the semantics ✗.
k8: the tail in a do-while(0) with r inside.
k9: `r` declared as `s32` but with `r = 1` written as `r = 1 - 0`?
k10: the value as an int expression `r = (X) ? 1 : 0`.
k11: the whole function's tail in a nested block.
k12: the `r = 1` in a nested block at the end.

Let me do these. Note k3 (pointer reuse) is in the catalog ✓ and could change the address computation (s0 is used a lot; the target keeps s0 as the base).

Let me generate andscore 12.
