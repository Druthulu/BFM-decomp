---
ts: 2026-10-22T13:05:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_wYvYcuHXDIssBjtMz15w
---
Item 1: best 20 (the plain no-launder body). All variants are 20 or worse.

Interesting: `gen_use2_cmp_self` (a compare with the same address — folded) → 20.

Now item 4. Let me write variants for item 4 focused on the ax/by 2nd sets and the op launder.

Ideas:
- Remove all launders (25).
- ax/by 2nd sets via different spellings.
- The op launder replaced by a plain-C equivalent (e.g. `op = (Gline_801372B0*)&D_800A6518[...]` twice? or a dead copy).
- The declaration order.
- white's declaration position.
- The statement order in the blocks.

Given the target's allocation (ax=s0, ay=s1, bx=s2, white=s3, by=s4) vs mine (ay=s0, bx=s1, white=s2, ax=s3, by=s4), the key is ax's priority.

Hmm! Let me think about GCC's global-alloc priorities: they're based on the number of references (refs) and the live range length. The launder on ax gave ax a 2nd set (a 2nd reference) and extended its live range.

**Hmm, what if instead the 2nd set is achieved by making ax's value flow through a DIFFERENT variable?** E.g., what if the source had:

```c
    s16 ax;
    ...
    ax = ay + 0x7B;
    ...
    /* second block */
    prim.x0 = ax; ...
```
Hmm.

What if the second block's `prim.x0 = ax` were spelled `prim.x0 = (s16)(ay2 - ...)`? no.

**What if we introduce a temp for ax's second use?** e.g. `t = ax;` then `prim.x0 = t;` — that changes the allocation ✗.

Hmm, what about: the launder is on ax AND by. Maybe the effect is mostly on `by` (which is pinned, so its allocation is fixed) and the "boost" comment says "-> by/ax/bx/ chain/ay revert to source order" — i.e., the by launder affects the scheduling of the chain by/ax/bx/ay.

So maybe the key is the SCHEDULING (the order of the 4 addiu's) rather than the allocation. And the allocation difference (ax=s3 vs s0) might be a CONSEQUENCE of the scheduling? No — the allocation is independent.

Hmm, hmm. Let me look at the diff again:
- mine[31]: li s2,255 (white) | target: li s3,255 → so white is s2 in mine, s3 in the target.
- mine[63-64]: lhu s1,26(sp); lhu s0,24(sp) | target: lhu s2,26(sp); lhu s1,24(sp) → these are ay = out.vx (sp+24) and bx = out.vy (sp+26)? So in mine, ay=s0 (sp+24 → s0) and bx=s1 (sp+26 → s1); in the target, ay=s1 and bx=s2 ✓ (the target: lhu s2,26(sp) = bx=s2, lhu s1,24(sp) = ay=s1).
- mine[72-75]: addiu s3,s0,123 (ax=ay+123); addiu s4,s1,-93 (by=bx-93); addiu s1,s1,-87 (bx=bx-87); addiu s0,s0,117 (ay=ay+117)
- target[72-75]: addiu s4,s2,-93 (by=bx-93); addiu s0,s1,123 (ax=ay+123); addiu s2,s2,-87 (bx=bx-87); addiu s1,s1,117 (ay=ay+117)

So the target's order: by, ax, bx, ay. Mine: ax, by, bx, ay.

And the allocation: target ax=s0, ay=s1, bx=s2, white=s3, by=s4; mine ay=s0, bx=s1, white=s2, ax=s3, by=s4.

So in mine, ax has a LOWER priority than in the target. The launder's 2nd set on ax (placed after the first use) — hmm, how does that RAISE ax's priority?

In GCC's global-alloc, the priority of an allocno is computed by `allocate_more_registers`/`global_alloc`: the order is by "refs" (the number of references) and then by the live-range length. A 2nd set adds a reference ✓ and extends the live range (the pseudo is live from the first set to the last use — the launder's set is after the first use, so the live range extends past it) ✓✓.

So the launder makes ax live LONGER (from the first set to the second set, which is past the first use). In the target, ax's live range extends to the second block. But without the launder, ax's live range also extends to the second block (it's used there!) — hmm, the uses are: prim.x1 = ax (in the first block) and prim.x0 = ax (in the second block). So ax is live from its definition to the second block anyway!

Hmm, so the launder doesn't extend the live range. But it adds a REFERENCE (the asm's output counts as a use/def of the pseudo).

Hmm, and the "S2 boost" comment: in GCC's scheduler, the priority of an insn depends on the number of sets/uses of the pseudo (the "S2" = the secondary priority in sched2?). Hmm.

OK, whatever the exact mechanism, the plain-C equivalent would be "a real 2nd set of ax that adds a reference". The candidates:
- `ax = ax;` (identity — not allowed, and folded)
- `ax = (s16)ax;` (folded for an s16)

Hmm! What if ax were declared as `s32` and the stores cast to s16? Then `ax = (s16)ax;` would be a real conversion → but it adds instructions (the sign extension) — v7 showed 211 ins (4 extra) and score 50 ✗.

Hmm, what if ax were declared `u16`? Then `ax = (u16)ax;` → a zero-extension → on MIPS, a zero extension from 16 to 16 bits = a no-op ✗ (folded).

Hmm, what about `ax = (u16)(ax + 0);`? folded.

What if the 2nd set has a DIFFERENT value? E.g. in the second block, ax could be recomputed as `ax = ay - 0x75 + 0x7B`? Hmm: ay was updated to ay_old + 0x75 in the first block, so ay_new - 0x75 + 0x7B = ay_old + 0x7B = ax ✓!! And the expression `ay - 0x75 + 0x7B` is different from `ay_old + 0x7B` → cse can't merge them (different expressions) ✓✓ and the value is correct ✓✓!

Hmm! But it adds an extra instruction (sub + add) ✗ — unless GCC folds `ay - 0x75 + 0x7B` into `ay - 4` (1 instruction!) ✓✓✓!!! YES: ay_new - 0x75 + 0x7B = ay_new - 0x75 + 0x7B = ay_new - 4 (since 0x7B - 0x75 = 6 → ay_new - 0x75 + 0x7B = ay_new + 6) hmm: ay_new = ay_old + 0x75, so ax = ay_old + 0x7B = ay_new - 0x75 + 0x7B = ay_new + 6 ✓. So `ax = ay + 6;` would be 1 instruction ✓ (the same count as the original addiu!).

But wait: the original computes `ax = ay_old + 0x7B` (1 addiu) in the first block, and my version would compute `ax = ay_new + 6` in the second block (1 addiu) — but the FIRST block still needs ax = ay_old + 0x7B → 2 addiu's total ✗ (the target has 4 addiu's: by, ax, bx, ay).

Hmm. Unless the first block doesn't compute ax at all! In the first block, ax is used for prim.x1 = ax. Hmm, so the first block needs ax.

Hmm, so we'd have: ax = ay_old + 0x7B (first block) and ax = ay_new + 6 (second block) → 2 addiu's → 5 total ✗.

Unless GCC's CSE merges them: ay_new + 6 vs ay_old + 0x7B — different expressions → no merge ✗.

Hmm. OK.

**What about by?** by = bx - 0x5D (first block), and in the second block by is used. The by launder gives it a 2nd set. Similarly, bx is modified in place (`bx = bx - 0x57`) after being used for by.

Hmm.

OK, let me think about the SCHEDULING instead. The 4 addiu's order: target = by, ax, bx, ay; mine = ax, by, bx, ay.

The source order of the computations:
```c
        bx = out.vy;          /* load */
        ay = out.vx;          /* load */
        by = bx - 0x5D;       /* addiu by */
        ax = ay + 0x7B;       /* addiu ax */
        bx = bx - 0x57;       /* addiu bx */
        ...
        ay = ay + 0x75;       /* addiu ay */
```
So the source order is: by, ax, bx, ay — EXACTLY the target's order ✓✓✓! And my compile produced ax, by, bx, ay — so the scheduler swapped the first two.

**SO THE TARGET'S ORDER = THE SOURCE ORDER** (sched1 didn't reorder them), and my compile reordered them (ax before by). The launder on ax/by changed the scheduling priority so that the source order was kept.

So the levers affect sched1's ordering of these 4 addiu's. The priority of an insn in sched1 depends on the pseudo's "S2" (the number of sets?) — the comment says "2nd set kills ax's S2" and "boost (same for by) -> by/ax/bx/ chain/ay revert to source order".

Hmm! So the launder on ax KILLS ax's S2 boost, and the launder on by BOOSTS by?! Hmm, confusing. Whatever: the net effect is that the source order is preserved.

In GCC's sched1, the priority of an insn is computed from the insn's cost and the "birth" of the pseudo. The 2nd set of ax (the launder) makes ax's pseudo 2-set → the "S2" (secondary) boost is removed → the addiu for ax is scheduled later (at its source position) ✓.

So: I need ax's addiu to keep its source position (after by's). Without the launder, ax's addiu got boosted (single-set pseudo → the birth boost) → it was scheduled EARLIER (before by).

Hmm! So the fix: make ax's pseudo 2-set (a real 2nd set) so it loses the birth boost ✓ — that's the "real 2nd set" trick. And by's launder does the same for by.

But: a real 2nd set must be value-preserving and not add instructions. `ax = ax;` → folded ✗.

Hmm, hold on: is `ax = ax;` really folded? In GCC 2.7, expand_assign with the LHS and RHS being the same variable → (set (reg ax) (reg ax)) → cse deletes it as a no-op ✓ folded. Hmm.

But the brief says identity statements don't count anyway.

Hmm, what about a 2nd set with a value-preserving CONVERSION that MIPS implements for free? E.g. `ax = (u16)ax;` for an s16 → the conversion s16→u16: in GCC, the value bits are the same; the RTL: (set (reg ax HI) (reg ax HI))? Hmm, for a u16 target from an s16 source, GCC 2.7 would... the modes are both HImode; the conversion is a no-op → folded ✗.

What about `ax = (s16)(u16)ax;`? Same ✗.

Hmm, what about making ax's 2nd set a *different variable's* value with the same content? E.g. `ax = bx - 0x57 + 0x74`? Hmm: bx_new = bx_old - 0x57; ax = ay_old + 0x7B. Is there a relation? ay = out.vx, bx = out.vy — unrelated ✗.

Hmm. What about `ay`? ay_new = ay_old + 0x75; ax = ay_old + 0x7B = ay_new + 6 ✓ (as computed before). So `ax = ay + 6;` in the second block would be a real 2nd set with 1 addiu. But then the first block's `ax = ay + 0x7B` is also needed → 2 addiu's for ax ✗ (the target has 1).

Hmm! Unless... the first block's prim.x1 = ax could be spelled differently: prim.x1 = ay + 0x7B! (the value is the same, computed inline) → then ax is only assigned in the second block ✓✓✓ — and the first block's `prim.x1 = ay + 0x7B` would be an addiu too ✗ (still 2 addiu's: one for prim.x1 and one for ax).

Hmm, unless the first block's prim.x1 uses the SAME addiu as the second block's ax... i.e., if ax is assigned BEFORE the first block and the second block just re-uses it (that's the current structure) — then ax has 1 set ✗.

Hmm, what if ax is assigned in the first block AND the second block's use is `prim.x0 = ax` (as now) — then the launder's 2nd set is what we need.

**Hmm, what if the second block's `prim.x0 = ax` were spelled `prim.x0 = ay + 6;`?** Then ax would only be needed in the first block (prim.x1 = ax) → ax would have 1 set ✗ and an extra addiu ✗.

OK, so we need a real 2nd set of ax with no extra instruction.

**!!!!!!!! IDEA: USE A DIFFERENT VARIABLE FOR THE SECOND BLOCK'S VALUE !!!!!!!!!!!!**

What if the source has TWO variables for ax's value:
```c
    s16 ax;
    s16 ax2;
    ...
    ax = ay + 0x7B;      /* first block */
    ...
    ax2 = ay + 6;        /* hmm, an extra addiu */
```
✗.

Hmm. What if the second block's ax value comes from a variable that was set in between? Hmm.

**!!!!!!!! IDEA: `ax = (s16)(ax + 0)` → folded. What about `ax = ax + 0 - 0`? folded.

**!!!!!!!! IDEA: WHAT IF THE 2ND SET IS A COPY FROM A DIFFERENT PSEUDO THAT HAS THE SAME VALUE — e.g. via the `prim` struct? Hmm: `ax = prim.x1;`!!! The first block sets prim.x1 = ax → so `ax = prim.x1` (a load from the stack) → an extra load ✗.

Hmm.

**!!!!!!!! WHAT ABOUT `by`? by = bx - 0x5D (the first block) and by is used in the second block (prim.y0 = by). A real 2nd set for by: `by = bx - 0x5D` again → cse merges it (the same expression) ✗ hmm, but wait: in the second block, bx has been changed (bx = bx - 0x57) → so `by = bx - 0x5D` in the second block would give a DIFFERENT value ✗ (semantics).

Hmm, what about `by = by;` ✗ (identity).

OK. Let me try a couple of things for item 4 empirically:
- The op launder removed alone (keep the ax/by launders) — a probe to see which lever matters.
- Only the ax launder removed.
- Only the by launder removed.
- ax/by as u16 with (u16) casts.
- The 4 addiu's source order changed (e.g. by = bx - 0x5D after ax = ay + 0x7B) → the source order changes → the target's order might be reachable without the levers!! ✓✓✓

**THAT'S AN IDEA: reorder the source statements so that the scheduler's output matches!** The target's order is by, ax, bx, ay — which IS the current source order. Hmm, so the current source order already matches the target's order, but my compile reorders to ax, by. If I reorder the source to ax, by, bx, ay... the scheduler might then produce ax, by, bx, ay (the source order) ✗ (that's what I have).

Hmm, but the scheduler's order depends on priorities, not just the source order. Hmm. Let me try: what if the source order were changed so that the boosted ax ends up second? I.e., if the source order is by, ax, bx, ay and the scheduler boosts ax to the front (giving ax, by, ...), then if I put ax FIRST in the source, the boosted ax stays first ✗.

Hmm, what if the source order were ax, by, bx, ay → the scheduler: ax is boosted → it stays first → ax, by, bx, ay ✗ (the target wants by first).

Hmm, so the target's order (by first) requires by to have a HIGHER priority than ax. The launder on by "boosts" by! (per the comment "boost (same for by)"). Hmm, but the launder on ax "kills ax's S2" (i.e., ax loses its boost).

Hmm, so the net: by is boosted above ax.

Hmm, how does a 2nd set BOOST the priority? In GCC's sched1, the priority of an insn = its cost + the "birth boost" of the pseudo it defines. A 2-set pseudo... hmm, the comment says the ax launder KILLS ax's S2 (so ax's boost is killed) and the by launder BOOSTS by. Hmm, contradictory unless the effect is about the ORDER of the two launders (the ax launder comes first, the by launder second).

Ugh, this is deep GCC scheduler territory.

PRAGMATIC APPROACH for item 4: try a bunch of variants:
- reorder the statements
- different 2nd-set spellings
- move the ax/by launders' positions (as plain-C assignments)
- change white's declaration
- etc.

Given the time (08:35), let me write ~20 variants for item 4 and score them. If nothing works, WALL.

Let me think about the most promising plain-C 2nd-set spellings for ax/by that don't add instructions:

(a) `ax = ax;` — an identity (not allowed by the brief, but let me test it to learn the mechanism — if it gives 0, I'll know the mechanism and can look for a legitimate alternative).

Hmm, the brief explicitly says identity-statement launders do NOT count as a crack. So even if `ax = ax;` scores 0, I can't claim a MATCH with it. But it's a useful probe.

(b) `ax = (s16)ax;` — folded ✗ (tested, no effect).
(c) `ax = (u16)ax;` — for an s16 ax: the conversion s16→u16 = the same bits → hmm, in GCC 2.7, converting SI→HI... the modes: s16 is HImode, u16 is HImode → the same mode → no-op ✗.
(d) `by = (s16)by;` — same ✗.

(e) A real 2nd set via a *different* expression with the same value: for by: `by = bx_old - 0x5D` — but bx_old is gone. Hmm, unless we keep a copy: `bx2 = bx;` hmm, that's an extra variable (and an extra set of bx) ✗.

(f) What about the SECOND block's `prim.y0 = by` being computed as `bx - 0x5D`? Hmm: in the second block, bx has been decremented (bx = bx_old - 0x57) → bx_new - 0x5D ≠ by ✗.

Hmm, (g): what if the source kept `by`'s value in the `prim` struct: `prim.y0 = by;` — the first block sets prim.y0 = by → then the second block could read `prim.y0`... ✗ (a load).

OK, let me just test (a) `ax = ax; by = by;` as a probe, plus a few structural variants. If the probe gives 0, I'll think about how to phrase a legitimate variant (maybe a "real 2nd set" that's not an identity: e.g. `ax = (s16)(ax | 0)`? hmm, `ax | 0` for an s16 → the promotion to int → the OR with 0 → folded to ax ✗).

Hmm! What about `ax = (s16)(ax + 0)` → folded.

What about a 2nd set that is value-preserving but not an identity: e.g. `ax = (s16)(-(-ax))`? folded.

What about `ax = (s16)(ax * 1)`? folded.

Hmm, what about `by = (s16)(bx - 0x5D)` recomputed in the second block from a SAVED bx? Hmm: what if we don't modify bx in place but keep both:
```c
        bx = out.vy;          /* bx_old */
        ay = out.vx;
        by = bx - 0x5D;
        ax = ay + 0x7B;
        bx = bx - 0x57;       /* bx_new */
```
The second block uses by (the old bx - 0x5D). If instead we wrote the second block's `prim.y0 = by` as `prim.y0 = bx + 0x6` (since bx_new = bx_old - 0x57 → bx_old - 0x5D = bx_new + 0x6 - ... let me compute: bx_new = bx_old - 0x57; by = bx_old - 0x5D = bx_new + 0x57 - 0x5D = bx_new - 6) → `by = bx - 6` ✓ — but that's an extra addiu ✗ (unless we replace the `by = bx - 0x5D` in the first block: the first block's prim.y0 = by → could be `prim.y0 = bx - 6`?? hmm, then by wouldn't exist).

Hmm! What if:
```c
        bx = out.vy;
        ay = out.vx;
        by = bx - 0x5D;      /* 1st set of by */
        ax = ay + 0x7B;
        bx = bx - 0x57;
        ...
        /* 2nd block */
        by = bx - 6;         /* 2nd set of by, the same value! a real 2nd set (a different expression) */
        prim.y0 = by;
```
Hmm!! But that's 2 addiu's for by ✗ (the target has 4 addiu's total: by, ax, bx, ay).

Hmm, unless the target's 4 addiu's ARE: by(1st), ax, bx, ay — and the 2nd block's by is a COPY (a move) not an addiu ✓ (the launder's copy would be a move... but the target has no extra move for by!). Hmm, the launder's "set by = by" is a no-op in the RTL (the asm is zero-width) → no instruction ✓.

So the launder's 2nd set costs ZERO instructions. A plain-C 2nd set that costs zero instructions must be folded... but a folded 2nd set doesn't count as a set (per the cookbook: "Every pure-C second-set spelling (x = x, x += 0, x &= -1, dead-reset) is folded before reg_n_sets is computed").

Hmm! But that cookbook note was about the BIRTH BOOST (sched1's single-set boost). Here we need the S2 (a different scheduler metric?).

Hmm, hmm. So maybe `ax = ax;` (folded by cse but the RTL still has 2 sets at the time sched1 runs?) — the cookbook says the fold happens BEFORE reg_n_sets is computed, but maybe the SET COUNT for the scheduler is computed differently (from the RTL's set count, which cse's deletion would reduce).

Let me just TEST `ax = ax; by = by;` (a probe) to see if it gives 0. If yes, I'll look for a legitimate non-identity spelling that behaves the same.

Let me also test: `ax = ax + 0; by = by + 0;` hmm (the promotion to int → the RTL (plus (reg ax) 0) → folded).

And: `ax = (s16)(ax); by = (s16)(by);` (tested: no effect).

Let me run these probes now.
