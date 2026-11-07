---
ts: 2026-11-06T06:26:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xC18RbMn70X8Er3NZXYd
---
Noted: I read moves.md by line ranges (which is the allowed route); I'll use grep for future lookups.

Back to the task: b1/b3/b4 all 3. So the fold persists.

Let me check: does b1 differ? No, 3 = same as w2 (the break was folded away).

Let me now try the `while (i < 0)` (b2) — it added 27 insns?! That means the loop wasn't optimized as expected (probably a real loop with the whole body... no, only the call). 188 insns vs 161 — 27 more. Odd. Maybe the loop prevented cse/hoisting. Drop it.

OK. Let me now think about whether the raw value can be made live across a call. 

AH WAIT. I just realized something! What about the `if (i != 11)` — in the *else* arm (i == 11), the target does `addiu a0,s3,132` etc. and then joins. What if we move the `otz = RotTransPers4(...)` call *before* the if by computing the args differently: pass `pa`/`pb` pointers and offsets... no.

Alternatively — what if we reorder the body so the packet stores come AFTER the RotTransPers4 call? The call's out-params are `&q->xy0..xy3`, and the stores write rgb/tag. If the stores came after the call, the codegen order would differ from the target (target: stores first, then call).

OK. Let me consider: is `move s1,v0` + `move a0,s1` really required? The target has 162 insns and we're at 161 with only this difference. So yes.

Hmm, let me reconsider the problem statement: maybe the crack is not to keep the copy but to make the *value* live across a call — e.g. by moving the `func_801823D4` call's argument to use a variable that's also used later.

What if we do:
```
otz = RotTransPers4(...);
AddPrim(...) uses otz?
```
no.

Hmm, hold on. What about restructuring so that the *sorted* value is stored in a separate variable and the raw one in otz, then the AddPrim uses otz (raw)... no, semantics.

Wait, actually — does semantics matter for scoring? The scorer compares instructions only. But the project rule is "real C moves only" and the body must be a faithful representation. A semantically different body would be wrong even if it scored 0. I should keep semantics.

Let me reconsider: is there any *real* code change that makes the raw value live longer? Yes: if the code used the raw value again. There's no such use in the original.

Hmm, but hold on — what about the `func_801823D4(otz, -0x1A)` call: what if we pass `otz` and ALSO assign the result to otz in the same statement... that's what it is.

OK, so the fold is a compiler behavior that the asm defeats. This is a WALL.

But wait — before declaring a wall, let me reconsider whether the target's `move s1,v0` could arise from a different *allocation* of the otz pseudo. If otz (r80) were allocated to v0 in the target, the copy would be a no-op and deleted. The target has it in s1 because otz is a global pseudo used in both loops (s1 is callee-saved; global-alloc assigns it because it's live across calls in loop 2). In my w2, otz is also in s1 (the target's second `move s1,v0` matches). So the allocation matches; only the fold differs.

Hmm, hold on! If otz is in s1 and the arg copy is `move a0,s1`, combine folds it to `move a0,v0` only because the set is adjacent. What if the set is NOT adjacent — e.g. if another insn sits between. What insn could legitimately be between? In the target, the asm was there.

What if we reorder the source so that something else comes between the call and the func_801823D4 call? E.g.:

```
otz = RotTransPers4(...);
i++;          /* or some statement */
otz = func_801823D4(otz, -0x1A);
```
That would move `i++` before the call — target has `i++` after func_8012E28C. Mismatch.

What about moving `q`'s store between? no.

Hmm, what if the `AddPrim`/`func_8012E28C` order changed? no.

OK. What about the **`li a1,-26`**: it's in the jal delay slot. The arg `-0x1A` is set up as `(set a1 (const -26))` which combine might merge... 

Hmm, what if we write the second call as `otz = func_801823D4(otz, -0x1A)` where `-0x1A` comes from a variable? no.

Let me now try ONE more creative thing: **swap the two calls' argument setup** by writing the depth-sort inline: 
`otz = func_801823D4(RotTransPers4(...), -0x1A);` → combine folds everything → 1 insn less. Worse.

OK. And what about making the raw value live across the *func_80010A08* call by moving the RotTransPers4 call earlier? The call needs q which comes from func_80010A08. But wait — could we allocate the packet *after* the RotTransPers4 call? The call writes to `&q->xy0` so q must exist.

Hmm, BUT: what if we split the packet allocation: `q = func_80010A08(0x24)` must be before. Yes.

So: WALL for item 1? Let me reconsider the numbers: w2 score 3 with 161 ins vs 162. 

Hmm, hold on. Let me reconsider — what about `-fno-...`? No, can't change flags.

Let me look at combine.c to see if there's a condition we can trip. In combine, try_combine is called with i3 and i2 from a LOG_LINK. The fold of `(set r80 v0)` into `(set a0 r80)` — this is `subst` of r80 → v0 in i3. It requires `reg_n_sets[r80] == 1`? or `REG_DEAD`. Since r80 dies at i3, the substitution is valid.

What if r80 had TWO sets (e.g. otz assigned twice in the same block before the use)? Then combine couldn't substitute... but the second set would be the func_801823D4 result which is after.

Hmm! What if we assign otz TWICE before the use — e.g.:
```
otz = RotTransPers4(...);
otz = otz;      /* folds */
```
no.

What about:
```
otz = RotTransPers4(...);
otz = func_801823D4(otz, -0x1A);
```
already.

Hmm, what if `otz` were assigned in a *previous iteration* too (it is! otz is set at the end of the loop each iteration). So r80 has multiple sets across the loop, but combine works per-block.

OK — let me look at combine.c's `try_combine` guard for the "i2 dead" substitution. Actually the mechanism might be `combine_simplify` / `subst`. Hmm.

Alternatively, maybe I can prevent the fold by making the arg copy a *different mode* operation: e.g. if the call's parameter were declared `s16` in the extern declaration! Then passing `otz` (s32) to an s16 param requires truncation+extension? In C, the parameter type s16 → the value is converted to s16 then back to s32 for the ABI. gcc would emit sll/sra. Extra insns.

Hmm, but what if the *prototype* is `func_801823D4(s32, s32)` (it is).

OK, let me now consider the alternative: accept a WALL for the otz move but... hmm, the item is 3 points away. 

WAIT. NEW IDEA! What if we make the *raw* value used by the `func_8012E28C` call at the end of the loop? Look:
```
otz = func_801823D4(otz, -0x1A);
AddPrim(... + otz * 4, q);
func_8012E28C(otz, zpush);
```
Target: `move a0,s1` at 306c for func_8012E28C uses the sorted otz.

What if instead the source were:
```
s32 raw = RotTransPers4(...);
otz = func_801823D4(raw, -0x1A);
AddPrim(... otz*4, q);
func_8012E28C(otz, zpush);
```
Then `raw` has one use → folded.

What if `func_8012E28C(raw, zpush)`? That would use raw after the sort call → raw live across func_801823D4 → the set materializes! But semantics: func_8012E28C takes the depth-sorted z? The target passes otz (sorted). Changing it to raw would be a semantic change (and codegen would differ: `move a0,s1` would read a different register).

No.

Hmm, what about the `AddPrim` index `otz * 4` — if that used raw, the sll would use the raw value's reg. Target uses s1 (the sorted value). No.

OK. Let me try one final idea: **`otz` as a `s32` but the assignment written as `otz = RotTransPers4(...) ;` with the call result stored to a *static*?** no.

Alright — let me now check the actual behavior of combine on a *minimal* case to see if there's any C form that keeps the copy... Actually, let me look at combine.c: what if the copy's source is not a hard register (v0) but a pseudo? The set is `(set r80 (reg v0))` — v0 is a hard register (the call's return). Combine substitutes v0 into `(set a0 r80)`. If instead the sequence were `(set r80 (reg rX))` where rX is a pseudo, combine would still substitute.

Hmm, what if the call result went through a *second* pseudo: `t = call(); otz = t; a0 = otz;` — combine folds t into otz into a0.

OK, I'm confident: this needs an opaque insn → WALL for the launder part, unless... 

hmm, hold on! What about the "empty asm-free" trick used in G14 line 187: "the launder tied-output on sc -> empty do { } while (0) (plain C keeps the CFG shape the asm forced)". There, the asm's role was CFG shape, and do-while(0) replaced it. In our case the asm's role is to be an insn between.

Let me look at the target more carefully: is the asm really between? orig.c has:
```
otz = RotTransPers4(...);
__asm__("" : "=r"(otz) : "0"(otz));
otz = func_801823D4(otz, -0x1A);
```
Yes.

Given the difficulty, let me consider the *cost* of continuing vs moving on. I have 4 more items, two of them 90/96 ins (small). The 307/308 ones are huge and likely harder. Time is ~23:35 (30 min in).

Let me make a decision: spend 10 more minutes max on item 1 with 2-3 targeted tries, then record.

Targeted try: what if I put the RotTransPers4 call inside a `do { ... } while (0)` AND the func_801823D4 call inside the same do-while, but with the loop *condition* being the loop counter `i < 12`? i.e., replace the outer `for (; i < 12; )` with `do { ... } while (i < 12)`? Hmm, that's a different loop shape but might produce the same code (the target's loop is a bnez at the bottom — the for loop compiles to a test at the bottom anyway). Then within the body... no help.

Alternatively: what if the func_801823D4 call is inside the loop body but the RotTransPers4 call is at the *end* of the previous iteration... no.

Hmm, let me try ONE thing: reorder so that `otz = RotTransPers4(...)` is followed by `q` stores? No, they must precede.

OK, what about this: **the `if (i != 11)` block between the set and the use**. What if we move the *pointer selection* to AFTER the call by using the pointers directly in the call and adjusting... no.

Alright, one more: what if the depth-sort call is `otz = func_801823D4(otz, -0x1A)` and we make the raw value live by using it in the *`i != 11` test of the NEXT iteration*? No.

Decision: record item 1 as WALL with best 3? Hmm, but the brief's DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0" — WALL is allowed with best = lowest score of a lever-free body. So WALL best 3 is legitimate IF I've done ≥20 min and ≥30 tries. I've done ~12 tries and ~30 min. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 30 scored tries! That's a lot. Let me generate a batch of variants to reach 30 — but they should be meaningful.

Hmm, wait. Actually, maybe I should reconsider: 30 tries is the bar for calling it a WALL. Let me generate a systematic sweep: declaration orders, statement orders, widths, do-while placements. That's cheap to score (each ~5s?). Let me time one: the sc.sh with 4 candidates took maybe 20s. So ~5s each. 30 tries = 2.5 min. OK.

But before that, let me think ONE more time about a real crack...

Hmm hm hm. What about making otz's first value used in the `AddPrim` index *through the loop-carried value*? no.

What about the **`pp`/`pf`** — they're already solved.

Hmm, what if instead of `otz` being reused for both loops, we split it: `otz` for loop 1 and `otz2` for loop 2? Then otz's pseudo is block-local → local-alloc → v0 → the copy folds even more.

What if otz is used *across* the two loops (as now)?

Let me look at the problem from the target's perspective once more: with the asm, otz's set at 301c is in s1. What if we could get the same by having otz live across the *func_801823D4* call? That happens if otz's value is used after that call. In the target, otz's value after the sort is a new set. So no.

Alright, WALL it is — but let me do the sweep to reach 30 tries and to be sure. Actually wait. Hold on. Let me reconsider ONE specific idea I haven't tried: **`otz` used in the `q->xy` argument setup**? No.

And another: what about making the first call return into a variable that is *also* the loop's `otz` but with a **different mode** — e.g. `u32 otz` vs `s32`. The assignment `otz = RotTransPers4(...)` where the function returns s32 and otz is u32: same SI mode. No change.

Let me also try: the call result assigned to otz, then `otz = (s32)(otz * 1)`. Folds.

OK, sweep time. Let me build a generator producing ~20 variants:
1. Decl order permutations of (pp, pf, zpush) — 6.
2. Statement order: zpush assignment before/after pp/pf — 2.
3. do-while placements — done.
4. `otz` declared in different positions.
5. Widths of zpush (s16, u16).
6. `q` declaration.

These may fix the *register* part differently but not the move.

Hmm, that's wasteful. The real question is the move.

Let me try ONE more creative approach: **make the arg copy non-adjacent by inserting the `q` argument setup**... 

OH WAIT!!! I think I've got it. What about the `AddPrim` call's first argument `D_800A651C[*(u16 *)&D_800B9A02].a + otz * 4`. The `*(u16*)&D_800B9A02` load is `lui v1; lhu v1,0(v1)`. That's between... no, after.

Hmm.

What about this: the `func_801823D4(otz, -0x1A)` — what if the -0x1A is computed via a variable that's declared in the loop? no.

OK, final answer attempt: let me look at what `-0x1A` does: `li a1,-26` in the delay slot. Fine.

Let me now run a systematic sweep to 30+ tries for the WALL, but let me include a couple of "real 2nd set" variants:
- `otz = RotTransPers4(...); otz = otz + 0;` (folds, but let's confirm)
- `s16 otz` variants
- `otz = (s32)RotTransPers4(...)`
- splitting the call statement

Hmm, hold on, hold on. What about the **`do { } while (0)` around the call combined with the `if (i != 11)`**... 

Actually, you know what? Let me look at the G14 example that cracked with do-while for a tied output: func_8018CDEC. Let me look at its win.c to see the exact shape — maybe the pattern applies.
