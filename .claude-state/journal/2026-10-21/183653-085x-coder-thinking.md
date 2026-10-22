---
ts: 2026-10-22T00:36:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_60sJSu2TrVEc4Uhvzx2Z
---
The switch is worse (37).

Let me think about the target's shape more: the target has the comparison chain where the *first* compare uses t3 and the *first* store uses t2. Hmm, in the target, the *first* comparison's constant (-150) is in t3 and the *first* store value (4) in t2. Then the subsequent compares use v0 (rematerialized).

Hmm, why would the first ones get regs? Because they're the *first* uses and the allocator... hmm.

Wait, maybe I should look at this from the "what does the ORIGINAL game asm look like" angle: the original asm (asm/ov_SC06_016/nonmatchings/...) — let me look at it! The original game asm is the ground truth for what we're matching... but no, our target is the build. Hmm, but the build was made to match the original.

Let me look at the original .s file to understand the intended structure: it might reveal that the original had a different *source* structure (e.g. the values loaded differently).

Let me check: asm/ov_SC06_016/nonmatchings/ov_SC06_016_jr_8017C8D0/func_801813B0.s.

Actually, that's the *target* the decompiler aimed at. Since the built object (with the lever) presumably matches it, looking at it won't add much beyond the build asm.

Let me think about the lever's effect once more. 12 asms on v. In the *target* asm, is there any trace of the asms? The asms generate no instructions, but they force v into a register *at that point* — and importantly, the asm's *output* redefines v, so the value compared is the asm's output (unknown), not the loaded value!

Hmm! So in the target, the value compared against -150 is the *asm output* — which GCC knows is the same reg as the loaded v1. So the comparison is still against the loaded value. OK.

But here's the thing: the 12 asms are *between* the load and the comparisons. Each asm is a "use" of v and a "redefinition". So the comparisons use the *last* asm's output.

Now, why would this change the constant hoisting? Because the 12 asms create 12 *sets* of v → in the RTL, v's pseudo has 13 sets → REG_N_REFS(v) is high. In the global allocator, v's priority is high → v gets a good reg. The constants (-150 etc.) have 1 ref each → the allocator decides to rematerialize them (they're "cheap" and used once) — except... hmm, then why are -150 and 4 in regs in the target?

Hmm, maybe because the *first* comparison's constant and the *first* store value are used in the "hot" path.

OK, let me try yet another approach for this item: make the *constants* fewer by restructuring the C so that the chain uses fewer distinct constants. E.g.:

```
if (v == -150) idx[i] = 4;
else if (v == -139) idx[i] = 3;
else if (v == -106) idx[i] = 2;
else if (v == -57) idx[i] = 1;
else idx[i] = 0;
```
What if instead:
```
if (v == -150) idx[i] = 4;
else if (v == -139) idx[i] = 3;
...
```
Same.

Alternatively, what if the *store values* were a *decreasing* sequence computed from a variable? e.g. `idx[i] = 4; ... idx[i] = 3;` → the constants 4,3,2,1.

What if we write `idx[i] = 4 - 1;`? folded.

Hmm.

Let me try a different structural idea: what if the *load* of v is moved/duplicated so that the value is used more? E.g., the lever's 12 asms are "12 uses" of v. What if the C had a *real* second use of v? E.g.:

```
v = *(s16 *)((u8 *)src + i * 8 + 2);
if (v == -150) ...
```
The value has 4 uses (the comparisons) already.

Hmm, what if the *comparison* is done on a *copy*:
```
s16 w = v;
if (w == -150) ...
```
That's a copy (adds a register, might change the pressure!). Hmm, but the target has v1 used for all 4 compares → a copy would be coalesced.

OK, at this point, let me consider the possibility that this item's lever is a "keepalive"-ish ref-count trick that can't be reproduced in plain C → WALL. But the wall tag would be new: e.g. `greg-const-hoist` or `reload-const-remat`. Hmm: the mechanism = "the 12 asms raise v's ref count; the allocator then rematerialises the loop-invariant comparison constants into the delay slots instead of hoisting them into regs".

Wait, actually — hmm! Let me reconsider: maybe the mechanism is entirely different. What if the asms' effect is to make GCC treat the *loop body* differently: with the asms, the loop body has more instructions (the asms count as instructions? no, they generate no code but they are RTL insns) → the loop's *size* changes → the "loop unrolling" or the scheduler's decisions change.

Hmm, hmm! But here's a cleaner thought: the 12 asms make the loop body *bigger* in RTL terms → the loop optimizer's "prescan" or the scheduler's *loop rotation* might behave differently. But the *constant hoisting* difference (6 vs 2) is a register-allocation/scheduling decision.

Let me try ONE more idea: what if the *first* comparison is separated from the rest by a statement? E.g. what if the C is:

```
if (v == -150) {
    idx[i] = 4;
} else if (v == -139) {
    idx[i] = 3;
} ...
```
vs
```
switch ...
```
tried.

What if the *value* stored is a variable computed from a chain? e.g.

```
s32 r;
if (v == -150) r = 4;
else if (v == -139) r = 3;
else if (v == -106) r = 2;
else if (v == -57) r = 1;
else r = 0;
idx[i] = r;
```
This gives a phi → the store would be a single store at the end → different shape (the target stores in each arm).

OK, let me make a decision: I'll do ONE more experiment for item 4 — the "copy" idea and a "u16" idea — and then record a WALL.

Actually, hold on! Let me reconsider the problem. In the target, the compare chain is:
```
bne v1,t3,4b4c   ; v1 vs -150 (t3)
   li v0,-139     (delay)
bne v1,v0,4b60   ; v1 vs -139 (v0)
   li v0,-106     (delay)
bne v1,v0,4b74   ; v1 vs -106 (v0)
   li v0,-57      (delay)
bne v1,v0,4b84   ; v1 vs -57 (v0)
   li v0,1        (delay)
sh zero,0(a2)
```
So the *chain* uses v0 as a scratch for the constants, rematerializing each. The target's structure = "the constants are NOT in regs; they're materialized in the delay slots".

In c1, GCC hoisted 6 constants into t2-t7 and the compares use them.

Hmm! Notice: in c1, the *store values* 4, 3, 2 are in t6, t4, t2 and the *compare constants* -150, -139, -106 in t7, t5, t3. So GCC kept 6 constants. The delay slots then hold only the last two.

What if the difference is the *order* of the chain or the *number of arms*? no.

What if the *loop* had a different *structure* (e.g. the loop body is bigger/smaller)?

Let me try: what if the *body* of the loop is restructured so the store to idx[i] happens... hmm.

New idea: what if the *asm's* effect is that GCC keeps the loaded value v in a register that is *also* used for the constants? no.

OK — pragmatic decision: item 4 = WALL, best 28 (c1), tries 2.

Hmm, but hold on. Let me try ONE more thing that's cheap and plausible: the C0505 "s16/u8 widths" move — the load is `*(s16 *)((u8 *)src + i*8 + 2)`. What if the type of v were s16 vs u16? Or what if the *comparison* constants were expressed differently?

And the "pointer reuse" move: the `idx[i] = ...` stores. Hmm.

Let me try one variant: change the comparison chain to use a *local* for the store value? no.

Actually, let me try: what if the *order* of the arms is reversed in the source (e.g. -57 first)? The target's order is fixed, so no.

Let me try: what if the *else* arm (idx[i] = 0) comes first in the source (i.e. `if (v != -150) {...}`)? That changes the branch structure.

OK, one more idea that might be THE answer: what if the *asms* are there to make the *load* of v not "pairable" with the comparison...

Let me just try a *diagnostic* to identify the mechanism: replace the 12 asms with 1 asm, 2 asms, etc. and see how the score changes. If 1 asm gives the same 28 as 0 asms, then the asms' *presence* (not count) matters. If 1 asm gives something closer, the count matters. This is diagnostic only (the count of asms is a lever, so I can't use it in the final answer, but it tells me the mechanism).

Cheap and informative. Let me do it: c3 = 1 asm, c4 = 4 asms, c5 = 12 asms (orig).

Let me run that.
