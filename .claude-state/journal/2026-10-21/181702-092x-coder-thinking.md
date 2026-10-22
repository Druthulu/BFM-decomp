---
ts: 2026-10-22T00:17:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_kr5O13yxzboil9q7FQeF
---
Excellent! The .greg dump shows:

```
;; 5 regs to allocate: 73 103 77 74 75
;; 103 conflicts: 73 74 75 103 29
;; 103 preferences: 2          ← r103 (the RESULT_DECL) prefers reg 2 ($2) ✓

;; Register dispositions:
73 in 16  74 in 17  75 in 18  77 in 2  101 in 3  102 in 2  
103 in 2  106 in 2  109 in 3  111 in 2  115 in 3  117 in 2  
122 in 2  124 in 3  127 in 2  
```

So r103 IS allocated reg 2 ($2) ✓✓ and r77 also in 2. And the temps: r102 in 2, r106 in 2, r111 in 2, r117 in 2, r122 in 2, r127 in 2 — all in reg 2 (they're in different blocks, so they can share).

So the RESULT_DECL r103 = $2 ✓ — in the GLOBAL allocation! Then the local temps also use $2 in their own blocks (they don't conflict with the global's live range... hmm, but the RESULT_DECL is live across the whole function ✗).

Hmm, but the observed code (V2) had the temps in $2/$3 ✗. Hmm, but the disposition says r127 in 2 (a temp) — and r103 in 2 as well. They're in different blocks → but r103 is live across the function (the return value) → conflict ✗.

Hmm, the conflicts list for r103: "73 74 75 103 29" — it doesn't list the local pseudos (they're not globals). The local pseudos get $2 in blocks where the global r103 isn't live? But r103 (the return value) is live from the `return` to the end ✗.

Hmm, whatever: the allocation says the RESULT_DECL is in $2 ✓ and the temps also claim $2 in various blocks.

So the problem: in the ROM, the temps are in $3/$4 and the result in $2 — i.e. the temps must NOT take $2.

In the V2 code, the tail block (9) has: r122 (6666, in 2), r124 (10000, in 3), r127 (10000, in 2), r103 (10000, in 2). Hmm, so in block 9, r127 and r122 both got $2 and r103 also $2?!

Hmm, the "Register dispositions" line lists the hard reg each allocno got — but for LOCAL pseudos the assignment is per block, and the dump may show the last one.

OK, whatever the mechanism, the fix must make the block-9 temps take $3/$4 instead of $2.

The temps in block 9 are the loads: r124 (in 3) and r127 (in 2) and r122 (in 2). The target: the loads in $4 (a0) and $3 (v1) → so in the target, the temps took $3/$4 and $2 was reserved for the result.

In the lever-free version, the temps grab $2 because they're LOCAL (allocated by local-alloc, which doesn't know the global wants $2? or because the global's live range isn't considered).

Hmm! Wait: in the pinned (target) version, `r` is a HARD REG $2 → the temps can't take $2 ✓.

In the lever-free version, r103 (the RESULT_DECL) is a global allocated $2 — but the LOCAL temps still took $2 ✗ (a bug/limitation in gcc 2.7's local-alloc: it doesn't know the global's allocation? It should — local-alloc avoids regs used by globals live in the block).

Hmm, in gcc's local_alloc, the hard regs available are those not conflicting with the live globals in that block. If r103 is live in block 9, then $2 should be excluded ✗.

Unless r103's live range does NOT include block 9! The RESULT_DECL is set at the return → live from the return to the epilogue. Block 9 is the tail block containing the return... hmm, then r103 is born IN block 9 → so in block 9, r103 is live from its set onward, and the temps (live earlier in the block) can use $2 before r103's set ✓✓ (no conflict, since they don't overlap).

That's it: in the target, the RESULT_DECL ($2, the pinned hard reg) is also set at the return, so the temps could have used $2 before... but they didn't (they used $3/$4) — because with a hard reg, the temps can't use $2 at all ✓.

So lever-free: I need the temps NOT to use $2. Since the RESULT_DECL is born at the return (in block 9), the temps (earlier in block 9) can use $2 ✗.

To avoid that, the RESULT_DECL's set must be EARLIER (before the temps) — i.e. the returned value must be computed BEFORE the loads. In the target, the `li v0,1` (r = 1) is at ins 55 — AFTER the first pair of loads (51-52) but BEFORE the second pair (56-57)!

Hmm! So in the target, the value's set (ins 55) is between the two load pairs. If the temps before the set could take $2, they would ✗ — but in the target the first pair took $4/$3 (not $2) — because $2 was reserved by the hard reg ✓.

Hmm OK. So lever-free, the first load pair can take $2 (before the result's set) ✗.

Unless the returned value's set comes BEFORE the loads. In the source, `r = 1;` comes before the if ✓ — but gcc SANK it (sched1) to after the first comparison ✗. So in the lever-free version, the `r = 1` set is sunk too (mine[55] `li a0,1` after the loads) — because gcc sinks it (it's dead until the return).

To prevent the sinking: make the value live earlier... e.g. if the value is used in the first comparison? Hmm.

Hmm! What if `r = 1` is NOT sunk because it's a "hard" value... hmm.

Alternatively: what if the source's structure puts the "return 1" set earlier, e.g.:
```c
    r = 1;
    if (A == B) {
        if (C == D) {
            r = E != F;
        }
    }
    return r;
```
Same.

Hmm, what if the source computes the comparisons FIRST and then assigns:
```c
    s16 a1, a2, a3, a4;
    a1 = *(s16*)(s0+6); a2 = *(s16*)(s0+0xA0); ...
    r = 1;
    if (a1 == a2 && a3 == a4) { r = ...; }
    return r;
```
→ the loads are all before `r = 1` → the temps would still take $2 before the set ✗ (the same problem).

Hmm, so the RESULT_DECL's set must be before the temps' sets to reserve $2. But the ROM has the set in the middle (after the first load pair) ✗.

Hmm, but hold on: in the ROM (pinned), $2 is reserved for the whole function (hard reg) — so the temps take $3/$4 throughout. For the lever-free version to match, the RESULT_DECL must be live from the function start (so $2 is reserved) — i.e. the RESULT_DECL's set must be at the TOP.

Hmm! What if the source sets the result variable at the top:
```c
    r = 1;                       /* at the top of the function */
    ...
    if (...) { r = E != F; }
    return r;
```
Then the RESULT_DECL's set is at the top → $2 reserved from there ✓ → the temps take $3/$4 ✓✓. But: the `r = 1` set would be materialized at the top (an extra `li v0,1` early) ✗ (the ROM has it at ins 55) — unless gcc sinks it back ✗ (gcc sank it in my nopin version, which is exactly the problem: the set is sunk, so the RESULT_DECL's live range starts late).

Hmm! But wait: the RESULT_DECL is a different pseudo from `r`. The RESULT_DECL's set = the copy from `r` at the return. So the RESULT_DECL is always born at the return ✗.

Hmm, so the RESULT_DECL (r103) is born at the return, and the temps (born earlier) can take $2 ✓ → the observed allocation.

BUT the target's temps take $3/$4 — because the pinned `r` (a hard reg $2) is set at ins 55 (mid-block) and the temps... hmm, wait: with the hard reg $2, the temps can't use $2 at all ✓ (a hard reg is reserved for the whole function) ✓.

So for a lever-free match, the temps must be prevented from using $2 in the region before the result's set. That requires the RESULT_DECL (or `r`) to be live from the function start.

IDEA: what if the function returns `r` where `r` is assigned at the TOP (before the calls) and the return copies it at the end? Then `r` is live across the whole function → it'd be in a callee-saved reg ✗ (not $2).

Hmm, but the RESULT_DECL is what got $2 (via the preference). The RESULT_DECL is born at the return ✗.

Hmm, unless the source has the return value set EARLY: e.g.
```c
    r = 1;                     /* early */
    ... calls ...
    if (A == B && C == D) { r = E != F; }
    return r;
```
Then `r` is live across the calls → a callee-saved reg ✗ (the ROM has the value in $2, live only at the end).

Hmm.

OK, so how did the ORIGINAL (ROM) source look? The ROM's `li v0,1` at ins 55 (after the first comparison) and the temps in $3/$4. With the hard-reg pin, this works.

For lever-free: gcc allocates the temps $2 (they're born before the result's set).

Hmm, is there any way to make the temps' live range NOT overlap the result's? The temps in block 9 are born at their loads; the result is born at the return. The temps die before the return ✓ → no overlap → they can use $2 ✓ (gcc's local-alloc: a reg is available if no live pseudo conflicts in that point).

Hmm, so the lever must make the temps' live range overlap the result's — i.e. the result's set must be BEFORE the temps' sets. In the ROM, the `li v0,1` (ins 55) is between the load pairs — so the SECOND pair of loads (ins 56-57) is born AFTER the result's set ✓ (so they can't use $2 ✓) but the FIRST pair (ins 51-52) is before ✗ (they took $4/$3 in the ROM because $2 was hard-reserved).

Hmm, in the ROM the first pair took $4 (a0) and $3 (v1) — hmm, why not $2? Because $2 was reserved ✓.

So the lever-free version needs the result's set to be before the FIRST load pair. That means the source's "r = 1" must be before the first comparison... but gcc sinks it (sched1) to after the first comparison ✗.

Hmm, why does gcc sink it? Because the scheduler sinks the `li 1` into the block where it's needed... The sink happened in my compile (mine[55] `li a0,1` after the loads at 51-52). Hmm, but the ROM has the same position (ins 55, after the loads at 51-52) ✓ — so both sink it the same way ✓. The difference is only the register.

So in the lever-free version, the result's set is at ins 55 (same as the ROM) — and the first load pair (ins 51-52) is before it → they can use $2 ✗ (the ROM has them in $4/$3).

To prevent the first load pair from taking $2, something else must hold $2 at ins 51-52. In the ROM, the pinned hard reg holds it (as a value? no — $2's value at ins 51-52 is whatever). Hmm, actually in the ROM, $2 at ins 51-52 holds... the value of `r`? The `li v0,1` is at 55, so before that $2 holds the previous value (dead) — but $2 is reserved for the hard reg, so gcc can't use it for a temp ✓.

So the lever: make $2 hold a live value at ins 51-52 in the lever-free version. What's live there? The result's value would be ideal — but its set is at ins 55 ✗.

Hmm, what if the source's "r = 1" is set EARLIER (before the comparisons) so that the RESULT_DECL's set is early? But gcc sinks the set... The sinking is of the `r = 1` (the user variable's set). The RESULT_DECL's set (the copy at the return) is even later.

Hmm, unless the source returns `r` directly with r's value... the RESULT_DECL is always a copy at the return.

Hmm, what if the function's return is via a "return r;" where `r` is the RESULT_DECL? Not expressible.

OK, item 5 seems to need the pin. Let me accept the wall for item 5 and move on.

Given the time (18:20, ~46 min elapsed), I have budget. Let me reconsider item 3 and item 4 with fresh eyes, since they follow the same pattern ("the returned value must be in $2").

Item 3: the ROM's structure has the `li v0,1` in a delay slot of the first compare, and the four compares branch directly to the epilogue. Without the pin, gcc materializes the constant at the return block.

Hmm, what if the source's four arms return a variable that is NOT constant-folded? E.g. what if the value is 1 but comes from a comparison that gcc keeps as a pseudo?

IDEA for item 3: what if the source is:
```c
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
```
What if instead:
```c
            v1 = 9;
            if (arg2 == v1) return 1;
            v0 = 1;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            ...
```
Hmm, the first arm returns the literal 1 (materialized in that arm's block) and the others return v0 (=1, a variable) → the arms would be different blocks → no cross-jump merge → the ROM's single `li v0,1` ✗ (there'd be 2).

Hmm.

What about this: the ROM's four compares all branch to the epilogue with $2 = 1. For gcc to branch directly to the epilogue (no copy), the pseudo holding 1 must be in $2.

Since a constant pseudo gets folded, the value must be non-constant...

WAIT. What about the possibility that the ROM's `li v0,1` is the set of the pseudo that holds the value of the MASK TEST? Let me re-look at the ROM:
```
17 lh v0,174(a1)
18 andi v1,a3,0xffff
19 and v0,v0,v1
20 bnez v0,+0x90
21 li v1,9
22 beq a2,v1,+0x94
23 li v0,1
24 li v1,17
```
Hmm! What if `li v0,1` is the set of a pseudo whose value is 1 = the result of the mask test (`(x & y) == 0` → 1)?! I.e. the source might be:

```c
    v0 = ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0);   /* 1 when the mask is 0 */
    if (v0) {
        v1 = 9;
        if (arg2 == v1) return v0;
        ...
```
Hmm! Then v0's set = the boolean (1 on this path). But the ROM's mask test is `and v0,v0,v1; bnez v0` — the AND result in $2 and the branch on it. If v0 held the boolean, gcc would compute `sltiu v0,v0,1` (the == 0 test) — an extra insn ✗ (the ROM has none).

Hmm, but gcc might keep it as: the AND result (in $2) is tested with beqz, and the "boolean" is materialized as 1 in the taken path ✓ — i.e. gcc's "condition propagation" turns the boolean into the constant 1 inside the block ✓✓ and the set `li v0,1` (ins 23) is the materialization of that constant ✓.

Hmm! So the source could be:
```c
    v0 = (*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0;    /* v0 = 1 in the taken path */
    if (v0) {
        v1 = 9;
        if (arg2 == v1) return v0;
        v1 = 0x11;
        if (arg2 == v1) return v0;
        ...
```
Hmm, but then the mask test would be `beqz v0` (the boolean) rather than `bnez v0` on the AND result ✗ (the ROM has the AND result in $2 tested with bnez).

Hmm, the ROM: `lh v0,174(a1); andi v1,a3,0xffff; and v0,v0,v1; bnez v0,+0x90` — so the branch is on the AND result (not a boolean). If the source computed the boolean, gcc would need `sltiu`/`seq` ✗.

Unless gcc optimizes `((x & y) == 0)` into a branch on the AND result (an inversion) ✓ — gcc DOES do that: `if ((x & y) == 0)` → `beqz (x&y)` (branch on the AND result) ✓✓ and the boolean value (1) is materialized in the taken path as `li v0,1` ✓✓✓ !!!

So the source could be:
```c
    v0 = ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0);
    if (v0) {
        v1 = 9;
        if (arg2 == v1) return v0;
        ...
```
and the ROM's bytes would be: the AND in $2, `bnez v0` (branch if the AND != 0 → skip), then `li v0,1` — hmm, but the `li v0,1` is at ins 23 (after the first compare at 22), not right after the branch at 20 ✗. Hmm, the scheduler moved it (it's dead until the return) ✓ plausible!

And the returns `return v0` → v0 = 1 (the pseudo, in $2 — since the pseudo v0 IS the value 1 and it's copied to the return reg $2 → the copy is a no-op if v0 is allocated $2 ✓✓).

Hmm! But would gcc fold the copy `set $2, v0` where v0 = 1 (a constant on this path)? The value is a constant 1 (propagated) → combine would fold it ✗ (the same folding problem).

Hmm, unless the propagation of "1" doesn't happen because the pseudo's value is a boolean expression in the RTL (not a constant) — gcc's "condition propagation" into a block is done by "cse"/"jump threading" which may or may not substitute the constant.

Hmm, in the ROM the `li v0,1` exists → so the value was materialized as a constant 1 ✓ (so gcc DID propagate the constant) → and yet the pseudo v0 was allocated $2 (in the ROM, because of the pin).

Hmm, so in the ROM the pin decides. Without the pin, the same folding happens ✗.

OK. Let me try the boolean formulation for item 3 anyway — it's cheap and the structure differs enough that it might land differently:

```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    s32 v1;
    ...
        v0 = ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0);
        if (v0) {
            v1 = 9;
            if (arg2 == v1) return v0;
            ...
```
Hmm, but then the mask test's structure changes (the `if` becomes `if (v0)`) and the ROM's `bnez v0,+0x90` ✓ (the jump if the AND != 0 = the skip) ✓.

Let me try it. Also try the version where the boolean is assigned but the test remains on the AND:
```c
    if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
        v0 = 1;   /* same as now */
```

Let me write the boolean variant and score it.

Also for item 4, a similar idea: the returned value `result` — hmm.

Let me try item 3's boolean variant now.
