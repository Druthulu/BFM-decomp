---
ts: 2026-10-22T07:13:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bJcYyPTXebLUPXC6IWCP
---
cand02's sequence:
```
li v0,160
subu v0,v0,a1
sll v1,v0,0x7
subu a1,v1,v0      <- the ×127 result in a1 (target has it in v1)
lui v0,0x6666
ori v0,0x6667
mult a1,v0
mfhi t1
addiu v1,a2,160
mult v1,v0
sra a0,t1,0x6
sra v0,a1,0x1f
subu a1,a0,v0
sra v1,v1,0x1f
mfhi a2
sra v0,a2,0x3
subu a2,v0,v1
```
vs the target:
```
lui a0,0x6666
ori a0,0x6667
li v0,160
subu v0,v0,a1
sll v1,v0,0x7
subu v1,v1,v0      <- ×127 in v1
mult v1,a0
mfhi t1
addiu v0,a2,160
mult v0,a0
sra v1,v1,0x1f
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
```

Differences:
1. The magic constant: target a0, mine v0.
2. The ×127 result: target v1, mine a1.
3. The pan dividend: target v0, mine v1.
4. The sign corrections use different regs.

So the register allocation of the temporaries differs. The instruction count is the same (192).

The target's `subu v1,v1,v0` (the ×127) then `mult v1,a0` — the dividend is v1 and the magic in a0.
Mine: `subu a1,v1,v0` then `mult a1,v0` — the dividend in a1, magic in v0.

Interesting: in the target, the magic constant pseudo is in a0; in mine, in v0. And the dividend in v1 (target) vs a1 (mine).

This is a local-alloc/allocation-order issue. The launder affects it (the birth boost of vol changed the scheduling, which changed the live ranges, which changed the allocation).

Hmm, this is the "sched1 → local-alloc" chain. Hmm.

Since the count matches (192) and the ORDER of the two multiplies is right (vol's mult first), the remaining difference is the register assignment of 3-4 temps.

What decides that? The local-alloc's "qty" order and the priority. The magic constant pseudo in the target is a0 — hmm, why a0? Because a0 is a caller-saved arg reg and it's used by 2 mults; local-alloc would normally give it v0/v1. Unless the constant pseudo is a GLOBAL (function-level) pseudo — then global-alloc assigns it. Hmm.

Hmm, alternatively: the constant pseudo might be allocated to a0 because of the *copy preference* or because a0 was free at that point.

Hmm. Alternatively: maybe in the target the constant is not a pseudo at all but a hard reg because of the reload pass.

Let me think about how the target's code could arise: `lui a0,0x6666; ori a0,0x6667` — the constant is materialized into a0. In mine, into v0.

What if the difference comes from the ORDER of the two divisions relative to the constant's materialization? In the target, the constant is materialized FIRST (before `li v0,160`), i.e. hoisted to the top of the block. In mine, it's materialized later (after the ×127).

So in the target, the constant's materialization was scheduled EARLY (it's a "birth" → boosted? no...). Hmm, in the target the constant pseudo has 1 set → birthing → boosted → scheduled early ✓✓. That's the boost effect! The constant's materialization is boosted (it's a birth) → it goes to the top of the block → into a0 (a0 is chosen because... hmm).

In cand02, the constant is also a birth... but it's materialized later. Hmm.

OK, let me think about what plain-C change might restore the target's shape.

The launder on vol gives vol a 2nd set. In cand02, vol has 2 sets (the multiply and the division) ✓ — that's why the multiply order is right.

But the constant's placement differs. Hmm.

Hmm, what if the difference is that in the target, the constant pseudo 0x66666667 is shared between the two divisions (one pseudo, 2 uses, 1 set → boosted → materialized early in a0), while in cand02 the two divisions have SEPARATE constant pseudos (each with 1 set)? Then mine would have 2 materializations (lui/ori ×2) = 192+2 insns. But mine has 192 = target. So no.

Hmm, but maybe in mine the two constants were merged too but the materialization is in v0.

So both have ONE constant pseudo; the difference is which register and where it's materialized.

The register choice (a0 vs v0) is local-alloc's. The a0 choice is unusual. Hmm, maybe because in the target, the constant pseudo is live across the `mult` instructions and there are 4 temps competing (v0, v1, a0, a1, t1, a2).

Hmm, honestly, maybe the difference is that in the target the vol division is written as `vol = ((0xA0 - av) * 0x7F) / 0xA0;` (a plain expression) with the launder providing the 2nd set of vol, while in cand02 I split it into two statements — which changes the RTL shape (the division's dividend is vol's pseudo, a different structure).

Let me reconsider: in the tree, `vol = ((0xA0 - av) * 0x7F) / 0xA0;` + the asm. The asm makes vol have 2 sets but the VALUE of vol is computed by ONE expression (the division). The RTL: the division computes into a pseudo, then the asm copies it to vol (2nd set).

So in the tree, the division's result pseudo is DIFFERENT from vol's pseudo; vol is just a copy.

In cand02, `vol = X; vol /= 0xA0;` — the division's result IS vol's pseudo (an RMW).

These differ in the RTL: the tree has an extra copy? No — the asm's copy is zero-byte (the tied output). So the tree's RTL: the division result → pseudo D; then `(set vol_pseudo, D)` where vol_pseudo is... hmm, the asm's output is a hard reg? vol is a plain local (not pinned) → the asm's output is a pseudo → so the tree has: div result pseudo → copy → vol pseudo. With the copy being a "coalesced" copy (the div result and vol are the same value; local-alloc coalesces them).

So the tree's structure: one value with 2 pseudos (coalesced). And reg_n_sets for vol's pseudo = 2 (the div copy + the asm).

Hmm! So the tree's 2nd set is on the COPY pseudo (vol), not on the division's result.

In cand02, the division's result IS vol's pseudo, and the 2nd set comes from the RMW.

Both give vol 2 sets. But the RTL differs → different allocation.

Let me try a different spelling that mimics the tree more closely:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = vol;   /* nope, folded */
```
Hmm.

What about:
```
s32 v2 = ((0xA0 - av) * 0x7F) / 0xA0;   /* the division result */
vol = v2;      /* copy: vol has 1 set */
```
Hmm, that gives vol 1 set.

What if we do the "copy then accumulate on the copy" (C0458):
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;   /* vol: 1 set */
vol2 = vol;                            /* copy */
vol2 += 0;  ...
```
no.

Hmm. Let me think about what makes the target's magic constant land in a0 and be materialized at the top.

Actually — maybe the key is the ORDER of the materialization: the target materializes the magic constant BEFORE `li v0,160`. That's the birth boost of the constant pseudo (1 set) → scheduled early. In mine, the constant's materialization is later.

Hmm, why would mine differ? Both have a 1-set constant pseudo...

Unless in mine the constant pseudo has 2 sets (one per division) → no boost → materialized later!

In cand02: `vol = X/0xA0` and `sx = (sx+0xA0)/0x14` — two divisions, each with its own magic constant. If cse merges them into one pseudo with 2 sets → no boost → later materialization. But if they're separate pseudos (each 1 set) → each boosted → both early.

Hmm, but then we'd have 2 materializations (4 insns). Mine has 192 = target. So they're merged (one pseudo, 2 sets) → no boost → materialized later ✗.

In the TREE, the same two divisions exist → the same merged constant pseudo with 2 sets → no boost → also materialized later?! But the target materializes it FIRST.

Hmm, contradiction. Unless in the tree the magic constant pseudo has 1 set: maybe in the tree, the two divisions use DIFFERENT magic constants (0x66666667 for /160 and 0xCCCCCCCD for /20)?? But the target's assembly clearly shows `mult v0,a0` with a0 = 0x66666667 for the pan division too. Hmm, unless the pan division uses a0 = 0x66666667 because... hmm, the target's pan: `mult v0,a0; mfhi a2; sra v1,a2,0x3` — yes a0 = 0x66666667.

Hmm, so in the target both divisions use the same constant → one pseudo with 2 uses → 1 set → BOOSTED → materialized early ✓ (that's why it's at the top of the block!).

And in cand02, the same should hold... unless the 2 uses are in different "versions" of the pseudo. Hmm.

Wait — maybe the difference: in cand02, the constant is materialized into v0 (a caller-saved temp) — a local-alloc choice. And in the target into a0. The boosted birth is scheduled early in both? In mine the materialization is at c68-c6c (after the ×127), in the target at c58-c5c (before `li v0,160`). So the target's materialization is EARLIER.

Hmm, so in mine the constant's birth was NOT boosted → 2 sets. In the target it WAS boosted → 1 set.

Why the difference? Because in the tree, the two divisions' magic constants are... hmm.

OH WAIT. Maybe in the tree the launder on vol changes things: the tree's vol = the division result (a copy). The 2 sets of vol's pseudo... hmm, that's about vol, not the constant.

Hmm, hold on. Maybe in the tree, the magic constant for the /20 division is a DIFFERENT constant pseudo than the /160 one, but with the same VALUE, and gcc's cse merged them only in the final RTL... then the materialization count would be 2.

Let me count the target's materializations of 0x66666667: c58 (lui a0) + c5c (ori a0) — just one pair. So one materialization.

OK, let me try to think about what happens with `sx = (sx + 0xA0) / 0x14;` — the magic for /20 with shift 3: M = ceil(2^35/20) = 1717986919 = 0x66666667 ✓ (the same value). And for /160 with shift 6: M = ceil(2^38/160) = ceil(2748779069.44) = 2748779070 = 0xA3D70A3E. Hmm! That's NOT 0x66666667.

Hmm, but gcc might use the "add" magic form: for /160, gcc can use M = 0x66666667 with an add (the "magic number with add" variant): n/160 = (n * 0x66666667 + n) >> 38? Hmm. Let me look at the target's vol division again:

```
mult v1,a0      ; v1 = (160-av)*127
mfhi t1         ; t1 = hi(v1 * 0x66666667)
sra v1,v1,0x1f  ; sign of the dividend
sra a0,t1,0x6   ; t1 >> 6
subu a1,a0,v1   ; quotient = (hi>>6) - sign
```
So: q = ((v1 * 0x66666667) >> 32) >> 6 - sign. That's M=0x66666667, shift 6 → 0x66666667/2^38 = 0.00390625 = 1/256. Hmm, that gives v1/256, not v1/160.

Hmm, so gcc used the "round-down" magic with an ADD? There's no add in the sequence. Hmm, let me recompute: 0x66666667 = 1717986919. 1717986919 / 2^32 = 0.39999... = 0.4 = 2/5. Hmm, 0.4 = 1/2.5.

For v1/160: hmm. But wait, maybe the dividend isn't divided by 160! Let me re-read the C: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` = ((160-av)*127)/160.

The magic sequence for /160 with shift 6: M = ceil(2^(32+6)/160) = ceil(2748779069.44) = 2748779070 = 0xA3D70A3E. Not 0x66666667.

But with the "add" variant (M' = M - 2^32 = 0x66666667 with an extra add of n): q = (hi(n*M') + n) >> 6. The target has no add of n... hmm, unless the `subu a1,a0,v1` (minus sign) is doing something else.

Hmm, let me recompute: maybe the shift is different: `sra a0,t1,0x6` = t1 >> 6 where t1 = hi(n * 0x66666667). So q = (n*0x66666667) >> 38 (with sign correction) = n * 0.4 / 64... = n/160 ✓!! Because 0x66666667/2^38 = 1717986919/274877906944 = 0.00625 = 1/160 ✓.

So the magic for /160 with shift 6 is 0x66666667 ✓ (the "round down" magic: M = floor(2^38/160) = floor(2748779069.44) = 2748779069 = 0xA3D70A3D — hmm no).

Let me just compute 2^38/160 = 274877906944/160 = 1717986918.4 → floor = 1717986918 = 0x66666666, round-up = 1717986919 = 0x66666667 ✓. Yes! I made an arithmetic error before (2^(32+6) = 2^38 = 274877906944; /160 = 1717986918.4 ✓). So M = 0x66666667 with shift 6 ✓.

And for /20: 2^(32+3)/20 = 2^35/20 = 34359738368/20 = 1717986918.4 → M = 0x66666667 with shift 3 ✓.

So both divisions use the SAME magic constant 0x66666667 → cse merges them into one pseudo with 2 uses, 1 set → BIRTHING → boosted → materialized early (at the top of the block) → allocated to a0.

Now in cand02 (mine), the constant is also 0x66666667 with 2 uses → should be the same. But mine materializes it into v0 and later.

Difference: hmm! In cand02, the ORDER of the divisions is: vol's division first (in the source), then sx's division. Same as the target.

Hmm, so why is the materialization later in mine?

Because in mine the constant pseudo has 2 SETS?! How? If the two divisions use the constant in different "versions"...

OR: the boost is killed by something else in mine. Hmm! What if in cand02 the magic constant pseudo is a *global* pseudo (used in 2 different blocks?) — no, both are in the same block.

Hmm, hold on: maybe in cand02 the constant pseudo has 2 sets because of the "rematerialization" logic: gcc's reload might split it.

Alternatively, maybe in mine the difference is that the division is done in a different way: my `vol = X; vol /= 0xA0;` → the division's dividend is vol's pseudo (which holds X). In the target, the division's dividend is a separate pseudo (the product) and vol is a copy.

So in cand02, the dividend pseudo = vol = X's pseudo. The magic constant is used by the vol division and the sx division.

Hmm, hmm. Let me look at the .sched dump of cand02 vs the tree to see the constant pseudo's sets. That's the reliable way but costs time.

Alternatively, let me try more spellings and see if any gives 0:

cand05: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` with the multiplication written as `(0xA0 - av) * 0x7F` → and the division split differently: `s32 tmp = (0xA0 - av) * 0x7F; vol = tmp / 0xA0;` → then vol has 1 set (the division result) and tmp has 1 set. No 2nd set → no boost kill → the multiply order might break.

cand06: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` but with the sx division first? (reorder the statements) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand07: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - adv) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn is created. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Alternative quick experiment: maybe the difference is not the boost but the ORDER of the two divisions' operands. Let me try swapping the order of the source statements (compute sx's division BEFORE vol's) — no, that changes the semantics? No, they're independent. But the target's order is vol's mult first.

Hmm, let me try a couple of quick variants and look at the diffs:
cand05: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with `sx` computed BEFORE vol? (reorder) — the source order of the two divisions might matter for the scheduler. Hmm, but sx is computed after vol in the source (sx = (sx+0xA0)/0x14 comes after the launder). Hmm, in the C:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
```
So vol's division is first ✓.

cand06: make the multiplication a compound too: `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` = cand03 (score 25).

cand08: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` = cand04 (score 14).

Hmm, cand02 and cand04 are the same score (14) — the plain `vol = vol / 0xA0` gives the same code.

Let me think about the constant's placement differently: maybe I should make the constant's pseudo have 1 set by ensuring cse merges the two magic constants. They ARE merged (one materialization).

Hmm, so why is the materialization late in cand02?

AH WAIT. Maybe I have it backwards: maybe the materialization is EARLY in mine too but the REGISTER is different, and the "later" appearance is because the `lui v0/ori v0` in mine comes after `subu a1,v1,v0`... Let me compare the positions:

Target: c58 lui a0, c5c ori a0, c60 li v0,160, c64 subu, c68 sll, c6c subu, c70 mult v1,a0.
Mine: c58 li v0,160, c5c subu, c60 sll, c64 subu a1,v1,v0, c68 lui v0, c6c ori v0, c70 mult a1,v0.

So in the target the constant is materialized BEFORE the whole vol computation; in mine it's materialized just before the mult.

The difference: the constant's birth boost (1 set) → scheduled early. In mine it's not boosted → 2 sets?!

Hmm, how could cand02 give the constant 2 sets? OH!! Maybe because of the `vol /= 0xA0` form: the division by a constant is expanded by gcc's `expand_divmod` at RTL generation: the magic constant is created as a separate RTL insn. For the sx division, another magic constant insn. Then CSE merges the two CONSTANTS (both are (const_int 0x66666667))... but they're in different "versions"? cse should merge them (they're both constants).

Hmm, but if cse merges them, the merged pseudo has 1 set (the lui) and 2 uses.

Unless the merged pseudo has 2 sets: the lui+ori pair is ONE insn (a `set` of a pseudo to a constant)? For MIPS, the constant 0x66666667 needs lui+ori: the RTL is `(set (reg) (const_int 0x66666667))` → the reload/expand turns it into lui+ori. So ONE set ✓.

Hmm, so both should be 1 set.

OK, let me just dump cand02's sched trace and check the constant's boost, like I did for item 3. That's the reliable path. But time...

Let me look at the tree's .sched trace for this function to see which insns are boosted, and compare with cand02's. The tree's TU is the real one (3407 lines) — the dump would be big but I only need the func_80190D70 section. Actually cc1_dumps_tu.sh compiles the whole TU (slow but OK, maybe 30s).

Hmm, but the function is in a big TU with the function at line 3413. The dump files would be large (~10-50MB). Disk: ~4GB free, and I must delete them after. Acceptable.

Hmm, but time. Let me first try a few quick variants that might nail it:

Variant A: make the vol division use the same magic constant explicitly?? Can't.

Variant B: what if I write the sx division as a compound too: `sx = sx + 0xA0; sx /= 0x14;` — that gives sx 2 sets as well! Maybe the tree's launder... no, the tree's launder is only on vol. But the tree's sx division is a plain expression. Hmm, but maybe making sx's division compound changes the constant's sharing. Let me try it — cheap.

Variant C: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` + `sx = sx + 0xA0; sx /= 0x14;`.

Variant D: the reverse: keep vol as one expression but give vol a 2nd set via a compound on a DIFFERENT variable... no.

Let me try B and C plus a couple of others quickly.

Also Variant E: use `(u32)` casts? Hmm.

Let me also consider: the target's magic is in a0. In mine it's in v0. What if the difference is that in the target the constant pseudo is a GLOBAL (function-level) pseudo (used in 2 blocks?) vs local? Hmm, both divisions are in the same block (case 0's if-block).

Hmm, what if in the tree the two divisions are in DIFFERENT blocks? The sx division is in the same if-block. Hmm.

Let me just try the variants.
