---
ts: 2026-10-22T00:16:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_oJxPG3lN0LKnbORM0c9M
---
This is the key mechanism (S2 birthing boost):

"on becoming ready, an insn whose pattern is SET(REG, …) — any REG, pseudo OR hard — with the dest live and REG_N_SETS(dest)==1 (birthing_insn_p) has its priority raised to max_priority → it wins every tie → single-set defs sink to just before their first consumer."

So: a single-set definition (a pseudo/reg defined once) gets boosted when it becomes ready, so it SINKS to just before its first consumer. Wait, "sink to just before their first consumer" — the boosted insn is placed as late as possible (just before its consumer)?

Hmm, "has its priority raised to max_priority → it wins every tie" — it wins ties, so it goes FIRST among ready insns? But then it says "single-set defs sink to just before their first consumer". Hmm, contradictory. Let me read more of the doc — the full explanation with the priority mechanics.

Also: "REG_N_SETS is counted after cse/flow — a source-level 2nd assignment that cse copy-propagates or flow dead-store-eliminates does NOT kill the boost".

So to kill the boost on the constant, we need REG_N_SETS(constant pseudo) > 1 — i.e. the constant must be *set* twice in the RTL, not just used twice. A source-level 2nd assignment that cse folds doesn't count.

So the launder `__asm__ __volatile__("" : "=r"(pv));` creates a 2nd SET of pv's register (the asm output is a set of the same reg? or a new reg tied to pv). Hmm, the comment says "kills the sched1 birthing boost" — and the doc says the boost applies to "any REG, pseudo OR hard".

So which reg's boost is killed? The launder is on pv (pinned to $3 = v1). With the launder, the asm creates a 2nd SET of the $3 reg → the lw (which sets $3) is no longer single-set → no boost for the lw.

Hmm! But the lw is the load of pv; if the lw is boosted, it SINKS to just before its first consumer (the AND at 139). That's what happens in MINE: the lw at 137 is just before the and at 139! Yes!! In mine: 137 lw v1,0(s1); 139 and v1,v1,a2. The lw sank to just before its consumer.

In the target: the lw is at 130 (early, not sunk) — because the launder gave $3 a 2nd set, killing the boost, so the lw stays at its source position.

And the constant (0xFF000000 → a0/a2): the "lui" is a single-set def → boosted → sinks to just before its first consumer (the and at 139). In mine: lui at 130 — hmm, that's not just before 139. Hmm, "just before its first consumer" — the consumer of the constant is the `and` at 139. In mine the lui is at 130, which is before the sll/addu. Hmm.

Wait, maybe I have it backwards: in mine, the constant's lui is at 130 (early) and the lw at 137 (late). In the target, the lw is at 130 (early) and the lui at 137 (late).

So in the target, the *lui* is late (137) = just before its consumer (139)? Yes! 137 lui, 138 (equal, maybe nop), 139 and. And in mine, the *lw* is late (137) = just before its consumer (139). So in mine, the lw got the boost (sank to its consumer) and the lui stayed early; in the target, the lui got the boost (sank to its consumer) and the lw stayed early.

So: the boost applies to whichever insn is a single-set def. In mine, the lw ($3 = pv's reg) is single-set → boosted → sank. The lui (constant) is also single-set → should also be boosted → but two boosted insns can't both sink... the one that becomes ready first wins.

With the launder, $3 has 2 sets → the lw is not boosted → the constant's lui gets the boost → sinks to 137. That's the target!

So the fix: give pv's register a 2nd SET in the RTL — without an asm!

How to give a register a 2nd set in plain C? A 2nd assignment to pv that cse does NOT fold and flow does NOT eliminate. E.g.:

```
pv = *(u32 *)p;
pv = pv & 0xFF000000;    /* 2nd set of pv (my split) */
```
Here pv's reg has 2 sets: the load and the AND. Does cse/flow kill the 2nd set? The doc says "a source-level 2nd assignment that cse copy-propagates or flow dead-store-eliminates does NOT kill the boost". My split's 2nd set is NOT dead (it's used in the store) and not a copy → so it should count! REG_N_SETS(pv's reg) = 2 → the lw is not boosted → the constant's lui gets boosted → sinks to just before its consumer.

But my candidate gave 11 mismatches with the lw at 137 (late) — hmm, so the boost wasn't killed? Let me check the candidate's dump to see the order. In the diff of the candidate:
```
137  lw	v1,0(s1)                        | lui	a0,0xff00
```
So in my candidate the lw is still at 137 (sunk) and the lui at 130. So the split did NOT kill the boost.

Why? Because `pv` is a *pinned* register (register u32 pv __asm__("$3"))! The doc note says: "the S2 birthing boost requires SET(REG_pseudo, …), and therefore that a `register __asm__` pin on the dest kills the boost ('Unpin first')" — but that note was CORRECTED: "in real 2.7.2, birthing_insn_p tests only reg_n_sets" — and there's a note: "the dest fails birthing_insn_p (needs SET(REG_pseudo,…)) → no S2 boost. Unpin first. ~~That reasoning does not hold.~~ birthing_insn_p (2.7.2 sched.c:2469) tests only ..." — the correction says the dest can be a hard reg too.

So with pv pinned to $3 (a hard reg), the lw (SET($3, mem)) is a single-set def of a hard reg → boost applies (per the correction). My split creates a 2nd set of pv → reg_n_sets($3) = 2 → boost killed. But the observed result says otherwise.

Hmm, unless the split's AND was folded into the store: `*(u32 *)p = pv | (...)` with pv = pv & 0xFF000000 → gcc computes the AND into a temp then ORs. So $3 would have sets: the lw (load) and... the AND's dest might be a different pseudo (not $3) if pv's reg is reused. Hmm: pv is pinned to $3, so the AND's result must go to $3 (pv's reg) → SET($3, ...) → 2 sets. Unless gcc used a temp and then copied.

Hmm, but the diff shows my candidate at 137 "lw v1,0(s1)" and 139 "and v1,v1,a2" — so the AND's dest is v1 = $3 → the AND is a set of $3. So $3 has 2 sets (the lw at 137 and the and at 139) — wait, the AND reads $3 and writes $3: "and v1,v1,a2" → dest = $3 = source. So $3's sets: the lw (137) and the and (139) = 2 sets → the lw should NOT be boosted → it should stay at its source position (early).

But it's at 137! Hmm. Unless the source position of the lw in my candidate is later. My candidate's source:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (X & 0xFFFFFF);
```
The lw is the 1st statement of that group, so its source position is early. But the compiler's RTL order: the load of pv comes after... hmm, the RTL order is the statement order: lw first.

Hmm, but the observed candidate has the lw at 137, i.e. after the lui (130). So the lw was moved down (sunk) or the lui was moved up.

Hmm, wait: maybe with the AND as a 2nd set of $3, the AND is the boosted one? The AND's dest is $3 (hard reg) and $3 now has 2 sets → not single-set → no boost for the AND either. Hmm, but the AND can't sink (it's the value used by the store).

Hmm, alternatively the boost applies to the *constant* (0xFF000000 → a2): single-set → boosted → should sink to just before its consumer (the and at 139)... but the lui is at 130 in my candidate. Hmm, that contradicts.

Unless "sinks to just before its first consumer" is wrong and the boost actually means "wins ties → goes FIRST" (i.e. hoisted up). Let me re-read: "on becoming ready, an insn whose pattern is SET(REG, …) with the dest live and REG_N_SETS(dest)==1 has its priority raised to max_priority → it wins every tie → single-set defs sink to just before their first consumer."

Hmm, "wins every tie" in the ready-list ordering means it's scheduled FIRST (earliest). But then "single-set defs sink to just before their first consumer" — that's the opposite. Unless "sink" here means "sink" in the sense of "the def sinks down to just before its consumer" = the def is placed LATE. But that contradicts "wins every tie → scheduled first".

Hmm, maybe the priority semantics in gcc's sched: higher priority = scheduled LATER? In gcc's ready list, the insn with the *lowest* priority number is chosen first? Let me read the actual doc section (sched.md) around those lines for the full explanation. Let me read sched.md lines 60-120.

This matters a lot: the difference between my candidate and the target is exactly this boost.

Let me read the doc.
