---
ts: 2026-10-22T00:03:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rAeXfHwRPlUqnyqHYngu
---
Same as v2. The `addiu a1,s0,36` keeps landing in the delay slot.

Observation: in ALL my variants, `addiu a1,s0,36` goes into the delay slot. In the target, the delay slot has the `sb`.

What if the `addiu a1,s0,36` were NOT delay-slot eligible? E.g. if it were a 2-insn sequence. Per the other function's comment: "a 2-insn macro is delay-slot-ineligible, so reorg falls through to the else thread".

The a1 arg is `(s32)((u8 *)ent + 0x24)` = ent + 36. To make it 2 insns, hmm: `ent + 0x24` is 1 insn (addiu). What if it were `(u8 *)ent + 0x24 + 0`? same.

Hmm! But wait — in the FIRST branch, the same expression `addiu a1,s0,36` appears at 17 (NOT in the delay slot) — and the first branch's delay slot holds the `sw`. So in the first branch, the addiu a1 was NOT chosen for the delay slot, even though it's the same insn!

So the delay-slot choice differs between the two branches. In the first branch, the delay slot = the `sw` (the last statement's store). In the else branch, the target's delay slot = the `sb`.

And in MY else branch, the delay slot = the `addiu a1`.

Hmm! So in mine, the `sb` was scheduled early (before the call) so it couldn't be the delay-slot filler; the `addiu a1` was left over.

In the target, the `sb` was the LAST insn before the call (so it became the delay slot) and the `addiu a1` was scheduled early.

So the difference: in the target, the arg setup was scheduled EARLY (at the top of the block, insns 16-19) and the store LATE.

In the first branch of the target, the same pattern: the arg setup at 16-19 (the top) and the stores after (20-28) with the last in the delay slot.

So in BOTH target branches, the arg setup is at the TOP of the block. In my else branch, it's not.

The first branch (unchanged in my candidates) DOES have the arg setup at the top. So gcc CAN do it. What's different in the else branch?

The else branch's call is `func_80128EA8(q, p, e)` where q is PINNED to $4 (a0). Hmm! The pin means a0 = q is a pinned copy... and the `move a0,s1` is the q = sub assignment.

Hmm, so in the else branch, a0's setup is tied to the pin.

Hmm, what if the pin on q is the problem? The pin is a lever of ANOTHER kind (the row kind is only "launder"), so the pin must STAY (the def already had it). Hmm, but "levers of other kinds the def already had (pins under other causes) may stay, never added". So the pin stays. OK.

Hmm, so the difference must be elsewhere. Let me compare the first branch and the else branch in the target:
- First branch: the call's args are (sub, (u8*)ent+0x24, (s32)D_800D3888) — EXPRESSIONS.
- Else branch: the args are (q, p, e) — VARIABLES.

In the target's else branch, the arg setup at 16-19 = `move a0,s1`, `addiu a1,s0,36`, `lui a2`, `addiu a2,a2,0`. Hmm, if the args were expressions, a0 = sub → no move needed (sub is in s1) → hmm, but the target HAS `move a0,s1`.

Hmm! So a0 = a MOVE. If the arg were `sub` (a variable in s1), gcc would set a0 = s1 (a1 reg copy) — hmm, that IS a move! `move a0,s1` — gcc copies the variable into the arg reg. So a0 = sub could be `move a0,s1` ✓ (a copy of the variable into a0).

Hmm! So the arg could be `sub` (not q). But the pin on q forces q into $4 = a0, and `q = sub` → `move a0,s1` — the same insn!

So both spellings give `move a0,s1`. But with the pin, `q = sub` is forced into $4.

OK so let me try: pass `sub` directly as the first arg (and drop q... but q is pinned and used by the store). Hmm, q is used by the store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` → the store's base is q = a0.

So: `func_80128EA8(sub, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);` and the store via q. Then a0 = sub → `move a0,s1`? Hmm, but q (pinned $4) is also $4 = a0 — conflict! The pin forces q into $4, and the call wants a0 in $4. If the store's base is q ($4) and the call's first arg is sub (in s1), then a0 = sub → `move a0,s1` — but that would clobber q ($4)! Hmm, q's value is needed for the store (which happens after/before the call).

Hmm, in the target, the store `sb v0,39(a0)` uses a0 — so q IS a0 ✓. So the call's first arg is q ✓ (the pin is consistent).

OK. So the args are (q, p, e) and a0 = q = $4.

Hmm, so the difference between the branches for the arg setup hoisting: the first branch's args are expressions, the else's are variables. And in the TARGET's else branch the arg setup IS hoisted. So variables CAN be hoisted.

Hmm, so why not in mine? Because in mine, the assignment `p = (s32)((u8 *)ent + 0x24);` — hmm, if p is allocated to a1, then the assignment becomes `addiu a1,s0,36` ✓ and it would be at the assignment's position (early) ✓. So mine should have it early too... unless p was NOT allocated to a1 and instead the copy to a1 happened at the call.

In mine, the delay slot has `addiu a1,s0,36` — so a1 = the value computed AT THE CALL. So p was a temp and the call copied it.

So the difference: in the target, p (and e) were allocated to a1/a2 (the "call arg reg" allocation); in mine, they weren't.

WHY? local-alloc's decision to allocate a variable to a call's arg register happens when the variable is ONLY used at that call and the reg is free. In mine, maybe a1/a2 were already taken (by other live values) at that point.

Hmm! What's live in the else branch? The `ent` pin ($16 = s0), q ($4), sub (s1), hw, r. And the call's args need a0-a3. Hmm, a1/a2 should be free.

Hmm, hmm. OR: the difference is that in mine, the LAUNDER-FREE body has the assignments p/e as separate statements, and gcc's local-alloc sees p's live range as [assignment, call] — it could be allocated to a1. Hmm.

Hmm, hold on! Maybe the difference is the ORDER of the p/e assignments relative to the call, and gcc's "call arg setup" is emitted by expand at the call. In the target, the arg setup insns are at the TOP of the block (16-19) — before the store (40-42). For the arg setup to be at the top, the SCHEDULER must have moved it there. sched2 can move insns earlier within a block if there are no dependencies. The arg setup (a1 = p's value) depends on p's assignment; the store doesn't depend on the arg setup.

So why would the scheduler move the arg setup to the top in the target but not in mine? Because of the LUID tie-break: the arg setup's LUID must be lower than the store's LUID. The arg setup's LUID = the call's LUID (if generated at the call) → higher than the store's ✗.

=> In the TARGET, the arg setup's LUID is LOWER than the store's → so the arg setup was generated BEFORE the store → the arg setup came from the ASSIGNMENTS p = ..., e = ... (which are before the store in the source) → p and e were allocated to a1/a2.

So in the target, p → a1 and e → a2. In mine, they weren't.

Why? Hmm! Because in mine, the `q = sub` assignment (pinned to $4) and the ORDER of the local declarations/allocnos! local-alloc's decision to put a variable in a call's arg reg: it's `global.c`'s "hard reg" allocation for the pseudo with a "call arg" preference.

Hmm, hmm. What if the difference is that in mine, p and e are assigned but the call is the FIRST use and gcc's expand emits the arg setup at the call...

Honestly, let me try the concrete experiment: what if the p and e assignments are REMOVED and the expressions are passed directly (v3, tried → same) — hmm, that should have given the arg setup at the call.

Hmm, v3 gave the same as v1. Hmm!

So in v3 (expression args), the arg setup was still late. Hmm! But in the FIRST branch (expression args), the arg setup is early ✓.

So the difference between the two branches is NOT the arg form. It's something else!

What's different about the else branch?
1. The pin on q ($4).
2. The store is a single statement (vs 4 in the first branch).
3. The block ends with `hw = 0x1C;` after the call.
4. The first call in the else branch is `func_8001CC3C(sub, (s32)D_801817A4, 0, 0)`.

Hmm, #4: the else branch has TWO calls (8001CC3C and 80128EA8), the first branch also has two (8001CC3C and 80128EA8) ✓ same.

#1: the pin. Hmm! The pin on q ($4 = a0): the pinned register is a0, and the call's first arg is a0. Hmm.

Let me test: remove the pin on q (use a plain local) and see if the arg setup gets hoisted. If yes, the pin is the culprit — but the pin must stay (it's a different row's kind, and "levers of other kinds the def already had may stay" — MAY stay, not MUST). Hmm, if removing the pin gives score 0 with no launder, that'd be a MATCH with the pin removed... but the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added" — removing an existing pin is not "adding" one, so removing it is allowed? Hmm, "Lever-free = none of the row kinds in <dir>/kinds remain" — the row kind is only `launder`. The pin is a different kind (a different row). So the pin may stay. Removing it would change the function's other rows' state... Hmm, the pin has its own row ("missing-parameter(pin $16)"). If I remove the pin, that other row's lever would be gone — that's not my row's business, but removing it might break that row's expectations. Risky. And the target clearly has the pin's effect (s0 = ent, a0 = q).

Hmm, but actually, the target has `move s0,a0` (insn 2) = the pin's effect ✓ and `move a0,s1` = q = sub ✓.

Let me test whether the pin is the culprit (as a diagnostic): remove the q pin and score. If the score becomes 0, then... hmm, but then I'd be removing a lever of another row. Hmm, but the pin might not be needed at all (the row for the pin might be a "missing parameter" row — the brief says the pin is under another cause and may stay).

Hmm, let me not remove the pin. Let me instead try to move the pin's declaration or other dials.

Let me try: what if the `q = sub;` assignment is placed differently, or the `q` declaration is moved? Hmm.

Let me try a quick diagnostic: keep the pin but make the store use `sub` instead of `q`:
```
        q = sub;
        ((Unkstruct_800B5CB8 *)sub)->unk27 = 0x33;
        func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
```
Hmm, the store's base would be sub (s1) → `sb v0,39(s1)` ✗ (the target has sb v0,39(a0)).

Hmm.

OK, time. Let me try ONE more thing for this item: the "3-qty sort bug" dial — add a quantity to the else branch's block. E.g., declare a dummy local... hmm, "no new features" but a scratch C variable is a legit dial (decl count). Hmm, but it would be dead code (refused).

Hmm. Alternatively, the ORDER dial: the residual class is "ORDER" and the doc says: "ORDER → the block wrap and the adjacent swap (R17, R18, R20, R21, R9, R7, R13, R3, R16, R6, R8, R5, R12, R14, R10, R15, R2, R4, R22, R23, R24, R26, R44, R45)".

R42 is "a statement moved several positions down its block" (from the C0505 catalog). Hmm, R42 is in the ORDER families? The list includes R9 (the run-split) and R17/R18.

I've tried moving the store before/after the call. Let me try moving the `q = sub` assignment to a different position, and moving the `hw` assignment.

Hmm, actually — hold on! What about the `hw = 0x1C;` AFTER the call? In the target, the else's tail: after the jal at 41, the insns 43+ are the rand() part. Hmm, the `hw` value (0x1C) is stored at the end: `*(u16 *)((u8 *)ent + 0x1A) = hw;`. The target: 43 `li v0,28` (0x1C) ... 45 `sh v0,26(s0)`. Hmm, `li v0,28` = 0x1C ✓ — so `hw` was folded into the store (the constant propagated) → `sh v0,26(s0)` at 45. Hmm, but the source has `*(u16 *)((u8 *)ent + 0x1A) = hw;` and hw = 0x1C. And the target has `sh v0,26(s0)` at 45 — hmm, 26 = 0x1A ✓.

OK.

So the else branch's residual is 4 insns of ordering. Let me try ONE more variant: what if the `hw` assignment is moved BEFORE the call (so the block has a different shape)? Hmm, that changes the semantics (hw is used after the call) — no, hw is used after, so moving it earlier is fine semantically.

Let me try:
```
    } else {
        register s32 q __asm__("$4");
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        hw = 0x1C;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
    }
```
Hmm, the `li v0,28` would then be scheduled early... the target has `li v0,28` at 43 (after the call). Hmm ✗.

OK, let me try the OTHER item shapes and come back if time permits. Actually, let me try one more clever thing for this item: the ORDER class's "block wrap" (R15?) hmm.

Hmm, let me think about the actual scheduler mechanism once more. The target's else block:
```
30 li v0,44          <- hw = 0x2C? no... hmm, li v0,44 = 0x2C. Hmm! In the else branch, hw = 0x1C. Hmm, 44 = 0x2C. Hmm!
```
Wait: insn 30 is `li v0,44` = 0x2C, which is the FIRST branch's hw value (0x2C)! Hmm, but the else branch's hw is 0x1C = 28, and the target has `li v0,28` at 43.

Hmm! So insn 30 `li v0,44` (0x2C) is in the else branch?! That's the if-branch's value. Hmm, that's the "cross-jump" duplication: the `hw` value is computed in both arms and merged. Hmm, `li v0,44` at insn 30 is before the second call (31-35). Hmm, weird.

Hmm, insn 30 `li v0,44` — hmm. Hmm, and 43 `li v0,28`. So there are two `li` constants. 0x2C = 44 and 0x1C = 28. Hmm, so the if-branch's hw = 0x2C is materialized at insn 30 (in the else branch?!) — that's the cross-jump merge: the value 0x2C is computed in the if-branch (which ends at insn 28-29) and... hmm, insn 29 is `j 2cb4` (the jump to the tail) and insn 30 is `li v0,44` — that's the ELSE branch's start (the target of the bnez at 7 → 2c80, hmm).

Hmm, the bnez at insn 7 goes to 2c80 (the else branch) and the fall-through is the if-branch (insns 8-29). So insn 30 = the else branch's start. And `li v0,44` (0x2C) at insn 30?! In the ELSE branch, hw = 0x1C. Hmm, so why 0x2C?

OH! Because of the "cross-jump merge": the `hw` variable is set in both arms to different values; gcc's cross-jump optimization (jump.c's cross_jump) merges the two arms' tails. The if-arm ends with `j 2cb4` (insn 29) → the tail. Hmm, and the else arm's `hw = 0x1C` (li v0,28 at 43) → the same tail.

Hmm, so the if-arm's `li v0,44` (0x2C) should be in the if-arm (insns 8-29): hmm, I see `li v0,156` (0x9C) at 20. Hmm, where's the 0x2C (hw = 0x2C in the if-arm)? It should be a `li v0,44` in the if-arm. But insn 30 (the else arm's start) has `li v0,44`.

Hmm, that's odd. Unless the if-arm's `li v0,44` was moved... Hmm, the if-arm is 8..29 and the else-arm is 30..56. The `li v0,44` at 30 is in the else arm. Hmm, so the if-arm's hw = 0x2C is... hmm.

Ohh, I bet the `hw` variable is register-allocated: the if-arm sets hw (v0 = 44) and the else-arm sets hw (v0 = 28), and the merged tail uses v0. But the if-arm's `li v0,44` should be inside the if-arm (before the `j 2cb4` at 29). Hmm, but the target shows the `j 2cb4` at 29 and `li v0,44` at 30. So the `li v0,44` is AFTER the jump — i.e., in the else-arm's block but belonging to the if-arm's value?!

Hmm, that means the target's if-arm does NOT set hw = 0x2C; instead the `li v0,44` at 30 is shared?! Hmm, but the else-arm sets hw = 0x1C at 43.

Hmm, wait: maybe the block layout is: the if-arm is 8..30 (ending with `li v0,44` at 30 and the `j 2cb4` at 29?? no, the j is at 29).

Hmm, insn 29 `j 2cb4` and insn 30 `li v0,44`. A `j` has a delay slot! The delay slot of the j at 29 is insn 30 = `li v0,44` ✓✓✓. So the if-arm's hw = 0x2C is in the delay slot of the jump to the tail ✓.

OK. So the if-arm's structure: ..., `li v0,44` (the delay slot of the j), and the else-arm: ..., `li v0,28` at 43, `sh v0,26(s0)` at 45.

Hmm, and in the else-arm, the `li v0,28` (hw = 0x1C) is at 43 — AFTER the second call (41). And in the if-arm, the `li v0,44` is at 30 (before the tail).

Fine, that's all consistent with the source.

OK. I need to wrap up this item. Let me try ONE more variant for the else branch: what if the source's else branch has the store BEFORE the q/p/e assignments? I.e.:
```
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        ((Unkstruct_800B5CB8 *)sub)->unk27 = 0x33;   /* the store via sub, before q */
        q = sub;
        p = ...;
        e = ...;
        func_80128EA8(q, p, e);
```
Hmm, the store's base would be sub (s1) → `sb v0,39(s1)` ✗.

Hmm.

What about making the `q = sub` assignment LATER so that a0 is set up at the call? Hmm, a0 = q = $4 — the pin means q is in $4 always. So `q = sub` → `move a0,s1` and the call's a0 = q (already in a0) → no copy ✓. So the `move a0,s1` is the q assignment ✓ and its LUID is early ✓ (the target has it at 16 — the 2nd insn of the else arm, right after the first call ✓✓).

Hmm! So in the target, the else arm's order is: [the first call's setup] 31-35, then `move a0,s1` (16?? no — the target's insn 16 is in the IF arm!).

Hold on. Let me re-read the target listing for the else arm:
```
29 j 2cb4
30 li v0,44
31 lui a1,0x0 ; HI16 D_801817A4
32 addiu a1,a1,0
33 move a2,zero
34 jal func_8001CC3C
35 move a3,zero
36 move a0,s1
37 addiu a1,s0,36
38 lui a2,0x0 ; HI16 D_801817B0
39 addiu a2,a2,0
40 li v0,51
41 jal func_80128EA8
42 sb v0,39(a0)
43 li v0,28
44 jal rand
45 sh v0,26(s0)
```
So the else arm = insns 31..45(+). And the `li v0,44` at 30 is the delay slot of the if-arm's j at 29 ✓.

So the else arm: the first call (8001CC3C) at 34 with its args at 31-33 (+ the delay slot 35), then the second call's args at 36-39, then `li v0,51` (40), the jal (41), the sb (42, delay), then `li v0,28` (43) = hw = 0x1C, then rand.

So the else arm's arg setup for the second call (36-39) is at the TOP of the arm ✓ (right after the first call) and the store (40-42) is at the END ✓.

So the source order (by LUID): [the first call], [the second call's arg setup], [the store], [the second call]. Hmm, the second call's arg setup before the store — so the arg setup's LUID < the store's LUID.

If the args are variables p, e assigned before the store, the arg setup (the copies to a1/a2) would be generated at the call (after the store) ✗. So in the target, the arg setup was generated by the ASSIGNMENTS (p → a1, e → a2 directly).

So I need p and e to be allocated to a1 and a2. In mine they aren't.

WHY? Because in mine, the call `func_80128EA8(q, p, e)` → expand generates: a0 = q, a1 = p, a2 = e as COPIES (p and e are separate pseudos). For p to BE a1, gcc's local-alloc must have allocated p to a1 — but the copy at the call means p is a separate pseudo copied into a1.

Hmm! In gcc, the call's arg setup is emitted by expand as: `a1 = p` where p is a pseudo. Then local-alloc can COALESCE the copy (a1 = p) — i.e., assign p to the reg a1 directly! gcc's local-alloc does this ("the copy to a hard reg is coalesced"): the pseudo p is assigned to a1 and the copy disappears.

So the coalescing of "p → a1" depends on the register availability at that point. In mine, a1/a2 were not free at the copy point (maybe because of the live ranges of other values), so p got a different reg and the copy remained.

Hmm! What could make a1/a2 free? The `ent` pin is $16 (s0), q is $4 (a0), sub is s1. Hmm.

Hmm, what if the issue is that the call's arg setup copies are generated at the CALL, and local-alloc's coalescing happens... hmm.

Hmm, let me look at the target's if-arm: the arg setup (16-19) is at the top of the arm, and the arm's statements (20-28) come after. So in the if-arm, the arg setup was ALSO generated at the call (the call is the last statement) and yet it was scheduled at the top. So the SCHEDULER moved it to the top! (sched2 moves the arg setup early — it's the classic "call setup at the top of the block" that gcc does to avoid the call clobbering the arg regs.)

Hmm! So in the if-arm, the arg setup was moved to the top by the scheduler. In the else-arm (target), the same. In mine (else-arm), the arg setup was NOT moved to the top.

Why not? sched2 moves insns earlier if it reduces the "pressure" or if the insn's priority is higher. Hmm.

Hmm, in the if-arm the arg setup is 4 insns (move a0,s1; addiu a1,s0,36; lui a2; addiu a2) and the statements are 4 stores. In the else-arm (target) the same arg setup + 1 store.

In mine (else arm), the arg setup was: move a0,s1 (36), lui a2 (37), addiu a2 (38), and the addiu a1 in the delay slot. Hmm! So the a1 setup was separated from the others. Hmm, that's odd: gcc moved a0 and a2 up but left a1 for the delay slot.

Hmm, so gcc's scheduler moved `move a0,s1` and the a2 pair up but not the a1 pair. Why? Because the a1 pair (addiu a1,s0,36) is a 2-insn macro?? no, it's 1 insn. Hmm, because a1 was busy? Hmm, a1 is the 2nd arg; the call at 41 uses a0,a1,a2,a3.

Hmm, hmm. In the target, the a1 setup is at 17 (the 2nd insn of the arm).

Hmm, what if in the target the arg setup was NOT moved by the scheduler but generated early because the args were expressions and the CALL was... hmm, in the if-arm the call is the last statement and the args are expressions → expand generates the setup at the call → the scheduler moved it to the top.

Hmm, so in mine's else-arm, why didn't the scheduler move the a1 setup up? Because... hmm, maybe because the store (which uses a0) was scheduled early and the a1 setup... no dependency.

OK — I've got to stop. Let me try a couple of blind variations (cheap) and then move on:

v5: swap the order of the p and e assignments vs q:
```
        p = (s32)((u8 *)ent + 0x24);
        e = (s32)D_801817B0;
        q = sub;
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
        func_80128EA8(q, p, e);
```
v6: the store with an explicit temp value:
```
        s32 t = 0x33;
        ((Unkstruct_800B5CB8 *)q)->unk27 = t;
```

Let me test v5 and v6. If neither works, record the WALL for this item (score 4) and move on to the last two items.

Hmm, actually, hold on. Let me reconsider the problem completely: the residual is 4 insns of ORDER. What if the issue is that in the target, the else-arm's SECOND call has its arg setup at the top because the FIRST call (8001CC3C) is in the same block and its arg setup (31-33) is at the top... and the second call's arg setup (36-39) comes right after the first call. Hmm, in mine: the first call's setup at 31-35? Let me check my v1's output: the diff showed no differences before insn 37, so mine[0..36] == target[0..36] ✓. So mine's first call setup is identical ✓ and mine[36] = `move a0,s1` ✓ (the target's 36 = `move a0,s1` ✓).

Then mine[37] = `li v0,51` vs the target's 37 = `addiu a1,s0,36`.

So the ONLY difference: the target has the a1 setup at 37 and the `li v0,51` at 40; mine has the `li v0,51` at 37 and the a1 setup in the delay slot (42).

So mine: the a1 setup is scheduled LATE; the target: EARLY.

Since the a1 setup is `addiu a1,s0,36` — an ALU op with no dependency except s0. Hmm.

In the if-arm, the target has the same `addiu a1,s0,36` at 17 (early, right after `move a0,s1` at 16) ✓. And in my if-arm (unchanged), the same ✓ — so in the if-arm, gcc schedules the a1 setup early. But in the else-arm, gcc schedules it late.

What's different?! The if-arm's arg setup: a0 = sub (s1), a1 = ent+36, a2 = &D_800D3888. The else-arm's: a0 = q ($4), a1 = ent+36, a2 = &D_801817B0.

The only difference: a0 = q (a PINNED reg, $4) vs a0 = sub (a copy).

Hmm! The pin! With the pin, q is in $4 = a0. The store `sb v0,39(a0)` uses a0. And the call's a0 = q = a0 ✓ (no copy).

Hmm, in the if-arm, the store `sb v0,39(a0)` also uses a0 (a0 = sub = s1) ✓ — the same shape!

Hmm, so both arms have a store to a0+0x27.

OK, the difference must be the number of statements/the block structure. Hmm, and the else-arm has a PINNED variable (q) whose reg is $4 = a0 — the pinned reg might constrain the scheduler (a pinned reg can't be clobbered, so the scheduler is more constrained).

Hmm! What if I remove the pin on q? Let me test it as a DIAGNOSTIC (v7): replace `register s32 q __asm__("$4")` with a plain local. If the score drops to 0, then the pin is the culprit — and then I'd have to decide whether removing it is allowed. The brief says the row kind is `launder`; the pin belongs to another row ("missing-parameter(pin $4-$7)"? Hmm, actually for this function the pin is $16 (ent) and $4 (q)). Removing a pin that the def has... the brief says levers of other kinds the def already had "may stay" — MAY. So removing them isn't forbidden per se, but it would change the state of the other rows (which is the expert's business). Hmm. And a "MATCH" requires the kinds in <dir>/kinds to be gone — the launder is the only kind. So removing the pin would still be a MATCH by the letter of the rule.

Hmm, but that would be "removing another row's lever" — the expert might object. Hmm. But it's a legitimate C change (removing a fake pin) — and the target's codegen would be checked. If the score is 0 without the pin, the pin was unnecessary, and removing it is a CLEANUP (like the completed item 1 did: "launder+pin both gone"! — in item 1, the agent removed BOTH the launder and the pin and the result was MATCH, with the note "pin $4 (row kind for this item is launder only; the pin row is a separate missing-parameter(pin $4-$7) residue row)").

So removing a pin is acceptable (item 1 did exactly that).

So let me test v7: no pins at all (ent and q unpinned) + no launder. If the score is 0 → MATCH!

But careful: the pin on `ent` ($16 = s0) — the target has `move s0,a0` (insn 2), which is the pin's effect! Without the pin, `ent = a0` would be a copy into a different reg (or a0 itself). The target's `move s0,a0` means ent is in s0. Without the pin, gcc would allocate ent to some reg — maybe s0 anyway (it's live across calls). Hmm! Since ent is live across calls, it must be in an $s reg → s0 probably ✓. So the pin might be unnecessary!

Similarly, q pinned to $4 (a0): the target has `move a0,s1` (q = sub). Without the pin, q would be allocated... q is used for the store (before the call) — hmm, and as the call's first arg. If q is unpinned, gcc might allocate q to s2 or a temp.

Let me test v7: no pins, no launder:
```
void func_8017DA30(s32 a0) {
    s32 ent;
    s32 sub;
    s32 hw;
    u32 r;

    ent = a0;
    ...
```
Let me try. This is promising! Because the pins constrain the scheduler (a pinned $4 = a0 might block the scheduler's freedom to move the a1 setup).

Let me write v7 with both pins removed.
