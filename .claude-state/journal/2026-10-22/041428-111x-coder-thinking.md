---
ts: 2026-10-22T10:14:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yOIOesKRQs3IzxzOABy8
---
All 4. The residual is stubborn: the a1 setup is sunk into the delay slot and the store is early.

Hmm. Let me think about the target's arm once more:
```
move a0,s1
addiu a1,s0,36
lui a2,0x0
addiu a2,a2,0
li v0,51
jal func_80128EA8
sb v0,39(a0)
```
Note "move a0,s1" — the q value (in s1) is copied to a0. Hmm, s1 = sub. And the store's base is a0.

Interesting: the store `sb v0,39(a0)` is in the delay slot, using a0. And "li v0,51" is before.

Ours:
```
move a0,s1
li v0,51
sb v0,39(a0)
lui a2,0x0
addiu a2,a2,0
jal func_80128EA8
addiu a1,s0,36
```
Hmm! Ours has the store BEFORE the a2 setup, and the a1 setup in the delay slot.

Both have the "move a0,s1" first.

So the scheduler put [li v0,51][sb] right after the move, and the a1 setup last.

In the target, the order is [move a0,s1][addiu a1][lui a2][addiu a2][li v0,51][jal][sb delay].

So the target's scheduling = the arg setup first, then the constant, then the call, with the store sunk.

In ours, the store (which is before the call in the source) is scheduled early and the a1 setup is sunk.

Hmm, what if the source order were: the store AFTER the call (x05 → 4) — then ours would be [move a0,s1][lui a2][addiu a2][jal][addiu a1 delay][li v0,51][sb]. That's v2's shape.

So in both cases the a1 setup ends up in the delay slot.

Why? Because the a1 setup is the LAST instruction before the call in the *scheduled* order — gcc's sched2 puts it there and reorg fills the delay slot with it.

To get the target's shape, the a1 setup must be scheduled EARLY (position 37) — before the a2 setup. Hmm.

What if the a1 setup were *forced* early by a dependency? E.g. if the store depended on it? no.

What if the value p were computed EARLIER in the source (before the `if`)? Then the addiu would be in the preheader ✗ (the asm would differ: the addiu would appear before the branch).

Hmm, but wait: would it? If p = ent + 0x24 is computed in the preheader, the addiu a1,s0,36 would be hoisted into the preheader — but the target has it in the arm ✗.

Hmm, what if p is computed in the *if* branch as well (both arms)? The addiu would be in the preheader ✗.

What if the p value is computed in the arm but the *call* is in a nested block? Hmm.

What about the "birth boost" mechanism: sched1 boosts instructions that are born late. The a1 setup is born at the call (its use) → it gets boosted... hmm, and the "li v0,51" (the store's constant) is also born at the store.

Hmm. What if the store were removed from the arm and moved elsewhere? no.

What if the store's value (0x33) were written to a *different* field such that the store's base is a0 but the value is loaded? no.

Honestly, this item's residual is the classic "the launder anchors the arg setup at the top of the arm" wall, and the notes already declared it a wall after 7 tries. I've done 14 more tries (plus the previous 7 = 21). I need 30 tries for a WALL.

Let me do one more batch of ~10 targeted tries for this item, then close it.

Batch ideas:
- The value p computed via a different expression: `p = (s32)(ent + 0x24);` (integer arithmetic, not pointer) — x12 did that → 4.
- `p = (s32)((u8 *)ent + 36);` (decimal)
- `p = (s32)(ent + 0x24);` with ent as u8*?
- The call with a0 = q explicitly: `func_80128EA8(q, p, e);` → maybe `func_80128EA8((s32)q, p, e);`
- The store before the func_8001CC3C call.
- The store value as `0x33` vs `(u8)0x33`.
- Move the whole else-arm content order: e.g. `func_8001CC3C(...)` last.
- The store using `q` vs a separate variable: `s32 qq = sub; ... ((Unkstruct_800B5CB8 *)qq)->unk27 = 0x33;` hmm, the pin is on q.
- Try removing the *pin* on q (but then the store's base changes) — v8 did that (5).
- Try `hw = 0x1C;` right after q = sub.
- Try making the call's first arg `sub` instead of q (q is a copy of sub): `func_80128EA8(sub, p, e);` — then a0 = sub (s1?) hmm, the target has "move a0,s1" so the first arg is a copy of s1 → q (in $4) ✓. If we passed sub directly, gcc would still copy to a0. But then q would only be used by the store → the store's base would be... hmm, q is pinned to $4 → the store's base a0 ✓ and the call's a0 = sub → also a0. Hmm! That might change things: then both the call's a0 and the store's base are a0 ✓ (no "move a0,s1" needed?). Hmm, the target HAS "move a0,s1" — so the first arg is copied from s1 (sub). With `func_80128EA8(sub, p, e)` the copy would also be "move a0,s1" ✓ and q (the pinned $4) would be... the pin forces q into $4, so the store's base is a0 ✓ and the call's arg would also be a0 = q? Hmm, gcc would use q for the call's first arg (same value) → the "move a0,s1" might disappear (if the call uses q directly, q is already $4 = a0 → no move!). Hmm, that changes the asm (the target HAS the move). Hmm, but the target's move a0,s1 suggests the call's first arg is NOT q but sub (copied to a0). Interesting!! So in the target, the call's first arg is a copy of sub, and the store's base is a0 (=q, the pinned $4).

So: `func_80128EA8(sub, p, e);` and the store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` where q = sub (pinned $4). Then: the call's a0 = a copy of sub (s1) → "move a0,s1" ✓, and the store's base = q = a0 ($4) → "sb v0,39(a0)" ✓✓.

In OUR source, the call is `func_80128EA8(q, p, e)` — the first arg is q ($4 = a0) → no move needed... but our asm HAS "move a0,s1"! Hmm, so ours also has the move. Because q is pinned to $4 and the call's first arg needs a0 — hmm, if q is in a0 already, no move. But our asm shows "move a0,s1" — so gcc copied s1→a0 (sub) rather than using q. Hmm, that's because the pin `register s32 q __asm__("$4")` — hmm.

Wait, in our v1 the call is `func_80128EA8(q, p, e)` — hmm, but our asm has "move a0,s1" — meaning the arg was sub (s1), not q. Hmm! Since q = sub and q is in $4 = a0, the call's first arg could be a0 directly. But gcc emitted "move a0,s1" — so gcc used a *different* value (sub in s1) for the first arg.

Hmm, that's odd. Unless the pin isn't actually taking effect for the call arg. Whatever — the target and ours agree on "move a0,s1".

Hmm, so maybe in the ORIGINAL source, the call's first arg was `sub` (not q)! And q was a separate pinned variable used only for the store. Let me test that variant: `func_80128EA8(sub, p, e);` with q used only for the store.

Hmm, but with q pinned to $4 = a0 and the call's first arg = sub (in s1) → "move a0,s1" ✓✓ — that MATCHES the target exactly! And the store's base = q = a0 ✓.

In our current source, the call's first arg is q — but gcc emitted "move a0,s1" anyway (maybe because the pinned q's value in $4 conflicts with the call's arg register assignment... hmm, the pin reserves $4 for q; the call's first arg also wants a0=$4 → conflict → gcc copies sub into a0 → "move a0,s1" and q stays in $4? but then q's value in $4 is the same as a0 → the store's base a0 ✓).

OK so both give the same. Fine.

Let me try the variant anyway: the call's first arg = sub.

Also: maybe the key is that in the target, the store's VALUE (0x33) is materialized before the call, and the store is sunk into the delay slot — that happens if the store is BEFORE the call in program order AND the scheduler decides to sink it (gcc's sched2 can sink a store past a call? NO — gcc never sinks a store past a call (it assumes the call may write memory). Hmm! So the store CANNOT be after the call unless gcc proved no aliasing.

Hmm! But the target HAS the store in the delay slot (after the call). So gcc did sink it — meaning gcc 2.7's alias analysis proved the call doesn't write *q (q points to a heap object; the callee could write anything...). Hmm, gcc 2.7's alias analysis (alias.c) can prove that a call doesn't alias a specific pointer if the pointer is known to point to a distinct object? With the "launder"/pinned q...

Hmm, interesting: the launder asm might have made gcc think q is "unknown" (a pinned register) → hmm, that would make aliasing MORE likely.

Hmm, wait. Actually: gcc 2.7's sched2 does NOT sink stores past calls. But the delay slot is filled by reorg with an instruction from BEFORE the branch — the delay slot instruction executes AFTER the call. So a store in the delay slot is effectively sunk past the call! That's legal only if the store doesn't alias the call's writes.

Hmm, so reorg chose the store for the delay slot → it must have judged it safe. Interesting.

So in the target, the store was scheduled right before the call and reorg moved it into the delay slot.

In ours (v1), the store is scheduled early (not adjacent to the call) and the a1 setup took the delay slot.

So the goal: get the store adjacent to the call (scheduled last before the call) and the a1 setup early.

Hmm! Since reorg picks the delay slot from the instructions *before* the branch, and the a1 setup was the last one before the call in ours...

What if the store were scheduled LAST before the call? In v1 the source order is [q=][p=][e=][store][call]. The scheduler put [move a0,s1][li v0,51][sb][lui a2][addiu a2][jal][addiu a1 delay].

Hmm, so the store was scheduled EARLY (right after the move) — before the a2 setup. Why? Because the store has no dependency on the a2 setup, and the scheduler (sched2) orders by... hmm, sched2 tries to place instructions to minimize the register pressure.

What if the store's base were q (a0) and the call's arg setup also uses a0 — the store must be after the a0 setup ✓ (it is).

Hmm, what if the store came after the call in the source (v2/x05) — then ours = [move a0,s1][lui a2][addiu a2][jal][addiu a1 delay][li v0,51][sb]: the store is after the call ✓ but the "li v0,51" is also after ✗ (the target has it before).

Hmm, so in the target the constant 0x33 is materialized before the call but the store is after. That's only possible if the store's value was computed early and the store was sunk — which requires the *source* order to have the store before the call, and the scheduler to sink it past the call (illegal) or reorg to move it into the delay slot (legal-ish).

In gcc, the delay-slot filling happens in reorg AFTER scheduling: reorg takes the last instruction before the branch and moves it into the delay slot. So the store must be the last instruction before the call in the scheduled order. In v1, the scheduled order before the call was [move a0,s1][li v0,51][sb][lui a2][addiu a2] — the last is "addiu a2,a2,0" (which can't go in the delay slot? it could) — hmm, but reorg chose "addiu a1,s0,36"?? That was in the delay slot, but "addiu a1" was scheduled... hmm, in v1 the "addiu a1,s0,36" appears in the delay slot — but where was it before? It must have been the last instruction before the call (scheduled after the a2 setup) → moved into the delay slot ✓.

So the scheduled order in v1 was: [move a0,s1][li v0,51][sb][lui a2][addiu a2][addiu a1,s0,36][jal]. And the delay slot took the addiu a1.

In the target: [move a0,s1][addiu a1,s0,36][lui a2][addiu a2][li v0,51][jal][sb delay] — the scheduled order before the call was [move a0,s1][addiu a1][lui a2][addiu a2][li v0,51] and the last (li v0,51) went into the delay slot?? But the delay slot holds "sb v0,39(a0)" — so the store was scheduled between "li v0,51" and the call, and the "li v0,51" stayed before.

So the target's scheduled order: ..., li v0,51, sb, jal.

So in the target, the store is the last before the call ✓ and the a1 setup is early.

The difference between the target and ours: the a1 setup's position (2nd vs last) and the store's position (last vs 3rd).

The scheduler's ordering of independent instructions is driven by the "birth" order and dependencies. The a1 setup (addiu a1,s0,36) is born at the call (it's the arg setup) → sched1's "birth boost" would push it LATE (it prefers to schedule instructions close to their uses?). Hmm, actually sched1 boosts instructions born late to reduce register pressure.

In the target, the a1 setup is early → so it was NOT born at the call; it was born earlier → meaning the value p was computed EARLIER in the target's source (e.g. before the store), and it was "live" from there.

Hmm! But in our source, p is assigned before the store too. Hmm, but the assignment `p = (s32)((u8 *)ent + 0x24);` is a statement whose value is used only by the call → gcc's sched can sink the computation.

Hmm, unless in the target's source, p's value was used by the STORE too? No, the store uses q.

Hmm! What if in the target's source, the call's args were computed in a way that made them "born" early — e.g. the launder asm (which is exactly the lever).

OK. Let me try one more class of moves: make p's value live across a *statement boundary* by using it in a way that has no code effect. E.g.:

```c
p = (s32)((u8 *)ent + 0x24);
if (p == 0) { }     /* no code, but p is used */
```
gcc folds `p == 0`? p is a constant-derived value; the comparison p == 0 → the front end folds it to false → no code, no use. Hmm.

What about using p in the store's *address*? e.g. no.

What about `p = (s32)((u8 *)ent + 0x24); q = sub;` — order variations tested.

What if p is computed via a *volatile*? no.

Hmm, what about the "keepalive" style: `p = p;`? identity → not allowed.

OK — let me consider the possibility that the a1 setup's early position comes from the *pin* on ent ($16): `addiu a1,s0,36` — the source is s0 (ent in $16 → hmm, $16 is s0!). So `addiu a1,s0,36` = ent + 0x24 where ent is in s0 ($16) ✓.

Hmm what if the *value* of the a1 arg were computed from a variable that's live earlier, e.g. `sub`? no.

Let me try: what if p is computed in the *if* branch too? no.

Let me try a few more variants quickly:
- the call's first arg = sub (not q)
- the call's first arg = q with a cast
- the store using q before the call (v1) but with the value written as `(u8)0x33`
- p assigned in the outer scope (before the if) — changes the asm but let's see
- e assigned as `(s32)D_801817B0` vs `&D_801817B0`?? hmm, D_801817B0 is a symbol (an int?).
- hw assignment moved into the arm's start.

Let me run one more batch and then close thisitem.
