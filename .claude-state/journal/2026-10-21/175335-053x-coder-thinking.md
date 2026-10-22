---
ts: 2026-10-21T23:53:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QNaT1YDwQnefpa0EKKJD
---
Even with no variable at all (variant H: pure literals, no temps), gcc produces the same 41-ins code with the constants in $2 and the "1" in the return block. So gcc's structure is: the constants get $2 (the first caller-saved reg it picks for the compare temps) and the "1" is materialized in the shared return block.

Wait — in variant H there is no "1" variable at all, yet the result is identical. So the "1"'s location (the shared return block) is a consequence of the block structure, not of a pseudo.

Interesting: so even with literal returns, gcc creates ONE `li v0,1` in the return block (via cross-jump merging). The ROM instead has it in the chain block's delay slot.

Hmm! So what if the source's arms return a value that requires the "li" to be in the chain block? In the ROM the `li v0,1` executes on BOTH paths of the first branch (delay slot) — i.e., it's set before any branch. So in the ROM's source, the "1" is set before the compares — a variable set to 1 in the chain block, whose copies were folded into the arms' returns, but the SET remained in the chain block because...

AH WAIT!!! I think I've got it: if the value is set in the chain block BEFORE the branches, and the arms' returns need it, gcc folds the copies... but the SET itself (the pseudo's set) is in the chain block. If the pseudo is eliminated (folded), the set disappears. But if the pseudo is NOT eliminated (because it's a real variable used in 4 places), then the set stays in the chain block and the copies are `set $2, v0` → folded to `set $2, 1`...

Hmm, but if the pseudo's set is folded into the copies, the set dies. UNLESS the copies can't be folded because the pseudo is in a register that is NOT $2 — then the copy is a register move, and the set stays! And then gcc's local-alloc gives the pseudo a register.

Hmm, so: the set stays in the chain block ONLY if the pseudo survives. And the pseudo survives only if the copies are not folded. And the copies are folded when the pseudo's value is a constant.

Circular again! BUT: there's a subtlety — gcc's "combine" folds the pseudo's set INTO the copy when the pseudo has a single set. With 4 uses (4 copies), combine would create 4 copies each with the constant → the pseudo dies.

Hmm, but in the ROM's code the copies don't exist at all (the arms branch directly to the epilogue) → the pseudo was $2 → the copies were no-ops → the pseudo's set stayed → the set was scheduled into the delay slot ✓.

So the ROM's compiler kept the pseudo in $2 (because it's the return reg) — the same as the pin.

So the question remains: how does gcc decide to allocate a pseudo to $2 without a pin? Via the "copy preference" (the pseudo is copied to $2 at the return) — global-alloc's copy preferences give the pseudo a preference for $2! But that only applies to GLOBAL pseudos (cross-block). If the pseudo is local (single block), local-alloc handles it and may not honor copy preferences.

Hmm! So if the "1"-pseudo were GLOBAL (live across blocks), global-alloc would use the copy preference (the pseudo is copied to $2) → it would get $2 ✓.

Is the "1"-pseudo global in the ROM? Its live range spans from the chain block to the arms (which are... hmm, the arms are all in the same "if" block? No! Each `if (arg2 == v1) return v0;` creates a separate basic block for the return. So the "1"-pseudo is live across blocks (from the chain block into the arm blocks) → it's a GLOBAL pseudo ✓✓.

And the const temp: also live across blocks (set in the chain block, used in the same block though — `if (arg2 == v1)` — the use is in the same block → the const temp might be local to the chain block!).

Hmm, but in mine the const temp got $2 — as a local pseudo, local-alloc picks it. And the "1"-pseudo (global) — global-alloc assigns it a callee-saved register typically ($16-$23) — but the target has it in $2 (caller-saved)!

Hmm, global-alloc assigns globals to callee-saved regs (s0-s7) preferentially... but the ROM has the "1" in $2. So in the ROM it's NOT a global pseudo (a global would go to $16+).

Hmm, so in the ROM the "1" was a LOCAL pseudo in $2, and the const temp also local, in $3.

OK so local-alloc decides. local-alloc's order: it processes the block's pseudos and assigns hard regs. In gcc 2.7 final.c's local_alloc: it iterates over the pseudos in the block in the order of `qreg`/priority? There's a function `local_alloc` that does:

```
  /* Allocate the hard registers to the pseudos... */
  for (i = 0; i < n_pseudos; i++) ...
```
with the pseudos sorted by "qty" I believe (`qsort (pseudos, n_pseudos, sizeof (pseudo_reg), pseudo_reg_qty_cmp)`) — hmm.

If sorted by qty DESCENDING: the const temp (8) before the "1" (5) → const gets $2 ✓ (matches mine). And in variant H (no "1" variable), only the const temps exist → they get $2 ✓.

To flip, the "1"-pseudo needs qty > 8: 1 set + 8 uses. Or the const temp needs qty < 5.

Hmm! What if the const temp is used ONLY in the compares but the compares are against *constants* (variant A/H)? Then each constant temp has qty 2 — but gcc created ONE pseudo for all four (since the code is identical, gcc's "combine" merged them? or they're 4 pseudos sharing $2 — with qty 2 each, they'd sort after the "1" (qty 5) → the "1" would win $2! But the result was unchanged (the constants in $2)!

So in variant H/A, either (a) gcc merged the constants into one pseudo (qty 8) → wins $2, or (b) qty isn't the criterion.

Hmm. Since the "1" in variant H doesn't exist as a variable at all (literal returns), there's no "1"-pseudo to compete! In variant H, the returns are literals → the "1" is materialized in the return block. So variant H tells us nothing about the competition.

But variant E (four temps + v0 variable) is the informative one: v0 (qty 5) vs 4 temps (qty 2 each) → still the const temp got $2 → so either the temps were merged into one pseudo, or qty isn't the criterion.

I need the alloc table to know. Let me do the cc1 dump — it's the sanctioned tool and will tell me the pseudo priorities. Let me check cc1_dumps_tu.sh usage first.

Actually, hmm, wait. There's a much better idea I keep missing: what if the "1"-pseudo's qty can be increased legitimately by using it in the FOUR comparisons? I.e., the ROM's structure could be read as: the value 1 is compared... no.

Alternatively: increase the "1"-pseudo's qty by having MORE returns! E.g. the four arms could each have TWO returns? no.

Hmm, but what about this: `v0 = 1;` and then the four arms `return v0;` → qty 5. What if instead the source had 8 uses: e.g. each arm `if (v0) return v0;`? adds a branch ✗.

OK, cc1 dump + alloc table. Let me look at thescript usage.
