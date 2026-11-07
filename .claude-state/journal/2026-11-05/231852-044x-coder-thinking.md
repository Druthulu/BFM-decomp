---
ts: 2026-11-06T06:18:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4fGV9brJPP1JafIOak4H
---
Not the do-while one; RM1 version may have it. Let me check RM1's win.c... Actually line 219 says "the copy wrapped in do-while(0)". Let me check the RM1 dir.

Actually, time. Let me think differently.

Key insight attempt: combine folds (set otz v0) + (set a0 otz) when otz is dead. To keep otz's set, otz must have a use between. What if the *argument* expression is `otz` but the call also has another use of otz in a *foldable* position, e.g.:

`otz = func_801823D4(otz, -0x1A);` 

what about `func_801823D4(otz, -0x1A)` written as `func_801823D4(otz, otz * 0 - 0x1A)`? tree folds (otz*0=0).

Hmm what about `func_801823D4(otz, (otz & 0) - 0x1A)`? folds.

Front-end folding is aggressive on constants.

What if the second argument is `-0x1A` but written as `i - i - 0x1A`? folds? Not necessarily if i is a variable — gcc's fold does simplify x - x to 0. Yes.

What about `(s32)(-0x1A + (otz != otz))`? A comparison creates a setcc; at RTL that's a comparison insn — extra.

OK, what about making otz's first value used by the *loop's* `if (i != 11)` test? no.

New angle: maybe we can avoid the issue by making the first call's result not go through otz at all: what if the target's `move s1,v0` corresponds to a *different* structure? Look at target:
```
301c: move s1,v0      (otz = RotTransPers4(...))
3020: move a0,s1      (arg)
3024: jal func_801823D4
3028: li a1,-26
302c: move s1,v0      (otz = func_801823D4(...))
```
So yes, otz's first set materialized.

Alternative: what if `otz` is declared as `s32 otz` and the call is `otz = RotTransPers4(...)` but otz is *volatile*? no.

What if otz is a *static* variable? no, adds loads.

Hmm — what about using otz in the `do { } while (0)` **condition**: `do { } while (otz, 0);`? Hmm, `(otz, 0)` folds to 0 at tree level, but maybe not: gcc's fold handles COMPOUND_EXPR with a side-effect-free first operand → folds to 0. Yes.

What about `while (otz && 0)`? folds.

What about a `switch (otz) { }`? An empty switch on otz — gcc would emit a comparison/jump table! Extra insns.

OK. What about the trick of making otz a *different type* so that the call result needs a conversion that folds? e.g. `u32 otz = RotTransPers4(...)`? same mode SI.

Hmm, what if the function returns s32 and we declare otz as `s32` — same.

Let me revisit: does combine actually do the fold, or is it *cse2*? The cse2 dump shows the set present. Then combine dump shows it gone. But wait — maybe jump2 (after combine?) no, combine is after flow, jump2 after reload.

Hmm, but there's also `sched` between combine and local_alloc.

Let me look at combine.c's behavior: try_combine can combine i2 (set otz v0) with i3 (set a0 otz) if the LOG_LINK exists (otz used by i3 and dead). LOG_LINKs are built by flow (find_basic_blocks) within a block. insn 151 and 164 are in *different blocks* (LOOP_END note between them) — but LOG_LINKs are per basic block... Actually find_basic_blocks creates LOG_LINKs for registers used in the same block. Since 151 is in the loop block and 164 after, there should be no LOG_LINK. Unless jump optimization merged the blocks (the do-while(0) loop was eliminated by jump_optimize after cse2? jump runs after cse2 at line 2929). Yes! Line 2929: jump_optimize after cse2. If the do-while(0) loop has an empty body... wait, the loop contains the call, so it can't be removed. Hmm, but a do-while(0) executes once; jump_optimize might thread it: the loop-back edge is never taken (condition constant 0), so jump_optimize deletes the loop end and merges the blocks! That would leave LOOP notes but no actual block boundary.

The cse2 dump shows notes LOOP_CONT/LOOP_END between 151 and 164 — that's *after* cse2 (the dump is written after cse2 but before jump?). Hmm, the .cse2 dump is written at the end of cse2, before jump_optimize. Then jump runs and merges.

So combine sees 151 and 164 in the same block and folds. That explains w2's behavior.

So do-while(0) doesn't create a lasting block boundary when the condition is constant false... but C0535 says it splits cse1 EBB — maybe for cse purposes only.

Hmm, so how did func_8018302C's do-while(0) keep the copy? Let me look at the RM1 win.c (line 219 says RM1).
