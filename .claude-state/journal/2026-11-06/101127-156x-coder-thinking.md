---
ts: 2026-11-06T17:11:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rHEqZhNphYTgYeLCMh7B
---
a2 still has the mask in t7. So the mask's register didn't change by moving its definition.

Let me think differently: maybe the *constant* 0xE100008E gets t6 because it's allocated by local-alloc as a *block-local* qty with priority 0.67, while the mask is a *global* qty (crosses a call? no calls in this function). Hmm, the function has no calls. So everything is block-local, and local-alloc handles all.

Local-alloc allocates in priority order. The mask (0.218 after hoisting) vs constant (0.67). Constant wins t6. So the mask's priority is LOWER because sched1 hoisted its definition early, lengthening its live range.

To raise the mask's priority: shorten its live range in the lreg dump. The hoisting is done by sched1 (constant hoisting). If the mask's definition stays near its uses, its lreg life would be 61 insns → priority 39/61 = 0.64 — still below the constant's 0.67, marginally.

To get the mask above the constant: increase refs. The mask has 13 refs. If we could give it 16+ refs: floor_log2(16)=4 → 4*16/61 = 1.05 > 0.67. But adding uses costs instructions.

Alternatively reduce the constant's priority: lengthen its live range (e.g., make it used later, so its lreg life is longer). The constant 0xE100008E is used in the third packet's `*q2 = ...`. If we could make its use later... The constant is a *store value*; combine might hoist it.

Hmm, what if we change the constant's spelling so it's not a single movsi? E.g., `*q2 = 0xE100008E;` vs `*q2 = (0xE1000000 | 0x8E);` — same after folding.

What if we assign the constant to a variable first: `u32 c2 = 0xE100008E; *q2 = c2;`? That gives the constant a named pseudo with maybe a longer range.

Actually, the six E1 constants are all similar; only the 0x8E one is at issue (it's the one that took t6). Why that one? Because it's the third in sched1's hoist order. If we reorder the packet blocks, a different constant might take t6, and the mask might still be t7 → no good.

Better: prevent the constants from being hoisted at all. They're hoisted to the top by sched1 because they're single-set constants (birthing boost). If the constants were "used twice" or dependent, they wouldn't hoist.

Hmm, what if we write the packet stores as `*(u32 *)(p2 + 4) = 0xE100008E;` — same.

What if we use a variable for each constant but declared at the top? Then the constant's definition might stay put.

Let me try: assign the constants to named variables right before their stores:
```
c0 = 0xE100008A; *q0 = c0;
```
This adds no instructions (the value goes into a pseudo, then stored) but changes the pseudo's birth/death and hoisting.

Actually the store value already is a pseudo (117). Naming it doesn't change.

What if the store is `*q2 = 0xE100008E + arg1 - arg1;`? Not foldable, adds instructions.

Alternative: make the *mask* win by making its refs higher — we have 12 uses. What if we use the mask in the packet stores too (e.g., the unk0 stores)? It's already in 12.

Hmm, what about splitting the mask into two variables with 6 refs each? Then each has priority floor_log2(6)*6/life. With life ~100 (half the tail), 2*6/100=0.12 — worse.

What if the mask is defined *inside* each of the 12 expressions as a literal? Then cse creates one constant pseudo (same).

What if the mask is computed as `0xFFFFFFFF >> 8`? That would add a shift.

What if the mask is a *signed* -1 >> 8? `m24 = (u32)-1 >> 8;` → gcc might fold to 0xFFFFFF at compile time (constant folding). Let me try: `m24 = (u32)-1 >> 8;` — gcc folds to 0xFFFFFF in the front end. Same.

Hmm.

What if we make the mask's definition NOT hoistable: e.g., `m24 = 0xFFFFFF;` is a constant; sched1 hoists it. If instead `m24` were computed from a variable (not constant-foldable), it couldn't hoist... but that adds instructions.

OK, maybe try: use `0xFFFFFF` inline everywhere (a1). Fix the a1 compile error first — the regex replaced "m24" inside the declaration `u32 m24;` leaving `u32 0xFFFFFF;`? I removed the declaration first, then re.sub replaced m24 → 0xFFFFFF; the remaining `m24 = 0xFFFFFF;` became `0xFFFFFF = 0xFFFFFF;` — I removed that line after, but the order: t=s.replace('u32 m24;\n',''), then re.sub on t (replacing all m24), then t.replace('    m24 = 0xFFFFFF;\n','') — by then the line is `    0xFFFFFF = 0xFFFFFF;`, so not removed → compile error. Fix: remove the assignment line BEFORE the regex.

Let me redo a1 properly and also try:
- a7: each use spells `0xFFFFFF` but assign to a variable `m` (same).
- a8: reorder the two halves: do the 6 `*ot` updates first, then the 6 unk0 updates? That changes instruction order — no.

Let me also try changing the constant's type: `*q2 = 0xE100008Eu;` vs `0xE100008E` (same value). Or write `*q2 = -0x1EFFFF72;` (two's complement of 0xE100008E = -520093554)? Same const.

Hmm, what about `*q2 = 0xE100008E;` where the constant is > 0x7FFFFFFF as unsigned — gcc may treat it as a 64-bit? no.

Let me try a1 fixed and a few constant-spelling variants.
