---
ts: 2026-10-22T13:01:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mR6R6UGuXYyJdnCGbeme
---
The register allocation differs: the target has ax=$s0(s0), ay=$s1, bx=$s2, by=$s4(s4), white=$s3(s3)... wait:

The target's mapping (from the diff): mine s2 ↔ target s3 (white), mine s1 ↔ target s2 (bx?), mine s0 ↔ target s1 (ay), mine s3 ↔ target s0 (ax).

And the target has `addiu s4,s2,-93` (by = bx - 0x5D → s4 = s2 - 93) while mine has `addiu s3,s0,123` (ax = ay + 0x7B → s3 = s0 + 123).

So the target: ax=s0, ay=s1, bx=s2, by=s4, white=s3.
Mine: ax=s3, ay=s0, bx=s1, by=s2(?), white=s2... hmm.

Mine: mine[72] addiu s3,s0,123 → ax = ay+123 → so ay=s0, ax=s3. mine[73] addiu s4,s1,-93 → by = bx-93 → bx=s1, by=s4. mine[74] addiu s1,s1,-87 → bx = bx-87 → bx=s1 ✓. mine[75] addiu s0,s0,117 → ay = ay+117 → ay=s0 ✓.

So mine: ay=s0, bx=s1, by=s4, ax=s3, white=s2.
Target: ay=s1, bx=s2, by=s4, ax=s0, white=s3.

Hmm, so the target: ax=$s0, ay=$s1, bx=$s2, white=$s3, by=$s4. Mine: ay=$s0, bx=$s1, white=$s2, ax=$s3, by=$s4.

Interesting: by=s4 in both ✓. The others are permuted.

The source has pins: `register u8 *mat __asm__("$23")` (s7), `register s16 by __asm__("$20")` (s4) ✓ by=s4.

The declarations:
```c
    s16 ax;                          /* $s0 = out.vx+0x7B */
    s16 ay;                          /* $s1 = out.vx+0x75 */
    s16 bx;                          /* $s2 = out.vy-0x57 */
    register s16 by __asm__("$20");  /* $s4 = out.vy-0x5D */
    s32 white;                       /* $s3 */
```
So the intended allocation: ax=s0, ay=s1, bx=s2, by=s4(pinned), white=s3.

That's the TARGET's allocation ✓. My candidate got a different one — because the declaration ORDER determines the allocation priority (global-alloc's density/priority). The current source declares: in, out, prim, mat, white, ax, ay, bx, by.

Hmm, so in the target, white=s3 and ax=s0 — meaning ax has a HIGHER priority than white? In global-alloc, the allocation order is by priority (the number of references/live range). white is used 4 times (r,g,b ×?) hmm.

The difference between mine and the target: the launders on ax and by gave ax/by a 2nd set (the S2 boost) — hmm, but by is pinned to s4 anyway. The launder on ax gave ax a 2nd set which "kills ax's S2" (the S2 = secondary priority class?) hmm, the comment says "LEVER A: 2nd set kills ax's S2" and the other comment says "boost (same for by) -> by/ax/bx/ chain/ay revert to source order".

Hmm. So the launders affect the *scheduling* priority, not the allocation. But the diff shows a register permutation.

Anyway: my w2 (with `ax = (s16)ax; by = (s16)by;`) gives the same score 25 as w1 (no replacement). So the 2nd set via the s16 cast didn't reproduce the effect (or it did something else).

Let me look at the target's S2 comments: "LEVER B: colors BEFORE x0 here — drops the sb LUIDs below the x0" and "store -> white's S2 boost fires", "li $s3,0xFF lands @31".

Hmm, "white's S2 boost" — S2 is the "second-level" priority in GCC's scheduler (sched1 vs sched2). So the levers affect the SCHEDULING.

Since my w1/w2 have the same 25 mismatches, the difference is in the allocation and the schedule.

Let me think about what the levers do:
1. The launder on `op`: keeps `op` (the address &D_800A6518[idx*0x14]) in a register. Without it, GCC computes the address again (2 uses: `aGsSortLine(&prim, op, 0)` — hmm, op is used once as an argument). Hmm, actually op is used once (as the 2nd arg). But the address computation involves `aD800B9A02 * 0x14` — a runtime value → the address is (reg + const) → hmm.

Hmm, the diff doesn't show any difference related to `op` — the diffs are all about the ax/ay/bx/white registers. So maybe the op launder is harmless to remove, and the ax/by launders are what matter.

2. The ax/by launders: they give ax and by a 2nd set → this changes the *birth boost* (sched1 boosts single-set pseudos) and the register allocation (a 2-set pseudo has a different "n_sets" → different priority in global-alloc?).

From the cookbook (§405-B): "Birthing-boost kill: sched1 boosts a single-set pseudo's def; making it 2-set removes the boost and sinks the insn."

So the launders on ax/by (2nd sets) remove their birth boost → they sink. My `ax = (s16)ax;` should also give ax a 2nd set... but the score is the same as w1 (no 2nd set at all) → 25. Hmm, that means the s16 cast did NOT create a 2nd set (GCC folded `ax = (s16)ax` into a no-op? For a 16-bit value in a 16-bit variable, the cast is a no-op → folded ✓).

So I need a REAL 2nd set: e.g. `ax = ax;` (identity — not allowed by the brief) or `ax = (s16)ax` where ax is declared s32? Hmm.

The G14 trick was `v = (s16)v` where v was an s32 (so the cast truncated → a real conversion). Here ax IS s16 → the cast is a no-op.

Options for a real 2nd set of ax (s16):
- `ax = (s16)(ax + 0);` → folded.
- Change the declaration: make ax an s32 and use `(s16)` casts where needed? That changes the semantics of the stores (the target stores `sh` (16-bit) — with an s32 ax, the store would be `sw` ✗ unless cast).

Hmm: `prim.x1 = ax;` where prim.x1 is s16 → the value is truncated at the store ✓. So if ax were s32, the code would still store 16 bits, but the intermediate computations would be 32-bit → different registers/insns (e.g. `addiu` on 32-bit vs 16-bit) — the arithmetic would be the same for these values. Hmm, risky.

Alternatively: give ax a 2nd set via a *different* real operation: e.g. `ax = ax;` is an identity (not allowed). Hmm, what about the "real 2nd set" being a copy into another variable? Hmm, that changes the allocation.

Hmm, what about `by = (s16)by;` where by is s16 → no-op ✗.

Hmm. What about making the 2nd set come from a *store*? E.g. `ax = (s16)(ax);` no.

Hmm, hold on: what did the launder actually do? `__asm__("" : "=r"(ax) : "0"(ax));` → in RTL: (set ax (asm ax)) → a 2nd set of the pseudo ✓ and the value is opaque.

So the "2nd set" is what matters (per the comment). A pure-C 2nd set: `ax = ax;` → the front end: (set ax ax) → hmm, GCC's expand_assign with the same variable → the RTL would be (set (reg ax) (reg ax)) → a copy → cse would delete it (a no-op copy) → hmm, but the n_sets might be computed before cse? The G14 note says: "Every pure-C second-set spelling (x = x, x += 0, x &= -1, dead-reset) is folded before reg_n_sets is computed" — so those DON'T work.

Hmm! But the G14/G15 MATCHes used `v = (s16)v` (a real conversion) and `vol = vol | 0x3000` (a real 2nd set with a different value).

So for ax (an s16), a real 2nd set with a DIFFERENT value that is still correct... hmm.

**AH WAIT!!! Look at the source!** The launder on ax is placed AFTER the first use:
```c
        bx = bx - 0x57;
        { ... op launder ... }
        ay = ay + 0x75;
        prim.x0 = ay; prim.y0 = by; prim.x1 = ax; prim.y1 = bx;
        aGsSortLine(&prim, op, 0);
        }
        __asm__("" : "=r"(ax) : "0"(ax));   /* LEVER A: 2nd set kills ax's S2 */
        __asm__("" : "=r"(by) : "0"(by));
        prim.attr = 0;
        prim.r = white; prim.g = 0; prim.b = 0;
        prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx;
        aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0);
```
So after the first aGsSortLine, ax and by are re-set (2nd sets) and then used again in the second prim (prim.x0 = ax; prim.y0 = by).

So the SOURCE could naturally have a 2nd set of ax and by if... hmm, they're assigned once each before.

Hmm! What if the original source assigned ax/by TWICE (e.g. computed them twice)? Like:

```c
        ax = ay + 0x7B;
        ...
        ax = ay + 0x7B;    /* recomputed */
```
That would be a real 2nd set (a duplicate computation) — GCC's cse would merge the two identical computations into one (CSE!) → back to 1 set. Hmm, unless cse doesn't merge them (they're in different blocks? cse works per block + the global CSE... cse would merge them if the value is still available).

Hmm, what about `ax = ay + 0x7B;` in the first block and `ax = (s16)(ay + 0x7B);` later? Same.

OK, so how do we get a real 2nd set that cse can't merge? The G15 trick: "the vol 2nd set that restores the multiply order (u16 cast = 1 andi) is ready before the bne" — they used a u16 cast on a u32 value (a real conversion).

For ax (s16): what if we make the SECOND set a conversion from a WIDER value? E.g. the second ax could come from a different expression whose value is the same but whose RTL differs.

Hmm, what about: the second `ax` set could be `ax = (s16)(ay + 0x7B);` where ay is s16 → the addition is s16 → the same RTL as the first → cse merges ✗.

Hmm, what if the second set is `ax = (s16)(u16)(ay + 0x7B)`? Hmm, (u16) of an s16 → the same value (mod 65536) but the RTL: a zero-extension of a 16-bit value → in GCC 2.7, (u16)x where x is s16 → the conversion is a no-op? (s16 → u16 → both 16-bit; the value bits are the same → no-op) ✗.

Hmm.

OK, so how do we get the "2nd set" effect for ax/by?

**!!!!!!!! IDEA: CHANGE THE DECLARATION OF ax/by TO s32 AND USE s16 CASTS AT THE STORES !!!!!!!!**

If ax is an s32:
- `ax = ay + 0x7B;` → the addition is 32-bit (the same addiu) ✓
- `prim.x1 = ax;` → the store is 16-bit (the assignment truncates) → `sh` ✓ (the target has `sh s0,36(sp)`).
- the 2nd set: `ax = (s16)ax;` → a real conversion (s32 → s16) → a truncation → in RTL: (set ax (truncate (sign_extend ...)))? Hmm, on MIPS, a 32→16 truncation is usually free (the value is already in a register; the conversion is a no-op in the RTL if the pseudo's mode is 32-bit and the conversion to 16-bit is just a SUBREG). Hmm, GCC's expand for `ax = (s16)ax` where ax is s32: the RHS is a HImode value → the assignment to the 32-bit ax → the value is sign-extended → the RTL: (set ax (sign_extend (reg ax))) — hmm, or (set (reg ax HImode) ...) then (set ax (zero_extend ...)). GCC's expand_assign for a narrow RHS into a wider LHS: it emits the narrow value into a HImode pseudo then a zero/sign extension into the SI pseudo → so ax (the SI pseudo) gets a 2nd set = (sign_extend (hi)) → a REAL 2nd set ✓✓ (and it's a distinct expression from the original → cse can't merge it with the first set).

But: this changes the *type* of ax → the arithmetic `(ay + 0x7B)` would be 32-bit if ay is s16? Hmm: `ax = ay + 0x7B;` with ay s16 → the addition is done in int (32-bit) per C's integer promotion → the result is assigned to ax (s32 now) → the same addiu ✓ (the target's `addiu s0,s1,123`).

Hmm, but the promotion: with ax as s16, `ay + 0x7B` is an int, then truncated to s16 on the assignment → GCC would emit the add and then... on MIPS, the truncation to 16 bits is free (the value is in a 32-bit reg; the HImode value is a SUBREG). Hmm, actually GCC 2.7 would emit the add in 32-bit and then the assignment to the HImode pseudo → the store would use the low half ✓. So with ax as s32 vs s16, the generated code is probably the SAME except for the 2nd set's conversion.

Hmm, but the *allocation* might change (the pseudo's mode).

This is getting deep. Let me try a batch of variants for item 4:
- v1: remove the launders (w1) → 25
- v2: ax/by as s32 with `(s16)` casts at the stores + a 2nd set `ax = (s16)ax;` hmm.
- v3: keep the ax/by as s16 but make the 2nd set a real conversion: hmm.

Hmm, wait. Let me reconsider. What does the launder on ax/by actually change? Let me diff the target against w1 more carefully — the diff showed register permutations (ax/ay/bx/white). So the launders affect the REGISTER ALLOCATION (greg/global-alloc priorities), not just the schedule.

Why would a 2nd set of ax change the allocation? In GCC's global-alloc, the priority is based on the number of references and the live range length. A 2nd set extends ax's live range (ax is live from its first set to its last use) — hmm, actually the launder's 2nd set is AFTER the first use, so it EXTENDS ax's live range (the launder is a "re-tie" that keeps ax alive until that point). Hmm, but the comment says "2nd set kills ax's S2" (a scheduling thing).

Hmm, in the diff: mine has ax=s3, ay=s0, bx=s1, white=s2; the target has ax=s0, ay=s1, bx=s2, white=s3.

So in the target, ax has the HIGHEST priority (s0 first), then ay (s1), bx (s2), white (s3). In mine, ay has the highest (s0), bx (s1), white (s2), ax (s3).

Hmm, so ax's priority dropped in mine. The launder on ax gave it a 2nd set → hmm, how does a 2nd set RAISE the priority? Hmm, maybe: with the launder, ax's live range is longer (it spans from the first set to the second set + the uses) → a longer live range → a higher priority in global-alloc → ax gets s0 ✓.

So the launder EXTENDS ax's live range! Because the 2nd set is placed after the first use, the pseudo stays live across that region.

Hmm, so a plain-C 2nd set of ax placed at the same position would extend the live range the same way ✓. But it must be a REAL 2nd set (not folded).

Hmm, but the "2nd set" must produce a value equal to ax's current value (the launder is value-preserving). A plain-C 2nd set that's value-preserving: `ax = ax;` (folded ✗), `ax = (s16)ax` (folded for an s16 ✗).

Hmm! What about a 2nd set whose value is DIFFERENT but the code is still correct? E.g. `ax = ay + 0x7B;` again — cse would merge it with the first (if the first is still available) → the 2nd set disappears ✗.

Hmm, what about `ax = bx - 0x57 + 0x74`? Silly.

Hmm, what about the ORDER: the first ax = ay + 0x7B (with ay = the old value) and the second ax could be recomputed from a DIFFERENT expression with the same value: e.g. the first `ax = ay + 0x7B` where ay = out.vx (the load) and the second `ax = out.vx + 0x7B`?? Hmm, but `out.vx` is reloaded → the value is the same but the expression differs → cse might not merge (the reload of out.vx is a different expression). Hmm, but that would add a load instruction ✗ (the target's second ax use doesn't reload).

Hmm, hold on: what does the target's code look like around the second prim? Let me look at the target's disassembly for the region. Let me dump the target for item 4 and look at the s0/s4 usage.

Actually, let me think about the ax/by 2nd sets differently: the launder `__asm__("" : "=r"(ax) : "0"(ax));` at that point re-ties ax to a fresh pseudo. The 2nd set extends ax's live range to that point.

**A PLAIN-C EQUIVALENT: `ax = ax;` — but it's folded by cse (a no-op copy is deleted).**

Hmm, BUT: the cookbook says the pure-C second-set spellings are folded before reg_n_sets is computed. Hmm, that was about the BIRTH BOOST. For the LIVE RANGE extension, a folded copy doesn't extend anything.

Hmm, what if the 2nd set is a real assignment whose value is the same but computed differently, e.g.:

```c
        ax = (s16)(ax + 0);   /* folded */
```

Hmm.

What about using a different variable? E.g. the 2nd set could be `ax = bx - 0x57 - 0x1C + 0x1C`? Silly and folded.

**WHAT ABOUT MAKING ax's SECOND SET A REAL CONVERSION BY CHANGING ITS TYPE?** As discussed: declare `ax` as s32 and write `ax = (s16)ax;` for the 2nd set. Hmm, but then the first set `ax = ay + 0x7B;` (32-bit) and the second `ax = (s16)ax;` → the RTL: (set ax32 (sign_extend (hi ax32))) hmm — that's a real 2nd set ✓ and it extends the live range ✓.

But the type change might affect other things (e.g. `prim.x1 = ax;` → the store truncates ✓ same).

Hmm, and `by` is PINNED to $20 with `register s16 by __asm__("$20")` — changing by's type to s32 would change the pin's mode → the register would hold a 32-bit value ✗ (the target's by is used as `sh s4,...` — a 16-bit store; with s32 by, the store would still be 16-bit but the pinned reg would be 32-bit — hmm, the target's `addiu s4,s2,-93` computes by = bx - 93 as a 32-bit add (with s16 semantics, the result is truncated to 16 bits — the target's `addiu s4,s2,-93` is a 32-bit add storing into a 16-bit var → the truncation is implicit) ✓ same.

Hmm, this is getting complicated. Let me just try a batch of variants for item 4 and see if any scores 0. But given the complexity (the register allocation), the chance is moderate.

Let me think about what's most likely to work:
The levers: (1) the op launder, (2) the ax launder, (3) the by launder.

Since the diff shows only register permutations (ax/ay/bx/white) and the `addiu` order, maybe the *scheduling* of the 4 `addiu` computations differs:
mine:  addiu s3,s0,123 (ax); addiu s4,s1,-93 (by); addiu s1,s1,-87 (bx); addiu s0,s0,117 (ay)
target: addiu s4,s2,-93 (by); addiu s0,s1,123 (ax); addiu s2,s2,-87 (bx); addiu s1,s1,117 (ay)

So the ORDER of the 4 addiu's differs: the target does by, ax, bx, ay; mine does ax, by, bx, ay.

And the register assignment differs.

Hmm, so it's a scheduling + allocation issue. The levers (the launders) affect the scheduling priorities.

This is the classic "sched1 priority" family. The moves.md has many such walls ("sched1-birth-boost", "S2 boost", etc.).

Given the difficulty, item 4 might also be a WALL. Hmm.

BUT: the brief says a WALL needs ≥30 scored tries. Let me generate variants and score them in bulk.

Let me now decide the overall plan given the time (it's ~08:00 now; I started at 06:37 → 1h23m). I've used a lot on items 1-2. Let me:

1. Spend ~20 min on item 4 with a batch of variants (aiming for a MATCH).
2. Spend ~10 min each on items 1-3 with a batch of 30+ variants each (to satisfy the WALL requirement of ≥30 scored tries) and record the best.
3. Write the log + results.

Let me be efficient. First item 4's variants.

Ideas for item 4:
(a) Remove the op launder only (keep the ax/by launders) — that keeps the ax/by 2nd sets but has an asm → not lever-free ✗ (the launder kind must be gone).
(b) Replace the ax/by launders with real 2nd sets:
   - `ax = (s16)ax;` with ax as s32 (type change)
   - `by = (s16)by;` with by as s32 — but by is pinned $20; a pinned s32 vs s16 → the pin's mode changes → the target's by is 16-bit? Hmm, the target's `addiu s4,s2,-93` then `sh s4,40(sp)` — hmm, `sh` stores 16 bits ✓. So by's pinned reg holds a 16-bit value. If by were s32, the pinned reg would hold a 32-bit value and the store would still be `sh` ✓ (the truncation at the store). Hmm, but the pin's mode affects the allocation (a 32-bit pinned reg vs 16-bit) — the same register $20 either way ✓.

Hmm, wait. Actually — hold on! Let me reconsider: maybe the 2nd set doesn't need to be value-preserving in the same way. What if the second `ax` set is a *recomputation* of the same value from the same inputs but spelled differently so cse can't merge it? E.g.:

First:  `ax = ay + 0x7B;`  (ay = out.vx)
Second: `ax = (s16)(ay + 0x7B);` — same expression, cse merges ✗.

What about: the second set could come from a *different* variable holding the same value: e.g. `bx + 0x18`? (bx = out.vy - 0x57 — no relation).

Hmm.

What about the trick used in G14: "the launder -> `v = (s16)v` (a real 2nd set)" — for v an s32. So for ax (s16), the analogous trick would need ax to be s32.

**LET ME TRY: declare ax and by as s32 (keeping the pin for by but changing the type), and add `ax = (s16)ax;` / `by = (s16)by;` as the 2nd sets.**

Hmm, but the pin `register s16 by __asm__("$20")` — if I change it to `register s32 by __asm__("$20")`, the pin stays (a pin, allowed) ✓.

Hmm, but wait: would the stores still be 16-bit? `prim.y0 = by;` where prim.y0 is s16 → the assignment truncates ✓ → `sh` ✓.

And `by = bx - 0x5D;` → 32-bit arithmetic (the same addiu) ✓.

Hmm, and the S2 boost: the 2nd set `by = (s16)by;` → a truncation → the RTL: (set by32 (truncate (reg by32)))? Hmm, on MIPS a 32→16 truncation of a register value is a no-op (the low half) → GCC might emit (set (reg by HImode) (reg by)) — i.e. a SUBREG copy → hmm, that's a "copy" that might be folded by cse ✗.

Hmm. In GCC 2.7, `by = (s16)by;` with by as s32: expand_assign: the RHS is a HImode value → the LHS is an SI pseudo → GCC emits (set (reg by) (zero_extend (reg by HImode))) hmm, or (sign_extend). Since by is s32 and the RHS is s16 → the conversion is a SIGN extension → (set (reg by SI) (sign_extend:HI (reg by HI))). And the HImode source: (set (reg tmp HI) (reg by SI))? Hmm, GCC would do: convert to HI mode = a truncation (extract the low half) → in GCC 2.7 with a 32-bit reg, the HI value is a SUBREG → (set (reg tmp HI) (subreg:HI (reg by SI))) → then sign_extend → (set (reg by SI) (sign_extend (reg tmp HI))).

Hmm, the sign_extend of a HI value: GCC would emit `sll tmp, 16; sra tmp, 16` (2 insns) ✗ — that would ADD instructions!

Hmm, but wait: GCC 2.7's mips backend: a sign_extend from HI to SI is `sll+sra` (2 insns) — unless it can use `sext` (the mips2 `seb`/`seh`? no, mips1 has no seb). Hmm, GCC's mips has "mips_sext" hmm.

Hmm, that would break the instruction count (207 = the target's count). So the s16-cast trick would add instructions ✗.

Hmm! Unless the 2nd set is a ZERO-extension (u16): `ax = (u16)ax;` → (zero_extend HI→SI) → on MIPS: `andi`? no, a zero extension from 16 to 32 = the value's low 16 bits → `move`+`andi 0xffff`? Hmm, in GCC's mips, a zero_extend from HI to SI is free (just use the reg, masking on use)? Hmm, GCC's mips has `mips_zer_extend`... hmm, actually for MIPS I believe the zero-extension from HImode to SIMode is done with `andi reg, 0xffff` (1 insn) — hmm, no: for a zero extension, the upper bits must be cleared → `andi` (1 insn) or the value is used with a `lhu` (no). Hmm.

Hmm, but the G14 example: "the launder -> `v = (s16)v` (a real 2nd set)" worked and MATCHED — so the s16 cast didn't add instructions there. Because the value's upper bits were already correct? For a sign-extension from a 16-bit value stored in a 32-bit reg: `sll v,16; sra v,16` (2 insns) — that would show up. Hmm, unless GCC knew the value was already sign-extended.

Hmm, in the G14 case, `v = (s16)v` where v was an s32 holding a sign-extended 16-bit value: GCC's expand would emit the truncation+extension, but the optimizer (combine) might fold it to a no-op if it can prove the value is already in range ✗ (it can't).

Hmm, but G14's MATCH had "v = (s16)v; u = tmp" — hmm.

OK, let me just TEST: item 4 with ax/by as s32 and the casts. And other variants. Let me write a batch.

Given the time, let me write a script that generates a bunch of variants for item 4 and scores them all.

Variants for item 4:
v1: remove all 3 launders (w1) → 25
v2: ax/by s32 + (s16) casts as the 2nd sets, op launder removed (w2-like but with the type change)
v3: same as v2 but with (u16) casts
v4: remove only the op launder, keep ax/by launders (not lever-free, but a probe)
v5: v2 + the order of the prim stores changed
v6: white's declaration order moved (decl order/scope is in the catalog!): the target's allocation is ax=s0, ay=s1, bx=s2, white=s3, by=s4. The current declarations are: white, ax, ay, bx, by. Maybe reordering the declarations (white after bx) changes the allocation! ✓ That's a catalog move ("decl order").

**v6 is promising!** The global-alloc order might follow the declaration order for equal priorities. Let me try reordering the declarations: ax, ay, bx, white, by.

Hmm, but the target's allocation is ax=s0, ay=s1, bx=s2, white=s3 — so white comes AFTER bx. Currently white is declared FIRST. So reordering to (ax, ay, bx, white, by) might give the target's order ✓.

Let me try that! And also (ax, ay, bx, by, white) etc.

Let me generate and score a batch.
