---
ts: 2026-10-22T07:22:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_59nCb5mJA25aKCzhg8HT
---
In cand01 (plain drop), the magic constant is in a2 and the sx in a3 (vs the target's a0 and a2). And the multiply order: mine has `mult a0,a2` (the pan's mult, at 120) BEFORE `mult v1,a2` (the vol's mult at 126) — so the PAN multiply is hoisted ahead ✓ (that's what the launder prevents).

So the launder's role: keep the vol multiply before the pan multiply.

C2 (compound divide) fixed the multiply order ✓ but the magic's placement/registers differ.

So I need BOTH: the vol multiply before the pan multiply AND the magic materialized at the top of the block in a0.

Hmm. In C2, the multiply order is right but the magic's placement is later.

Recall the tree's launch order in the case-0 block: 266 (the product, boosted), 264, 261, 259, 451 (ori), 450 (lui) — so the magic was launched last → first in the chain.

In C2: 452 (ori), 451 (lui), 266, 264, 261, 259 — the magic was launched first → last in the chain.

The difference: in the tree, at T-30 the ready list was "451 (1) 266 (7f000001)" → the boosted 266 won → 266 launched first, 451 later. In C2, the ready list was "452 (1) 266 (1)" → a tie → 452 won (higher UID first).

So the ONLY difference is the boost on 266 (the product's birth) — in the tree it's boosted (1 set), in C2 it's not (2 sets: vol has the product and the copy).

So I need the product in its own pseudo (1 set) → i.e., the plain form `vol = X / 0xA0` where the dividend is a separate pseudo ✓ — but then vol has 1 set, and the quotient's birth would be boosted (which is what breaks the multiply order? hmm, no).

Wait: in the plain form (cand01), what happened? The multiply order was wrong (the pan's mult hoisted ahead). In the plain form, vol = the quotient (1 set) → the quotient's birth (insn 273-ish) is boosted → boosted → launched early → lands LATE in the chain → hmm, that would put the vol multiply later → the pan's mult before it ✓ consistent with cand01's wrong order!

So: the tree needs the quotient's birth NOT boosted (vol has 2 sets) and the product's birth boosted (the product in its own pseudo).

So I need vol to have 2 sets AND the dividend to be a separate pseudo. That's exactly the tree's structure.

So: `vol = X / 0xA0;` (the plain form: the dividend separate ✓, vol = the quotient with 1 set) + a 2nd set of vol.

The 2nd set must not emit an instruction. Hmm, but the tree's 192 vs cand01's 191: the tree has ONE more instruction than the plain drop. Where? Looking at cand01's diff: mine lacks `nop` at 129 and has fewer instructions around. Also the target has "j d70" twice (167-169) vs mine once. Hmm, the count difference (191 vs 192) is due to a `nop` in the target (the target's `addiu v0,a2,160; nop; mult v0,a0` — the nop is a branch-delay filler) — mine doesn't have that nop because its layout differs.

OK so: I need vol's 2nd set. Let me think about which plain-C spellings give a normal local 2 sets WITHOUT an extra instruction...

**KEY INSIGHT ATTEMPT**: In the tree, the asm's 2nd set is on pseudo 137 (vol). The asm is `(set 137, asm_operands)`. In plain C, the equivalent would be a copy `(set 137, 137)` — self-copy. cse removes it... but does it? cse's `make_regs_eqv` might treat it as a no-op. Hmm, cand12 (vol = vol) gave the same score as cand01 → removed.

Hmm, BUT: what if the self-copy is written as a copy from a DIFFERENT pseudo that has the same value, where the source pseudo is later coalesced? Like:

```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* vol: 1 set (the quotient) */
```
and the tree's asm gives vol a 2nd set. What if instead we give the QUOTIENT pseudo 2 sets in a way that the copy is free?

Hmm, what about this: `vol = X / 0xA0;` — the division's result pseudo IS vol. What if we write:
```
vol = X / 0xA0;
vol = vol;    /* removed */
```

What about making the division's result go into a temp and then assigning to vol:
```
s32 q = X / 0xA0;   /* q: 1 set; the dividend is a separate pseudo ✓ */
vol = q;             /* vol: 1 set */
```
Hmm, vol has 1 set.

What if:
```
s32 q = X / 0xA0;
vol = q;
vol = q;   /* cse removes */
```

ARGH.

**NEW ANGLE**: What if the 2nd set is not needed on vol but the boosted QUOTIENT's birth can be neutralized another way? The quotient's birth (the division result → vol) is boosted because vol has 1 set. What if vol's pseudo has 2 sets because it's assigned in TWO places in the source — e.g. an initialization plus the division?

```
s32 vol = 0;             /* set 1: vol = 0 (dead, but a set) */
vol = X / 0xA0;          /* set 2 */
```
The first assignment is dead → removed by flow → 1 set. Hmm, but wait: does flow remove it BEFORE the reg_n_sets count? The dead store `vol = 0` is removed by cse/flow (dead code elimination). Hmm.

BUT: what if the first assignment is NOT dead? E.g.:
```
s32 vol;
vol = X / 0xA0;
```
no.

What about a conditional assignment:
```
if (av < 0) { vol = 0; } else { vol = X / 0xA0; }
```
→ a real branch. No.

Hmm. What about `vol = X / 0xA0;` where X's computation makes vol's pseudo have 2 sets... no, the sets are per-pseudo.

**IDEA: use the `& 0xFFFF` compound on the CALL ARGUMENT**: the call arg is `(vol | (0x3000 | sx)) & 0xFFFF` — that's a use.

**IDEA: What if the launder's role could be played by giving the DIVIDEND pseudo 2 sets instead?** The dividend (145 in the tree) has 1 set (boosted) — I need it boosted, so 1 set ✓ (the plain form). Hmm, but in C2 the dividend was vol itself (2 sets). So the plain form is right for the dividend.

So the ONLY thing needed: vol (the quotient's pseudo) must have 2 sets.

Hmm, what if we could give the quotient's pseudo 2 sets by making the division's result assigned to a pseudo that is ALSO used elsewhere... no.

**IDEA: What if the second set of vol comes from a compound assignment on the CALL's argument variable?** The call arg is an expression; if we introduce a variable:
```
s32 arg = vol | (0x3000 | sx);
func_8002D4C8(0x9E5, arg & 0xFFFF);
```
That doesn't touch vol.

**IDEA: what if the 2nd set of vol is created by the `& 0xFFFF` on vol itself?** i.e. `vol = vol & 0xFFFF;` before the call — a compound assign that CHANGES the value (truncates). Hmm! But wait: what if the target's code also has that truncation? The target's code: `andi a1,a1,0xffff` — the mask is applied to the combined value in a1, not to vol.

Hmm, but what if we write:
```
vol = vol & 0xFFFF;    /* a real 2nd set (compound assign) — but it changes vol's value! */
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
The value: vol is 0..0x7F, so `vol & 0xFFFF` == vol ✓ semantically identical! And the code: the `andi` would be applied to vol's register instead of the combined a1 → the instruction sequence changes: `andi a1,a1,0xffff` (the target, on the combined value) vs `andi v?,v?,0xffff` on vol then `or`... The target has:
```
ori a1,a1,0x3000
or a1,a1,a2
andi a1,a1,0xffff
jal
```
With the mask on vol: `andi a1,a1,0xffff` (vol) then `ori a1,a1,0x3000`, `or a1,a1,a2` — the ORDER of the andi vs the ori differs → different instruction order → score mismatch. Hmm! Unless gcc reorders them (the andi and ori are independent → the scheduler decides).

Hmm! That's worth a try: it gives vol a REAL 2nd set (a compound assign, the G11 recipe!) with the same value (since vol ≤ 0x7F) and the same instruction count (the andi moves from the combined value to vol).

Hmm, but the target's andi is on the combined value (a1 = vol|0x3000|sx). If we mask vol first, the mask is redundant but the instruction is the same count ✓. But the ORDER of the andi relative to the ori/or might differ, and the mask's operand would be vol's register instead of a1.

Risky but cheap to test. Let me try:
cand13: `vol = vol & 0xFFFF;` before the call (with the call arg unchanged: `(vol | (0x3000 | sx)) & 0xFFFF`).
Hmm, then there'd be TWO andis (one on vol, one on the combined) → +1 insn. Let me instead write the call arg as `(vol | (0x3000 | sx))` without the & 0xFFFF (since vol is already masked and the ori/or of sx (which is ≤ 0xF00) and 0x3000 stay within 16 bits) → then the count is the same ✓ but the semantics change slightly (the target masks the combined value; the combined value is ≤ 0x3FFF anyway → the mask is a no-op ✓).

So:
```
vol = vol & 0xFFFF;              /* real 2nd set of vol */
sx = sx << 8;
func_8002D4C8(0x9E5, vol | (0x3000 | sx));
```
Hmm, but the target's `andi a1,a1,0xffff` — where does it come from in the target? The C is `(vol | (0x3000 | sx)) & 0xFFFF`. So the target's andi is on the combined value.

If I mask vol instead, the andi is on vol's register (a1 in the target? vol is in a1 per the target: `ori a1,a1,0x3000` — a1 holds vol!). Hmm interesting: in the target, a1 = vol (the quotient), then `ori a1,a1,0x3000` → a1 = vol|0x3000, `or a1,a1,a2` → |sx, `andi a1,a1,0xffff`.

So if I write `vol = vol & 0xFFFF;` the andi would be on vol's reg (a1?) → `andi a1,a1,0xffff` then `ori a1,a1,0x3000` then `or a1,a1,a2`. The target has ori, or, andi. So the ORDER differs (andi first vs last) → the scheduler might reorder them (they're independent: andi on a1 vs ori on a1 — they're NOT independent, both write a1!).

So the order would be forced: andi then ori (or ori then andi — both write a1, so they're dependent). The target: ori, or, andi. So my version would give: andi, ori, or ✗ (different order).

Hmm. Unless gcc's combine folds `x & 0xFFFF` into the subsequent `| 0x3000`... Hmm, `(vol & 0xFFFF) | 0x3000` — combine might fold the mask into the or? Not likely.

OK, let me think about yet another approach: give vol a 2nd set via a compound assign that does NOT change the emitted code: e.g. `vol += 0;`? folded.

Hmm, hold on! What about `vol = vol;` but written as `vol = (s32)vol;`... folded.

What about assigning vol from a *volatile* source? No.

**RADICAL IDEA**: what if we change WHICH variable is laundered? I.e., what if the tree's asm is on vol, but maybe a DIFFERENT variable with 2 sets would produce the same scheduling? The launder's job: make the quotient's birth unboosted. Only vol's own set count matters.

**IDEA: what if vol is declared as a `register` variable?** Not allowed (adding a pin).

**IDEA: what if the quotient is assigned to vol TWICE via two different divisions?** e.g.:
```
vol = X / 0xA0;
vol = X / 0xA0;   /* cse merges */
```

**IDEA: What if the division's result is assigned to a variable that is then assigned to vol, and the 2 sets are on the DIVISION RESULT pseudo (not vol)?** Hmm: in the tree, the 2 sets are on vol (137): the quotient and the asm.

Hmm, what if:
```
s32 q = X / 0xA0;    /* q: 1 set */
vol = q;              /* vol: 1 set */
```
and then the call uses vol. vol's birth (the copy) is boosted → same problem as the plain form.

Hmm, but WAIT: in the plain form (cand01), the quotient's birth is boosted. In the "q then copy" form, the COPY's birth is boosted. Either way, one boosted birth in the wrong place.

**IDEA: what if we could give the QUOTIENT pseudo 2 sets by having the division's result used in two places?** E.g., the division computed twice? no.

OK, let me try a few things empirically (cheap):
cand13: `vol = vol & 0xFFFF;` before the call + the call arg without the mask.
cand14: `vol = vol & 0xFFFF;` + the call arg unchanged (2 andis → 193 ins, but let's see).
cand15: the plain form + `vol = vol;` — done (cand12).
cand16: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` + `vol = vol | 0x3000;`?? changes the value ✗.
cand17: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` + `vol = vol & 0x7F;`? changes the value (vol ≤ 0x7F ✓ semantically fine!) → hmm, but the andi on vol (a1) — the target's andi is on the combined value. Same issue as cand13 but with a different mask. Hmm, but the count: the target has ONE andi (on the combined). If I add `vol &= 0x7F` I'd have 2 andis → +1.

Hmm, unless I remove the & 0xFFFF from the call arg: `(vol | (0x3000 | sx))` — but then the target's andi disappears and mine has the andi on vol → the count is the same ✓ but the position differs (andi on vol before the ori).

Let me test cand13 and see the diff. Actually, the ordering issue: `andi a1,a1,0xffff` then `ori a1,a1,0x3000` — hmm, wait. If vol is masked first and then ORed with 0x3000, gcc might FOLD the mask into the or: `(vol & 0xFFFF) | 0x3000` — gcc's fold might simplify to `vol | 0x3000` if vol's range is known < 0x10000... it isn't known. Hmm, but gcc's "widening" fold: `(x & 0xFFFF) | 0x3000` — the mask's bits that are ORed with 0x3000 (bits 12,13) are not in the mask → so the fold can't remove the mask. But gcc might move the mask to the combined expression: `(vol | 0x3000 | sx) & 0xFFFF` — hmm, that's a different value (the mask would also clear 0x3000's bits? no: 0x3000 & 0xFFFF = 0x3000 ✓, and sx ≤ 0xF00 ✓). gcc wouldn't do that transform.

Let me just test cand13/cand14 and look at the diffs. Cheap.

Also, let me try:
cand18: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `sx = (sx + 0xA0) / 0x14;` then before the call: `vol = vol & 0xFFFF;` — same as cand13.

Let me write and score these.

Hmm, also worth trying: what if the 2nd set comes from a compound assign on vol that gcc keeps because the value differs in a way gcc can't see but the TARGET's code also has? E.g. the target's code has `andi a1,a1,0xffff` — if we write `vol = vol & 0xFFFF;` the emitted andi is on vol's reg. In the target, the andi is on the combined a1. But hold on — in the target, a1 holds vol at the time of the ori (a1 = vol). So the target's `andi a1,a1,0xffff` is applied to (vol|0x3000|sx) — the same register a1. So if we mask vol first (`andi a1,a1,0xffff` where a1 = vol) and then `ori a1,a1,0x3000` and `or a1,a1,a2`, the instruction sequence is: andi, ori, or vs the target's ori, or, andi. The SET of instructions is the same but the order differs → the score would show 1-2 diffs.

Hmm, but maybe gcc reorders: `andi a1,a1,0xffff` and `ori a1,a1,0x3000` both write a1 → they're dependent (a read-modify-write) → the order is fixed by the dependency.

Hmm, so cand13 would give a diff of ~2. But it might also fix the multiply order! Let me test.

Actually hold on, there's a subtlety: if we mask vol BEFORE the pan's division, the andi would be scheduled earlier (right after the vol division) → different position.

Let me test a few variants and look at the diffs. Let me be efficient: generate 4 variants, score them, and look at the best diff.
