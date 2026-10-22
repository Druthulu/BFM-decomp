---
ts: 2026-10-22T00:38:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_c2NsugGP23mrtQKMipge
---
Key differences for item 5:
1. Frame size: mine 24 vs target 32 (the `pad` local's 8 bytes missing — the target reserves 32, mine 24).
2. Register: the target uses v0 where mine uses v1 for the value (because in the target, the asm forced v0's value to be "opaque" and the allocator chose v0 for it; in mine, GCC chose v1).

So the lever does two things: the frame pad (8 bytes) and the register choice (v0 vs v1).

Plain-C ways:
(a) The frame: make `pad` occupy 8 bytes of stack. E.g. `s32 pad[2];` with a real use? Or `s32 pad;` + `pad = v0;`? A dead store to a local doesn't allocate stack space (GCC removes it). Hmm, but if the store is *not* dead (e.g. pad is read later or its address is taken and used)...

How about: `s32 pad;` and use it in a real way that doesn't change the semantics: e.g. `pad = v0; ... v0 = pad;`? Hmm, that's a launder (identity).

Hmm. What about making the frame bigger with a *real* local that's used? The target's frame is 32 bytes; mine is 24. The difference is 8 bytes = one s32 pad? Hmm, `s32 pad;` = 4 bytes; the frame difference is 8. Hmm, maybe the target's frame includes pad (4) + alignment (4)?

Let me look at the target's full asm to see the frame and the stack usage.

(b) The register: v0 vs v1 for the value. In the target, the value v0 is in v0 and the *copy* v1 = v0 is in v1 (the target has `move v1,v0` at 24! and `slti v0,v0,3`). So the target: v0 holds the value, v1 = a copy (for the else branch: `addiu v0,v1,-2`).

In mine: v1 holds the value and there's no copy.

So the target's structure: the value is in v0, and the else-branch uses a *copy* in v1. In mine, the value is in v1 and the else branch uses it directly.

The asm's effect: v0 is "opaque" (the asm redefines it) → the allocator keeps the *original* v0 value in v0 (can't coalesce) and makes a copy in v1.

Hmm! So the asm forces a *copy* of the value. In plain C, the copy exists in the source: `v1 = v0;` — the source has:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    __asm__(...);
    if (v0 < 3) { ... } else { v0 = v1 - 2; ... }
}
```
So v1 = v0 is a real copy in the source! With the asm, GCC can't coalesce v0 and v1 (because the asm redefines v0, so v0's value at the asm differs from v1's copy) → they get different regs. Without the asm, GCC coalesces (v1 = v0 → the same reg) → v1 is used and the value is in v1.

So the plain-C fix for the register part: make the copy *real* — i.e. ensure v0 and v1 don't get coalesced. Coalescing is blocked if the two values differ (e.g. v0 is redefined after the copy). Hmm: in the source, after `v1 = v0`, v0 is *not* redefined before `if (v0 < 3)`. So they're the same value → coalesced.

In the target: `lh v0,252(s0)` (v0 = the value), `move v1,v0` (the copy), `slti v0,v0,3` (the test on v0). So the target has both v0 and v1 holding the same value — the copy is real (not coalesced) because the asm intervened.

Plain C: to prevent the coalescing, v0 must be *redefined* between the copy and the use. E.g. if the asm were replaced by a real redefinition of v0... e.g. `v0 = v0;`? identity (forbidden) and folded.

Hmm! But what if the *source* is restructured so that v0 is naturally redefined? Look at the target's code after the test:
```
if (v0 < 3) {
    v0 = *(s16 *)(unk20 + 0x12);
    v0 = (v0 + 2) & 0x3FF;
    if (v0 < 4) { unkFC = 0; }
} else {
    v0 = v1 - 2;
    unkFC = v0;
}
```
In the *if* branch, v0 is redefined (twice). In the *else* branch, v0 = v1 - 2 (using the copy).

So the copy v1 is needed in the else branch because v0 is redefined in the if branch. But GCC's coalescing happens at the RTL level: v1 = v0 (a copy) and then v0 is redefined in one branch → the copy can't be coalesced *if* the copy is live across the redefinition. In the target, the copy is made *before* the test (v1 = v0 at 24), and the if-branch redefines v0 → so v1 must keep the old value → they can't share a reg → the copy is real.

But in my c1, GCC *did* coalesce: it used v1 for the value and the else branch did `addiu v1,v1,-2` (no copy). So GCC optimized the copy away: since the copy v1 = v0 is only used in the else branch (where v0 is redefined), GCC could just use v0's value directly (v0 = v0 - 2). Hmm, but that changes the *order*: in the target, the else branch computes v1 - 2 where v1 is the *old* value; in mine, v0 - 2 where v0 is the old value too (in the else branch v0 isn't redefined before). Same semantics.

So GCC's copy propagation removed the copy — the classic "combine/copy propagation" (cse make_regs_eqv) merged v1 and v0 since they're equivalent.

To prevent that, the copy must be made *unmergeable*: e.g. if between the copy and the use, v0 is redefined in a way that... hmm, in the else branch v0 is redefined *after* the use.

What if the *order* of the statements changes: e.g.
```
v1 = v0;
if (v0 < 3) { ... } else { v0 = v1 - 2; ... }
```
The else branch's use of v1 is *after* the if-branch's redefinition of v0 — so the two values differ on the paths → the copy must be preserved! But GCC's cse merged them anyway (it did: mine has no copy).

Hmm, GCC's cse make_regs_eqv: v1 and v0 are equivalent (v1 = v0 with no intervening redefinition on the *common* path). The if-branch redefinition of v0 happens on a different path, so at the join point they're equivalent → merged. But the *use* of v1 in the else branch happens *before* the join → hmm, in the else branch, v0 is not yet redefined, so v0 and v1 are equivalent there → GCC rewrites the use of v1 to v0 → the copy is dead → removed.

So the copy is removable because the else branch uses it *before* v0 is redefined.

To make the copy non-removable, the else branch must use v1 *after* v0 is redefined. E.g. restructure:
```
v1 = v0;
if (v0 < 3) {
    v0 = ...;
    ...
} else {
    v0 = v1 - 2;   /* uses v1 (old) */
    unkFC = v0;
}
```
Hmm, in the else branch, v0 = v1 - 2 — the use of v1 is *before* the redefinition of v0. So it's removable.

What if the source were:
```
v1 = v0;
if (v0 < 3) { ... } else { v0 = v1; v0 = v0 - 2; }  /* hmm */
```
no.

What if the *order* were:
```
v1 = v0;
if (v0 < 3) {
    v0 = *(s16 *)(...);
    v0 = (v0 + 2) & 0x3FF;
    if (v0 < 4) { unkFC = 0; }
} else {
    v0 = v1 - 2;
    unkFC = v0;
}
```
That IS the current source. And GCC removed the copy.

So how did the *original game code* look? The target asm has the copy (move v1,v0) — the original source must have had a *real* difference between v0 and v1 at that point.

Hmm, what if the original had the *order*:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;      /* copy */
    if (v0 < 3) { ... } else { v0 = v1 - 2; ... }
}
```
Same as now. And the original compiler (or this one) kept the copy because of the asm.

So the asm's role here = prevent the copy coalescing. A plain-C way to prevent coalescing: make the copy *necessary*, i.e. v0 must be redefined *before* the copy's use in a way that differs.

Hmm! What if the *if* branch's redefinition of v0 were *hoisted* before the test? E.g.:

```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    v0 = v0 + 0;     /* no */
```

Hmm.

What if the *test* used v1 instead of v0? I.e. swap the roles:
```
v0 = CAST_SIGN(s16, a0, 0xFC);
if (v0 != 0) {
    v1 = v0;
    if (v1 < 3) {
        v0 = *(s16 *)(...);      /* redefine v0 */
        v0 = (v0 + 2) & 0x3FF;
        ...
    } else {
        v0 = v1 - 2;
        ...
    }
}
```
Now: v1 = v0 (copy), the test uses v1, and the if-branch redefines v0. So at the test point, v0 and v1 are equivalent → the test on v1 could be rewritten to use v0 → merged again. Hmm, but the *else* branch uses v1 (the old value) and redefines v0 → same as before.

Hmm, the copy is only removable if the *uses* of v1 can be rewritten to v0. In the else branch, v0 is redefined *by* the use (v0 = v1 - 2) → the use of v1 is fine to rewrite to v0 (v0 = v0 - 2). So it's removable.

To make it non-removable, the else branch must use v1 *after* v0 has been redefined. E.g.:

```
} else {
    v0 = v1 - 2;      /* v0 redefined */
    unkFC = v0;       /* uses v0 */
}
```
Hmm, the use of v1 is before the redefinition.

What if:
```
} else {
    unkFC = v1 - 2;   /* use v1 directly, no v0 redefinition */
}
```
Then v0 is not redefined in the else branch at all → the copy is still removable (v1 → v0).

Hmm, so the copy's purpose in the original: the *else* branch computes v0 = v1 - 2 where v1 is the pre-test value. Since v0 == v1 there, the copy is semantically redundant — the compiler removed it. In the target, the asm prevented the removal.

So this is the same class as item 1: the lever prevents an optimization that a plain-C rewrite would allow. The only plain-C way to prevent it: make the two values genuinely different (but the semantics must stay) — impossible — OR make the copy *not* a copy but a real 2nd set.

Hmm! "Real 2nd set": what if v1 = v0 is replaced by a *genuine* second computation of the same value? E.g. `v1 = CAST_SIGN(s16, a0, 0xFC);` (recompute the load!). Then v1 and v0 are two separate loads of the same memory location. CSE would fold the second load into the first (same address, no intervening store) → merged. Hmm, but with the "m"(pad) memory input in the asm, the asm *clobbers* memory (it has a memory input but no clobber... hmm, "m"(pad) is an input, not a clobber, so the asm doesn't invalidate memory).

Hmm! But wait: in the target, the load `lh v0,252(s0)` happens ONCE (the value is loaded once into v0 and copied to v1). So the original didn't reload.

OK, so for item 5, the two differences are: (a) the frame (8 bytes: the `pad` local), (b) the v0/v1 copy.

For (a): the frame. How to reserve 8 bytes in plain C? A local array or a local whose address is taken. E.g. `s32 pad[2];` — but if unused, GCC won't allocate it. To force the allocation, the address must be taken *and used* in a way that survives... e.g. `pad[0] = 0;` (a dead store — removed).

Hmm! What if the *frame* difference isn't about `pad` but about something else? Let me look at the target's frame usage: the target's frame is 32 bytes, mine 24. The function's locals: v0, v1, pad (4 bytes each = 12 → 16 with alignment). Hmm, mine's frame is 24 and the target's is 32.

Let me look at the target's asm to see the stack usage (does it store anything at sp+0..?).

Let me dump the target asm for this item.
