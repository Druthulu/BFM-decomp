---
ts: 2026-10-22T00:23:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IxQWHOtac793IQplKVGg
---
candA = same 13 — the reorder didn't produce the copy. So gcc still coalesces v1 = mode.

Hmm: with the store after the copy, mode is live at the copy point. But gcc's cse "make_regs_eqv" can still merge mode and v1 if it can prove they're equal (the copy v1 = mode with mode live → cse would replace v1's uses with mode's reg!). Yes — cse's copy propagation: v1 = mode (a copy), and mode is live → cse propagates mode into v1 (the copy is removed, v1's uses read mode's reg). That's the "cse-copy-merge" wall tag!

So the copy is merged by cse because the two are provably equal. The launder defeats cse (the asm is opaque).

Hmm! So how do we get a real copy in plain C? We need two values that are equal but cse can't prove... impossible in C (cse uses value numbering: mode and v1 have the same VN → merged).

Unless the copy is a *different* operation: e.g. `v1 = mode` where mode is u16 and v1 is s32? A widening copy — cse can still merge it (a zero/sign extension is a known pattern). Hmm.

What if the two values are related by a *mask* that gcc keeps as a separate op? E.g. the target's move v1,v0 is a plain register move.

Hmm. So the v1 launder's effect = a real copy instruction. In plain C, a copy that cse can't merge...

What about a copy of a *volatile* read? E.g. `v1 = mode;` where mode is volatile → the load is volatile and the copy is a real move! But the mode computation isn't volatile in the target.

Hmm, what if v1 is assigned from a *different but equal* expression? E.g. `v1 = mode;` → `v1 = (s32)(u16)(mode & 3);`? The value is the same but the expression is different → cse's value numbering: mode = x & 3 (VN: and(x,3)); v1 = (s32)(u16)(mode & 3) → VN: and(and(x,3),3) — hmm, cse would simplify and(and(x,3),3) = and(x,3) → same VN → merged.

Hmm.

What about making the copy *necessary* by using a different width: e.g. `v1 = (s16)mode;`? Then v1 = sign-extended(mode) — the target's move is a plain move, and the values are equal only if mode fits in s16 (mode is 0-3 ✓). But cse's VN: (s16)(and(x,3)) vs and(x,3) — different VNs (different types) → NOT merged! But would gcc emit the extension? Since mode ∈ [0,3], the extension is a no-op → gcc's fold would drop it (the value range is known) → the copy would be merged again.

Hmm.

What about the ORDER: `mode` is used by the store (sh v0,254(s0)) and v1 by the comparisons. The target's copy is v1 = v0 — a plain move. gcc emits a move when two different pseudos hold the same value and can't be coalesced. Regalloc coalesces them if possible, but the target has them in different registers (v0 and v1) — so the copy was NOT coalesced by regalloc either! Because the copy is a "pseudo copy" that gcc's regalloc usually coalesces (move-related) → it would merge v1 and mode into one register. But the target has them separate (v0 and v1)!

Hmm, so the target's move v1,v0 is a *real* register-to-register move that regalloc didn't coalesce. That happens when the copy is a "hard" copy — e.g. when the source is a hard register or when the pseudo has a fixed register.

Hmm, notice: the target's `move v1,v0` — v0 and v1 are both temps. If the copy were a normal pseudo copy, regalloc would coalesce (both would be in the same reg). So the copy must have been forced.

Hmm, but wait: the launder's asm output was tied to v1 — gcc's regalloc can't coalesce a tied pair. So the asm forces v1 into a separate register from mode's reg.

So without the asm, we can't get that copy: any copy would be coalesced.

Hmm, but the constraint: "MATCH = the kinds in <dir>/kinds gone" — the launder must go. If the copy can't be reproduced, this item is a WALL (cse-copy-merge).

Hmm, but hold on. Maybe there's a way: what if the copy is *not* a copy of the same value but the source has TWO separate computations of the same value, e.g.:

```
s32 mode = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;
...
v1 = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;   /* recomputed */
```
Then the two computations are CSE'd (same expression) → merged. Unless one is volatile.

Hmm. What if the store uses a DIFFERENT expression that's equal but not CSE-able, e.g. via a union/pointer alias? E.g.:
```
v1 = (s32)(u16)*(u16 *)((u8 *)s0 + 0x70) & 3;    /* the same load, but through a different expression */
```
CSE would merge the two loads (same address) and the ands.

What if the second one goes through a `volatile` pointer? That adds a different load (extra insn).

Hmm.

OK, so item 3 might be a WALL (cse-copy-merge). But let me first check the e launder's part, and consider whether the v1 copy could be produced another way.

Hmm, wait. Actually, let me reconsider. What if the copy could be produced by an *in-place compound assignment*? Like the `&=` trick: `v1 = mode; v1 &= 3;`? Hmm, that would be a real op (andi) — but the target has a MOVE, not an andi. The score counts instruction mismatches → an extra andi would break it.

Hmm, what about `v1 = mode;` where mode is declared as a different type, e.g. `u16 mode` and `s32 v1`? Then the copy is a zero-extension (andi) — no.

So the target's `move v1,v0` must come from the launder. → the v1 launder is load-bearing → WALL?

Hmm, but hold on! Let me reconsider: maybe the v1 copy is not needed if the *whole* structure changes. E.g. what if v1 is not a copy of mode but the comparisons use a different variable? The target's code:
```
13 andi v0,v0,0x3     ; mode = x & 3
14 move v1,v0
15 sh v0,254(s0)      ; store mode
```
Then later the comparisons use v1 (mode's copy) — e.g. "if (v1 == 1)".

What if the source computed the comparison values differently, e.g. `if (mode == 1) goto case1;`? Then no copy is needed at all! The target's copy exists because the original source had something like:

```
v1 = mode;    /* a copy the game code made */
```
Hmm, in the original game source, maybe:
```
mode = x & 3;
unkFE = mode;
v1 = mode;
if (v1 == 1) ...
```
The original compiler (not gcc) kept the copy as a real move.

For us: gcc merges it. To keep it, we need... hmm.

What if we make the copy *not* a copy: e.g. `v1 = mode;` where mode is `volatile`? Then the store `unkFE = mode` and `v1 = mode` would each do a volatile load → 2 loads → extra insns.

Hmm, what if `mode` is declared volatile but the *load* is hoisted... no, volatile forbids that.

What if the comparison uses a value that's provably equal but from a different source: e.g. `if (v1 == 1)` where `v1 = mode` and mode is a *const* expression? no.

OK: I think the v1 part is a WALL (cse-copy-merge). But wait — the row's "kinds" = launder. A PARTIAL result is allowed: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". Hmm, PARTIAL means: the win.c scores 0 while keeping some of the row's levers (e.g. keeping the launder but removing... hmm).

Actually PARTIAL:<kinds still kept> means: the body still has some of the row kinds (e.g. launder) but scores 0. Hmm, that's for when only SOME of the levers can be removed. In our case: if I can remove the e launder but not the v1 launder, then the result would be PARTIAL:launder (win.c scores 0 with the v1 launder kept). But the baseline already scores 0 with both launders! So PARTIAL would require removing at least one.

Hmm, that's a valid outcome: PARTIAL:launder with the e launder removed and the v1 launder kept, scoring 0. That's progress (one fewer launder). The brief: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So the row kind "launder" is still kept (the v1 one) → PARTIAL:launder.

Let me aim for that: remove the e launder (and maybe the v1 one) and score 0. If only the e launder can go → PARTIAL:launder with 1 try.

Let me test candB (candA + e launder removed) — but candA also had the reorder which didn't help. Let me make candC = base.c with ONLY the e launder removed (keeping the v1 launder) → does it score 0? If yes → PARTIAL:launder (the v1 launder remains).

Let me score candB first (it has both the reorder and the e launder removed, v1 launder already removed in base) — hmm, base.c already removed BOTH launders. So candB = base + reorder (e launder already gone). Let me instead build candC from orig.c: remove only the e launder.

Let me do that: sed -z on orig.c: remove the e launder line only.

And also candD: from orig.c, remove the v1 launder only (keep e's) → score?

These two tell me which launder is load-bearing.

Let me run them.
