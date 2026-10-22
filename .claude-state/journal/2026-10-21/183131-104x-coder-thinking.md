---
ts: 2026-10-22T00:31:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bm0v0PIEaixA8krRhhlz
---
c1's listing (22-45):
```
26 lw v0,108(s1)
27 lui v1,0x0
28 addiu v1,v1,0
29 lhu v0,6(v0)
30 nop
31 sh v0,0(v1)
32 lw v0,108(s1)
33 nop
34 lhu v0,10(v0)
35 nop
36 addiu v0,v0,-64
```
Target (from the earlier dump):
```
26 lw v0,108(s1)
27 nop
28 lhu v0,6(v0)
29 lui v1,0x0
30 addiu v1,v1,0
31 sh v0,0(v1)
32 lw v0,108(s1)
33 nop
34 lhu v0,10(v0)
35 nop
36 addiu v0,v0,-64
```
So the target has: [26 lw][27 nop][28 lhu][29 lui][30 addiu][31 sh] and c1 has [26 lw][27 lui][28 addiu][29 lhu][30 nop][31 sh].

So in the target, the p10 materialization (lui/addiu) comes AFTER the v6 load (lhu) and there's a nop BEFORE the lhu; in c1, the materialization comes BEFORE the lhu and the nop after.

So the difference: the relative order of the p10 materialization and the v6 load, plus the nop's position.

In the target: the v6 load (lhu) is at 28, and the p10 materialization at 29-30 → the materialization is after the load. In c1: the materialization at 27-28, the load at 29.

And the nop: the target's nop at 27 (before the load), c1's nop at 30 (after the load). So the nop (the p10 asm's hole) is where the asm was scheduled.

Hmm: the p10 asm is after "p10 = &D_80190048;" in the source. The asm's hole position = where the asm was scheduled. In the target, the hole is at 27 — before the v6 load. So the asm was scheduled BEFORE the v6 load?!

Hmm, but the asm depends on p10's materialization (its "0" input) — so the materialization must precede the asm. In the target, the materialization is at 29-30, AFTER the hole at 27. Contradiction!

Unless the hole at 27 is the v6 asm's hole (the v6 re-tie) and the p10 asm's hole is at 33 or 35. And in c1 (the v6 asm removed), the p10 asm's hole is at 30, and the v6 hole... hmm, c1's nops: 30, 33, 35. The target's nops: 27, 33, 35. So c1 has nops at {30, 33, 35} and the target at {27, 33, 35}.

So in the target there are 3 nops: 27, 33, 35. In c1: 30, 33, 35. So one nop moved from 27 to 30.

Hmm, so the p10 asm's hole: in the target it's at 27 and in c1 at 30. Hmm, but the p10 materialization is at 29-30 in the target (after the hole at 27)?! That can't be for the p10 asm.

Unless the hole at 27 is the v6 asm's hole. The v6 asm is after "v6 = ...->unk6;" in the source. Its hole would be after the lhu (28)... but it's at 27 (before). Hmm!

Unless the target's lhu at 28 is NOT the v6 load but something else! Hmm: in the target, 26 "lw v0,108(s1)" (o = param_1->unk6C) and 28 "lhu v0,6(v0)" (v6 = o->unk6) ✓ that's the v6 load.

So the v6 asm's hole should be after 28. But the nop is at 27.

Hmm, so maybe the nops are not the asms' holes but the original game's nops (the target is the retail binary, and it has nops wherever the original compiler put them). And the banked body reproduces them via the asms' holes.

So in the target: nops at 27, 33, 35. In c1: nops at 30, 33, 35. The bank's version (with both asms) would have holes at the asms' positions: the v6 asm (after the lhu) and the p10 asm (after the p10 materialization) → 2 holes. But the target has 3 nops. Hmm, so one nop is a real nop in the original code (not from an asm).

Ugh. OK, so c1 is 4 off: the p10 materialization's position relative to the v6 load, and the nop position.

Hmm, the real question: can I get the ORDER right (the materialization after the load)? In c1, the materialization (lui/addiu) is before the load. In the target, after.

The materialization's priority: p10's pseudo is single-set → boosted → sunk to its consumer (the store) → hmm, in the target the materialization (29-30) is right before the store (31) ✓ boosted. In c1, the materialization is at 27-28, before the lhu (29) — NOT sunk to the store.

Hmm! So in c1, the p10 pseudo is NOT boosted (its boost is killed?) or the asm's presence changes it.

Hmm, wait: in c1 the p10 asm is still present! The asm creates a 2nd set of p10 → the boost is killed → the materialization stays at its source position (before the lhu? hmm, the source order is: v6 load, [asm v6 removed], p10 = &D_80190048, [asm p10], store). So the materialization's source position is AFTER the v6 load → the target ✓. But c1 has it BEFORE the lhu. Hmm!

Confusing. Let me flip: in the TARGET, the materialization is after the lhu (its source position ✓) and the boost is killed (the p10 asm gives it a 2nd set ✓). In c1, the p10 asm is present → the boost should be killed → the materialization at its source position (after the lhu) — but c1 has it before the lhu ✗.

Hmm, so in c1 the materialization was HOISTED above the lhu. Hmm, that means it was boosted (max priority → hmm, boost = placed LATE, not early).

I'm clearly not modeling gcc correctly. Let me try instead: what if the v6 load is moved in the SOURCE (e.g. after the p10 assignment)? I.e.:
```
            o = ...->unk6C;
            p10 = &D_80190048;
            [asm p10]
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            *p10 = v6;
```
Hmm, that changes the source order of the lhu and the materialization → the schedule might match the target (lhu then materialization) ✓. But the target's order is [lhu][lui][addiu][sh] — the lhu BEFORE the materialization. In the current source, the lhu is before the p10 assignment ✓ — so the source order already matches the target. And c1 doesn't. So the scheduler moved the materialization up in c1.

Hmm, so the c1 residual is: the materialization is hoisted above the lhu. What would prevent that? The p10 asm is a barrier (volatile) — it's between the p10 assignment and the store. Hmm, the materialization is before the asm (it's the asm's input) → so the materialization is before the asm. The lhu is before the p10 assignment. So the source order is: lhu, materialization, asm, store. And the asm (barrier) forces the materialization to stay before the asm ✓, and the lhu could be moved anywhere before the asm.

In c1: [lw][lui][addiu][lhu][nop][sh] — the lhu moved AFTER the materialization. In the target: [lw][nop][lhu][lui][addiu][sh] — the lhu is before the materialization, and the nop (hole) is before the lhu.

So in the target, the hole (asm) is before the lhu?! But the asm must be after the materialization (its input)...

UNLESS the nop at 27 is NOT the asm's hole but a real nop from the original game code, and the asm's hole is at 33 or 35 (where c1 also has nops) ✓✓ — c1 has nops at 30, 33, 35 and the target at 27, 33, 35. So the p10 asm's hole could be at 33 in both ✓, and the difference is the nop at 27 (target) vs 30 (c1) — the v6 asm's hole! In the target, the v6 asm's hole is at 27 (before the lhu?) hmm.

OK: the v6 asm's hole: the v6 asm is after the lhu in the source → its hole should be after the lhu. In the target, the nops are at 27 (before the lhu at 28), 33, 35. Hmm, so the v6 asm's hole is NOT after the lhu.

Unless the target's "lhu v0,6(v0)" at 28 is not the v6 load but the unkA load, and the v6 load is elsewhere. Ugh, I'm at 28: "lhu v0,6(v0)" — offset 6 = unk6 ✓ (the v6 load) and 34: "lhu v0,10(v0)" = unkA ✓.

So in the target: [26 lw o][27 nop][28 lhu v6][29 lui][30 addiu][31 sh v6][32 lw o][33 nop][34 lhu unkA][35 nop][36 addiu].

The nop at 27 sits between the "lw o" and the "lhu v6". The v6 asm is between the lhu and the p10 assignment in the source. So the asm's hole should be between the lhu (28) and the materialization (29). There's no nop there. Hmm!! So the asms' holes are at 33 and 35? Both after the store (31)? Hmm, the p10 asm is before the store in the source.

So the target's nops at 33 and 35 are after the store and the second o load. The v6 asm and the p10 asm (both before the store in the source) → their holes should be before the store. Hmm, so the holes at 33/35 don't correspond either.

I think the nops in the target are just the original game's nops (the retail code had nops), and the banked body's asms coincidentally produce holes in the same places. In c1 (one asm removed), one hole moved.

So: for item 4, the target's 3 nops are reproduced by the 2 asms + something else? Hmm, 2 asms → 2 holes; the target has 3 nops; so one nop is a "natural" nop (a branch delay slot or a hole). Hmm, but the nops at 27/33/35 are not delay slots (no branches nearby).

Hmm, whatever. Empirically: c1 = 4 (the count matches!). The only difference is the order of [lui/addiu] vs [lhu] and the nop's position. If I can move the p10 materialization after the lhu in the schedule, and the nop to 27...

What if I move the p10 assignment in the SOURCE to after the v6 load? It already is. Hmm, what if I move the v6 load LATER in the source (after the p10 assignment)? Then the source order = [materialization][lhu][asm][store] → the schedule might keep the materialization first (as in c1) ✗.

Hmm, what if the v6 load's source position moves EARLIER (before "o = ...")? Then the lhu would be even earlier ✓ (the target has the lhu at 28, right after the lw o at 26 — hmm, the lhu depends on o (the lw) so it can't be before it).

Hmm, so in the target the order is [lw o][lhu v6][lui][addiu][sh]: the lhu is between the lw and the materialization. In c1: [lw o][lui][addiu][lhu][nop][sh].

The difference: the lhu is 2 slots later in c1. Why? Because of the "class" rule (S6): "Independent insn separates address-gen from use" — the materialization (lui/addiu) is the address-gen for the store, and the lhu is an independent insn that got placed between them.

Per S6: "Steer via which independents are available (statement order)."

Hmm! So if the lhu (an independent insn) were NOT available at that point, the materialization and the store would be adjacent. In the target, the lhu is BEFORE the materialization.

What makes the lhu unavailable in c1? Hmm.

Hmm, in the target, the lhu is at 28 and the nop at 27 — maybe the v6 asm's hole is at 27 (i.e. the asm was scheduled between the lw and the lhu!) — but the asm depends on v6 (the lhu's result) → it can't be before the lhu. UNLESS the asm's "=r"(v6) output is a NEW reg (not v6's) and the "0"(v6) input is v6's reg → the asm depends on the lhu ✓ so the hole must be after the lhu.

I'm stuck on the exact mechanism. PRAGMATIC: try a few source-order variants for item 4 and see if any hits 0:
(a) Move the `v6 = ...` load to before the `o = ...` assignment? (can't: it depends on o)
(b) Move the p10 assignment before the v6 load:
```
            o = ...->unk6C;
            p10 = &D_80190048;
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            *p10 = v6;
```
(the p10 asm stays after the p10 assignment)
(c) Move the `o = ...` assignment earlier? It's already first.

Let me try (b) — and also (d): the "o" load moved later.

Let me do (b) and (d) in one batch and score.

Time check: I need to wrap up soon. Let me do this batch for item 4, then handle items 1 and 2 (the vol launder) with the compound-assignment experiment, then write everything up.

Let me generate the variants for item 4 from c1.c (which has the v6 launder removed and the p10 launder kept):
(b): move the p10 assignment before the v6 load.
(d): move the o assignment... hmm, o is used by the v6 load. In the target, the "lw o" is at 26 and the lhu at 28. Fine.

Let me do (b) only, plus (e): move the v6 load to just before the store:
```
            o = ...->unk6C;
            p10 = &D_80190048;
            [asm p10]
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            *p10 = v6;
```
Hmm, that's (b) with the asm in place. Let me construct (b) as: move the line "p10 = &D_80190048;" (and its asm) to before "v6 = ...->unk6;".

In c1.c the text is:
```
            o = ((Unkstruct_80185380 *)param_1)->unk6C;
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            p10 = &D_80190048;
            __asm__ __volatile__("" : "=r"(p10) : "0"(p10) : "memory");  // !FAKE: launder ...
            *p10 = v6;
```
(b):
```
            o = ((Unkstruct_80185380 *)param_1)->unk6C;
            p10 = &D_80190048;
            __asm__ ...
            v6 = ((Unkstruct_80185380_2 *)o)->unk6;
            *p10 = v6;
```
Hmm, but the asm's input is p10 and the store uses p10 — the asm between them ✓.

Let me generate (b) with a sed -z multi-line replacement.

Honestly, the probability of hitting 0 is low. Let me timebox: generate (b), score it; if not 0, record item 4 as a WALL (best = 4, the lever-free body? hmm — c1 is NOT lever-free (it keeps the p10 launder) → the "best" for a WALL = the lowest score of a LEVER-FREE body = base (39) or v1 (28) → best = 28.

Hmm! And for the PARTIAL option: c1 (score 4) is not 0, so no PARTIAL.

OK let me do (b) and then move on.
