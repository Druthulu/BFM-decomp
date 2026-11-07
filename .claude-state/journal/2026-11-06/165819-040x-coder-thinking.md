---
ts: 2026-11-06T23:58:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eMDhQGSiqRGn5BZh9Qt5
---
p14 == G_nopin exactly (same residual: s3->s4 x10, s4->s3 x5). So `*q = val; p = q;` reproduces the target's copy — the launder is cracked lever-free.

Now only the reg order remains: base=s3, mode=s4 in mine; target base=s4, mode=s3.

Now the allocno priorities: base r72 pri 1518, mode r73 pri 1204. But wait — does p14's allocno table differ from G_nopin's? The C is different (store first), which changes the RTL order, but the allocnos for base/mode are the same.

Hmm, so now I need to flip mode and base. Let me think about the live lengths again.

Hmm, here's an idea I haven't tried: change the ORDER of the C statements that determine mode's first reference vs base's last reference. 

Actually — what about the live_length definition? Let me check flow.c's reg_live_length computation. It might count instructions from the first to the last reference. If I can move `mode = -1` later... no.

BUT: what if I can make `base`'s live range *shorter*? base's last use is in `if (mode == 0 && (res & 1)) { func_800D00E4(...base...) }`. That's near the end. And base's first use is in the first if. So base's live is 158.

What if I *reorder* the 5 ifs so that base's first use is later? No, that changes code.

Hmm. What if I could make mode's live range start EARLIER (worse) — no, we want shorter.

Wait, actually maybe I should re-examine: is base really r72 with 8 refs? Let me count base uses in p14: 5 unkA3D8 + 1 unkA3DE + 1 final unkA3D8 = 7 uses + 1 set = 8. Yes.

Mode: set -1, set 0, use in `mode >= 0`, use as arg, use in `mode == 0` = 5.

Priorities fixed. Hmm.

Unless... I can make mode's live length shorter by moving its last use earlier? The last use `if (mode == 0 && ...)` at the end. What if I restructure that condition? `if (mode == 0 && (res & 1))` — mode is used at the very end. Fixed.

What if I can make mode's live range shorter by *initializing* it later — no.

Hmm, what if `mode`'s first reference moves later because the `mode = -1` statement is placed after the cnt call in the C? Let me check: currently `mode = -1;` is right after `st = func_8002F648();` and before the if. The cnt call is after the if. So no.

Wait — actually, what if I move the `cnt = func_80029504();` call BEFORE the mode if? That changes code order. No.

OK. So the only lever left is making base's refs 7 or mode's refs 7+ / live ≤65.

IDEA: make base a *parameter-like* variable... no.

IDEA: What if `base` is used to compute the address in ONE of the ifs via a different expression that the compiler CSEs into the same register? E.g., `((Unkstruct_80010178 *)D_800AF630)->unkA3D8` in one if instead of base. Then base's refs drop to 7, but a new pseudo (the D_800AF630 address) appears — however cse would equate it with base's value and reuse the register, emitting the SAME code! Let me think: `((Unkstruct_80010178 *)D_800AF630)->unkA3D8` computes D_800AF630 fresh — cse sees the constant address, already in base's qty, so it substitutes base's register. The RTL would have a `set (reg newpseudo) (symbol_ref)` insn that cse deletes as redundant (it's already available). Hmm, actually if base holds it, cse replaces the new pseudo's uses with base and deletes the set. So the final code is identical, but the *allocno ref count* of base... the ref would be via the new pseudo which is deleted. So base's refs drop by 1! And the emitted code stays the same!

That's the classic "two spellings of the same address, cse merges them" trick. Let me test it.

Specifically, change one of the 5 `((Unkstruct_80010178 *)base)->unkA3D8` to `((Unkstruct_80010178 *)D_800AF630)->unkA3D8`.

But careful: cse might keep a separate pseudo if it can't prove equivalence. Let's test.

Actually, even better: I could change the LAST use (the func_800D00E4 argument). Let me try several positions.

Let me generate candidates q01..q05, one per if-site, plus q06 for the unkA3DE site.

Also, for mode: add a ref via a spelling that cse folds, e.g. `mode = 0;` in the if could be spelled as `mode = 0;` ... hmm, adding a redundant `mode = -1` that's dead? flow deletes it before global-alloc. 

Let me test the base-spelling idea.
