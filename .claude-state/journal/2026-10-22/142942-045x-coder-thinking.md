---
ts: 2026-10-22T20:29:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ioNTml3xjgBZsWd2iKiD
---
w5 (triple src sets) is 19, not 2 — interesting, so the sets changed things back to 86 ins (extra reg). Hmm.

w1 is the best at 2. The residual: mine emits `nop` for calls Z and Y; target emits `addiu a1,sp,16`.

Why does the target re-materialize? Because in the target the address is a *constant* each time (reload remat), not a value in a1. Mine sets a1 once (from the pinned src) and reuses.

To force rematerialization at each call, the argument must be a *constant expression* at each call, not a value held in a hard reg. In score-0 (launder+pin), the address was folded as a constant into a1 at each call (`set a1, (plus fp 16)`) — three addiu. But score-0's source was the pinned src with the launder.

So the target = score-0 shape: calls use `(void *)m` (constant fp+16) folded per call, AND the copy's source base is a register (a1).

In w1, the calls use `(void *)src` where src is a hard reg whose value is the constant — gcc treats it as a reg value (not folded). Hence one addiu.

So: keep `src` for the copy (movstr source, giving the a1 base), but write the calls with `(void *)m` (constant). That's w4 = 19. Hmm! w4's calls use the constant, but the movstr dest created the fp+16 pseudo again (as in c_struct) → s1.

Difference between w4 and score-0: score-0 has no movstr (scalar copies with direct fp stores). w4 has the movstr, whose dest address pseudo (fp+16) merges with the call constant.

So: copy via the pinned src but with SCALAR loads/stores (like score-0) — that's w3 = 22 (because the loads from src got folded per-load: `lui v0; lw v0,off`). Hmm, w3's source loads folded because src's constant was substituted into each load. But wait, w3 also had `src = (int *)m` after; score 22, 90 insns.

Hold on: why did the score-0 body (with launder) NOT fold, but w3 (no launder) folds? Because the launder. Right.

So we need: scalar loads from a *non-foldable* source base. The movstr gives that but creates the dest pseudo.

What if the movstr is used but the *calls'* address constant is prevented from merging with the movstr dest pseudo by having the movstr dest be a *different* stack slot? No.

What if the copy is a movstr into m, and the calls pass `(void *)m` but with the address pseudo's local-alloc eligibility broken? E.g., after the movstr, add a real second set of a variable that holds the address... that's w5-like.

Hmm, wait. Let me reconsider w1's 2-diff. Only calls Z and Y lack the addiu. What if I make the address a *pseudo* that is set fresh before each call but doesn't cost a register: e.g., use the variable `o2` (int) assigned `(int)m` right before each call? w6 (single set) = 19.

What about making each call's argument a separate *real second set* of src, where the sets are separated by the calls (w5) — 19.

Hmm, w1's mechanism: after `src = (int *)m;` (a hard-reg set), the calls use src. GCC's reload sees a1 already = fp+16 and doesn't reload for calls 2,3 because... it thinks a1 survives the call?! That's suspicious. Maybe gcc's call insn for these functions does NOT clobber a1 because... it does clobber. Unless the pinned hard reg $5 is treated specially.

Let me look at the target again: 3 addiu. So the target's calls each use the constant directly.

New idea: make the calls' argument `(void *)m` (constant) while the *copy* is a movstr whose dest address does NOT become a cse base. What if the movstr dest is written through a hard register? Not allowed (new pin).

What if the movstr dest is `(void *)m` via a *void pointer* variable that's... same.

OK, what about the *order* of cse: if the call-arg constant appears BEFORE the movstr dest in the RTL... The copy comes first in the C.

Alternatively: what if the copy is into m but through a *different* pointer variable that is initialized from a call? no.

Let me try: make the calls use `(void *)m` but insert a *real second set* of the constant into a variable before each call, e.g.:
```
mp = m; RotMatrixX(..., (void *)mp);
mp = m; RotMatrixZ(..., (void *)mp);
mp = m; RotMatrixY(..., (void *)mp);
```
with `int *mp` — three sets of a *pseudo* (not a hard reg). Multi-set pseudo → not local-alloc → global allocno → maybe spilled → remat per call? In score-0, multi-set was avoided. Let me test w8 with 3 mp sets, and also 2 sets.

Also: `mp = m;` before each call with the movstr copy (from src).

And w9: calls `(void *)mp` where `mp` is set once but as `int *mp = m;` declared *inside* the if after the copy — same as single set.

Let me test the multi-set variants.
