---
ts: 2026-11-06T22:06:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s8HgBKrmzF0Ui8erR5z5
---
All 5. That's 19 more tries; total scored tries on this item ≈ 9 (w1,w2,w3,w6,w7,w8,w9,w10,w11,w12,w13) + 19 = 30. Good, I've hit the 30-try mark.

Wait, let me count precisely: w1, w2, w3, w6, w7, w8, w9, w10, w11, w12, w13 = 11; b1-b19 = 19. Total 30. Plus orig baseline. 

Best lever-free: 4 (w13, 56 ins, REG-caller).

Hmm, but before recording a WALL, let me reconsider w13 once more: score 4, and the only diff is the compare's register (a0 vs v1) — 4 register pairs. What if I can flip it?

In w13: iv2c=v0, iVar2=a0, one=v0 (reused after iv2c dies). The compare uses a0 (iVar2) because the copy `iVar2 = iv2c` propagated iv2c→iVar2 in the compare.

What if I add a second use of iv2c *after* the compare, so iv2c stays live and can't be v0 (conflict with one)? Then combine's substitution would still rewrite the compare to a0... but maybe with iv2c live, the compare would use iv2c? No, the substitution replaces the compare's operand.

Hmm, but actually: would cse propagate `iVar2 = iv2c` into the compare if iv2c is used later? cse propagates regardless.

Hmm, but wait: if iv2c is live after the compare and iVar2 is also live, they're different registers. The compare uses iv2c (v1). If cse replaces iv2c with iVar2 there, the compare uses a0 — wrong.

Unless cse can't because... no.

OK so what about a variant where the copy direction is `iv2c = iVar2` and iv2c is live after the compare (blocking combine from deleting), and cse is blocked by a second def of iv2c... The second def would be the "real second set" trick. E.g.:

```
iv2c = iVar2;          // def 1
...
iv2c = iv2c;           // launder — no
```

What about a real second set: after the compare, `iv2c = iv2c + 1;`? That's a real computation but it changes the code (adds an insn).

Hmm.

Actually, what about a *conditional* second set: 
```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
No.

I think WALL it is. But hold on — the w13 result (4, 56 ins) is interesting: it's a different *body* (inverted copy). Its best is 4, lower than the base's 5.

Let me try 2-3 quick variants around w13 to see if any hits 0 — specifically making iv2c live at the compare:
- c1: w13 + use iv2c later (in r instead of iVar2)? Then iVar2 dies at the copy → coalesce.
- c2: w13 + iv2c used in the compare and iVar2 kept alive by... 

Hmm, in w13 the compare uses a0 = iVar2 — because cse propagated. To prevent that, iv2c must not be equivalent... 

What if in w13 the copy is `iVar2 = iv2c;` and iv2c is a HImode variable? Then iVar2 = sign_extend(iv2c)... 

Let me try c1: w13 with the copy through an s16 temp:
```
{ s16 t2; t2 = (s16)iv2c; iVar2 = t2; }
```
Then cse can't equate iVar2 with iv2c → the compare keeps iv2c. And combine folds the sign-extend to a copy (since the range is known) → `iVar2 = iv2c`, which survives (iVar2 live later). iv2c is live at the compare → conflicts with `one` (v0) → iv2c takes v1. iVar2 takes a0.

The result would be: `move a0,v1`?? The copy is `iVar2 = iv2c` = a0 = v1 → `move a0,v1`. But the target is `move v1,a0`. Wrong direction again.

Hmm! Unless the allocator assigns iv2c = a0 and iVar2 = v1. Then the copy would be `move v1,a0` ✓ and the compare `beq a0,v0` ✗ (target: beq v1,v0).

Argh, the direction.

OK: the target's copy is iv2c = iVar2 (v1 = a0). For that, iv2c must be the dest and iVar2 the source. And the compare uses iv2c (v1).

So the C must be `iv2c = iVar2` with the compare on iv2c and cse not propagating.

cse propagation requires the copy to be visible. Blocking it requires a second def of iv2c (which then must not be folded away) or a different EBB.

What about a second def that is *conditional*: e.g., assign iv2c in the then arm and in the else arm? That's w9 (57 ins, extra).

What about: assign iv2c in the else arm only, and in the then arm assign `iv2c = iVar2` too... w9.

What about making the then arm's assignment free by having the then arm NOT set iVar2 separately? In the target, the then arm has `li a0,1` (iVar2=1) and the join has the copy. If instead the then arm sets `iv2c = 1` (li v1,1) and the join copies to iVar2 (`move a0,v1`) — 2 insns in the then arm, 1 at the join; target: 1 in the then arm, 1 at the join. So 1 extra.

Unless the then arm's `li v1,1` and the join's `move a0,v1` can be merged into `li a0,1` + ... no.

Hmm, what if the then arm jumps directly to the compare (skipping the join copy) and iVar2 is set by `li a0,1` directly? Then the join copy `move a0,v1` executes only on the else path. And on the then path, iVar2 = 1 and iv2c = 1 (set in the then arm).

then arm: `li a0,1; li v1,1; uVar5=0; j CMP` = 3 insns + delay.
else arm: `addiu v1,v0,1; sll; move a0,v1` — the move at the end of the else arm.
join: `li v0,1; beq v1,v0`.

Count: then arm 3 (vs target 2), so 57. Still 1 extra.

Ugh — unless the then arm's `li v1,1` is not needed because iv2c is compared and... 

Hmm, hold on! What if the compare is moved INTO the else arm and the then arm doesn't need iv2c at all? Then:
- then arm: `iVar2 = 1; uVar5 = 0; goto AFTER;` (target: li a0,1; j; move t3,zero) ✓ 2 insns + delay
- else arm: `iv2c = t+1; param_2 <<= 4; move a0,v1?; one = 1; beq v1,v0; move t3,zero`

But the target's compare is shared (at the join) — the then path jumps TO the compare (insn 27 is the join target). Actually wait: the then arm's `j 63c4` targets insn 27 (the move), which is the join. So the compare is shared. If the compare were only in the else arm, the then path would jump past it — different layout.

Hmm, but the *effect* is the same (uVar5=0 already on the then path). The generated code would differ though: the then arm's jump target would be after the compare. The target's j targets the move at 27.

So no.

Let me accept the WALL. Actually wait — let me reconsider one thing: maybe I can get the then arm to set iv2c for free using the *delay slot*. The then arm is `li a0,1; j; move t3,zero`. The delay slot holds `move t3,zero` (uVar5=0). If we set iv2c=1 in the then arm, reorg could put `li v1,1` in the delay slot and move `move t3,zero` before the j: `li a0,1; move t3,zero; j; li v1,1`. Still 3 insns + delay = 4 total vs target's 3. So 57.

OK. WALL.

Hmm, but hold on. Let me reconsider the whole thing once more. What if the copy doesn't need to be `iv2c = iVar2` — what if we make `one`'s assignment the thing that's copied? No.

Actually, let me try ONE more idea: what if we make the compare's operand a **hard register** by comparing `one` with something... 

What if `iv2c` is assigned from `iVar2` and then compared, and we make `iVar2` a HImode variable so the copy `iv2c = iVar2` is a sign-extend that cse can't equate? We'd need the compare to use iv2c and the sign-extend to fold into a plain move at combine (so no extra insns). For the fold, combine must know the range — it does. But then after folding, combine would merge the copy into the compare... 

Hmm, unless the sign-extend insn is in the same block and combine folds it into a copy AND the copy is `iv2c = iVar2` — the same as before. Yeah.

OK, final answer for this item: WALL, best 4 (w13), with the evidence "combine/cse copy-merge: the target's move is the asm's reload tie; without it cse propagates iv2c==iVar2 into the compare and combine deletes the copy (55 ins)".

Hmm, but the wall tag should be from walls.txt or a new `<pass>-<what>`. `combine-copy-merge` exists: "combine merges a reg copy the target keeps, so the pin stays (G23)". Or `cse-copy-merge`. I'll use `combine-copy-merge`.

Wait, but actually: is the best 4 or 5? The best = lowest score of a lever-free body = 4 (w13). But w13 is a different body (inverted). The WALL's best should be the best lever-free body's score. w13 is lever-free (no asm) and scores 4. So best = 4.

Hmm, but hold on: does w13 keep any kinds? It has the pins ($8/$2/$4/$3/...) which are NOT row kinds (row = launder). So w13 is lever-free w.r.t. the launder. Good.

Now, before finalizing, let me double-check the results.tsv format and the requirement "each MATCH/PARTIAL has its win.c scoring 0". For a WALL, win.c = the best lever-free body (w13). Let me set win.c = w13.c and verify its score (4). The row: result WALL, best 4, tries 30, wall combine-copy-merge, evidence ...

Hmm, wait. But there's a subtlety: the brief says "WALL (best = lowest score of a lever-free body)". So yes.

But hmm, should win.c be the best lever-free body or the original partial? For a WALL, I'll put the best lever-free body (w13) as win.c since that's the item's outcome. Actually, careful: the expert diffs orig.c -> win.c lever lines to verify PARTIAL claims. For a WALL, no verification needed. I'll put w13 as win.c (best lever-free) — that seems right.

Hmm, but is it risky? If win.c = w13 and it's not 0, that's expected for a WALL.

Actually, wait. Let me reconsider one more time whether I should keep pushing. The budget says past 30 min stop. It's 15:04 now, item started 14:43 → 21 min. Oh! Only 21 minutes! I have time. Let me use it for a couple more serious attempts.

Let me think about the cse propagation more concretely. In b1 (plain `iv2c = iVar2`), the result was 55 ins with `beq a0,v0`. Which pass did the propagation? Let me check b1's cse dump: does the compare use reg 100 (iv2c) or 77 (iVar2)?

From the w2 dump (which had the sign-extend), the compare used 100. For b1, let me dump and check. If cse propagated in b1, the compare would use 77.

Actually, in w2 the compare used 100 because the last def of 100 was the sign-extend. In b1 there's no second def, so cse would propagate.

So: cse propagation of `iv2c = iVar2` → compare uses iVar2 → then the copy is dead → deleted by cse's dead-code elimination (delete_dead_from_cse). Result 55.

To block: a second def of iv2c that survives to combine AND doesn't add an insn. Impossible?

What if the second def is in a *different* block, e.g., in the loop body's previous iteration? Like a variable that's assigned in the if-arm and also in the else-arm... 

Hmm, what about this: assign iv2c in the ELSE arm (`iv2c = iVar2;` at the end of the else arm) and in the THEN arm assign `iv2c = iVar2;` too — but with the then arm's iVar2 = 1 folded... we get the extra `li v1,1`.

Hmm, unless the then arm's assignment is written so that it's the SAME insn as `li a0,1`: e.g., if iv2c and iVar2 could be the same variable at that point... 

WAIT. What if the then arm doesn't set iv2c because iv2c is set to 1 *before* the if, and the else arm overwrites it? Like:

```
iv2c = 1;                       // before the if: li v1,1  (1 extra insn!)
if (cond) { iVar2 = 1; uVar5 = 0; }
else { ...; iVar2 = t+1; param_2 <<= 4; iv2c = iVar2; }
one = 1;
if (iv2c != one) uVar5 = 0;
```
- then path: iv2c = 1 (from before), iVar2 = 1.
- else path: iv2c = iVar2 = t+1.
Insns: `li v1,1` before the if (+1), then the else arm's copy `move v1,a0` (+1) = 57. Unless the `li v1,1` merges with something.

Hmm, but the target's then arm has `li a0,1` — and if iv2c=1 is set before the if, the then path would be `li v1,1` + `li a0,1`.

No.

OK — what about assigning iv2c = iVar2 at the *join* but with a second def that's *dead but not deleted before cse*? E.g., after the compare: `iv2c = iv2c;` — launder (self-assign). Forbidden? It's an identity statement — "identity-statement launders ... do NOT count as a crack". Right.

What about `iv2c = iVar2; ... if (iv2c != one) uVar5 = 0; ... iv2c = 0;` (a real set, dead at the end)? That's a dead store — flow deletes it (flow runs after cse2, before combine). But cse1 runs BEFORE flow: cse1 sees the second def and doesn't propagate to the compare? Hmm, cse1's reg_eqv: a later def of iv2c invalidates the equivalence AFTER that def, but the compare is BEFORE the second def. So cse1 would still propagate the copy to the compare.

Hmm, in w2, the sign-extend chain's def of reg 100 came BEFORE the compare, so it invalidated.

So we need a def of iv2c between the copy and the compare that doesn't add an instruction.

The sign-extend chain was exactly that but combine folded it.

What if the between-def is a computation that combine can't fold and that is *needed*? The only value needed is iVar2 itself.

Hmm! What about: `iv2c = iVar2; iv2c = iv2c | (iVar2 & 0);` — identity.

What about `iv2c = iVar2; if (iv2c != iVar2) ...`? no.

OK, here's a REAL idea: make the second def a *conditional* one that flow keeps and that costs nothing because it's in an existing branch. Hmm.

Actually — what about this: the value iv2c could be defined in the THEN arm as 1 and in the ELSE arm as iVar2, and the join compare uses iv2c. That's w9 (57). The extra insn is `li v1,1` in the then arm.

Can we avoid it by making the then arm's iv2c = iVar2 *after* iVar2 = 1, where the copy folds into the constant? `li v1,1` — still an insn.

Unless... the then arm's `iVar2 = 1` could be *replaced* by `iv2c = 1; iVar2 = iv2c;`? That's `li v1,1; move a0,v1` — combine folds `move a0,v1` with the constant → `li a0,1`. So we'd get `li v1,1; li a0,1` = 2 insns. Same.

Hmm.

OK, what if the then arm's value is NOT a constant? It is (1).

Alright, let me try one more experiment: what if the copy is placed at the join and iv2c gets a second def from a *loop-carried* perspective — e.g., iv2c declared outside the loop and assigned at the top of the loop body before the if? Then on each iteration... the value would be stale for the then path.

Hmm.

Let me try yet another thing: maybe use `uVar5` as the copy destination trick... no.

Let me now consider: maybe the *sched* difference matters more. In the target, the store `sw v0,-4(t0)` is at 39 with the do-while keepalive. Our w13 has 56 ins and score 4 — the diff shows only the register differences at 21, 25, 27, 29. So the rest matches.

If I could get iv2c into v1... 

In w13, iv2c = v0. Why? Because iv2c's live range ends at the compare (which was rewritten to a0), so v0 was free... Actually, local-alloc assigns registers per block; iv2c is used in the else arm (born there) and the join. Hmm.

What if I add a second use of iv2c after the compare (in the store expression) — then iv2c stays live and can't take v0 (one's reg)? Then iv2c → v1, and the compare... cse would still propagate to iVar2. Hmm, but with iv2c live after, cse's propagation would make the compare use iVar2 and keep iv2c's def... 

Honestly, let me just test one: w13 + `r = (uint)((iVar2 & 0) | (iv2c << 3)) | c6b;` — no, that adds an andi.

What about `r = (uint)(iv2c << 3) | c6b;` in w13 (iVar2 dies at the copy → coalesce). Tested in w11 (different base) = 20.

OK. Let me take stock: 21 minutes spent, 30 tries. The evidence strongly supports a WALL. Let me record it.

Hmm, actually, hold on. Let me reconsider the problem from scratch one final time, because there might be a much simpler trick I'm missing: what about making the copy `iv2c = iVar2` where `iVar2` is a **struct field** or where the copy goes through **an existing pinned variable**?

Look at the pinned variables in scope at that point: `six` ($2), `m` ($2), `c74` ($4), `c3` ($3), `one` ($2). All $2-$4.

What if the copy's destination were `c74` or `c3`? Those are uint variables pinned to $4/$3, assigned in the loop body earlier. If we reuse `c3` ($3 = v1!) for the copy... 

WAIT. `c3` is pinned to $3 = v1! And the target's move is `move v1,a0` — v1! What if `iv2c` were `c3`? That's a pin though (c3 already exists, and it's a pin lever of an existing kind — allowed to stay!).

The rules: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin ... ; no new lever of any kind." The row kind is `launder`. Pins already exist and may stay. But *using an existing pinned variable for the copy* — is that "adding a lever"? The pin already exists; assigning a new value to it is using it. Hmm, that's a gray area: the pin's *purpose* in the original body is `c3 = 0x3000000` for the `m | c3` store. Reusing c3 for the copy would be a NEW use of the pin as a lever — arguably adding a lever (the pin now steers a different value).

Hmm. But is it? The brief says "levers of other kinds the def already had (pins under other causes) may stay, never added". Using an existing pin for a new purpose = adding a lever use. I'd say it's not allowed... but let me consider: the kinds file lists what must be removed. The expert diffs orig.c → win.c lever lines. If I add a new assignment to a pinned variable, that's not a new pin declaration — it's using an existing variable. The diff would show a new statement `c3 = iVar2;`.

Risky. The intent of the task is "real C moves only". Reusing a pinned variable to steer a register is effectively a register-steer lever (the pin's $3 is doing the work). I should avoid it.

Hmm, but wait: `c3` is a `uint` pinned to $3. It's assigned `c3 = 0x3000000` and used in `*p1 = m | c3`. If I wrote `c3 = iVar2;` and compared `if (c3 != one)`, the pin would force c3 into v1 — exactly the target's iv2c register! And the copy `c3 = iVar2` would... cse would still equate c3 with iVar2? c3 is a hard register ($3) — cse does NOT propagate across hard registers in the same way; in fact, a hard register can't be copy-propagated (the value lives in a fixed reg). Actually cse can record reg_eqv for hard regs too... but a hard register assignment is a real insn (`move v1,a0`) that can't be deleted unless all uses are replaced — and uses of a hard reg can be replaced by cse's fold_rtx.

Hmm, but there's a catch: `c3` is used earlier in the loop body for the store; reusing it later for iv2c is fine.

But this feels like using a pin as a lever — exactly what the task forbids ("no new lever of any kind"). The pin $3 exists "under another cause" (the store's constant), but using it to steer iv2c is a new lever use.

Hmm. However — consider: the target's v1 assignment for iv2c comes naturally from the allocator. Using c3 would be cheating the intent.

I'll avoid it. Actually... hmm, let me reconsider. The task's aim is to find *real C* that makes the compiler produce the target code. Reusing a variable that happens to be pinned is not real C — it's a pin lever. Skip.

Let me check the time: 15:05. 22 min. OK.

Let me do a couple more serious attempts with a different idea: **the `do-while` block split at cse1 might actually work if the do-while body contains a store** (as in the C0535 second use: `do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0);`). Maybe the split only survives when the body has a memory op (which cse can't move across). Hmm.

Our copy is a pure register op.

What if the do-while body contains the copy AND a store that's already there? E.g., wrap `iv2c = iVar2;` together with the following `puVar3[-1] = uVar1;`? No, that store comes after the compare.

Hmm.

Let me try ONE more: maybe the *header* includers differ — the item must score 0 on all 141 includers, but maybe on some includer the code differs. No.

OK, decision: WALL. Let me write the results row.

Actually, wait. Let me reconsider the score-4 body (w13) once more: the diff was `v0->a0 x3, a0->v1 x2`. What if I tweak the declaration order or use a temp to shift the allocation? E.g., in w13, iv2c=v0 because... Let me try a couple of variants of w13 with different declaration order (iv2c declared before/after other vars) — cheap shots at the register bank.

Actually, in w13, the compare uses a0 (iVar2) — the register difference is not just an allocation preference; the code shape differs (`move a0,v0` vs `move v1,a0`). Even if the registers flipped, the direction would still be wrong (iVar2 = iv2c vs iv2c = iVar2).

Unless the allocator gives iv2c=a0 and iVar2=v1: then `move v1,a0` ✓ (iVar2 = iv2c → v1 = a0) and the compare uses... a0 (iv2c after substitution? the compare was rewritten to iVar2 = v1). Hmm: if the compare uses iVar2 = v1, that's `beq v1,v0` ✓!!! 

Wait! In w13, the compare was rewritten to use iVar2 (a0). If instead iVar2 were allocated v1 and iv2c a0, the compare would be `beq v1,v0` ✓ and the copy `move v1,a0` ✓ (iVar2 = iv2c, i.e., v1 = a0) ✓ — EXACTLY the target!

So w13 with the registers swapped would be a MATCH! The current allocation: iv2c = v0, iVar2 = a0. We need iv2c = a0, iVar2 = v1.

Hmm, and `one` = v0.

In w13, the else arm computes `addiu v0,v0,1` → iv2c in v0; the join `move a0,v0` → iVar2 in a0; compare `beq a0,v0`.

Target: else arm `addiu a0,v0,1` → iVar2 (source) in a0; join `move v1,a0` → iv2c in v1; compare `beq v1,v0`.

So the target's value is born in a0 (iVar2) and copied to v1 (iv2c). In w13 the value is born in v0 (iv2c) and copied to a0 (iVar2).

To match, I need iv2c to take v1 and iVar2 a0, with the copy direction iv2c = iVar2... but w13's C is iVar2 = iv2c. For the emitted instruction to be `move v1,a0` (dest v1 = iv2c, src a0 = iVar2), the C must be `iv2c = iVar2` with iv2c in v1 and iVar2 in a0 — the ORIGINAL direction!

So back to the original direction. The problem: cse propagates and kills the copy.

BUT: w13 showed that when the copy's dest (iVar2) is live after, the copy survives. In the original direction, the dest iv2c is dead after the compare → the copy is deleted.

So: make iv2c live after the compare (a second use) AND keep cse from propagating... cse propagation would rewrite the compare's operand to iVar2 regardless.

Hmm, in w13 the compare was rewritten (to iVar2) because cse/combine propagated. In the original direction with iv2c live after, the same propagation would rewrite the compare to iVar2 → `beq a0,v0` (wrong) while the copy `move v1,a0` stays (right). Score would be like 4 but with a different pattern.

Hmm. So we need to block the propagation itself.

Let me test the original direction + a second use of iv2c to see what happens. If cse propagates, we get `move v1,a0; beq a0,v0`. Not matching.

OK so the propagation must be blocked. The propagation is cse's (or combine's). Let me determine which by checking b1's cse dump: if after cse the compare uses iVar2, it's cse.

Let me check quickly.
