---
ts: 2026-10-21T23:58:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_40mMEGyUaggaUbGPISNL
---
No change (folded).

OK. I've spent ~1h15m on this item. Let me make it a WALL, but first let me try the ONE remaining structural idea that I believe could work, based on the v9 insight: **the load must use p (s0) and the materialization must be in a separate reg (v0) with a copy.**

The v9 experiment showed: when the address expression is used twice (once in p's assignment, once in a raw MEM), gcc materializes it TWICE (s0 for p, v0 for the MEM). What if instead the MEM uses p (so only p's materialization exists) but the address expression is used twice so that... hmm, we showed that gives 1 materialization + coalescing.

Hmm. What if we use the address expression twice where the SECOND use is a MEM *through p* but with the raw address spelled? no.

Hmm, hold on, hold on. Let me re-look at the v9 result:

mine[17-18]: lui s0; addiu s0,s0,0     ← p's materialization (p → s0)
mine[21-22]: lui v0; addiu v0,v0,0; lhu v0,0(v0)   ← the MEM's materialization (A → v0) and the load

target[17-19]: lui v0; addiu v0,v0,0; move s0,v0
target[22]: lhu v0,0(s0)

So the target: ONE materialization (v0) → copy to s0 → the load uses s0.
v9: TWO materializations (s0 for p, v0 for the MEM) → the load uses v0.

What if the C were: the MEM uses p AND the address expression is used twice? Then: p's materialization (s0) and the MEM's address = p (s0) → 1 materialization, no copy.

For the target we need the materialization to be in v0 and copied to s0. So the materialization's reg (v0) must be a separate quantity from p.

In v9, the MEM's address quantity (A) was separate from p, and it got v0 (caller-saved, short-lived) while p got s0. The load used A (v0) because the MEM's address was the raw symbol.

**So: if the MEM's address were p (s0) AND there were also a raw-symbol MEM somewhere else (which creates A in v0), we'd have: A (v0) + p (s0) with the load using s0.** But that's 2 materializations (A's and p's) → 4 insns vs the target's 3. ✗ (unless p = A).

Hmm, so we need p = A, i.e. p's value = the MEM's address quantity. In C: `p = &D_800B99DC;` and a raw MEM `*(u16 *)&D_800B99DC` — then p and A are separate quantities (v9). Hmm, in v9, was p = A? p's materialization was s0 and A's was v0 → separate.

So cse did NOT unify p's assignment with the MEM's address. Hmm, because the MEM's address is (symbol_ref) and p's value is (symbol_ref) — cse's find_best_addr looks for a REG with that value in the table. p's reg_equiv = the symbol (a CONST pseudo) → at find_best_addr time (during cse), p is a pseudo whose value is the symbol → is p's REG in the table with the value? The table records EXPRESSIONS, and p's reg is a REG — cse records REG entries for pseudo definitions. Hmm.

OK. Whatever the details, empirically: to get the copy, the value must be in a reg that's separate from p, and p must be a copy of it. gcc-2.7.2 collapses.

DECISION: WALL for func_8018483C.

Hmm, but hold on. Let me try ONE more: **the `p = pb;` copy where pb is a pseudo whose value is a REG because pb = a copy of another pseudo that is a CONST**... no, collapses.

**What about a copy through a function call?** no.

**What about `p = pb` where pb is a struct member?** memory.

**What about the "asm-free" version of the giv-init fence**: §34's "giv-init fence" is an asm. The giv-init MOVE (`loop.c:5556 if (reg != result) emit_move_insn`) happens when a GIV's init is not coalesced. If p were a GIV (loop.c's notion), the init could produce the move! A giv is created for loop-invariant pointer assignments inside loops!

So: if `p = &D_800B99DC;` were INSIDE the loop, loop.c might treat it as a giv and emit the init in the preheader as a copy (the "giv-init" move)!

The def's comment says exactly this: "loop.md L4 preheader-copy"!

And the ORDER issue (the preheader's q, p, r order) — hmm. If p's assignment is inside the loop, the preheader would have the giv init. But the preheader's load `*p & 1` (insn 22) is BEFORE the loop... and it uses s0.

Hmm! But WAIT: if p's assignment is inside the loop and the giv init is in the preheader, then p is live in the preheader (the giv init defines it) → the load can use it ✓✓✓!! The giv init in the preheader: `p = <the giv's base>` → the "move" (the copy!) ✓.

So the C would be:
```
    i = 0;
    q = &D_801E87B2;
    r = &D_8018F078;    /* hmm, the order */
    D_801E86BC = (*p & 1) + 3;   /* p used before the loop — but the giv init defines p in the preheader ✓ */
    D_801E86C0 = D_800B99D8;
    for (; i < 4; i++) {
        p = &D_800B99DC;   /* inside the loop → loop-invariant → giv */
        ...
    }
```
Hmm, but p's value is used before the loop (in the preheader) — the C would be using an uninitialized p (the assignment is in the loop). Semantically broken but the compiler doesn't care (it just warns). Hmm, but then gcc might not create a giv (the assignment is used before...).

Hmm, alternatively: p's assignment is in the loop AND the preheader's use is ALSO in the loop (hoisted)? The load can't be hoisted (the loop writes *p)... but wait, if the loop writes *p and the load is of *p, the load can't be hoisted. Hmm, but the target HAS the load in the preheader (insn 22) — before the loop (the loop head is insn 32). Hmm, and the loop writes *p (insn 91 `sh v0,0(s0)`). So the load at 22 is NOT loop-invariant (it would be re-loaded each iteration if it were in the loop). Since the target has it once in the preheader, it IS in the preheader in the source.

So the C: the load is in the preheader, and p's assignment must ALSO be effectively in the preheader (else p is uninitialized).

BUT: if p's assignment is in the loop, loop.c hoists it (it's loop-invariant) → the giv init in the preheader → and the load in the preheader uses p ✓ — and the C is semantically OK-ish (the load would be of the uninitialized p in the source, but after hoisting it's the hoisted value).

Hmm, in C the source order would be:
```
    for (; i < 4; i++) {
        p = &D_800B99DC;    /* hmm, must come before the use in the preheader?? */
```
The preheader's load `D_801E86BC = (*p & 1) + 3;` is BEFORE the loop in the source → p is uninitialized there → the compiler may warn but compile. And after hoisting, the giv init is in the preheader, so the load would use the hoisted value. But the ORDER in the preheader: the giv init is placed at the preheader's start (loop.c inserts the init at the preheader), and the load is later → ✓.

And the ORDER of the preheader's materializations: q (s3), p's giv init (v0→s0), r (s2) — hmm, the giv init would be placed... loop.c places the giv init at the beginning of the preheader? Then the order would be p's init, q, r. Hmm, the target has q, p, r. Hmm.

But the scheduler can reorder the independent materializations! `lui s3` (q), `lui v0`+`move s0,v0` (p), `lui s2` (r) are all independent → sched2 orders them by LUID (source order) → q, p, r ✓ if the source order is q, p, r.

Hmm, but if p's assignment is inside the LOOP, the giv init's LUID would be... the loop body's LUID (later) → the order would be q, r, p ✗.

Unless q and r are also inside the loop! Then the preheader's order = the loop body's order: p, q, r? The target has q, p, r. Hmm, so the loop body order would be q, p, r — but the source has q, p, r before the loop. If they're all in the loop body in the order q, p, r → the preheader order = q, p, r ✓✓✓!!!

And the preheader's load `D_801E86BC = (*p & 1) + 3;` and `D_801E86C0 = D_800B99D8;` — those are in the preheader in the target (insns 22-30), AFTER the three materializations (15-21). If they were in the loop body, they'd be hoisted (the load can't be hoisted; the store to D_801E86C0 can't be hoisted either due to aliasing). Hmm, so the load and the stores are in the preheader in the source, and q, p, r are in the loop body?? Then the preheader's order would be: [load, stores] then [hoisted q, p, r] — the target has the materializations FIRST (15-21) then the load (22). ✗ (unless the scheduler moves them: the materializations are independent of the load... the load `lhu v0,0(s0)` depends on s0 (p's materialization) → so the materialization must precede the load ✓. And the LUIDs: the hoisted materializations have later LUIDs than the load → sched2 would place them after ✗).

Hmm, unless the loop's preheader insertion puts the hoisted code BEFORE the other preheader code. loop.c's `hoistinvariant` inserts the hoisted instructions at the preheader's "before the loop" point — and the preheader is created by splitting the block; the hoisted code goes at the END of the preheader (just before the loop) or the beginning? In gcc's loop.c, the hoisted code is appended to the preheader's insn chain, which is BEFORE the loop. And the preheader's other code (the load, the stores) was there first → the order would be: load, stores, hoisted. ✗

So the target's order (materializations first) means the materializations have EARLIER LUIDs than the load → they're earlier in the source. So q, p, r are before the load in the source. ✓ (as in the current def). So p's assignment is before the load → p's assignment is in the preheader, NOT in the loop.

=> The giv theory doesn't fit either. UNLESS the giv is created from a p assignment in the loop AND the preheader's load is a separate statement.

Hmm, hold on: what if the C is:
```
    q = &D_801E87B2;
    p = &D_800B99DC;        /* in the preheader */
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;
    D_801E86C0 = D_800B99D8;
    for (...) { ... }
```
and the giv comes from the LOOP's own induction variable? The loop counter i is a giv. Hmm, the giv-init fence in §34 was for a "counter-derived pointer" (R44). Our function has no such pointer.

OK. FINAL: WALL for func_8018483C. I've spent 1.5 hours. The brief says 20-30 min per item and to record a wall.

Let me now write up this item and move to the remaining 3 items (8017DA30, 80184828, 8017D81C), which I haven't looked at yet. Let me be efficient: look at each, and if the launder is of the same "address copy" kind, I'll have learned the pattern. If they're the "address used twice" kind (like item 2), the dead-reset trick will crack them.

Let me check the wall tag. The mechanism: "gcc-2.7.2 collapses the copy of a constant address pseudo (cse's forward scan forwards the reg_equiv), so the target's `lui v0; addiu v0,v0,0; move s0,v0` (an address materialised in a temp and copied into the $s reg) has no lever-free C spelling". A new tag: `cse-const-addr-copy`.

Hmm, walls.txt says a new tag is `<pass>-<what>`, lowercase. So: "cse-const-addr-copy" ✓.

Let me now write the notes and move on. Actually, let me first quickly look at the remaining 3 items' shapes to plan.

Let me look at func_8017DA30 (src/ov_SC02_004, 34 lines) — the smallest.
