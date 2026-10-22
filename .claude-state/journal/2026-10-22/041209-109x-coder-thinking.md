---
ts: 2026-10-22T10:12:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ynO7OkqVNKyytAreyBq1
---
Now I can see clearly:

TARGET else arm:
```
move a0,s1
addiu a1,s0,36
lui a2,0x0
addiu a2,a2,0
li v0,51
jal func_80128EA8
sb v0,39(a0)     ; delay slot
```
OURS (v2):
```
move a0,s1
lui a2,0x0
addiu a2,a2,0
jal func_80128EA8
addiu a1,s0,36   ; delay slot
li v0,51
sb v0,39(a0)
```
So in ours, the a1 setup is in the delay slot, the store comes after the call (as a separate block?), and the "li v0,51" is after the call.

Hmm interesting: in ours, "li v0,51" and "sb v0,39(a0)" are AFTER the jal (they're in the fall-through path of the delay slot?). Hmm, no: the delay slot executes after the call. So ours: jal; delay slot = addiu a1,s0,36; then li v0,51; sb v0,39(a0).

So in ours the store is after the call ✓ (source order) but the "li v0,51" is also after the call (the constant is materialized late).

In the target: the "li v0,51" is BEFORE the call and the store is in the delay slot.

So the target: the store's value (0x33) is materialized before the call, and the store itself is in the delay slot.

Ours (v2): the store's value is materialized after the call (the li v0,51 is after).

So the difference: the "li v0,51" position and the "addiu a1,s0,36" position.

Target order: [move a0,s1] [addiu a1,s0,36] [lui a2][addiu a2] [li v0,51] [jal] [sb delay]
Ours:         [move a0,s1] [lui a2][addiu a2] [jal] [addiu a1 delay] [li v0,51] [sb]

So in the target, everything is hoisted before the call; in ours, the a1 setup is sunk into the delay slot and the li v0,51 is after the call.

Interesting. The target's shape = "all the arg setup + the store's value at the top of the arm, the call, and the store in the delay slot".

This is the shape you get when the *store* is BEFORE the call in the source (so its value is materialized before the call) and the scheduler sinks the store into the delay slot (legal if the call doesn't alias).

That's v1! In v1: the source has the store before the call. Ours (v1): [move a0,s1] [li v0,51] [sb v0,39(a0)] [lui a2][addiu a2] [jal] [addiu a1 delay].

Hmm, so in v1 the store stayed before the call (not sunk into the delay slot) and the li v0,51 is before it ✓ (matching the target's li position relative to the store). But the a1 setup went to the delay slot in v1 too.

Hmm, so:
- v1: store before the call in the asm; li v0,51 before the store ✓; a1 in the delay slot ✗.
- v2: store after the call; li v0,51 after the call ✗; a1 in the delay slot ✗.

The target: store in the delay slot (i.e. after the call); li v0,51 before the call; a1 at the top.

So we need: the store's value materialized before the call, the store itself sunk into the delay slot, and the a1 setup at the top.

Hmm! What if the source order is: store BEFORE the call (so "li v0,51" is before the call ✓), and the scheduler sinks the store into the delay slot? In v1 the store stayed before the call. Why? Because the delay slot was taken by the a1 setup (which is a candidate too). If the a1 setup were NOT delay-slot-eligible (e.g. because it must come before the call's a1 use... hmm, it IS the a1 setup).

Hmm, the delay slot of a jal can hold any instruction that doesn't conflict with the call's register usage. The a1 setup (addiu a1,s0,36) sets a1 = the second arg — that's fine in the delay slot (it's set before the call executes). But gcc's reorg fills the delay slot with the LAST instruction before the branch — and here it chose "addiu a1,s0,36" (which in v1 was scheduled last before the call).

In the target, the delay slot holds the STORE. So in the target, the last instruction before the call was the store.

So: in the target, the store was scheduled right before the call (after the arg setup) and then sunk into the delay slot.

So the source order should be: [arg values ready] [store] [call]? Hmm, but the store is to q->unk27 and the call is func_80128EA8(q, p, e) — if the store is before the call in program order, the value 0x33 is materialized before the call ✓ and the store itself is right before the call → the delay slot ✓.

But in v1 (store before the call in the source), ours produced: [li v0,51][sb] then [lui a2][addiu a2][jal][addiu a1 delay]. Hmm, the store was NOT adjacent to the call: the a2 setup came after the store, and the a1 setup went into the delay slot.

So the scheduler ordered: a0, li v0, sb, a2, jal, a1(delay). Weird. The store was scheduled before the a2 setup.

To get the target's order, the store must be scheduled after the a2 setup (i.e. just before the call).

Hmm, what if the store's base is not q but a0 (pinned)? In the target the store's base IS a0 (q pinned to $4). Hmm, in v1 our store's base is also a0 ✓.

So the difference is purely the scheduler's choice.

What might make the scheduler place the store later? The store depends on the value 0x33 (a constant) and on a0 (=q). If the store were "later" in the dependency chain...

Hmm, what if the store's VALUE were a variable (e.g. a temp set earlier)? E.g.:
```c
s32 t = 0x33;
((Unkstruct_800B5CB8 *)q)->unk27 = t;
```
Then the "li v0,51" would be earlier (before the call) and the store's base a0... but the temp t would live across the call → a callee-saved reg → "li s3,51" ✗ (different asm).

Hmm. What if the value 0x33 is written as `0x33` but the store is `*(u8 *)((u8 *)q + 0x27) = 0x33;`? Same.

Hmm, what about the ORDER of the call args? The target: a0=q (move a0,s1), a1=ent+0x24, a2=D_801817B0.

In our source: `func_80128EA8(q, p, e);` — the args are q (a0), p (a1), e (a2) ✓.

Hmm, what if we spelled the args as expressions (no p/e variables): `func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);` — the notes' v3 tried that → 4.

Hmm.

Let me think about the scheduler. sched2 (the final scheduling) orders the block. The target's order suggests the store was scheduled last before the call. In ours, the a1 setup was last.

The scheduler's choice depends on the "birth boost" of instructions: instructions that are born late (like the constant materialization) get boosted.

Hmm, what if the store came AFTER the call in program order (v2) but the value 0x33 was materialized before the call? That would happen if the constant's materialization is independent of the call and gets hoisted. In v2, ours has "li v0,51" AFTER the call — so no.

What if the store's value were computed from something that requires the call's args? no.

Hmm. What if we use `q` (the store's base) differently: e.g. the store could be `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` — the base q = a0. Since a0 is the call's first arg, the store must not clobber a0 before the call → the store is AFTER the call in the target (delay slot) ✓ legal.

So in the target, the store was moved after the call by the scheduler (it's a "sink"). In v1 (store before the call in the source), the scheduler kept it before (it can, since the source order is before) — but the target's has it after.

Hmm, so the target's source likely had the store BEFORE the call, and the scheduler SANK it into the delay slot. That requires the scheduler to prefer the store as the delay-slot filler and to place it after the arg setup.

In v1, ours placed the a1 setup in the delay slot. Why is the a1 setup a delay-slot candidate in ours but not in the target? Because in the target, the a1 setup was scheduled EARLY (at the top of the arm) — so it wasn't available at the delay slot.

So the root cause is the same: the a1 setup is sunk in ours. Everything else follows.

So: how do we get the a1 setup (ent+0x24) computed early, at the top of the arm?

The value p = ent + 0x24 is used only by the call. The scheduler sinks the computation to just before the call (or into the delay slot).

To force it early, the value must have another use earlier, or be "live" earlier.

Hmm! What if p is computed BEFORE the `if` (in the preheader)? Then the addiu would be in the preheader ✗ (different asm).

What if p is computed at the top of the else arm but the *call* is in a nested block? Hmm.

What if the a1 argument is not a computed pointer but a *value already in a register*? E.g. if `ent + 0x24` were... hmm, the target computes it with addiu a1,s0,36 — so it's computed in the arm.

Hmm, what if the p value is computed in the *if* branch too (i.e. both arms compute it)? Then it'd be in the preheader ✗.

What if there are TWO uses of p: the call arg and something else in the arm? E.g. if p were also stored somewhere → extra insns ✗.

Hmm, what if the *call* is written with the argument expression `ent + 0x24` inline (v3) — then the addiu is part of the arg setup, which the scheduler might treat differently! The notes tried v3 → 4. Hmm.

Let me look at v3's diff to see where it lands. And v4.

Let me run the diff forv3 and v4.
