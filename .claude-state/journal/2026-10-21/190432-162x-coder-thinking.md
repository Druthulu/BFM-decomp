---
ts: 2026-10-22T01:04:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CuWahuLKm7Esejg6wFak
---
z8 (the clean per-branch re-computation) = 13. So the "clean" version doesn't work; z2 worked because in the else branch the re-computation was the *negated* expression, which changed the RTL in a way that reproduced the target.

Hmm! So the else branch's negation is *needed* to get the target's code?! That means the target's else branch is NOT `sum - x`... hmm, but the target's asm is `subu v0,v1,a0` = sum - x (v1 = sum, a0 = x). Hmm, and with z2 (diff = x - sum in the else branch), GCC's compiled code was `subu v0,v1,a0` — the same!

So GCC turned the else branch's `diff = x - sum` into `subu v0,v1,a0`?! That means GCC *negated* it: x - sum where x = a0 and sum = v1 → `subu v0,a0,v1`... but the observed code is `subu v0,v1,a0`. So GCC did NOT use the second assignment; it used the first (sum - x). So GCC dropped the second assignment in the else branch.

Why? Hmm! Because of the do-while! The do-while creates a loop; GCC's *loop* optimizer or the *cse* pass... hmm.

OR: maybe GCC's fold turned the comparison `diff < 0x10` (with diff = x - sum) into the *equivalent* test on the negated value? Since the else branch is entered when x - sum < 0 (i.e. sum - x > 0)... hmm, and the test `diff < 0x10` with diff = x - sum < 0 → always true → GCC could fold the whole thing to "return 1"! But it didn't (the code is still there).

Hmm, GCC 2.7.2 probably: in the else branch, the value x - sum is *provably negative* (since the else branch is taken when x - sum < 0) → so `diff < 0x10` is always TRUE → GCC would fold the branch to "return 1"! But the target's code keeps the test. So GCC didn't fold it (its range analysis is weak) — but it did keep the *first* assignment's value in the comparison?!

I'm confused, but empirically z2 works and z8 doesn't.

Hmm, hmm. Since z2's *compiled output* is byte-identical to the target, the *behavior* is identical. But the C source is "wrong" in the sense that it computes the negated value and then the compiler ignores it. That's fragile and confusing.

Hmm, let me look for a cleaner alternative that also scores 0. Options:
(a) The (s16) cast version (z3, cb009) — value-changing in the abstract but folded by GCC.
(b) z2 (the negated re-computation) — weird.
(c) Hmm, what about the do-while + a *real 2nd set* of a *different* variable? E.g. in the else branch, re-set `sum`? Hmm.

Let me think about what the *asm* needs: the target's else branch:
```
9cf4: subu v0,v1,a0     ; sum - x
9cf8: slti v0,v0,16
9cfc: bnez v0,9d08
```
and the if branch:
```
9cd8: subu v0,a0,v1     ; x - sum
9cdc: bltz v0,9cf4
9ce0: slti v0,v0,16     ; delay
9ce4: bnez v0,9d08
```
So both branches compute the difference and test it; the *shared* structure is what the do-while restores (the "return c" fold is blocked).

So the *value* of the cast/re-computation doesn't matter for the shape; what matters is that the value is "fresh" (a new set) so the fold is blocked. In the if branch, the re-computation (the same expression) is folded by CSE → hmm, but then it wouldn't be a "fresh set"...

Hmm! But z2 (with the *same* expression in the if branch) scored 0, so the if branch's re-computation (folded by CSE?) still worked. Hmm, confusing.

OK, let me take a practical approach: try more variants of the *if*/*else* re-computation to find one that is both score 0 and clean:
- if branch: `diff = *(s16 *)(s1 + 0xA) - sum;` (the same) + do-while
- else branch: variants:
  - `diff = sum - *(s16 *)(s1 + 0xA);` (the same) → z8 = 13
  - `diff = *(s16 *)(s1 + 0xA) - sum;` (the negated) → z2 = 0
  - `diff = 0 - (sum - *(s16 *)(s1 + 0xA));` (an explicit negation) → hmm, that's the same as the negated one but explicit.
  - `diff = (s16)diff;` (the cast) → 0

Hmm. So for the else branch, we need the value to be "fresh" in a way that the compiler doesn't fold. The negation works because GCC's *value numbering* treats `x - sum` as a different value from `sum - x`... and then the comparison uses the NEW value → the compiled code should be `subu v0,a0,v1` (x - sum) — but the observed code was `subu v0,v1,a0`!

Hmm, unless the *order* of the registers differs: in the else branch, maybe v1 = x and a0 = sum? Let me check: in the target, `lh a0,10(s1)` loads x into a0, and v1 = sum (from `addu v1,v1,v0`). So `subu v0,v1,a0` = sum - x ✓ (the target's else branch).

In z2's compiled output, the else branch is `subu v0,v1,a0` = sum - x. But the source says diff = x - sum → `subu v0,a0,v1`. So GCC used the FIRST assignment (sum - x) — i.e. it dropped the second one.

So GCC *did* drop the negated re-computation. Why? Because the comparison `diff < 0x10` — hmm, GCC must have used the *first* value. Hmm, maybe because the *do-while* loop confused the value numbering (the loop's back edge) and GCC's cse didn't update the value → it used the stale value.

AH, that's probably it: the do-while(0) creates a loop; the "fresh set" inside the loop is a *different* value in the loop's RTL, and the *use* after the loop (the comparison) uses the value from *before* the loop (the loop is never entered — hmm, but the do-while(0) is entered once).

Hmm, GCC's loop optimizer would rotate the do-while(0) loop... The do-while(0) executes its body once. GCC's "loop rotation" would move the body *before* the loop test → the body's assignments become unconditional → and the value after the loop is the body's value. Hmm.

OK, empirically z2 works and is value-preserving *in the compiled output* but the C is confusing. Hmm.

Let me try to find a cleaner one: what if the else branch's re-computation is written as a *separate variable*? E.g.:
```
} else {
    s32 d2 = sum - *(s16 *)(s1 + 0xA);
    diff = d2;
    do { } while (0);
    ...
}
```
Hmm.

Honestly, let me reconsider: which is the best deliverable for func_8018656C?
- Option A (z2): the do-while + a re-computation (the negated expression in the else branch). Compiled output identical; the C's else branch computes a value that the compiler discards. Confusing but the *effect* is right.
- Option B (cb009/z3): the do-while + `diff = (s16)diff;`. Compiled output identical (GCC folds the truncation). The C says "diff is truncated to 16 bits" — a semantic difference in the abstract, but the compiled code is the target's.

Hmm, hmm. Both have a "C says one thing, the compiler does another" property. Hmm.

Hmm, hold on! Let me reconsider Option B: is the truncation really value-changing? diff = x - sum where x, sum are s16-derived. In the *if* branch, diff ≥ 0 (the branch condition). Hmm, and the comparison is `diff < 0x10`. Hmm, if diff is truncated to s16, then for diff ∈ [32768, 98302] the truncated value is negative → the comparison differs. So yes, value-changing in the abstract.

Hmm, hmm. But: does the *game* ever have such large diffs? Probably not (the values are small coordinates). But "probably" isn't proof.

Hmm, what about the "real 2nd set" in the *if* branch only, with the else branch using a different clean replacement? The if branch's re-computation (the same expression) is the "real 2nd set" ✓; the else branch needs something that (a) is value-preserving and (b) blocks the fold.

What if the else branch's replacement is `do { } while (0);` + `sum = sum;`? (identity — forbidden).
What if it's `do { } while (0);` + `diff = diff;`? (identity — forbidden).
What if it's `do { } while (0);` + `x = *(s16 *)(s1 + 0xA);` where x is a new local? Hmm, a new local (an extra stack slot → the frame changes!). Hmm, unless it's a register-allocated local. Hmm, the frame: the target's frame is 48 bytes; adding a local might change it.

Hmm, what about the else branch: `do { } while (0);` + `diff = *(s16 *)(s1 + 0xA) - sum;` (z2's version)? The compiler drops it (using the earlier value) — so the *behavior* is the target's ✓ but the C is odd.

Hmm, hmm, hmm. Wait, actually, let me reconsider: is it possible that GCC does NOT drop it, and that the else branch's compiled `subu v0,v1,a0` is actually the *negated* computation because the register assignment differs? I.e. maybe in z2's else branch, GCC assigned x to v1 and sum to a0? Hmm: `subu v0,v1,a0` = v1 - a0. If v1 = x and a0 = sum → x - sum ✓ = the negated value! Hmm! But the *load* `lh a0,10(s1)` puts x in a0 (the same as the target) and `addu v1,v1,v0` puts sum in v1. So v1 = sum, a0 = x → `subu v0,v1,a0` = sum - x. Hmm, unless the *whole function*'s register assignment differs... but the score is 0 (byte-identical) → the loads are the same → v1 = sum, a0 = x → the else branch computes sum - x.

So GCC dropped the negated assignment. Confirmed by the byte-identical asm.

OK. Decision: for func_8018656C, I'll use z2 (the do-while + a real 2nd set) since it's in the moves.md catalog ("real 2nd set") and the compiled output is the target's. I'll note in notes.md that in the else arm the re-computation is written as the same expression pair and that gcc keeps the first value (the compiled output is the target's byte-for-byte).

Hmm, hmm. But hmm, the C in the else arm says:
```
diff = sum - *(s16 *)(s1 + 0xA);
do { } while (0);
diff = *(s16 *)(s1 + 0xA) - sum;   /* the negated value! */
if (diff < 0x10) { return 1; }
```
That's a C that computes the negation and then tests it — but the compiler uses the first value. A reader would say the C is wrong. Hmm.

Versus Option B (the (s16) cast): the C says "diff is truncated to 16 bits" — also a semantic change, but a *plausible* one (the game's original code may well have used 16-bit arithmetic — indeed the *first* block of this very function writes `diff = (s16)D_80126B62 - sum;` with an explicit (s16) cast! So the game's code plausibly had s16 diff arithmetic in places).

Hmm! Actually, that's a good argument for the cast: the surrounding code (the first block) uses `(s16)` casts on the camera values, suggesting the original game code used 16-bit values there. And the target's asm for the first block: `lh a0,0(a0)` (a 16-bit load) then `subu v0,a0,v1` (a 32-bit subtraction of the *sign-extended* values) → the game's diff was 32-bit there.

Hmm, so no.

OK, let me try yet another clean option: what if the *if* branch uses the re-computation (the same expression) and the *else* branch uses a *cast on a different variable*? E.g. in the else branch: `do { } while (0);` + `sum = (s16)sum;`? Hmm, sum is a *value* (x + y) — the truncation changes the else branch's `diff = sum - x` computation... but wait, the else branch's diff is assigned BEFORE the do-while (`diff = sum - *(s16*)(s1+0xA);`), so a later `sum = (s16)sum;` doesn't affect diff's value! It's dead (except it might block the fold). Hmm! And it's a *value-changing* statement (truncating sum) but sum is dead afterwards → the program's behavior is unchanged! Hmm, but "sum" is used... after the else branch? No: sum is a block-local; after the else branch ends, sum is dead. So truncating it is harmless ✓.

So the else branch: `do { } while (0); sum = (s16)sum;` — hmm, but that changes sum's value; sum is dead after → the behavior is unchanged ✓. And it's a "real set" of sum.

Let me test this variant (z9): if branch: do-while + `diff = *(s16 *)(s1 + 0xA) - sum;` (the same expression = a real 2nd set); else branch: do-while + `sum = (s16)sum;`.

Let me try it. If it doesn't work, I'll go with z2 and document it.

Let me also try: else branch: do-while + `diff = sum - *(s16 *)(s1 + 0xA);` but with the *if* branch using the cast.

Let me write a few and score.
