---
ts: 2026-11-06T16:38:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lV1ZVsR6Hny0LxyDs2MO
---
In the pinned original: only 1 global pseudo (73 = self), assigned a1. Everything else is block-local: 75 in 4 (a0 = mask? it's the mask pseudo, block-local to block1), 76 in 2 (v0 = f pinned), 79 in 3 (v1 = p), 82/83 in v0/v1 for else (q in v0? 82 in 2 = v0, 83 in 2 = v0? dispositions: 82 in 2, 83 in 2 — both v0? weird; and q maybe 83).

Wait the target else: q in v0, g in v1. In this dump, reg 82 in 2 (v0), 83 in 2 (v0)? Both in 2 can't be if live together. Maybe one is in a different block.

Anyway: the pinned body's advantage is that `self` (73) is the only pseudo needing a global reg, and it lands in a1 because... it conflicts with a0? "73 conflicts: 73 2 3 4 29" — includes 4 (a0), so not a0 → a1.

In c1 (pointer self), the cast created an extra pseudo 72 (the param, a1) and self 73 (a0). Why the difference? In c1, expand created 72=arg0 then 73=copy. In the pinned orig, there's no separate param pseudo — because the param pseudo is only used to compute self, and expand may not create a param pseudo at all if the parameter is only used once... Actually in the pinned orig, `self = arg0 + zr` — the parameter a0 is used directly (hard reg) in the addition, no param pseudo. So 73=self is the only one.

In c1, `self = (Unkstruct*)arg0` — a copy; expand created a param pseudo 72 for arg0 then a copy to 73. Why? Because the parameter is used in a conversion? Hmm, the K&R param declared s32, assigned to a pointer. The conversion SImode→Pmode... Since Pmode==SImode, maybe expand still does a conversion copy.

So the fix: avoid creating the param pseudo, i.e., have `self` be the *same pseudo* as the parameter (self = arg0 assignment optimized away?) or use arg0 directly with a cast at each use.

If we use `arg0` directly with casts at each use, then the code uses a0 everywhere, no copy. Not target (target has move a1,a0 and uses a1).

So we need one pseudo for self that is initialized directly from the hard reg a0 (like the pinned version's `self = arg0 + zr`), i.e., an expression that makes expand load the hard reg directly into the new pseudo without creating a param pseudo. `self = arg0;` in C: expand_expr for the param yields a hard reg (a0), and the assignment to self creates `(set self a0)`. But then cse/copy-prop might fold self into a0 — that's what happened in the non-pinned versions? Wait, my win.c (s32 self, no pin) had `self = arg0;` and got score 16 with then=a1, else=a0. Let's dump win.c (s32 self, no pin, no cast) to see.

Actually win.c's assembly: then a1, else a0 (same as c1). Let's dump win.c and look at greg.
