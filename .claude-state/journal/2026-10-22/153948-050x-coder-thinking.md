---
ts: 2026-10-22T21:39:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VGKtaTAeWUtrUy3EB91j
---
t_u8 (testval u8, byteval u8): order is now correct (move v1,v0 at 7, move a0,v1 at 8) but the second move's *source* is v1 ($3) instead of v0 ($2): cse merged testval = byteval (both QImode) → copy from $3.

So with both u8, order fixed but source wrong. With only testval u8, we got a REG-caller mismatch.

I want: `move v1,v0` (byteval=$3 from src=$2) then `move a0,v0` (testval=$4 from src=$2).

The problem is cse merging byteval/testval (equal values) → one copy's source becomes the other's register.

Hmm, in t_u8: `move v1,v0` then `move a0,v1`. So the second copy reads $3. Target wants `move a0,v0`.

So I need testval's copy to be from src ($2 = v0), not from byteval. If testval is SImode and byteval QImode, cse sees them as different modes → no merge (that's the u8 case: `move a0,v0` from v0 ✓) but the order is wrong (a0 first).

So: u8 byteval gives the right sources, wrong order; both u8 gives the right order, wrong source.

Can I get the right order with u8 byteval (SImode testval)? The order issue: `move a0,v0` before `move v1,v0`.

Why is the a0 copy first? sched1 priority. In the target, the $3 copy comes first. In t_u8 the order is right but for a different reason (the second copy is a copy from v1, dependent on the first → forced order).

Idea: make the $3 copy a dependency of something scheduled early... or make the $4 copy depend on the $3 copy *without* changing the source. Not possible in C (a copy from $3 is the only way).

Alternative: change the *pin* order in the source? The RTL order of the copies follows the statement order (byteval = src before testval = src). sched1 then reorders. Since both are ready at the same cycle, sched1 picks by priority then by the "ready list" order. Hmm, in sched1 (gcc 2.7.2 sched.c), `ready_add` inserts by priority; for ties, it appends? Then the queue order is birth order. So why is a0 first?

Unless the priority differs: testval's copy feeds the beqz → but the beqz is in another block. Hmm, sched1 computes priority via `max_insn_queue_length`? Actually sched1 computes `INSN_PRIORITY` = length of the longest path to the end of the block (via `schedule_insn` and `priority` function `max_priority`?). Both copies have 1 successor... 

Wait: for u8 byteval, the $3 copy is a QImode subreg copy that may be represented as a different insn. Maybe the a0-first ordering is a *combine* artifact: `move a0,v0` might not be a copy but the result of the branch's operand... The beqz at 13 uses a0 directly: the copy a0=src might be folded into the branch's operand requirement (the branch needs the value in a register, and $4 is a fixed hard reg... hmm).

Actually here's the thing: $4 is hard-pinned, so `testval = src` must be a move $4,$2. That move is scheduled early (7 in mine, 8 in target). And the $3 move is scheduled right after. The target has $3 first.

Could it be the *uid order*: sched1's ready list ties are broken by the order insns were added, which is RTL order. So target's RTL must have the $3 copy before the $4 copy. In my u8 source, byteval=src is first, so the RTL should have $3's copy first... unless the copies are created by different passes at different times (e.g. one is created by local-alloc/global-alloc as a spill/coalesce, the other by expand).

The pins with __asm("$3") create hard-reg pseudos; `byteval = src` — the assignment to a hard-reg variable... In gcc 2.7.2, `register u32 x asm("$3")` makes x a hard register; the assignment generates a move to $3 at expand time. Both are expand-time moves in source order.

But the QImode one (u8 byteval) is a subreg move: maybe combine/flow turns it into something else, or the ordering pass (sched1) reorders.

Hmm. Let me try a different tactic: give byteval's copy a reason to be scheduled first by making its consumer earlier. E.g. move the `pcVar2[0] = (u8)(byteval * 8 + 8);` earlier? That changes the target's shape (sb at 25).

Alternatively make testval's copy be scheduled later by making its value's use later: `testval` is used in the if. If I write the condition to use `(testval != 0)` after some other op... The condition is at the top of the loop body.

Alternative: reverse the `||` operands: `if ((testval != 0) || (iVar3 == c5))`. Then the first branch is beqz on testval... but the target has beq v0,t2 first. So no.

Hmm, what about making byteval's value *not* cse-equal to src by giving it a real 2nd set inside the loop? Like the dead-reset: after the sb, `byteval = 0;`? That would break the class... but the copy order issue is at birth, not cse.

Let me reconsider: in the u8 variant, mine = a0 then v1 (target v1 then a0). Both are "move from v0". What if the *birth* of the $3 copy were earlier than the $4 copy by making byteval's copy depend on something that dies earlier? Hmm.

Or: what if the $4 copy is born later in the RTL because `testval = src` is placed after the `param_2 = param_2 << 4;` statement? I tried u8_late_test — no change (still a0 first).

Hmm, since source order has no effect, sched1 reorders by priority. The priorities: the $4 copy → used by beqz at 13 (next block) — no priority contribution; the $3 copy → used at 19/25 (next block) — none either. Then tie... but they're ordered a0 first consistently. So maybe the ready-list tie-break is by *uid descending* or by "the last insn added first".

Let me look at sched1's ready_add in the gcc 2.7.2 source if available in tools/bin? We have the compiler but maybe not sources. Skip.

Practical approach: try a handful of real-C variations that change which value feeds the branch:
- make the branch test use a different variable, e.g. `if ((iVar3 == c5) || (testval != 0))` → `if ((iVar3 == c5) || (src != 0))` and drop testval? But testval is a pin ($4) that must stay (not a row kind, but removing a pin = removing a lever of another kind; allowed? "levers of other kinds the def already had may stay, never added" — so removing them is allowed as long as the body still matches. But removing a pin may change codegen.)

Let me try `if ((iVar3 == c5) || (testval != 0))` with testval assigned as u32 but *used via a copy*... 

Alternative: what if byteval is declared `s16` (I got score 2 as well, ORDER) — same as u8.

Let me look at the ORDER diff for s16 to confirm it's the same swap.

Then: how about making byteval's copy have a *dependency* on an insn that is scheduled at 7? E.g. byteval = src (move v1,v0) is currently at 8 in mine... 

Honestly, maybe try: `byteval = (u8)src;` with testval u32 (cast.c was u32 base...). Let me try combos:
- byteval u8 + testval u32 + testval assigned from a *cast* to u32 of src: same.
- byteval u8, and give testval a 2nd set: `testval = src;` then later `testval = src;`? no.

What about swapping which register is pinned to which variable? Not allowed (that changes the pins' meaning, and it's a lever change).

Hmm, what about the s16 case: score 2 ORDER. Let me check if the s16 diff is the same swap; if so, try byteval s16 + testval s16 (like t_u8 but s16): then the copy source might be v1 again.

Let me think differently: the real difference between target and mine is the *relative order* of two independent moves. This is sched1's birth order. moves.md has "sched1-birth-order" (func_801372B0): "sched1 orders two independent insn births opposite to source; reorder moves the other". And walls has `sched1-birth-order`. Hmm, in func_801372B0 the wall was that reordering doesn't help.

But here we have a knob: u8 vs u32 changes it (u8 → correct order with wrong source; u32 → wrong order). So the copy *mode* affects sched1's priority. 

What about `s16 byteval` + `u32 testval`? score 2 ORDER (same as u8). What about byteval u32 but with a cast at use? `pcVar2[0] = (u8)(byteval * 8 + 8);` is already a cast.

What if byteval is u32 but the sb uses `(u8)((byteval << 3) + 8)`? Hmm.

Idea: keep byteval u32 (right sources: a0,v0 from v0) but force the order by making the $4 copy depend on the $3 copy in a way that doesn't change the source: e.g. `testval = src;` where src is itself copied... no.

Alternative: make byteval's copy NOT a copy but an andi result: e.g. `byteval = src & 0xf;`? cse would fold. `byteval = src & 0x1f;`? changes semantics? byteval is used as `byteval*8+8` stored as u8. src is 0..15. `src & 0x1f` == src (value-preserving for the range, but not provably identical to gcc? gcc knows src < 16 from the andi, so nonzero_bits → folds).

What about `byteval = src + 0;`? folded.

Hmm, what about making byteval's copy produce a *different insn* that lands at index 7: e.g. `byteval = src * 1`? folded.

OK: the real question — which insn does sched1 schedule first and why? Let me test a probe: give byteval's use an earlier consumer in the same block. E.g. put `uVar4 = 0;` ... no.

Actually — maybe I'm overcomplicating. What if the *target's* order comes from the u32 spelling with the $3 copy born before the $4 copy because in the original the byteval assignment was a separate statement *with a use* in between... 

Let me try: use byteval in the condition too: `if ((iVar3 == c5) || (testval != 0) || (byteval == 0x10))`? changes semantics/insns.

Alternative: give the two copies different *lifetimes*: byteval is used at 19 (sll v1,v1,3) and testval at 13 (beqz). If I make testval's use in the same block... no, the branch ends the block.

Hmm, wait. Maybe the a0-first order comes from *local-alloc combining* the $4 copy with the beqz's operand: since testval is used only by the beqz, its copy could be folded into the branch... no, $4 is fixed.

Let me try yet another approach: what if testval is u32 but assigned as `testval = (u32)byteval;`? Then the copy is $4 = $3, wrong source (like t_u8). No.

What if the copy sources are right but the order flips when byteval's declaration is *after* testval's (decl_order.c = 2 ORDER)? Let me look at decl_order's listing — maybe it fixed something else. It was on the u32 base (score 2 ORDER). Let me check what its diff is.

Let me check decl_order and s16 listings.
