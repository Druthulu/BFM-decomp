---
ts: 2026-11-06T15:46:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GwMXXRr1QmGUliuHYonI
---
Clear: mine emits `move a0,s0` for both calls (the address `mb+0x18` is held in s0 and moved to a0); target emits `addiu a0,s0,24` for both — the +0x18 add is re-derived at each call site.

So the target has the base &D_800AF630 in s0 and does `addiu a0,s0,0x18` at each call. Mine has `move a0,s0` — meaning `mb + 0x18` was folded into the pointer (the launder's absence lets cse/combine fold the +24 into the base? no...).

Hmm, mine: `move a0,s0` — a0 = s0 = mb+0x18? Let me look at the surrounding asm.

Actually the fix should make the +0x18 re-derived as an addiu off the base reg. The launder made mb opaque, so `mb + 0x18` is computed twice (addiu each time), and the base (mb = &D_800AF630) lives in s0.

With plain C, cse knows mb == &D_800AF630 + 0, so `mb + 0x18` is a constant address `&D_800AF630 + 0x18`; it materializes that into a register and does `move a0,s0`.

Wait, mine has `move a0,s0` for BOTH calls — meaning s0 holds mb+0x18. Hmm.

The target: `addiu a0,s0,24` — s0 holds the base.

The launder's effect: after the launder, mb is unknown, so `mb + 0x18` can't be folded to a constant; it's computed as `addiu a0, mb_reg, 0x18`. And the *first* call also does `addiu a0,s0,24`. So both calls do addiu off s0 (the base).

So the fix: make `mb + 0x18` not fold into a constant address, without the asm.

The §373 dead-reset: after the first call, `mb = 0;` — this makes cse forget mb's constant value. Then the second `mb + 0x18`... but mb is 0 → wrong. Unless we use a fresh variable for the second call:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
mb2 = (u8 *)&D_800AF630;
func_800491AC(mb2 + 0x18);
```
Hmm, mb2 = the same constant; cse would fold mb2's constant value again. The dead-reset only helps if the second expression uses a variable whose constant value is NOT known.

Alternative approach: make mb a *computed* value cse can't fold, e.g. `mb = (u8 *)&D_800AF630;` then `mb += 0;`? folds.

Hmm, what does the target's first call do? Let me look at the target asm around those sites.
