---
ts: 2026-10-22T00:00:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_09vv89oIhNXgAREytPiW
---
So mine[36] = `move a0,s1` (matched with target[36]), then:
- target[37] = `addiu a1,s0,36` — mine[37] is something else (insert means the target has an extra insn here).
- mine[37] and mine[38] match target[38] and target[39] = `lui a2` and `addiu a2,a2,0`.
- target[40] = `li v0,51` — mine[39] is something else.
- mine[39] matches target[41] = `jal func_80128EA8`? Hmm, and mine[40] = `addiu a1,s0,36`, mine[41] = `li v0,51` are deleted, and target[42] = `sb v0,39(a0)` matched with mine[42].

So mine:
```
36 move a0,s1
37 lui a2,0x0
38 addiu a2,a2,0
39 jal func_80128EA8      (?)
40 addiu a1,s0,36
41 li v0,51
42 sb v0,39(a0)
```
Hmm, that's odd: the `addiu a1,s0,36` AFTER the jal? That can't be (it would be in the delay slot... hmm, the delay slot of the jal at 39 is insn 40 = `addiu a1,s0,36` ✓!!). So mine has the jal at 39 with the delay slot = `addiu a1,s0,36`, then `li v0,51` and `sb v0,39(a0)` after the call.

And the target:
```
36 move a0,s1
37 addiu a1,s0,36
38 lui a2,0x0
39 addiu a2,a2,0
40 li v0,51
41 jal func_80128EA8
42 sb v0,39(a0)     (delay slot)
```

So in the target, the `sb` is in the delay slot and the arg setup is before the call. In mine (v2), the `sb` is AFTER the call (since I put the store after the call in the source) and the `addiu a1` took the delay slot.

And in v1 (the store before the call in the source), mine was:
```
36 move a0,s1
37 li v0,51
38 sb v0,39(a0)
...
42 addiu a1,s0,36
```
Hmm, v1's diff was:
```
37 li v0,51 | addiu a1,s0,36
38 sb v0,39(a0) | --
insert mine[41:41] target[40:41] : li v0,51
42 addiu a1,s0,36 | sb v0,39(a0)
```
So v1's mine: 37: li v0,51; 38: sb; 39: lui a2; 40: addiu a2; 41: jal; 42: addiu a1,s0,36 (delay slot!). Hmm, so in v1 the delay slot was `addiu a1,s0,36` and the store was before the call.

The target wants: the arg setup (a0, a1, a2) before the call, the `li v0,51` before the call, and the `sb` in the delay slot.

So the target's execution order: move a0,s1; addiu a1,s0,36; lui a2; addiu a2; li v0,51; jal; sb (delay).

So the `sb` is LAST (in the delay slot) and the `li v0,51` is right before the jal. So the store is the LAST thing before the call → the source has the store after the call (as in v2) but the compiler didn't put it in the delay slot in v2 — instead it put `addiu a1,s0,36` in the delay slot.

Hmm. In v2, the `addiu a1,s0,36` (the 2nd arg) went into the delay slot, and the store went after the call. In the target, the store is in the delay slot and the args are all set before.

Hmm! So the target's delay slot = the store. The delay slot is chosen by the scheduler as the last instruction before the call. To get the store there, the store must be the LAST instruction scheduled before the call.

In the target: li v0,51 (insn 40) then jal (41) then sb (42, delay slot). So the `li` and the `sb` are adjacent, and the `sb` is in the delay slot.

Hmm, so the source order in the target's original was probably:
```
   ... args ...
   q->unk27 = 0x33;    /* the li + sb */
   func_80128EA8(q, p, e);
```
i.e. the store BEFORE the call (as in v1). But in v1, the scheduler put the `addiu a1,s0,36` in the delay slot instead of the `sb`, and the `li v0,51`/`sb` were scheduled before the arg setup.

Hmm, in v1 mine: 37: li v0,51; 38: sb; 39: lui a2; 40: addiu a2; 41: jal; 42: addiu a1 (delay slot).
Hmm, wait, that means in v1 the arg setup was incomplete at the call: a1 = s0+36 was set in the delay slot ✓ (legal) and a2 set before.

In the target, ALL the args are set before the call and the `sb` is in the delay slot.

So the difference: the target's delay slot holds the store, mine holds the arg setup.

Hmm! So the launder in the original def was what made the target's shape (the 3-output launder forces q, p, e into a0, a1, a2 — and being "already in the arg regs" they can't be moved into the delay slot, so the delay slot is free for the store!).

Without the launder, gcc has freedom: it put `addiu a1,s0,36` in the delay slot.

So I need the delay slot to be the store. How? The store `sb v0,39(a0)` must be the LAST insn before the call and the args must all be ready before.

In the source (v1: store before the call), the scheduler chose the arg setup for the delay slot. Hmm.

What if the store is placed after the args are set in the source? The source order:
```
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        func_80128EA8(q, p, e);     /* the call */
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;   /* after */
```
That's v2 → the delay slot got the arg setup. Hmm.

Hmm, so in both cases gcc puts the arg setup in the delay slot. The target has the STORE there.

Hmm! Maybe the difference is the arg `p = (s32)((u8 *)ent + 0x24)` = `ent + 36` → `addiu a1,s0,36`. In the target it's at 37 (before the call). In mine it's in the delay slot. To force it before the call, maybe the launder did that (the launder's "=r"(p) output is a hard reg, and gcc must materialize p into a reg before the asm → the `addiu a1,s0,36` hmm).

Hmm! Actually: with the launder, the 3 values q, p, e are tied to specific registers (the asm's outputs). The asm is a real instruction with a LUID, so the arg setup happens BEFORE the asm, and the asm (in the delay slot of the jal!) hmm — the launder asm is the delay-slot filler in the original! Because an asm has priority 1 (per §373) and gets scheduled into the delay slot... but the asm emits NO instructions, so the delay slot shows the next real insn.

Hmm! So in the original (with the launder), the delay slot of the jal was the ASM (zero bytes), and the visible insns around it are: `li v0,51` before the jal and `sb v0,39(a0)` after?? Hmm, no: the delay slot is ONE instruction. The target's insn 42 = `sb v0,39(a0)` is the delay slot of the jal at 41.

So in the original with the launder: the asm was the delay slot? But then the `sb` wouldn't be there. Hmm, the target's insn 42 is the `sb` — so the delay slot is the store, and the launder (in the original def) would be... hmm, the launder's asm has 3 outputs tied to q, p, e which are the call's args. So the asm would be scheduled right before the call, taking the delay slot? But the target's delay slot is the `sb`.

Hmm, so in the original (with the launder), the delay slot = the asm (zero bytes) → but the target shows `sb v0,39(a0)`. Hmm, so the asm's zero-width insn doesn't occupy the delay slot; the delay slot holds a real insn.

OK whatever. The question: how do I get the `sb` into the delay slot in a lever-free body?

Idea: the store must be the last instruction before the call, and the arg setup must be complete before it. The `li v0,51` is right before the store. So the order: ... args (a0,a1,a2) ... li v0,51; sb; jal.

So the source order should be: the call's args computed, then the store, then the call. In v1 the source was: q=..., p=..., e=..., store, call — and gcc scheduled: li, sb, lui a2, addiu a2, jal, addiu a1(delay). Hmm, gcc moved the `addiu a1` LAST (into the delay slot) and the store EARLIER.

Hmm, so gcc prefers to put the arg setup in the delay slot. To change that, the arg setup must be "not delay-slot eligible" — e.g., a 2-insn macro (per the def's comment in the other function: "a 2-insn macro is delay-slot-ineligible").

Hmm! What if the arg `p` were computed as a 2-insn expression? E.g. `p = (s32)((u8 *)ent + 0x24)` → `addiu a1,s0,36` (1 insn). Hmm.

Alternatively, what if the store's base/value is such that the store is a 2-insn sequence? no.

Hmm, what if the CALL is `func_80128EA8(q, p, e)` and one of the args is a 2-insn macro? Hmm, the target's args: a0 = s1 (move), a1 = s0+36 (addiu), a2 = &D_801817B0 (lui+addiu = 2 insns!).

Hmm! a2's materialization is 2 insns (lui+addiu) — and the target has them at 38-39 (both before the call). In mine (v1), the lui/addiu for a2 were at 39-40 (before the jal at 41) too. Hmm.

OK, so in v1 the difference is just WHICH insn goes in the delay slot: mine put `addiu a1,s0,36` there, the target put `sb v0,39(a0)`.

Why did gcc put the addiu in the delay slot? Because the delay slot is filled with the last scheduled insn before the call, and the scheduler had freedom. The target's original had the store there.

Hmm, per the ORDER class: "statement order IS the schedule among equal-priority insns (rank_for_schedule's LUID tie-break)".

So if the store's LUID were later than the arg setup's, the store would be scheduled later (into the delay slot). In v1, the store's source position is BEFORE the call (LUID before the call's arg setup?). Hmm, the arg setup (a1 = p) is derived from p's assignment which is before the store. So the LUID order: p=..., e=..., store, call-args. Hmm, the store's LUID should be AFTER p's → so the store should be scheduled after the addiu... but gcc put the addiu in the delay slot (i.e., LAST).

Hmm, delay slot filling: gcc's `reorg`/`sched2` picks the delay-slot insn. It's usually the last insn before the call in the final order.

In v1's mine: li, sb, lui a2, addiu a2, jal, addiu a1. So the `addiu a1` was moved INTO the delay slot, i.e., it was scheduled last (after the sb). Because the `addiu a1` has a lower LUID? Hmm, no: a1 = p = ent+36; p's LUID is early.

Hmm, maybe the addiu a1 was DELAYED because the scheduler wanted to minimize the live range.

OK, empirically: how do I get the store in the delay slot? Let me try moving the store to be the last statement before the call but ALSO ensure the args are ready. E.g.:

v3:
```
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        func_80128EA8(q, p, e);
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
```
= v2 (the store after the call) → the delay slot got the addiu.

v4: store before the call (= v1) → the delay slot got the addiu.

Hmm. Both give the addiu in the delay slot. Hmm, so what determines it?

In the target, the delay slot is the store. The store's LUID must be the highest among the call's insns.

Hmm, what if the store is written as the LAST statement in the block (after the call)? = v2 → the delay slot got the addiu. Hmm, but in v2 the store was after the call in the SOURCE, so the store's LUID is after the call's → the scheduler could move it into the delay slot (before the call) → but it didn't; instead the addiu went there and the store stayed after.

Hmm, gcc's reorg moves the delay-slot insn from the block AFTER the call into the delay slot (that's the classic "reorg delay slot" transformation: it moves an insn from the fall-through path into the delay slot). So the store (after the call in v2) should be a candidate for the delay slot... but reorg's choice is based on the priority/cost.

Hmm. In v2, the delay slot got `addiu a1,s0,36` — which in the source comes before the call (it's the arg setup). So reorg/sched chose the arg setup.

Hmm, why would the target choose the store? Because in the original (with the launder), the delay slot was taken by the ASM (the launder), and the visible insn there is... hmm! If the asm occupied the delay slot (zero-width), then the target's `sb v0,39(a0)` at insn 42 would be a NORMAL insn after the call. Hmm! But then the call's return address... the target's insn 41 = jal, 42 = sb (delay slot). If the asm were the delay slot, the sb would be at 43.

Hmm, so the target's delay slot = the sb. So the original's delay slot was the store, meaning the launder asm was NOT in the delay slot. Hmm, but the launder has 3 outputs tied to the call's args — the asm must come before the call (its outputs are the args). If the asm were immediately before the jal, it would be the natural delay-slot candidate. Hmm, but the target's insn 40 is `li v0,51` (not an asm, since asms are invisible) — so the asm could be at 40 (invisible) with the `li v0,51` also at 40? Hmm, an asm is a real insn occupying a slot; the delay slot holds ONE insn. If the asm were the delay slot, the `li v0,51` would be at 39 and the sb at 41.

The target: 38 lui a2, 39 addiu a2, 40 li v0,51, 41 jal, 42 sb. So the delay slot (42) = the sb. And the `li v0,51` at 40 is right before the jal. If the launder asm were between them, the `li v0,51` would have to be at 40 and the asm invisible at 40/41... Since the asm is invisible, the layout would show: 40 li v0,51, [asm invisible], 41 jal, 42 sb. The asm would be in the delay slot only if it were between 40 and 41 — but the delay slot is a specific slot. Hmm, the asm (if it's the delay-slot insn) would be at 42's position... but 42 shows the sb.

OK, so: in the original with the launder, the delay slot was probably the launder asm, and the `sb v0,39(a0)` was a normal insn right after the call. But the target shows the sb at 42 (the delay slot) — hmm, since the asm is invisible, the sb would appear at 42 if the asm is at 42?? No: the sb is a real insn; if the asm occupied the delay slot, the sb would be at 43 and the jal at 41 with the delay slot (42) invisible.

Hmm! Actually, the target's listing shows 42 insns for the delay slot: insn 41 = `jal`, insn 42 = `sb`. If the delay slot were an invisible asm, the listing would show the sb at 42 only if the asm is BEFORE the sb... The listing is a linear insn list, so an invisible asm would appear as a gap? The dump lists the actual instructions; the asm (zero bytes) would appear as... hmm, the dump shows `nop` for delay slots of branches. The `jal` at 41 with a delay slot at 42 = the sb.

So the delay slot is the sb. Then the launder asm is elsewhere (before the jal). And the `li v0,51` at 40 — hmm, the asm would be between 39 and 41 → at 40 (invisible). But then 40 shows `li v0,51`. Hmm, so the asm is at 40 and the li v0,51 is... ugh, the numbering.

OK, let me think about it as: the launder asm (3 outputs) must be scheduled before the call, and it has priority 1 (per §373: asm always has priority 1 = highest). So the asm is scheduled as early as possible?! Priority 1 means it's scheduled FIRST (highest priority). Hmm, §373 says "pri(asm) = 1, always" — in gcc's sched, priority 1 is the highest. So the asm is scheduled early (right after its inputs are ready: q, p, e).

So with the launder: q, p, e are computed, then the asm (invisible, priority 1 → scheduled early), then the call args (already in regs), then the store, then the jal.

Hmm, whatever. The point: without the launder, gcc's scheduling differs.

What I need: a lever-free C whose schedule puts the store in the delay slot and the arg setup before.

Options:
(a) Make the delay-slot-eligible insn the store by giving the arg setup a lower priority... e.g., by making the store's LUID later. Hmm.

(b) Use the C0505 "statement order" dial: move the store to a different position in the source.

Let me try a few positions:
v3: the store right after `e = ...` but with the call's args in a different order? Hmm.

v4:
```
        q = sub;
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
```
= v1 (store before the call).

Hmm, v1 and v2 both put the addiu in the delay slot.

Let me think about WHY. The delay slot insn must not conflict with the call. `addiu a1,s0,36` sets a1 = the 2nd arg — that's fine in a delay slot. `sb v0,39(a0)` stores — also fine.

gcc's reorg: "delay slot" filling picks an insn from the block after the call (the fall-through) or from before. Hmm.

Since both v1 and v2 give the same result, and the target differs, maybe the launder's effect is: the asm forced the args into regs EARLY (so the arg setup couldn't be moved), and the store was free to take the delay slot.

To mimic: make the arg setup happen EARLY (before the store) in the source, and the store LAST. Hmm, that's v2 (the store after the call). Hmm, but v2's delay slot = the addiu.

Hmm, in v2, the source order is: q, p, e, [call args: q, p, e], [store]. The compiler computes a0=q, a1=p+36, a2=e as late as possible (right before the call) — and the store (after the call in the source) can't be moved before the call (it would change semantics? no — actually the store to q->unk27 could be moved before the call only if there's no aliasing... gcc doesn't move stores across calls).

So in v2, the store stays after the call, and the delay slot is filled with the addiu.

In v1, the store is before the call in the source, but gcc scheduled it EARLY (li, sb at 37-38) and put the addiu in the delay slot.

So in both cases the delay slot = the addiu (the last arg setup).

For the target, the delay slot = the store. So the store must be scheduled LAST among the pre-call insns, and the args before it.

In v1, the store was scheduled EARLY (li v0,51; sb) — before the a2 materialization. Why? Because the store's LUID... hmm, the store is the last statement before the call in v1's source, so it should have the highest LUID among the pre-call insns → scheduled last. But it wasn't!

Hmm, unless gcc's scheduler (sched1/sched2) reordered because the store's insns (li, sb) are independent of the args.

Hmm, in v1's mine: 37 li v0,51; 38 sb; 39 lui a2; 40 addiu a2; 41 jal; 42 addiu a1. Hmm, and where's `move a0,s1`? At 36. So the a0 setup is at 36.

Hmm, so the order in mine: a0, li, sb, a2(lui+addiu), jal, a1(addiu, delay).

The target: a0, a1, a2(lui+addiu), li, jal, sb(delay).

Hmm! So the target's schedule: all the args, then the value load, then the call with the store in the delay slot.

In mine, the store (li+sb) is scheduled right after the a0 setup — EARLY. So gcc scheduled the store early (it's independent).

To make the store scheduled LATE (into the delay slot), its LUID must be higher than the args' LUIDs... it already is (the store is the last statement in v1). Hmm, but gcc scheduled it early anyway?!

Hmm, unless gcc's sched2 has a rule that a store can't be moved into a delay slot (it can, but with a cost), and the store was moved EARLY for another reason.

Hmm, let me look at the target's other branch (the first `if` arm) for comparison:
```
14 lui a3,0x5000
15 ori a3,a3,0x40
16 move a0,s1
17 addiu a1,s0,36
18 lui a2,0x0 ; D_800D3888
19 addiu a2,a2,0
20 li v0,156
21 sb v0,39(a0)
22 lw v0,4(a0)
23 li v1,16384
24 sh v1,26(a0)
25 sh v1,24(a0)
26 or v0,v0,a3
27 jal func_80128EA8
28 sw v0,4(a0)
```
Here the store `sb v0,39(a0)` is at 21, well before the call (27), and the call's args (a0,a1,a2) are at 16-19. And the delay slot (28) = `sw v0,4(a0)` (the last store).

In the source (first branch):
```
        func_8001CC3C(sub, (s32)D_800D387C, 0, 0);
        ((Unkstruct_800B5CB8 *)sub)->unk27 = 0x9C;      /* sb */
        ((Unkstruct_800B5CB8 *)sub)->unk1A = 0x4000;    /* sh */
        ((Unkstruct_800B5CB8 *)sub)->unk18 = 0x4000;    /* sh */
        CAST_WIDTH(s32, (u8 *)sub, 4) |= 0x50000040;    /* lw/or/sw */
        func_80128EA8(sub, (s32)((u8 *)ent + 0x24), (s32)D_800D3888);
```
So the `sw` (the |= store) is the last statement before the call → it lands in the delay slot ✓. And the `sb` (the first store) is scheduled early (insn 21) — because... hmm, interesting: in the target's first branch, the `sb` (the FIRST store) is at 21 (early) and the `sw` (the LAST store) is in the delay slot.

So in the first branch, the stores are scheduled in source order and the LAST one goes into the delay slot ✓. And the arg setup (a0,a1,a2 at 16-19) is BEFORE the stores (20-28) — even though the call's args are set up at the END of the source (the call is the last statement)!

Hmm!! So in the first branch, the arg setup is scheduled BEFORE the stores. That's because the args are set up early (gcc hoists the arg setup to the top of the block for the call — the "call setup" is scheduled at the top of the block to avoid the call-clobbered regs).

So gcc's pattern: the call's arg setup goes at the TOP of the block, then the block's statements, then the call with the last statement in the delay slot.

Now, in the else branch of the target: a0 (16: move a0,s1), a1 (17: addiu a1,s0,36), a2 (18-19), then `li v0,51` (40) and `sb` (42, delay). Hmm, so the arg setup is at the top ✓ and the store is the last statement → the delay slot ✓.

So in the else branch, the source order should be: [arg setup stuff] ... `li v0,51; sb` ... call. And the `sb` is the LAST statement before the call.

In v1 the source WAS: q=..., p=..., e=..., store, call — with the store last before the call. But gcc scheduled the store EARLY (insn 38) and the addiu a1 in the delay slot. ✗

Hmm! Why? Compare with the first branch where the last store went into the delay slot.

Difference: in the else branch, the arg `p = ent+0x24` is a pointer computed from `ent` (a pinned reg) → `addiu a1,s0,36`. In the first branch, the same `addiu a1,s0,36` appears at 17 (at the top) ✓. So in the else branch, gcc should also put the arg setup at the top: a0=move a0,s1 (16), a1=addiu a1,s0,36 (17), a2=lui/addiu (18-19) — that's exactly the target!

But in mine, the arg setup was split: a0 at 36, a2 at 39-40, and a1 in the delay slot. So gcc did NOT hoist the arg setup to the top in the else branch.

Why? Because of the ORDER of the statements? In the first branch, the arg setup is hoisted because... hmm.

In v1's source (else branch): q = sub; p = ...; e = ...; store; call. The args are q, p, e — the variables are assigned right before the call. gcc's arg setup: a0 = q, a1 = p, a2 = e.

In mine, `move a0,s1` (a0 = q = sub = s1) at 36, `addiu a1,s0,36` (a1 = p) in the delay slot, `lui a2/addiu` at 39-40.

So gcc put a1's setup LAST (in the delay slot) instead of at the top. The difference from the first branch: in the first branch, a1 = (s32)((u8 *)ent + 0x24) — the same expression! And it was at 17 (the top).

Hmm! So in the first branch gcc hoisted the whole arg setup to the top, but in the else branch it didn't. Why?

Maybe because in the else branch, `q` is PINNED to $4 ($a0)! `register s32 q __asm__("$4")` — the pin forces q into $a0. So a0 = q is a "copy" of a pinned reg... hmm, the pin means q lives in $4. So a0 = q = sub is free (no move needed)? But the target has `move a0,s1` at 16! So a0 = s1 (the value of sub) — a move from s1 to a0.

Hmm, so the pin didn't force q into $a0?! The pin says q is in $4. But the target has `move a0,s1` — so a0 (=q) = s1 → q's value is s1 → but the pin says q is in $4... Hmm, the pin is on the VARIABLE q, so q is allocated $4, and `move a0,s1` puts s1's value into a0=$4. So q = sub = s1 → the copy `move a0,s1` ✓. OK.

So in the else branch, the pinned q ($4) and the arg a0 = q — no extra move.

Hmm, and the `p` and `e` are unpinned locals.

OK. So the difference between the branches: in the first branch, the arg setup is at the top (16-19), in the else branch in mine it's split. What could cause that? The ORDER of the statements: in the first branch, the call is the LAST statement; in the else branch (v1), the call is also the last statement.

Hmm! Wait, in the FIRST branch of the target, the arg setup at 16-19 is BEFORE the stores (20-28). And gcc's "call setup at the top of the block" is a real gcc behavior (the call's arguments are set up early to avoid the "call clobbers" problem). Hmm.

But in mine's else branch, the arg setup is NOT at the top. Hmm, why? Because the `addiu a1,s0,36` was moved to the delay slot. Hmm, and `lui a2` was at 39.

Hmm, hmm. Let me look at the ORIGINAL def (with the launder) and see if IT scores 0 — yes, presumably. And the launder forces q, p, e into specific regs early, which forces the arg setup early.

So what makes gcc hoist the arg setup to the top of the block? Hmm, gcc's `expand` puts the call's arg setup right before the call, but the SCHEDULER (sched2) can move them earlier. In the first branch they moved to the top.

Hmm, the difference: in the else branch, the arg `p` is a VARIABLE (p) assigned before, while in the first branch the arg is an EXPRESSION `((u8 *)ent + 0x24)`. Hmm, in mine's else branch, the args are q, p, e — all variables.

So maybe: with the args as variables, gcc keeps the setup close to the call; with an expression, it hoists.

Hmm! Let me try: in the else branch, pass the EXPRESSIONS directly instead of the variables:
```
        func_80128EA8(sub, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
```
Hmm, but then the store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` uses q = sub. So q is still needed for the store. Let me write:

```
    } else {
        register s32 q __asm__("$4");
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(sub, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
        hw = 0x1C;
    }
```
Hmm, but the target has `move a0,s1` — so a0 = q (the pinned $4) = sub = s1 ✓ (the move). If I pass `sub` directly as a0, gcc would use a0 = s1 (no move) ✗. So I need to pass q.

Hmm. So: `func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);` — with a1 as an expression and a2 as an expression, a0 = q (pinned).

And the store: `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` before the call.

Let me try that (v3). The hope: the expression args get hoisted to the top of the block, and the store (the last statement) lands in the delay slot.

Hmm, but the store's LUID: the store comes before the call in the source, and the call's arg setup (the expressions) comes after → so the arg setup has a higher LUID → scheduled after the store → hmm, that would give the target's order? The target: args (16-19) then li (40) then sb (42).

Hmm, the `li v0,51` (the store's value) is at 40, right before the jal. So the store's value load is scheduled late, and the store itself is in the delay slot.

So the order: args (early), then the value load, then the call, with the store in the delay slot.

In the first branch (target): the arg setup is at 16-19 (early), then the `li v0,156` at 20 and `sb` at 21 (the first store's value+store), then the other stores, then the jal at 27 with the `sw` (the last store) in the delay slot.

So the pattern: the arg setup at the top, the statements in source order, the last statement in the delay slot.

In the else branch (target): the arg setup at 16-19, then the `li v0,51` at 40, the jal at 41, the sb at 42 (delay). So the store (the only statement) is last → the delay slot ✓.

So I need: the arg setup hoisted to the top of the block. In mine's else branch it wasn't. The difference vs. the first branch: the args are variables vs expressions.

Let me test v3 with expression args.

Note: I must keep `q` (pinned $4) as the first arg to get `move a0,s1`.

Hmm, wait: is `move a0,s1` really q? The target: 16 `move a0,s1` — a0 = s1. And s1 = the value of sub (lw s1,32(s0) at 6). And q = sub. So a0 = q = s1 ✓ (a move from s1 to a0).

If I pass `sub` directly (not q), gcc would set a0 = s1 directly (no move) since sub is already in s1 → `move a0,s1` wouldn't be needed. Hmm, but the pin on q forces q to be in $4 → so a0 = q requires a move ✓.

OK so: `func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);` — hmm, but the first arg q is a variable → gcc would set a0 = q... q is pinned to $4 = a0 → so a0 = q directly? But q's value = sub = s1 → the assignment `q = sub` becomes `move a0,s1` ✓ (the pin forces the copy into a0).

OK let me write v3:
```
    } else {
        register s32 q __asm__("$4");
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
        hw = 0x1C;
    }
```
Let me test.

Hmm, also I should consider: maybe the whole thing needs the FIRST branch to stay as is. Yes, keep it.

Let me write and score v3.
