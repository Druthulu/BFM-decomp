---
ts: 2026-10-22T00:19:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Gfk76mirXQ350IrG0hMv
---
Now I understand the mechanism precisely:

S2: "Single-set def sinks to its consumer / multi-set def stays at source position (the BIRTHING BOOST)".
- Kill the boost (def sits too LATE, want it at source position): add a 2nd SET that survives cse — the §30 #3 re-tie `__asm__("" : "=r"(x) : "0"(x))` in a LATER bb, or the end-of-function dead-volatile `__asm__ volatile("":"=r"(x))` for spilled pseudos. "A plain C reassignment does NOT work if cse/flow can eliminate it (t5/t6 proofs)."

So the launder's job: kill the boost of the pw load so the load stays at its source position.

For my item (func_8018AA98): the target has the lw EARLY (source position) → I need to KILL the boost on the lw. A plain C reassignment doesn't work if cse/flow can eliminate it.

But my split (`pv = pv & 0xFF000000;`) should create a real 2nd set of pv's reg ($3)... but the result didn't kill the boost (the lw still sank to 137). Why? Because... hmm.

Wait, maybe the issue is that the AND's dest is not $3. Let me check the candidate's code: "137 lw v1,0(s1); 139 and v1,v1,a2" — dest = v1 = $3 = pv's reg. So $3 has 2 sets. Hmm, but maybe gcc assigned the AND to a different pseudo and later coalesced it into $3 at regalloc time. The REG_N_SETS is counted on the PSEUDO before regalloc. The pseudo for pv is pinned to $3 (a hard reg with a pseudo?). Hmm, with `register u32 pv __asm__("$3")`, gcc creates a pseudo tied to the hard reg $3. The AND's result: `pv = pv & 0xFF000000` — the result is assigned to pv's pseudo (the same pseudo, since pv is a variable) → so the pseudo has 2 sets → REG_N_SETS=2 → the boost is killed!

But observed: the lw still sank. Hmm, unless the boost that matters isn't the lw's but the constant's, and the constant's boost in mine is not applied because... hmm, wait. Let me re-examine: in the TARGET, which def is at its "source position"?

Target order: 125 lui(base), 126 addiu, 127 ?, 129 lhu(bidx), 130 lw(pv), 131 sll, 132 addu, 137 lui(mask), 139 and.
Mine:    125 lui(base), 126 addiu, 127 ?, 129 lhu(bidx), 130 lui(mask), 131 sll, 132 addu, 137 lw(pv), 139 and.

Source order (target's source): the statements are:
```
bidx = (u16 *)&D_800B9A02;
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
The RTL source order: the load of pv comes before the mask's use. The constant 0xFF000000 is materialized at its first use (the store's AND).

In the target: the lw (pv's load) is at 130, i.e. at its source position (early) — so the lw was NOT boosted (no sinking). The constant's lui is at 137 — sunk toward its consumer? The constant's first consumer is the `and` at 139 — so the lui at 137 is "just before its first consumer" → the constant IS boosted (single-set) → sunk. ✓.

In mine (base, no launder): the lw is at 137 (just before its consumer, the and at 139) → the lw IS boosted (single-set) → sunk. And the constant's lui at 130 is at its source position (early, right after the lhu) → the constant is NOT boosted?!

Hmm, why would the constant not be boosted in mine? Because only ONE insn can win? The doc says the boost applies to any single-set def that becomes ready. Hmm, but maybe the constant's pseudo has 2 sets in mine? The constant 0xFF000000 is used twice (both masks) — but that's 2 USES, 1 SET. So it's single-set → boosted → should sink. But in mine it's at 130 (early).

Hmm, unless the constant's pseudo in mine is *split*: 0xFF000000 appears in the first store as (pv & 0xFF000000) and in the second as (*(u32*)(ot+0x40) & 0xFF000000). Both are 32-bit ANDs with the same constant → one pseudo.

Hmm, but wait: in mine, is the constant's pseudo really at 130? "130 lui a2,0xff00" and the and at 139 uses a2. So yes, single def, 2 uses, at 130 (early = source position) → NOT boosted.

Hmm, so in mine the lw got the boost and the constant didn't; in the target, the constant got the boost and the lw didn't. Both can't be boosted simultaneously... Actually they can: the boost is applied "on becoming ready" — the ready-list order matters. Whatever.

The key: with the launder, $3 (pv's reg) has 2 sets → the lw is not boosted → the constant gets the boost → target order. ✓ Consistent.

Now, in my candidate (split pv), $3 should have 2 sets: the lw and the AND. Hmm, but wait — the AND's dest: `pv = pv & 0xFF000000` — pv is a *variable* pinned to $3. In gcc, the pseudo for pv is a pseudo with a hard-reg binding. The AND writes the same pseudo → SET(pseudo). So REG_N_SETS(pseudo) = 2 → the lw (which sets the same pseudo) is not single-set → not boosted. Then the constant should get the boost → the lui should sink to 137.

But my candidate shows the lw at 137 still. Hmm! Unless the AND was *not* a set of pv's pseudo: gcc might have computed the AND into a separate temp and then stored... but the final "and v1,v1,a2" writes $3.

Hmm, hold on: maybe the problem is the *direction*: the lw is at 137 in my candidate = sunk = boosted. If the boost were killed, the lw would be at its source position. But maybe the lw's source position in my candidate is NOT early! Because I moved the split: my candidate is
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (X & 0xFFFFFF);
```
The load is still first. Hmm.

But actually, WAIT: what is the RTL source order? gcc's RTL for `pv = *(u32*)p; pv = pv & 0xFF000000; *(u32*)p = pv | (X & 0xFFFFFF);`:
- The store `*(u32*)p = ...` involves X = *(s32*)(...) which involves *bidx (volatile load) and the address computation. gcc expands the whole RHS first: the address of X, the lhu (volatile), the lw of *(s32*), the and, the or, then the store. But the *statements* are separate: the load of pv is its own statement, so its RTL comes first.

Hmm, so the load is early in the RTL.

Unless: cse/flow reordered? The doc says REG_N_SETS is counted after cse/flow. Hmm.

OK, empirical approach: let me try more variants for this item and see which one gets 0. The diff is only 11 register transpositions, so we're close.

Variants to try:
(b) split the OTHER value (the second masked value) instead: 
```
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
→ introduce a temp for the second masked value.
(c) both splits.
(d) split pv AND reorder statements.
(e) keep the launder's *position* semantics: the launder was at the END of the function (after the last call). The 2nd set of pv is at the end. So maybe the key is that the 2nd set is in a LATER bb (the doc: "add a 2nd SET that survives cse — the re-tie in a LATER bb"). My split is in the SAME bb.

Hmm! But actually the doc says REG_N_SETS is per pseudo, not per bb. But the doc's example (func_801770E0) killed the boost by using a *fresh variable* (u4, u5) — i.e., a different pseudo for the value used later, so the original pseudo's def (the call result) became... hmm, in that example they *created* boosts, not killed them.

Let me think about the goal differently: I want the lw (pv's load) to NOT be boosted, i.e. pv's reg to have 2 sets in the RTL. Options:
1. A 2nd assignment to pv that survives cse/flow: `pv = pv & 0xFF000000;` — the AND's dest = pv's pseudo. But then the store uses pv. Does cse eliminate it? No, the AND is needed. Does flow? No. So pv's pseudo has 2 sets.

Hmm, but then the AND itself is a set of pv's pseudo, and the AND's dest is the same pseudo as the load's dest → the AND is also not single-set. OK.

But empirically the lw was still sunk. So maybe my assumption about which insn got boosted is wrong; maybe the lw is at 137 not because of a boost but because of the *priority* rules (S3: a chain fed by a load has pri+1...). Hmm, the lw feeds the AND which feeds the store; the load has latency 2 → the chain has higher priority → it sinks? no, higher priority = scheduled earlier (in the backward scheduler, "picked early = placed late"!).

AH WAIT. Important: "schedule_block schedules each bb BACKWARD (from the tail): picked early = placed late." So the *ready list* picks the insn to place LAST first... Hmm, "picked early = placed late" means the first picked insn ends up last in the final order. So a HIGH priority insn is placed LATE (at the end)!

That flips my reading: the boost (priority → max) makes the insn be placed LATE = "sink to just before its first consumer" ✓ consistent with the doc's S2 title: "Single-set def sinks to its consumer".

OK so: the boost → the def is placed as late as possible (just before its consumer).

In mine: the lw is boosted → placed late (137, just before the and at 139) ✓. The constant's lui: not boosted → stays at its source position (130) ✓.

In the target: the lw is not boosted → stays at source (130); the constant is boosted → placed late (137) ✓.

So I need to kill the boost on the lw. My split should have done it (2 sets of pv's pseudo)... but it didn't. Why?

OH! Maybe because the AND's dest is NOT pv's pseudo: `pv = pv & 0xFF000000;` — hmm, it is.

Hmm, unless gcc's "expand" of `pv & 0xFF000000` produced a *new* pseudo for the AND result and then a copy to pv's pseudo? That would be 2 sets of pv's pseudo (the copy) — still 2 sets. Hmm.

Wait, maybe the problem: with pv pinned to $3 (a HARD reg with a pseudo binding), the load `pv = *(u32*)p` might write the pseudo, and the pseudo is bound to $3. REG_N_SETS(pseudo) counts the sets of the pseudo. If the AND writes the same pseudo, count = 2.

Unless the pinned variable's pseudo is *not* reused: with `register u32 pv __asm__("$3")`, gcc creates a local pseudo (DECL_RTL) hard-reg-bound. Both the load and the AND write that same pseudo. So 2 sets.

Hmm, so why didn't it work? Let me actually verify my candidate's code: I wrote
```
    pv = pv & 0xFF000000;
    *(u32 *)p = pv | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```
Hmm wait, in the ORIGINAL source the store is:
```
    *(u32 *)p = (pv & 0xFF000000) |
                (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C + (*bidx * 20)), 0x40) & 0xFFFFFF);
```
My sed replaced "    *(u32 *)p = (pv & 0xFF000000) |\n" with "    pv = pv & 0xFF000000;\n    *(u32 *)p = pv |\n". ✓.

And the candidate's diff showed "and v1,v1,a2" at 139 — so the AND is there. And the lw at 137. So the lw is still boosted (sunk) — meaning pv's pseudo still has 1 set?!

Hmm! Maybe the AND is done into a temp pseudo and the *store* uses the temp; the "and v1,v1,a2" we see is the final copy... no, "and v1,v1,a2" IS the AND.

Hmm, is it possible that the lw at 137 is NOT pv's load but something else? "lw v1,0(s1)" — s1 is a saved register (the function's frame pointer?) holding the address p. In the target, "lw v1,0(s1)" at 130. Yes, that's the load of pv = *(u32*)p where p is in s1.

Hmm OK. So why is the lw boosted in my candidate?

Possibility: the boost is on the *load* because the load's dest pseudo has 1 set... but the AND writes the same pseudo → 2 sets. Unless gcc's cse turned `pv = pv & 0xFF000000` into a *new* pseudo (because pv is a pinned/hard-reg-bound variable, gcc may not allow multiple sets of the same pseudo? no...).

Hmm, wait. Maybe the issue is that the boost is killed but the lw is at 137 for another reason: the S4 rule "one insn wedged between a load and its consumer" — no.

Alternatively, maybe the lw's position is determined by the *priority* (S3): the chain lw→and→store has a load in it (latency 2) → the chain's priority is +1 over the constant's chain (lui→and, ALU only, pri 1). In the backward scheduler, higher priority = placed LATE. So the lw (in the pri-2 chain) is placed later than the lui (pri-1 chain) → the lw at 137 and the lui at 130! And the boost (max priority) applies to the *single-set defs*...

Hmm, if priority alone explains the mine-vs-target difference, then the boost isn't the cause. But the target has the lw EARLY, which contradicts the priority argument (the lw's chain has pri+1 → placed later)... unless in the target, the load is NOT in the chain: hmm.

I think I need the actual dump (sched1 trace) to reason. But that's expensive.

PRAGMATIC: let me just try a bunch of variants empirically. The variants that could move the lw earlier:
1. Make the load's dest a FRESH variable (single-set) — no wait, that CREATES a boost.
2. Give pv's reg a 2nd set (my split) — tried, no effect.
3. Reorder: move the `pv = *(u32*)p;` load to a different position in the source (e.g. right before the store) — that changes its source position → the "unboosted" position moves. Hmm! Since the lw is boosted (sunk to its consumer), moving its source position won't help.

Hmm, but if it's boosted, it always sinks to its consumer.

4. Make the load feed something else too, so its consumer is earlier? no.

Let me reconsider: maybe the boosted insn in mine is NOT the lw but the constant's lui, and the *lui* is placed late... no, the lui is at 130 (early) in mine.

OK, let me look at the actual numbers again for mine (base.c, no split):
```
125 lui a0,0x0
126 addiu a0,a0,0
127 ?
129 lhu v1,0(a0)
130 lui a2,0xff00
131 sll v0,v1,0x2
132 addu v0,v0,v1
133 ?
137 lw v1,0(s1)
139 and v1,v1,a2
143 lhu v1,0(a0)
154 and v0,v0,a2
157 lhu v0,0(a0)
```
Note 133-136 are equal between mine and target (not shown in the diff) — those are probably the address computation for `ot` (addiu etc.) and the 2nd lhu.

Target:
```
125 lui a2,0x0
126 addiu a2,a2,0
127 ?
129 lhu a0,0(a2)
130 lw v1,0(s1)
131 sll v0,a0,0x2
132 addu v0,v0,a0
133 ?
137 lui a0,0xff00
139 and v1,v1,a0
```

So in the target, the lw is at 130 and the lui at 137; in mine, the lui is at 130 and the lw at 137. They're SWAPPED! Both are single-set defs competing for the same slot.

So: in the target, the *lui* (constant) is boosted (sunk) and the lw is not; in mine, the lw is boosted and the lui is not.

Hmm, so the boost went to a different insn. With the launder, pv's reg has 2 sets → the lw is not single-set → the constant's lui takes the boost. ✓ (consistent with the launder's comment).

With my split, pv's reg should also have 2 sets... but the observed result is the same as the base. So my split did NOT give pv's pseudo a 2nd set. Why?

AH — I bet I know! The `& 0xFF000000` AND: gcc's expand for `x & 0xFF000000` produces `andi` if the constant fits in 16 bits — 0xFF000000 doesn't. So it uses the constant pseudo (lui 0xff00) + and. Fine.

But the AND's DEST: since pv is pinned to $3 (a hard reg), the AND's result must be in $3... but the pinned variable's pseudo is a *pseudo* bound to $3, and the AND writes it. So 2 sets.

Hmm, unless the split made gcc generate: the AND into a temp pseudo, and then the store reads the temp — because gcc's RTL for `pv = pv & 0xFF000000` where pv is a *variable* (memory-less, in a register): the assignment's RHS is computed into a temp and then copied to pv's pseudo. gcc usually does the "set" directly into the destination pseudo (no copy) — but for a hard-reg-bound pseudo, maybe not.

Hmm, and in the emitted code we saw "and v1,v1,a2" — one instruction, dest $3. If there were a copy, we'd see "and v0,v1,a2; move v1,v0" (2 insns) — the count was 177 = 177, so no extra copy.

So the AND does write $3. So the pseudo has 2 sets: the lw (137) and the and (139). Then REG_N_SETS = 2 → the lw is not single-set → the boost should go to the constant's lui → the lui should sink to 137 and the lw should be at 130.

But that's not what happened. So my model is wrong somewhere.

Possibility: the boost is applied to the insn when it BECOMES READY, and only one insn gets boosted (the first to become ready). The lw becomes ready early (its operands are ready) → it gets the boost → placed late. The constant's lui also becomes ready early. Hmm.

But in the target, the lw is at 130 — EARLY. So the lw was NOT boosted. And the constant's lui was.

The difference between the target and mine: the launder creates a 2nd set of pv's reg → the lw is not single-set → not boosted. ✓ my model.

And with my split, the lw should also not be single-set... unless the *split* didn't produce a 2nd set of the SAME pseudo. Hmm! What if gcc's cse/flow eliminated the 2nd set: "a source-level 2nd assignment that cse copy-propagates or flow dead-store-eliminates does NOT kill the boost".

The split: `pv = pv & 0xFF000000;` then `*(u32 *)p = pv | (X & 0xFFFFFF);`. The AND is NOT dead and NOT a copy... unless gcc rewrote it as: the store's RHS = (pv & 0xFF000000) | (X & 0xFFFFFF) with the AND computed into a temp pseudo (not pv's pseudo!) — i.e. gcc's RTL for the *variable* pv is: since pv is a variable whose value is used in the store expression, gcc may substitute the expression directly (SSA-ish) rather than storing into pv's pseudo. YES! That's it: gcc's RTL for `pv = pv & 0xFF000000;` creates a *new* pseudo for the AND result, and then `*(u32*)p = pv | ...` reads that new pseudo. gcc does NOT necessarily write into pv's DECL_RTL pseudo — with a local variable, gcc typically creates a new pseudo for each assignment (the "copy" to the variable's pseudo may be optimized away by cse/flow when the variable is not address-taken).

But then the *load* `pv = *(u32*)p` — its result also went into a temp pseudo, and the load's dest is a single-set pseudo!

Hmm! So in the base version (no split): the load's dest pseudo is single-set → boosted → sunk to its consumer. The AND (pv & 0xFF000000) is computed into another pseudo, single-set → also boosted?! Two boosted insns...

Hmm, but in the base, the AND is part of the store's RHS expression: `(pv & 0xFF000000) | (X & 0xFFFFFF)`. The AND's dest is a single-set pseudo → boosted → sunk to just before its consumer (the OR). And the load's dest is single-set → boosted → sunk to just before its consumer (the AND).

But in mine, the load is at 137 and the AND at 139 (adjacent) — consistent with both sinking to their consumers! And the constant's lui (used by the AND at 139) is at 130 — hmm, it should also sink to just before the AND (139). It's at 130 instead.

Hmm, so the constant's lui did NOT sink. But it's a single-set def too...

Unless: the constant pseudo (0xFF000000) has 2 SETS! Because it's used twice: in the first store's AND and in the second store's AND — but cse would merge them into 1 set...

Hmm, OR: the constant pseudo's def is `lui a2,0xff00` — and 0xFF00... hmm, wait. Is the "lui a2,0xff00" the constant 0xFF000000? And is there another use of 0xFFFFFF? The second store: `(*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF)`. So 0xFFFFFF is another constant (andi 0xffffff fits in 16 bits → andi!). And 0xFF000000 needs the lui.

So the 0xFF000000 constant has 2 uses (both ANDs) → 1 set → boosted → should sink to just before the first consumer (139). But it's at 130 in mine.

Unless the priority rules put it earlier. Hmm, the "boost" raises the priority to max_priority — but max_priority is "≈ the launching insn's". Hmm, and priority is "longest-chain-from-bb-top" — the constant's chain (lui→and→or→store) has priority ≥ the load's chain? The load's chain: lw→and→or→store: load cost 2 → the chain's priority is 1 higher.

Since the scheduler is backward, higher priority = placed LATER. So the load chain (pri+1) is placed later than the constant chain (pri). ✓ mine: the load at 137, the constant at 130.

And the boost raises a single-set def's priority to max → placing it even later (just before its consumer). In mine, the load IS just before its consumer (137 vs 139) ✓ boosted. The constant's lui at 130 is at its chain position (not boosted?). Hmm, why isn't the constant boosted?

Maybe because the constant's pseudo is not "live" at its def? Or because the boost only applies to a def whose dest is *live* (the doc says "with the dest live").

Hmm, the constant 0xFF000000 is live from the lui to its last use — live. Hmm.

Wait, maybe the difference: in the TARGET, the constant's lui is at 137 (just before the and at 139) = boosted; the load at 130 = its chain position. And in MINE, the load at 137 = boosted, the constant at 130 = chain position.

So in both cases exactly ONE of the two is boosted. The boost goes to the one that becomes ready FIRST (or has the max priority rule).

In the target, the constant is boosted and the load isn't. For the load not to be boosted, its dest must have 2 sets (the launder provides that) ✓.

In mine (base), the load is boosted. The constant is not boosted — why not? Because the boost is applied to the insn that becomes ready first, and only one gets it? Or because the constant's pseudo has 2 sets (2 uses → hmm, uses don't matter).

Hmm, let me look at the actual mechanism in gcc 2.7.2's adjust_priority:

```c
static void
adjust_priority (insn)
{
  rtx reg = ...; /* the dest */
  ...
  if (birthing_insn_p (insn) && ...)
    INSN_PRIORITY (insn) = max_priority;
}
```
and birthing_insn_p tests `reg_n_sets (dest) == 1` (2.7.2: reg_n_sets at 2490).

So EVERY single-set def gets max_priority when it becomes ready. Then multiple insns would have max priority, and the tie-break would be LUID (source order) → the LAST one picked is placed... hmm, in the backward scheduler, among equal priorities, the LUID rule picks the highest LUID first (= placed later). So among the boosted insns, the one with the highest LUID (latest in source) gets placed last?? Hmm, confusing.

Let me think in the backward scheduler: we schedule from the tail. The ready list contains insns whose successors are all scheduled. We pick ready[0] and place it before the already-scheduled tail. "picked early = placed late" — hmm, that contradicts: if we schedule backward and place each picked insn immediately before the scheduled tail, then the FIRST picked ends up LAST in the final order.

So: pick order = reverse of the final order. Among equal priority, the LUID tie-break picks the HIGHEST LUID first → the highest-LUID insn is placed LAST in the final order.

Hmm, wait: rule 4.iii says "highest LUID first (= placed later) → forward order among full ties = ascending LUID = source order". So yes: among full ties, the insn with the highest LUID is placed last.

Now, the boost: max_priority. In the ready list, the sort is by priority (highest first) — so a boosted insn (max_priority) is picked BEFORE others → placed LAST. ✓ "single-set defs sink to just before their first consumer" (the consumer is already scheduled, so the def is placed right before it).

So: if BOTH the load and the constant were boosted, both would be placed late, just before their consumers. The load's consumer is the AND (139) and the constant's consumer is also the AND (139)! Both would be placed just before 139 — but they can't both be at the same place; the one picked first (higher LUID?) goes later.

In mine: the load is at 137 (just before the and at 139) and the constant at 130. So only the load was boosted.

Why wasn't the constant boosted? Because when the constant's lui became ready, the load was already scheduled? No — the load is at 137 (later). Hmm, backward scheduling: the tail is scheduled first; the load at 137 is closer to the tail than the constant at 130. So the load was picked EARLIER (placed later).

Hmm, both are candidates for the same slot. If both were boosted (max priority), the tie-break is LUID: the higher LUID is picked first → placed later. The load has a higher LUID (later in source) than the constant? The load statement comes first in the source... so the load has a LOWER LUID. Then the constant (higher LUID) would be picked first → placed later → the constant at 137 and the load at 130 = the TARGET!

But mine has the opposite. So in mine, the constant was NOT boosted while the load WAS. Difference: in the target, the load's pseudo has 2 sets (launder) → the load is not boosted → the constant (boosted) is placed last. In mine, the load IS boosted and the constant is NOT.

So why is the constant not boosted in mine? Because... hmm! Maybe because the constant pseudo in mine has 2 sets! Where would the 2nd set come from? The 2 uses of 0xFF000000 (the two ANDs). If cse merged them into one pseudo with 1 set... but maybe gcc's cse created the constant pseudo with 2 sets (one per use) — cse's "reg_eqv" may not merge the two constants (they're both 0xFF000000 constants, but cse might keep 2 separate constant insns, each with its own pseudo!). Hmm, but then the emitted code would have 2 luis. The target has ONE lui (at 137) used by both ands (139 and 154). So it's one pseudo with 2 uses.

Hmm. So in mine, the constant has 1 set and 2 uses and is NOT boosted, while in the target it IS boosted. The difference must be the "dest live" test or the priority interaction.

Hmm, maybe: the boost sets priority = max_priority, but the *effective* placement also depends on the chain priority. The constant's chain: lui→and→or→store: pri 1. The load's chain: lw→and→or→store: pri 2 (load cost 2). In the backward scheduler, the chain priority determines when the insn becomes ready: the consumer (and) has pri 2; the load (its pred) has pri 2; the constant (another pred of the and) has pri 1.

The ready list picks the highest priority first. The load (pri 2 + boost) is picked before the constant (pri 1) → the load is placed later (at 137) and the constant earlier (130). ✓ mine.

In the target, the load is NOT boosted → pri 2; the constant IS boosted → max_priority (> 2?) → the constant is picked first → placed later (137), and the load at 130 ✓.

So for the target, the constant's boost must give it a priority higher than the load's pri-2 chain. max_priority is the "launching insn's" priority — fine.

So the question remains: why is the constant not boosted in mine? If it were boosted (max pri), it would beat the load's pri 2.

Hmm! Unless in mine the constant's dest pseudo has 2 sets. Where from? OH WAIT! Maybe in mine, the constant 0xFF000000 is used in TWO different ANDs, and gcc's cse created the constant pseudo ONCE but with 2 sets?? No...

Hmm, alternatively: in mine, maybe the two ANDs don't share the constant: the first AND uses the constant, the second AND (in the second store) uses a *different* constant pseudo (0xFF000000 again) — but the emitted code shows only ONE lui (at 130) — and both ands (139, 154) use a2 → so they share.

OK, let me stop theorizing and get the actual sched1 dump. The brief mentions tools/cc1_dumps_tu.sh and .run/P40/T10/hdump.sh for dumps. But maybe I can reason from experiments: what makes the constant boosted?

Alternatively — maybe the answer is much simpler: what if I *split* the constant too, e.g. give the constant's pseudo 2 sets?! Hmm.

Let me look at this from the "what does the C source need to look like" angle:
Target: the load of pv happens EARLY (right after the bidx load), and the constant 0xFF000000 is materialized LATE (just before its first use).

The original source (game's source) probably was:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
```
Same as ours. And with the original compiler (not gcc 2.7.2) the order came out as the target. Our gcc 2.7.2 needs a nudge.

The nudge in the banked body is the launder. What plain-C nudge gives the load a 2nd set?

Per the doc: "add a 2nd SET that survives cse — the §30 #3 re-tie `__asm__("" : "=r"(x) : "0"(x))` in a LATER bb, or the end-of-function dead-`volatile` `__asm__ volatile("":"=r"(x))` for spilled pseudos. A plain C reassignment does NOT work if cse/flow can eliminate it (t5/t6 proofs)."

"in a LATER bb" — the 2nd set must be in a later basic block! Because REG_N_SETS is per pseudo, and a pseudo live across bbs... Hmm, but the counts are global per pseudo. Hmm, but the doc says "in a LATER bb" for the re-tie. My split is in the same bb — and it didn't work, consistent!

Why would the bb matter? Because in the same bb, cse/flow may eliminate the 2nd set... but our 2nd set (the AND) is live and used. Hmm.

Hmm, hold on. Let me re-read: "add a 2nd SET that survives cse — the re-tie in a LATER bb, or the end-of-function dead-volatile for spilled pseudos". Maybe the point is: the 2nd set must be a set of the SAME pseudo (not a new pseudo). In my split, the AND's dest is a NEW pseudo (a temp), not pv's pseudo! Because gcc assigns `pv = expr` to a fresh temp pseudo and (for a register variable) may or may not copy to pv's pseudo.

That's the key: to give pv's PSEUDO a 2nd set, the 2nd assignment must write to pv's pseudo. gcc does that when the variable is *address-taken* or when it's a "local variable whose address is never taken" — gcc's local vars live in a pseudo (DECL_RTL) and assignments do write to it... but cse/flow can then propagate.

Hmm, since the load `pv = *(u32*)p` — its result goes into pv's pseudo (the load's dest IS the pseudo). And `pv = pv & 0xFF000000` — the AND's dest should also be pv's pseudo (gcc reuses the same pseudo for the variable's assignments in the same bb when the value isn't otherwise needed). So the pseudo has 2 sets. And yet the boost wasn't killed.

Unless the AND's dest was a NEW pseudo because... hmm.

OK — empirical: let me test the hypothesis by trying a variant where the split's result is used in a way that forces the AND into pv's pseudo.

Actually, better: let me test the doc's recipe directly: "a plain C reassignment does NOT work if cse/flow can eliminate it". Let me try a variant where the 2nd assignment to pv is in a LATER bb! E.g.:

```
    ...
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    pv = pv;   /* hmm, identity */
```
No.

Hmm, what about making the 2nd set of pv be a *real* value stored somewhere? E.g. the second store could use pv:
```
*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
pv isn't used there.

Hmm, what if the split's 2nd set is used LATER (in a later bb)? The function's last statement is the launder (at the end). What if I add a real use of pv at the end? That would change the code (extra instructions) → no.

OK OK. Let me think about the "later bb" requirement differently: maybe REG_N_SETS is computed per pseudo and my split DOES give 2 sets, but the boost is not killed because the boost test is on the *dest of the boosted insn* and the boosted insn is the AND, not the lw! I.e.: the load's dest pseudo has 2 sets → the load is not boosted ✓ (good, that's what we want) — but the AND's dest is the same pseudo (also 2 sets) → the AND is not boosted either. And the constant (1 set) → boosted → should be placed late. But in my candidate the constant is at 130 (early) — contradiction!

So in my candidate the constant was NOT boosted. Grr.

Let me just look at the sched1 dump. There's `.run/P40/T10/hdump.sh` and `tools/cc1_dumps_tu.sh`. The brief says dumps go under my item dir and must be deleted after. Let me look at hdump.sh to see how to use it.

Actually, maybe a cheaper experiment first: try the variant where the split is done differently:
(a) `pv = pv & 0xFF000000;` (done: 11)
(b) `pv = pv & 0xFF000000;` and use pv in the store (done)
(c) split the second store's masked value: `m2 = *(u32 *)(ot + 0x40); m2 = m2 & 0xFF000000; *(u32 *)(ot+0x40) = m2 | ((u32)p & 0xFFFFFF);` — this gives the SECOND masked value a 2nd set; but the constant 0xFF000000 now has 2 uses still.

Hmm, what if the launder's effect is on the *constant* rather than pv? The launder is `__asm__ __volatile__("" : "=r"(pv));` — out-only, on pv. It creates a new pseudo (the asm's output) tied to pv's reg. Hmm, "tied" — so the asm's output pseudo is a *copy* of pv's pseudo. So pv's pseudo gets an extra SET? If the asm's output is a distinct pseudo tied (equal) to pv's pseudo, then the tie means REG_N_SETS(pv_pseudo) might count 1 (the tie is a separate pseudo).

Hmm! But the comment in the source says "zero-byte 2nd SET: kills the sched1 birthing boost". So the author believes it creates a 2nd set of pv.

Honestly, let me now consider the alternative: maybe the *boost* being killed is on the CONSTANT pseudo, and the mechanism is: the asm's output pseudo is born at the END of the function; the boost applies to "an insn whose dest is live" — the constant's def is live; hmm.

Time check: I've spent a lot on this item. Let me be pragmatic: try 3-4 more variants quickly, and if none works, record a WALL with the evidence and move on to the other 7 items (some of which may be easy, e.g. item 8 with the same "out-only launder" pattern, and item 3/7).

Variants for func_8018AA98:
V1: `pv = pv & 0xFF000000;` split (11) — done.
V2: Split the second store's value instead:
```
    m2 = *(u32 *)(ot + 0x40);
    m2 = m2 & 0xFF000000;
    *(u32 *)(ot + 0x40) = m2 | ((u32)p & 0xFFFFFF);
```
V3: Both splits.
V4: The split placed differently: `pv = pv & 0xFF000000;` but with the store using `pv` — done in V1. What about assigning the masked value to a *fresh* variable: `u32 pm = pv & 0xFF000000; *(u32*)p = pm | ...;` (a fresh single-set local → creates a boost on the AND → the AND sinks to just before its consumer (the OR) — maybe that's what we want!).

Hmm! Interesting: V4 makes the AND a single-set def of a FRESH pseudo → boosted → the AND sinks to just before the OR. And the load (pv's pseudo, 1 set) → also boosted → sinks to just before the AND. Hmm, that gives: load, AND adjacent, near the OR — not the target.

What we want: the load EARLY (at its source position) and the constant's lui LATE (just before the AND).

To make the load early: the load's dest must NOT be single-set → pv's pseudo needs 2 sets → the split (V1). But V1 didn't do it. So maybe the split's AND went to a different pseudo. To force the AND into pv's pseudo... hmm, how about making pv's assignment the LAST use of the masked value in a way that gcc writes to the pseudo?

Actually! Here's a thought: gcc's "local variable" handling: a variable's assignments create SETs of its pseudo only if the variable is "address-not-taken" and gcc keeps it in a pseudo. But when the variable is used in the same statement right after, cse may substitute. In V1, the store reads pv → cse propagates the AND's result into the store's expression, and the AND's dest pseudo becomes single-use → flow may even delete the SET to pv's pseudo (dead store to a local var) → so pv's pseudo has just 1 set (the load) → the boost stays. That explains it!

So: to give the load's dest a 2nd set that survives flow, the 2nd set must be USED (not dead) — e.g. the value stored back to memory. `*(u32 *)p = pv | ...` stores the masked value to memory, but the AND's result feeds the OR, not directly the store.

What if we make the masked pv the DIRECT stored value? I.e.:
```
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
The store's value = OR(and(pv, mask), and(X, mask2)). The AND's result is used by the OR. The AND's dest pseudo is used once → flow keeps it (it's not dead). But is the AND's dest pv's pseudo? If gcc assigned it to pv's pseudo (because the source says `pv = ...`), then pv's pseudo has 2 sets and the boost is killed. But flow/cse may have replaced pv's pseudo with a fresh temp.

The doc says: "REG_N_SETS is counted after cse/flow — a source-level 2nd assignment that cse copy-propagates or flow dead-store-eliminates does NOT kill the boost (proof: exp/t5.c, exp/t6.c — both still boosted)". So in the t5/t6 experiments, the 2nd assignment was eliminated. Our V1's 2nd assignment: was it eliminated? The generated code shows the AND exists (it's needed). But whether its dest is pv's pseudo or a fresh temp is the question.

Hmm, in V1 the emitted code is "and v1,v1,a2" — v1 = $3 = pv's reg (pinned). So the AND's dest IS $3 (the pinned reg). But that could be a *different* pseudo that was later coalesced into $3 by regalloc! The pinned variable pv is in $3; the AND's temp pseudo could be allocated to $3 as well (since pv's pseudo is dead after the load... no wait, pv's pseudo is live until the AND reads it).

Ugh. So: in V1, pv's pseudo (holding the loaded value) is read by the AND, then dead. The AND's result is in a fresh pseudo → 1 set → boosted → the AND sinks to just before the OR. And the load's pseudo: 1 set → boosted → sinks to just before the AND. So the load is at 137 (just before the and at 139) ✓ observed. And the constant: hmm.

So V1 didn't change anything because the split didn't create a 2nd set of the LOAD's pseudo.

How to create a 2nd set of the LOAD's dest pseudo (pv's pseudo) that survives flow? The value loaded must be *redefined* into the same pseudo. That requires the variable to be "volatile" (then flow won't touch it) — but volatile is a lever-ish thing... Actually! `volatile u32 pv` — hmm, "volatile" for a local variable: the doc mentions "the end-of-function dead-`volatile` `__asm__ volatile("":"=r"(x))` for spilled pseudos" — they used a volatile ASM. But a `volatile` local variable is plain C!

But: "no new lever of any kind" — is a volatile local a "lever"? The lever census kinds: pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. A volatile local isn't in that list. But the brief's constraint says "no new lever of any kind" — hmm, a volatile store/load would be a "barrier"-ish thing (it forces the compiler to keep memory accesses). Since pv is a local (in a register), making it volatile would force it to memory → completely different code. NO.

Hmm. But what about this: the *load* pseudo needs a 2nd set. What if the same local is assigned twice with a value that is USED:
```
u32 pv2 = *(u32 *)p;   /* load into a fresh single-set local → boosted → sinks */
```
no.

Alternatively, think about the reverse: maybe I should target the CONSTANT's boost instead! What we need in the end: the load EARLY, the constant LATE. Currently (base): load LATE (boosted), constant EARLY (not boosted).

If I could make the LOAD not boosted, the constant (boosted) would be late and the load early ✓ — that's the target.

To kill the load's boost: the load's dest pseudo needs 2 sets. The load's dest is the pseudo for the loaded value (a temp, since the value is used once). To give it 2 sets: use the loaded value TWICE! E.g.:

```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
pv is used once. If pv were used twice, the load's pseudo would have 1 set but 2 uses — the boost is about SETS, not uses. Hmm! REG_N_SETS(dest)==1 → the boost applies. So uses don't matter; only sets.

So I need the load's dest pseudo to have 2 SETs. A load has 1 set by definition. So the *pseudo* must be set elsewhere too — i.e. the same pseudo must be the dest of another insn. That means the loaded value must be copied into an existing pseudo, or...

What if we load into a variable that is ALSO assigned elsewhere later? E.g.:
```
u32 pv;             /* local */
pv = *(u32 *)p;     /* load → SET(pv) */
...
pv = something_else;  /* 2nd SET → but this changes semantics */
```
Semantics change → no.

Hmm, but what if the 2nd set is a *copy* that cse keeps? Like:
```
pv = *(u32 *)p;
pv2 = pv;      /* copy: SET(pv2) reads pv — doesn't add a set to pv */
```
no.

To add a set to pv's pseudo, we need an insn with dest = pv's pseudo. `pv = <expr>` does that (if gcc keeps it as a set of the pseudo rather than propagating).

In V1, `pv = pv & 0xFF000000;` should be a SET of pv's pseudo... but gcc's cse/flow replaced pv's pseudo with a fresh temp (the "copy propagation" mentioned in the doc).

Hmm, so how do we make gcc keep a 2nd set of a pseudo? Use the variable in a way that forces materialization: e.g. take its ADDRESS? That would force it to memory.

Hmm, what about a *volatile* read of the variable? `volatile u32 pv;` — a volatile local is stored in memory (stack) → completely different.

What if pv is declared `register u32 pv __asm__("$3")` (already) — hmm.

OK, radical alternative: change the *source structure* so that the load's value is used in a way that gives the load's dest 2 sets naturally. E.g.:

```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
What if instead:
```
pv = *(u32 *)p;
t = pv & 0xFF000000;    /* t: single-set → boosted */
*(u32 *)p = t | (X & 0xFFFFFF);
```
The load's dest (pv's pseudo) still has 1 set. The load is still boosted → sinks. Same.

Hmm.

What about attacking from the other side: make the CONSTANT boosted (so it goes late) AND make the load early by *reducing* the load's chain priority? The load's chain: lw→and→or→store. The constant's chain: lui→and→or→store.

Both feed the same AND. The load has latency 2 → pri 2; the constant's chain pri 1. In the backward scheduler, the higher-pri insn is placed later. So the load goes later. To make the load earlier, its chain's priority must be ≤ the constant's. The load's priority is raised by the load's latency (2). Hmm, "Priorities can only be RAISED by C edits, never lowered" (S3).

Hmm, but if the constant is boosted to max_priority, it beats the load's pri 2 → the constant is placed later (137) and the load earlier (130) ✓ = the target!

So: I need the constant to be boosted. It's a single-set def (1 set, 2 uses) — so why isn't it boosted?!

Hmm, maybe because of "with the dest live": the constant's dest (0xFF000000 pseudo) — is it "live"? Yes.

OR maybe because the boost is applied to the FIRST insn that becomes ready with max priority, and only one gets it (the code might set priority = max_priority only for the launching insn). The doc: "on becoming ready, an insn whose pattern is SET(REG, …) ... has its priority raised to max_priority (≈ the launching insn's)".

Hmm, in the backward scheduler, "becoming ready" happens for an insn when all its successors are scheduled. The load and the constant both become ready when the AND is scheduled. The boost is applied to each as it becomes ready. So both would be boosted. Then the tie-break among equal (max) priorities: the LUID rule → the highest LUID is picked first → placed LAST.

The LUIDs: the constant's lui is early in the source (its def is materialized at the first use) hmm, actually where is the constant's lui in the RTL? The constant pseudo is created when the AND is expanded → at the AND's position (early in the RTL, before the store). The load is at the pv statement.

Source order: the pv load statement comes BEFORE the store statement, so the load has a LOWER LUID than the constant's lui. Among max-priority ties, the highest LUID (the constant's lui) is picked first → placed LAST (at 137) → the constant is late ✓ = the TARGET.

But in MINE, the constant is EARLY (130) and the load LATE (137). So in mine, the load won → the load was boosted and the constant wasn't (or the constant's priority was lower).

If both were boosted, the constant (higher LUID) would be placed last → target. So in mine, the constant is NOT boosted. Why?!

REG_N_SETS(constant pseudo) == 1 → should be boosted. UNLESS the constant pseudo has 2 sets in mine! Hmm, how? If the two ANDs (in the two stores) each got their own constant pseudo (cse didn't merge them) — then each has 1 set... but the emitted code shows one lui used by both ands.

Hmm, unless the emitted "lui a2,0xff00" is for the SECOND use and the first use has its own constant that was... no, only one lui exists.

Wait, actually, let me re-look at the mine diff:
```
137  lw	v1,0(s1)                        | lui	a0,0xff00
139  and	v1,v1,a2                        | and	v1,v1,a0
```
mine[137]=lw, target[137]=lui. mine[139]=and v1,v1,a2 (a2 = the constant), target[139]=and v1,v1,a0 (a0 = the constant).

And mine[130]=lui a2,0xff00, target[130]=lw v1,0(s1).

So both have exactly one lui. ✓ shared.

So the difference is just WHERE the lui is (130 vs 137) and correspondingly the load (137 vs 130).

Given the LUID rule, if both were boosted, the higher-LUID (the lui? or the lw?) is placed last. Which has the higher LUID? The lw (pv load) is at an earlier source position than the lui? The lui is materialized at the expansion of the AND, which is in the store statement — AFTER the pv load statement. So the lui has a HIGHER LUID → picked first → placed last (137) → target.

So in the target, both are boosted (or the load is unboosted and the lui is boosted). In mine, the load is boosted and the lui is NOT boosted (it stays at its chain position 130).

Why is the lui not boosted in mine? Because... the priority of the lui's chain is 1 and the boost sets it to max_priority — if max_priority is the "launching insn's" priority, maybe max_priority is small (like 1) in this block, so boosting doesn't change anything! I.e. the boost raises the priority to max_priority, which may be LOWER than the load's pri 2? Hmm, no: max_priority should be the max.

Hmm, hmm. But notice: in the target the load is at 130 — the load's chain pri is 2 and the constant's chain pri is 1 — if the constant were boosted to max (=2 or more), it'd be placed later. If the load is NOT boosted, its pri stays 2 and the constant's boosted pri (max) > 2 → constant placed later ✓.

In mine: the load IS boosted (pri → max) and the constant is NOT boosted (pri 1) → the load (max) is placed later ✓ (137) and the constant (pri 1) earlier (130) ✓.

So the question is: why is the constant not boosted in mine? Maybe because in mine, the constant's dest pseudo is NOT live at its def? Hmm.

OR: maybe the boost applies only to insns whose dest is a PSEUDO (not a hard reg)? The doc's correction says "any REG, pseudo OR hard". Hmm.

OR: maybe the boost is applied only ONCE per bb (the first single-set def that becomes ready)? If so, in mine the load becomes ready first (it's earlier in the RTL, so it becomes ready earlier in the backward pass?) and takes the boost; in the target, the load is NOT single-set (2 sets from the launder) so the constant takes the boost.

That model fits perfectly! And it also explains why my V1 split didn't help: the split didn't give the LOAD's dest pseudo a 2nd set.

Hmm, but V1's split gives the AND's dest (a fresh pseudo) 1 set, so the AND would be boosted (it becomes ready when the OR is scheduled, later). Hmm.

OK, so the key question remains: how to give the LOAD's dest pseudo a 2nd set, in plain C?

Hmm! What if the loaded value is stored into a variable that is ALSO used later in a way that requires materialization? E.g.:

```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
→ the load's dest pseudo is used once (by the AND) → flow may keep it as a temp.

What if:
```
pv = *(u32 *)p;
t = pv & 0xFF000000;
*(u32 *)p = t | (X & 0xFFFFFF);
```
→ the load's dest is pv's pseudo (1 set).

To get 2 sets on the load's dest pseudo, the value must be SET twice into the same pseudo. E.g.:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;   /* 2nd set into pv's pseudo */
```
For this to survive, gcc must not propagate. gcc's cse would replace the use of pv in the AND with the load's value, and then the SET to pv's pseudo becomes dead → flow removes it → 1 set. That's the "t5/t6 proof" in the doc.

To prevent that, the 2nd set must be USED in a way that can't be folded. E.g. if pv's value is used AFTER the 2nd assignment in a way that requires the pseudo... but then the 2nd set is the load's set (the last one) and the load's set is what got propagated away.

Hmm. Actually — what if the ORDER is reversed: first a real assignment, then the load? Like:
```
pv = 0;              /* SET 1 */
pv = *(u32 *)p;      /* SET 2 (the load) */
*(u32 *)p = (pv & 0xFF000000) | ...;
```
Then pv's pseudo has 2 sets: the "= 0" and the load. But cse/flow would remove the "= 0" as a dead store (it's overwritten before any use) → 1 set. Unless the "= 0" is used...

Hmm. What about:
```
pv = *(u32 *)p;
... uses ...
pv = 0;      /* dead store at the end → flow removes it */
```
No.

What if the 2nd set is in a LATER BB (as the doc says)?! E.g. put the masked value into a variable that's used in a later bb... but the function has only one bb after the last call? Let me look at the function structure: the launder is at the end of the function. Are there multiple bbs? The function has calls (RotMatrixZ, ApplyMatrixSV, func_80016638) → each call ends a bb. So the last statements are in a later bb than the pv load!

Indeed: `func_80016638(...)` is a call → the code after it (including the launder) is in a NEW bb. So the launder's 2nd set of pv is in a LATER BB than the load! And the doc says the re-tie must be "in a LATER bb"!

So the fix: give pv a 2nd set in a later bb. In plain C: after the last call, assign pv again in a way that survives flow. E.g.:

```
func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
pv = pv & 0xFF000000;    /* 2nd set of pv, in a later bb */
```
But this is dead code → flow removes it. Unless the value is USED. Hmm, but the launder's output is also dead (the asm's output is unused) — and yet it counts! Because an asm's output can't be deleted by flow (asm insns are not flow-removable).

So we need something in a later bb that (a) sets pv's pseudo and (b) survives flow. A store to memory! E.g. `*(u32 *)p = pv;`? That changes semantics (an extra store) → the target has no such store → mismatch.

Hmm, what if the *existing* code in the later bb uses pv? It doesn't.

Hmm, so we need a 2nd set of pv's pseudo in a later bb that survives. Options:
- A store of pv to memory that the target also has? No.
- Hmm, what about making the LAST store use pv? E.g. the last store is `*(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);` — no pv.

Hmm.

OK, alternative: maybe instead of giving the LOAD 2 sets, I should prevent the load from being the "first boosted" by another means. E.g. if the constant's def is boosted instead.

Per my model (only one boost per bb, first to become ready), the load (earlier RTL) wins. To make the constant win, the load must not be single-set.

What if the load's value is used TWICE (2 uses)? Then the load's dest pseudo is still 1 set → still boosted. Hmm.

What if the load is *split* into two loads? E.g. `pv = *(u32*)p;` → the value used once. Hmm.

What if the AND is written to read pv twice: `(pv & 0xFF000000) | ((pv & 0) & 0xFFFFFF)`? Nonsense.

Hmm, what about making the load's dest pseudo have 2 sets by loading into a variable and then re-loading... no.

OK, let me look at the t5/t6 experiments mentioned in the doc: "exp/t5.c, exp/t6.c — both still boosted". Maybe those files exist in the repo (exp/ dir?). Let me look for them — they might show the exact shapes that failed, and maybe a nearby one that worked.

Let me search for exp/t5.c.

Actually, let me reconsider the whole approach. Since the target's order requires the load early, and the load's chain has pri 2 (load latency), while the constant's chain has pri 1 — with the boost, the constant gets max pri and goes late. Without a boost on the constant, the load (pri 2) goes late.

What if I RAISE the constant's chain priority to ≥ 2? "Priorities can only be RAISED by C edits, never lowered." The constant's chain: lui → and → or → store. Its priority is 1 (all ALU). If the constant's chain were fed by a load, it'd be pri 2. Hmm! What if the mask constant is derived from a LOAD? E.g. instead of the literal 0xFF000000, use a value loaded from memory? That changes the code (extra load).

Alternatively, what if the constant is computed as `~0x00FFFFFF` (a NOT of another constant)? The chain: lui (0x00FFFFFF) → nor → and. Hmm, that's an extra insn.

Hmm, but wait: the *boost* is exactly the mechanism the launder used. The launder gave pv a 2nd set → the load isn't boosted → the constant (boosted) wins. So the constant IS boosted in the target. So the model "only one boost per bb" must be wrong, OR in the target the load is not single-set (correct) and the constant is single-set (boosted) — both facts.

So in mine, why isn't the constant boosted? If both were boosted, the LUID tie-break would put the constant (higher LUID) last → the target. So in mine the constant is NOT boosted. Its dest has 1 set... unless the constant pseudo has 2 sets in mine!

AH WAIT!!! I think I've got it: in mine, maybe the constant 0xFF000000 has 2 SETS because the second store's AND uses a *separate* constant pseudo (cse created a second lui?). No — only one lui in the code.

Hmm, but what if the *second* use of the constant comes from a different pseudo that was coalesced? E.g. cse created constant pseudo A (1 set) for the first AND and constant pseudo B (1 set) for the second AND, and then... no, only one lui exists.

OK, empirical again. Let me try: what if I write the second store's mask differently to change the constant's set count, e.g. `(*(u32 *)(ot + 0x40) & 0xFF000000)` → `(*(u32 *)(ot + 0x40) & ~0xFFFFFF)`. Hmm.

Let me instead try the simplest possible experiment set for this item:
E1: V1 (split pv) → 11 (done)
E2: split the second store's value (m2 = m2 & 0xFF000000)
E3: E1 + E2
E4: use a fresh local for the first masked value: `u32 pm = pv & 0xFF000000; *(u32 *)p = pm | ...;`

E4 creates a single-set def (the AND) → boosted → the AND sinks to just before the OR; and the load's dest (pv's pseudo) has 1 set → boosted → the load sinks to just before the AND. Result: load, AND adjacent, late. Not the target.

Hmm.

E5: make the load's dest have 2 sets by loading into a variable and then re-assigning from a *different* source that keeps the value: e.g.
```
pv = *(u32 *)p;
```
→
```
pv = *(u32 *)p;
pv = pv;   /* identity — explicitly disallowed */
```
no.

Hmm, what about the load's *value* being used in a context that forces a copy into an existing pseudo: e.g. the store `*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);` — the AND's dest is a fresh pseudo. If instead we write the store as:
```
*(u32 *)p = pv & 0xFF000000 | X & 0xFFFFFF;
```
same.

I wonder — maybe the trick is elsewhere: maybe the *load* should be moved to a different statement position so that its "consumer" is different. Hmm.

Let me try to get the sched1 dump to see the priorities. The brief says: ".run/P40/T10/hdump.sh (header pass dumps), tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps)". Let me look at hdump.sh — maybe it dumps a TU's cc1 passes.

Given the time, let me consider: maybe this item is a WALL (the launder is load-bearing for the birth boost and there's no plain-C way to give a load's dest a 2nd set that survives flow). But the doc says: "the end-of-function dead-`volatile` `__asm__ volatile("":"=r"(x))` for spilled pseudos" — both are asm. So the doc's own recipes for killing a boost are asm-based! That suggests a plain-C 2nd set generally does NOT work (as the t5/t6 proofs show).

Hmm, but the moves.md has several launder MATCHes via "real 2nd set" (e.g. "launder->real 2nd set pv &= 0xFF000000 split"). Those are cases where the launder's effect was cse-related, not boost-related.

Given the doc's explicit statement ("A plain C reassignment does NOT work if cse/flow can eliminate it"), and our V1 failing, this item may be a WALL with tag "sched1-birth-boost".

But wait — before giving up, let me reconsider: maybe the fix is to make the *constant* have 2 sets (so the constant is not boosted) and the load... no, we want the opposite.

Hmm, let me reconsider the direction: maybe we don't need to kill the load's boost; maybe we need the *load* to be boosted but placed EARLY. "Boosted = max priority = placed LAST". Hmm.

What if the load's chain priority were LOWERED? Can't.

What if the load were removed from the chain: i.e. the load's value is used by the AND, but if the AND were in a different bb or the load's consumer were earlier...

Hmm, what about this: what if the whole first store is restructured so that the load of pv happens in a *different* position — e.g. the load is moved to just before the store (it's already). Hmm.

Let me look at the target's full instruction list for this function to see the whole picture, and my candidate's. Maybe there's a cheaper structural difference. Let me dump both around 120-160.

Actually, let me reconsider the problem from the "original source" angle: the target came from the ORIGINAL game's compiler (not gcc 2.7.2) — wait, no! Hmm, actually for these "nonmatchings" the target IS the original game's assembly (from the retail ROM), and we're trying to reproduce it with gcc 2.7.2. The banked body with the launder reproduces it exactly. So the launder is a gcc-2.7.2-specific hack.

OK. Given the time budget (20-30 min/item, 8 items), let me time-box item 1 (func_801832A8) and item 5 (func_8018AA98) and move on. Actually, I'm already ~40 minutes in on item 1. Let me record item 1 and item 5 attempts efficiently.

Let me reconsider the priority of the whole shard: 8 items × ~25 min = 3.3 hours. That's a lot but it's the task. I should move fast.

Strategy: For each item, the launder removal is the goal. Let me look at each item's launder and see if the "real 2nd set" applies (like item 5) or if the launder is a *barrier-like* scheduling device (item 1).

Let me now do quick experiments for item 5 (func_8018AA98) with a few more variants, then move to other items, then come back.

For item 5, let me try:
E2: split the second store's masked value (m2).
E4: fresh local for the first masked value.

And also:
E6: `pv = pv & 0xFF000000;` AND ALSO make the second store use a fresh local:
```
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
```
Hmm.

Let me think about which is most likely: the launder is `__asm__ __volatile__("" : "=r"(pv));` — out-only, at the END of the function, in a later bb. Its output pseudo is a 2nd set of pv's reg. The effect per the doc: kills the boost of the *load* (which is in an earlier bb) — because REG_N_SETS(pv's reg) becomes 2 (the load and the asm output, if the asm output is tied to the same pseudo).

Hmm! "tied" — in gcc, `__asm__("" : "=r"(pv))` with pv a variable: the output operand is a new pseudo TIED to pv's reg (via a TIE insn). The tie means the asm's output pseudo and pv's pseudo are equal. REG_N_SETS counts sets of the *pseudo* — the tie insn is a SET of the output pseudo (a copy). If gcc ties them (make_regs_eqv), the two pseudos are equivalent and cse may merge them into one → then the load's dest pseudo has 2 sets ✓ (the load and the tie/copy).

So the mechanism: the asm creates a 2nd SET of the pseudo that the load writes.

In plain C, to create a 2nd set of the load's dest pseudo that survives cse/flow, we need... the value to be SET twice into the same pseudo, with the 2nd set not being propagated away.

Hmm! What if the 2nd set is a *store* of the value to memory? E.g.:
```
pv = *(u32 *)p;
...
*(u32 *)p = (pv & 0xFF000000) | (X & 0xFFFFFF);
```
The store's value is the OR — not pv.

What if we make the store write pv itself in a separate statement and the target has such a store? No.

OK, alternative idea: give the *load* a 2nd set by making the loaded value the dest of a MOVE into an existing pseudo — i.e., if the value is copied into a variable that already has a pseudo (like the pinned pv!).

WAIT. pv is PINNED to $3! So pv's pseudo is a hard-reg-bound pseudo. The load `pv = *(u32*)p` — is its dest pv's pseudo or a temp? If pv is a pinned (hard-reg) variable, gcc might load directly into a temp and then copy to pv's pseudo... or load directly into pv's pseudo.

Hmm! Here's an idea: if the load's dest is a TEMP (not pv's pseudo), then giving pv a 2nd set wouldn't kill the load's boost. Conversely, if I could make the load write into pv's pseudo AND give pv's pseudo a 2nd set...

In V1 I split: `pv = pv & 0xFF000000;` — the AND's dest = pv's pseudo (2nd set of pv's pseudo) — but the LOAD's dest may be a temp! Then the load's temp has 1 set → boosted → sunk. And the constant (1 set) → also boosted? but only one boost wins...

Hmm, and the observed V1 result: the load still at 137 (sunk) ✓ consistent with the load being boosted.

And in the target: the load is NOT sunk. So in the target, the load's dest has 2 sets — meaning the load writes pv's pseudo directly and pv's pseudo has a 2nd set (the asm tie).

So the difference between the target and my V1: in the target the LOAD writes pv's pseudo (2 sets: load + asm), in mine the load writes a temp (1 set) and pv's pseudo gets the AND.

How to make the load write pv's pseudo directly? If the variable is used in a way that requires it (e.g. its address is taken, or it's a "volatile" var). Hmm, or if the value is used more than once?

Actually, gcc's RTL for a local variable: `pv = *(u32*)p;` → the load's dest is a fresh pseudo (reg) and then flow/cse may eliminate the copy to pv's DECL_RTL. For a *pinned* variable, hmm.

Honestly, at this point the empirical route is best: let me try a batch of variants for item 5 and see if any hits 0. Variants:
V1 (done, 11): split pv.
V2: `u32 pm = pv & 0xFF000000;` (fresh local) + store uses pm.
V3: `pv = pv & 0xFF000000;` AND `m2` split for the second store.
V4: reorder: move the `ot = ...` statement BEFORE the first store? (changes semantics? `ot` is computed from bidx and D_800A651C; the first store writes to *p, and ot is a different address. But `*(u32 *)p = ...` modifies p's target; ot is computed from D_800A651C + bidx*20 — independent of p. So reordering is safe semantically!) That changes the RTL order and hence the LUIDs and the schedule! Cheap to try.
V5: move the pv load later/earlier in the source.

Let me try V2, V3, V4 in one batch (3 files), then score each.

Actually, let me think about V4 more: the target's order is: [base addr] [lhu bidx] [lw pv] [sll/addu] [lui mask] [and]... The `ot = *(s32 *)(...)` statement computes the 2nd address; the target's 133-136 region (equal in both) probably contains the address computation for ot.

Let me now just run the experiments. Time is ticking; let me batch 3 variants.

To generate them, one sed -z command writing 3 files (cumulative transforms must be independent → I'll write each variant from orig.c separately using 3 separate sed commands... hmm, that's 3 commands + 3 scores = 6 calls).

Alternatively, use a single sed -z run with the `w` command after each transform, but I need each variant to start from orig.c. Trick: use the `w` command to save the ORIGINAL into a hold space first? Hmm: -e 'h' saves the pattern; then transforms; then 'w file'; then 'g' to restore the original, then the next transform. Like:

sed -z -e 'h' -e 's|A|B|' -e 'w v2.c' -e 'g' -e 's|C|D|' -e 'w v3.c' -e 'g' -e 's|E|F|' -e 'w v4.c' orig.c > /dev/null

That works! (g = get from hold space).

Let me do that.

V2: fresh local for the masked value:
  decl: add `u32 pm;` — where? The decls are in the function; add after `register u32 pv __asm__("$3");`.
  s|            pv = pv & 0xFF000000;|...| — V2 = replace the store's expression:
  old: "    *(u32 *)p = (pv & 0xFF000000) |\n                (CAST_NONSTRUCT..."
  new: "    pm = pv & 0xFF000000;\n    *(u32 *)p = pm |\n                (CAST_NONSTRUCT..."
  and add the decl.

V3: V1 + the second store's masked value split:
  "    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);"
  → "    m2 = *(u32 *)(ot + 0x40);\n    m2 = m2 & 0xFF000000;\n    *(u32 *)(ot + 0x40) = m2 | ((u32)p & 0xFFFFFF);"
  with decl `u32 m2;`

V4: reorder: move the `ot = ...` statement before the first store.

Let me write the sed command. Careful with the escaping of special chars: `*`, `(`, `)`, `&` (in the replacement & = the whole match), `|`, `.`, `[`, `]`, `^`, `$`, `\`.

In the replacement, `&` must be escaped as `\&`, and `\n` is a newline.

Let me construct:

V2:
sed expr 1: s|    register u32 pv __asm__("\$3");|    register u32 pv __asm__("$3");\n    u32 pm;|
  (note: in the file the line is "    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */  // !FAKE: pin $3 ...")
  Let me match a shorter unique prefix: `register u32 pv __asm__("\$3");` — the `$` in BRE is special only at the end of the pattern; `\$3` — hmm, in BRE, `$` is special only at the end of the regex, so "$3" is literal. But to be safe, escape as \$.
  The replacement: the matched text + "\n    u32 pm;" — I need to keep the rest of the line, so I should match only the prefix and replace with prefix + new line:
  s|register u32 pv __asm__("\$3");|register u32 pv __asm__("$3");\n    u32 pm;|
  Careful: in the replacement, "$3" is literal, fine. But `&` isn't present. OK.

sed expr 2: s|    \*\(u32 \*\)p = (pv & 0xFF000000) \|\n|    pm = pv & 0xFF000000;\n    *(u32 *)p = pm \|\n|
  In the pattern, `&` is literal (BRE), `*` needs escaping, `(` `)` literal in BRE. The `|` delimiter conflicts with the literal `|` in the source → escape as `\|` in the pattern. In the replacement, `&` must be escaped as `\&`.

Let me write it carefully. Pattern: `    \*\(u32 \*\)p = (pv & 0xFF000000) \|\n`
Hmm, in BRE, `(` and `)` are literal, so `\(` would start a group. I need literal parens → just write `(` `)`. And `*` → `\*`.

Pattern: `    \*(u32 \*)p = (pv & 0xFF000000) \|\n`
Replacement: `    pm = pv & 0xFF000000;\n    *(u32 *)p = pm \|\n`
Wait, the replacement contains `&` which must be escaped: `\&`. And the literal `|` in the replacement is fine (delimiter only matters in the pattern? No! The delimiter terminates the s command, so the replacement can't contain an unescaped `|`). So escape it as `\|`.

So replacement: `    pm = pv \& 0xFF000000;\n    *(u32 *)p = pm \|\n`

OK. Let me now also handle V3 and V4. This is getting long; let me do V2 and V4 (V3 is more complex).

Actually, let me reconsider: is there a smarter way? Let me look at the "worked example" from T10 (func_80181F4C) — its notes say the win was a "do-while(0) ref boost". And the moves.md for launder items shows "real 2nd set" wins. Those are cases where the launder was a cse-opaque device.

For item 5, the launder is explicitly "kills the sched1 birthing boost" → a boost device → the doc says the only ways to kill a boost are asm-based re-ties... but our constraint forbids asm. Hmm, but wait: the constraint forbids *launder* asm and *new* levers. What about a `do { } while(0)`? No.

Hmm, what about the "2nd SET ... in a LATER bb" recipe: the doc says the re-tie in a later bb works. In plain C, a 2nd set in a later bb that survives flow... e.g.:

```
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    pv = pv;     /* identity → disallowed, and flow removes it */
```

Hmm.

What if the 2nd set is a *store* to a global that the target also stores? No.

OK, let me try the empirical variants. Let me do V2 and V4 now.

Actually, hold on. Let me reconsider the problem once more. What if the real 2nd set doesn't need to be of pv at all? The boost applies to single-set defs. The load's dest temp has 1 set. What if the load's dest temp gets a 2nd set because the SAME temp is used for something else? E.g. if the AND's result were the same temp as the load's dest (in-place): `pv = pv & 0xFF000000` — in-place AND: dest = the load's temp! Then the load's temp has 2 sets (the load and the AND) → the boost is killed ✓✓.

That's exactly what V1 does IF gcc does the AND in place. And in the emitted code, the AND was "and v1,v1,a2" — in place (dest = src = v1)! So the AND's dest IS the load's temp (in-place) → 2 sets → the boost should be killed!

But V1 gave the same 11 mismatches with the load still at 137. Hmm!! Unless the "in place" AND was introduced by regalloc (coalescing) rather than in the RTL.

Hmm, in gcc's RTL, `pv = pv & 0xFF000000` where pv's value is in a temp T: the AND's dest is a NEW temp T2 (gcc doesn't do in-place unless the variable is the same pseudo). If pv is a *variable*, gcc's assignment creates a new pseudo each time...

Unless we can force in-place by using the SAME variable: `pv = pv & 0xFF000000;` — gcc's RTL: the RHS is computed into a temp, then a SET(temp2, temp). Hmm.

OK, empirical. Let me just run the variants. Let me be quick.

Let me do 3 variants in one sed -z command (using h/g to restore between) and then score each.

V2: fresh local pm (as above).
V3: split the second store (m2).
V4: reorder the `ot` statement before the first store.

For V4, the source is:
```
    bidx = (u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (CAST_NONSTRUCT(u32, *(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)), 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
```
V4: move the `ot = ...` line to before the `pv = *(u32 *)p;` line? Or between bidx and pv? Hmm, the `ot` line's RTL would then be earlier → its address computation is earlier → different schedule. Let me try moving `ot = ...` to right after `bidx = ...`.

Let me write the command. Patterns:
V4 expr: s|    pv = \*\(u32 \*\)p;\n|    ot = *(s32 *)((u8 *)\&D_800A651C + (*bidx * 20));\n    pv = *(u32 *)p;\n| then remove the original ot line: s|    ot = \*(s32 \*)((u8 \*)\&D_800A651C + (\*bidx \* 20));\n|| — careful, that would remove the first occurrence (the one I just inserted). Use a different order: first remove the original ot line (it's unique), then insert it before the pv line.

Let me do: -e 's|    ot = \*(s32 \*)((u8 \*)\&D_800A651C + (\*bidx \* 20));\n||' -e 's|    pv = \*\(u32 \*\)p;|    ot = *(s32 *)((u8 *)\&D_800A651C + (*bidx * 20));\n    pv = *(u32 *)p;|'

Hmm, note: `&` in the pattern is literal (fine); in the replacement, `&` must be escaped → `\&`.

This is getting messy. Let me simplify by choosing a different, simpler set of variants. Time is precious.

SIMPLER IDEA: What if I make the load's dest have 2 sets by loading pv into a variable that is ALSO the dest of a later assignment in the same expression...

Hmm, what about this trick: `pv = *(u32 *)p;` → `pv = *(u32 *)p; pv = pv & 0xFF000000;` (V1) — and ALSO make the store use `pv` such that the AND is in-place in the RTL. To force in-place, gcc does in-place when the source and dest pseudo are the same, which happens when the variable's pseudo is reused. Since pv is a *pinned* variable (hard reg), maybe its DECL_RTL pseudo IS reused for the AND. In V1's emitted code the AND was in-place (and v1,v1,a2) — but that could be regalloc coalescing.

Let me test whether the RTL has 2 sets by checking if the *schedule* changed at all... V1's score was 11, exactly the same as base? Let me compare the diffs: base gave 30 with different mismatches (a0->a2 x6, v1->a0 x3...). V1 gave 11 with the same pattern (125 lui a0 vs lui a2 etc.). So V1 ≈ base (both 11? no, base was 30).

Hmm wait: base.c (no launder, no split) scored 30; V1 (split) scored 11. So the split DID change things! It reduced the residual from 30 to 11. Interesting!

Let me look at V1's residual more carefully:
```
125  lui	a0,0x0    | lui	a2,0x0
126  addiu	a0,a0,0 | addiu	a2,a2,0
129  lhu	v1,0(a0)  | lhu	a0,0(a2)
130  lui	a2,0xff00 | lw	v1,0(s1)
131  sll	v0,v1,0x2 | sll	v0,a0,0x2
132  addu	v0,v0,v1 | addu	v0,v0,a0
137  lw	v1,0(s1)   | lui	a0,0xff00
139  and	v1,v1,a2   | and	v1,v1,a0
143  lhu	v1,0(a0)  | lhu	v1,0(a2)
154  and	v0,v0,a2  | and	v0,v0,a0
157  lhu	v0,0(a0)  | lhu	v0,0(a2)
```
So V1's order is the same as base (lui at 130, lw at 137) but the REGISTERS differ: V1 uses a0 for the base and a2 for the mask, while the target uses a2 for the base and a0 for the mask.

And base.c's diff (score 30) showed the same register pattern? The base diff showed:
```
125  lui	a0,0x0  | lui	a2,0x0   (from the first diff, mine[125:127] vs target[125:127])
```
Hmm, the base diff (from the very first v1.c score, 30) showed:
```
replace mine[194:202] target[194:200]  ...
```
That was item 1, not item 5! Let me recheck: the score 30 diff I got for item 5 was V1 (the split). And base.c for item 5? I didn't score it! I scored orig.c (0) and then cand.c (V1, 11). So V1 = 11.

OK so for item 5, V1 (split pv) = 11, with the ORDER matching the target (lui at 130 in mine, 137 in target — no wait, mine has lui at 130 and the target has lui at 137: NOT matching).

Hmm, right: the order still differs (the lui/lw swap) and the registers differ.

Hmm, so the split gave 11 vs (unknown base). Let me score the base (no split, just the launder removed) for item 5 to see the delta. That's worth knowing.

Let me do that now: create base5.c = orig.c minus the launder line, and score.

Then I'll know if V1 helped.

Let me also prepare more variants. Let me run the base score first.
