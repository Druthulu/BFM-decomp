---
ts: 2026-10-22T00:54:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zsRffvMIVsZXXmQeHR2T
---
Same as before: `or a2,v1,v0` — the OR computed directly into a2 (r's reg), no copy. So the copy STILL dissolved even with r as u16.

Hmm! Why did 8003DF8C work then? Let me look at the 8003DF8C q15 target vs mine... it MATCHED, so the copy survived there.

Hmm, the difference: in 800D0D7C, `now` is a LOCAL variable (a pseudo) and `r = now` — the copy is between two pseudos. In 8003DF8C, `i = arg0` — the source is the PARAMETER (a hard reg a0 at entry).

Hmm! So the HImode copy from a HARD REG survives, but from a pseudo it doesn't?

Hmm, or maybe: in 800D0D7C, the `now` value is used later (now & 0xFF00), so `now` stays alive → the copy `r = now` is a copy of a live pseudo → cse propagates r's uses to now? Hmm, but then the `andi v0,a2,0xff` would become `andi v0,a3,0xff` (reading now) — mine has `or a2,v1,v0` and then `andi v0,a1,0xff` (the arg1 & 0xff) — hmm, where's r & 0xFF?!

Mine[5] = `or a2,v1,v0` (now → a2), mine[6] = `andi v0,a1,0xff` — that's arg1 & 0xff. So mine's `r & 0xFF` was FOLDED (the lbu) ✓ (as I predicted). And mine has no `andi v0,a2,0xff` at all.

So the fold happened and the copy dissolved.

In 8003DF8C, the target's copies are of the PARAMETERS (arg0/arg1) — and the fold wasn't an issue there.

So for 800D0D7C I need BOTH:
1. the copy `r = now` to survive (so that `r & 0xFF` doesn't fold to the lbu), and
2. the copy `h = arg0` to survive.

For (1): the source `now` is a live pseudo (used later for `now & 0xFF00`) → cse propagates r → now?? Hmm, no: cse propagates the COPY's destination into the source's uses or vice versa. The merge means r and now share a pseudo.

Hmm, why doesn't the u16 width help here? Because the copy `r = now` (u16 dest) still gets merged by combine's copy propagation (combine works on the RTL: `(set (reg:HI r) (reg:SI now))` — hmm, combine might not merge across modes).

Hmm, but it did merge (the OR went directly into a2 — well, hmm, actually the OR result went into a2 = r's register. So r and now share the pseudo ✓ merged).

Hmm! Hmm, so combine merged them despite the mode difference? Hmm, or maybe the merge happened at the C level (gcc's expand assigned the expression's result directly to r's pseudo).

Hmm: `r = now;` where r is u16 and now is u32 → the RTL is `(set (reg:HI r_pseudo) (reg:SI now_pseudo))`? Hmm, but gcc might instead do `(set (reg:HI r_pseudo) (truncate (reg:SI now_pseudo)))` → and then combine folds the truncate into the source (since the upper bits of now are don't-care? no, now is u32 → the upper bits matter → the truncate is a real op `andi` ✗ hmm, but the OR went directly into a2 → so no andi).

Hmm, that means gcc decided r and now are the SAME pseudo (no truncation at all) — i.e. gcc's "cast" of a u32 to a u16 was optimized away because the value's upper bits are don't-care... hmm, for a u16 destination the truncation IS needed semantically (the value must fit in 16 bits) — but gcc 2.7's HImode convention says the upper bits are don't-care, so the "truncation" is free ✓ — the destination pseudo can just BE the source pseudo (with the upper bits garbage) ✓.

Hmm! But then the u16-ness doesn't create a separate pseudo → no opaque copy ✗.

Hmm, but in 8003DF8C, `i = arg0` with i as u16: the source arg0 is a hard reg (a0) — the copy into the HImode pseudo is a separate insn (the pseudo is HImode, the reg is 32-bit) → `move` ✓ and it escapes cse ✓.

Hmm! So the difference: in 8003DF8C the source is a HARD REG (the parameter) and the copy is into an HImode pseudo. In 800D0D7C the source is a pseudo (now) → the copy is pseudo→pseudo → merged.

Hmm, so for 800D0D7C's `r = now`: the source `now` must be a hard reg... hmm.

Hmm! What if `now` were not a variable at all, and the packed value were computed inline? Then `r = (D_80078EB0 | (D_80078EB1 << 8))` — hmm, the expression's result would be computed into a temp (a pseudo) and copied into r → hmm, the copy would be pseudo→pseudo ✗ merged. Hmm.

Hmm, but the copy's SOURCE would be the expression's temp — and the target has `now` (a3) used later for `now & 0xFF00` → so `now` must be a variable ✓.

Hmm. So `r = now` is a pseudo→pseudo copy. For it to survive, the HImode trick needs the SOURCE to be a hard reg.

Hmm! What if `now` were read twice from the globals? I.e.:
```c
r = D_80078EB0 | (D_80078EB1 << 8);      /* r = the packed value */
now = r;                                  /* now = a copy of r */
```
Hmm, then the roles swap: `now` (the copy) would be in the copy's reg and `r` the original. The target: a3 = the original (now), a2 = the copy (r). Hmm.

Hmm, what if:
```c
u16 r;   /* the copy */
u32 now;
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;      /* the HImode copy — but pseudo→pseudo ✗ */
```
Hmm.

Hmm, so what made 8003DF8C work? `i = arg0` — the source is the parameter's hard reg ✓.

Hmm! So for 800D0D7C, the `h = arg0` copy (arg0 = a parameter, a hard reg) with h as u16 should survive ✓ (like 8003DF8C's i/j)! And the `r = now` copy (pseudo→pseudo) would NOT survive ✗.

Hmm, so I need the r copy to survive differently.

Hmm! What if `now` is a u32 but the copy is made from a HARD REG? Hmm.

Hmm, what if the packed value were computed into a variable whose value is in a hard reg at that point? Hmm, gcc's local-alloc decides.

Hmm! Alternatively: what if `r` is u16 and `now` is ALSO u16? Then `r = now` is a pseudo→pseudo HImode copy → merged ✗.

Hmm.

Hmm, what about this: what if the copy's SOURCE is a hard reg because `now` is a "constant"? Hmm.

OK, let me think about the target's structure once more:
```
or a3,v1,v0     <- the packed value in a3
move a2,a3      <- the copy
```
Both a2 and a3 are caller-saved. So both the source and the copy are in caller-saved regs.

Hmm! And in the 8003DF8C target:
```
move s3,a0       <- the copy of arg0 into a3?? hmm, s3 is callee-saved
```
Hmm, the 8003DF8C target: `move s3,a0` (arg0 → s3) and `move s2,a1` (arg1 → s2) — hmm, s2/s3 are callee-saved! And the earlier diff showed `lw v1,0(a2)` vs `lw v1,0(t0)` — hmm.

Hmm, so in 8003DF8C the copies of arg0/arg1 went into callee-saved regs (s2/s3) — because i and j (the u16 copies) are live across calls → they need callee-saved regs ✓✓✓.

AH, that's the key difference! In 800D0D7C, `r` and `h` are NOT live across calls (no calls in that function!) → they can be in caller-saved regs ✓.

Hmm OK. So in 800D0D7C, the copies are r (a2) and h (t0) — both caller-saved.

Hmm, so how do I get the `r = now` copy to survive?

Hmm! The `h = arg0` copy: arg0 is a parameter (a hard reg a0) → with h as u16, the HImode copy from the hard reg survives cse ✓ (like 8003DF8C).

Hmm, but w05-w08 (h=u16) scored 17-22 — hmm, not better. Hmm, let me check w13 (r=u16, h=u16, with dead): score 18, 44 ins. Hmm, 44 ins (vs the target's 45) — closer in count!

Hmm, w15 (r=s16, h=u16): 46 ins, score 21. Hmm.

Hmm, let me look at the diff for w13 (r=u16, h=u16): maybe the copies partially survived.

Let me check. Also for the u16 h case: `h = arg0` with h u16 → the copy survives? And the uses of h: `(u32)h & 0xFF` → `andi v0,t0,0xff` ✓ and `h - v1` → h is u16 → promoted (zero-extended) → hmm, gcc 2.7's don't-care convention → `subu v0,t0,v1` ✓ (no extra insn).

Let me look at w13's diff.

Hmm, time is passing (~19:15). Let me be efficient: let me look at the diff of the best few variants (w12, w13, w14) in one call, then decide.

Actually, the diff output is long. Let me instead check the insn counts: the target is 45. w13 = 44 (r=u16,h=u16,with dead), w14 = 44 (r=u16,h=s16,without dead), w05 = 44 (r=s32? hmm).

Let me get the diffs for w13 and w14 in one call each. Hmm.

Let me just do w13.
