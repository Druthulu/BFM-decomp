---
ts: 2026-11-06T14:48:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PWj8Xmgl5vr4R3zHKOI9
---
All 4. Let me check v6's diff — maybe the structure changed. Let me look at v6 and v2 diffs.

Actually, all 4 with the same MIXED category. Let me check v2's diff (the mask).

Hmm. Let me think differently. The target's branch structure requires the compiler to not fold `t != 3` given `t == 5`. The only real-C way is to make t opaque. 

Wait — what if the check uses a value that's the RESULT of an earlier real computation that the compiler can't constant-fold because it's not a constant? For example, if the check were `if (t != mode)` or something. But the target checks `t != 3`.

Hmm. The target's `bne t,3` compares t with the constant 3. For the compiler to keep it, it must not know t==5.

What if I reorder so the `t == 5` check comes AFTER the `t != 3` check? But then the semantics change (the `if (t!=3)` would run for all t, not just t==5). Let me see: the target's flow is:
- if t==3 -> sel_054
- if t==5 -> check t!=3 (true) -> sel_094
- else -> after

What if I write:
```
if (t == 3) goto sel_054;
if (t != 3) {          // always true here (t != 3 and t != 0)
    if (t == 5) goto sel_094;
}
goto after;
```
Hmm, that changes the structure.

Actually, the target's structure `bne t,5,L71; bne t,3,L73` is: if t!=5 goto after; if t!=3 goto sel_094. Since the fall-through is t==5, the second is always taken. 

What if I write the C as:
```
if (t == 3) goto sel_054;
if (t != 5) goto after;     // explicit negation
if (t != 3) goto sel_094;   // redundant
goto sel_054;               // fall-through? 
```
The compiler would fold `t != 3` given t==5 (fall-through). Hmm.

The issue is the compiler's jump.c threading. Let me check: does gcc 2.7.2's jump.c thread conditional branches based on known values? There's `thread_jumps` which redirects jumps through blocks. And `jump_optimize` has a pass that converts `if (x) ... ` based on known values from previous comparisons? Actually, the fold `t==5 => t!=3` is a simple logical deduction: 5 != 3, so if t==5 then t!=3. This is done by... hmm, maybe by the front-end's fold on the `if (t != 3)` after `if (t == 5)`? No, the front-end doesn't track.

Wait — actually, maybe the fold is done by `cse`'s constant propagation: after `if (t == 5)`, on the fall-through path, cse knows t==5 (it records the comparison in the fall-through). Then `t != 3` with t==5 folds to true. cse does record "known values" from comparisons? cse has `record_jump_equiv` which records that after a conditional jump, the compared register equals the constant on one path. YES! cse.c has `record_jump_equiv` that adds a REG_EQUAL note on the register after a branch (e.g., after `if (t == 5) fall-through`, it records t == 5). Then the next comparison `t != 3` gets folded.

So cse (cse1/cse2) is the pass. The launder (asm) invalidates the equivalence (cse sees a set of t), preventing the fold.

To prevent cse from recording t==5, I need a "set" of t between the two comparisons. Real C: `t = ...` that cse sees as a set but that doesn't change the value. But any `t = expr` emits code unless folded. The C0414 "dead-reset" is exactly this: `t = 0;` after a use — cse's forward scan invalidates the equivalence at the second set, and flow deletes the dead set before sched1. But here, if I do `t = 0;` inside the t==5 block, it changes t to 0, so `t != 3` would be true (0 != 3), same as before! And then t is used later as `D_801802E4[t]` — wait, after the t==5 block, `if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0)`. So t must be restored. Hmm.

But wait — the C0414 dead-reset: `p = 0;` immediately after a use, then `p` is re-set before the next use. If I do:
```
if (t == 5) {
    t = 0;       // cse sees a set -> invalidates the t==5 equivalence
    if (t != 3) goto sel_094;   // t==0, so true -> goto sel_094
    ...
}
```
Then t is 0, and `t != 3` is true -> goto sel_094. Same behavior as t==5 (both != 3). And the `t = 0` set would emit `move t,0` — extra code. Unless it's deleted as a dead store. But t is used in `t != 3` after, so it's NOT dead. Hmm.

Wait, the C0414 dead-reset is `p = expr; use(p); p = 0;` where the `p=0` is DEAD (p not used after). For us, after `t = 0`, t IS used in `t != 3`. So not dead.

Hmm. Unless I structure it so the `t=0` is dead:
```
if (t == 5) {
    t = 0;          // set, invalidates cse
    if (t != 3) goto sel_094;   // uses t
    ...
}
```
t=0 is used, not dead.

What if I use a different variable:
```
if (t == 5) {
    s32 u = t;      // copy: cse sees u = t, doesn't invalidate t==5
    if (u != 3) goto sel_094;  // cse might propagate u=t and fold
}
```
cse would record u == t, then u==5, fold.

Hmm.

What if I invalidate cse's t==5 record with a dead set of t, then re-establish t? Like:
```
if (t == 5) {
    s32 save = t;
    t = 0;          // invalidates cse's t==5
    t = save;       // restores; cse sees t = save, not the constant 5
    if (t != 3) goto sel_094;   // cse doesn't know t==5 now
    ...
}
```
The `t = 0; t = save;` — cse sees two sets. The first is dead (t overwritten by t=save before use), so flow might delete it. The second `t = save` — cse records t == save, but save == 5? cse knows save == t (old) == 5? Maybe. Hmm.

The C0414 trick: `p = expr; use(p); p = 0;` — the `p=0` is dead and deleted by flow, but cse sees it and invalidates. For us, I need a dead set of t AFTER the t==5 branch but BEFORE the t!=3 check, and then t must be valid for the check. But a dead set of t would leave t undefined for the check. Unless the check uses the pre-set value... no.

Hmm, what if the dead set is of a DIFFERENT variable that aliases t? No.

Wait — maybe I can use the C0414 trick differently: the t==5 equivalence is recorded on the fall-through of `bne t,5,L71`. If I put a dead set of t on the fall-through path before the `t != 3` check, cse invalidates. But the check then uses the dead-set value? No — if I do `t = 0;` (dead because immediately overwritten by... nothing). Hmm.

Let me think about the exact cse behavior. cse's `record_jump_equiv` adds a REG_EQUAL (const 5) to t after the branch. Then at `if (t != 3)`, cse sees t has a known value 5 and folds. To prevent, cse must see a SET of t between the branch and the check. A real C statement `t = t;` is a self-set (deleted before cse? flow runs after cse, so cse sees it? No — jump.c's no-op move deletion happens before cse? The self-copy deletion is in flow (line 951), which runs AFTER cse. But there's also `delete_noop_moves` in jump.c (before cse). Hmm. And `t = t` is an identity launder (forbidden anyway).

What about `t = t + 0;`? The front-end folds to t, so no RTL set. cse sees nothing.

What about `t = (s16)t;`? If t is s32, `(s16)t` is a sign-extend; the front-end might fold if t is already s16-range? t is s32, so (s16)t is a real conversion: `sll t,16; sra t,16`. That emits 2 instructions (extra code). But maybe cse/fold removes them if t is known to be (s16)a1? Hmm, the compiler knows t = (s16)a1, so (s16)t == t. It might fold. Let me test v3 was `(s16)a1 != 3` (folded, 4). Let me test `t = (s16)t;` before the check.

Actually, wait — the front-end knows t was assigned (s16)a1, so `(s16)t` is redundant and folds. cse sees nothing.

Hmm.

What about `t = t * 1;`? folds.

What about `t = t ^ 0;`? folds.

All fold at the front-end.

What about an operation the front-end can't fold but that produces no code? There isn't one in pure C.

Hmm. Unless I use a value that's genuinely recomputed: e.g., `t = (s16)a1;` again inside the t==5 block. The front-end doesn't know a1's value, so `t = (s16)a1` is a real computation: `sll; sra` (2 instructions). Extra code. But maybe cse merges it with the earlier `t = (s16)a1`? If cse CSEs the two computations, it would delete the second and re-establish t==... hmm, actually cse would merge them into the same pseudo, and since a1 is unchanged, the second `(s16)a1` == t (same pseudo). Then cse records t == (s16)a1, not the constant 5. So the t==5 equivalence from the branch might be invalidated by the set? Hmm, if cse merges the two, the "set" of t is the same expression, and cse knows t == (s16)a1. The branch recorded t==5. Which wins? cse might keep t==5 (the branch is more recent). Hmm.

Let me just test: v7: `t = (s16)a1;` before the check. This might emit 2 instructions or be CSE'd.

Let me also test v8: the C0414 dead-reset style with a save/restore.

And v9: recompute via a different expression: `t = (s16)(a1 & 0xFFFF);`? hmm.

Let me test v7 and v8.

v7:
```
if (t == 5) {
    t = (s16)a1;
    if (t != 3) goto sel_094;
    ...
}
```
v8:
```
if (t == 5) {
    s32 save = t;
    t = 0;
    t = save;
    if (t != 3) goto sel_094;
    ...
}
```
Hmm, v8's t=0 is dead (overwritten by t=save). Flow deletes it. But cse sees it and invalidates t==5. Then t = save: cse records t == save. save == 5 (cse knows save==t==5?). Hmm, cse might fold t==5 again. Let me test.

Actually, the cleaner C0414 pattern: put a dead set of t AFTER the check, not before. But the check needs to see t!=3. Hmm.

Wait, maybe the dead set should be between the branch and the check but on a DIFFERENT path... no.

Let me think about cse's record_jump_equiv: it records the equivalence on the register after the branch. Then the next use of t (in the check) uses the equivalence. If there's a SET of t between, cse's forward scan invalidates. A dead set that flow deletes AFTER cse would work: cse sees it, invalidates; flow deletes it (so no code); then the check... but wait, if flow deletes the set, the register t's value at the check is the OLD value (5), and the check is compiled as `bne t,3` (using the register). The deleted set doesn't affect codegen. So:

```
if (t == 5) {
    t = 0;          // dead? no, used by the check
    ...
}
```
No, t=0 changes the check's operand.

Hmm, the dead set must be dead (not affect the check). But any set of t before the check affects the check. Unless the set is overwritten before the check:
```
if (t == 5) {
    t = 0;          // dead: overwritten by t = save
    t = save;       // restore
    if (t != 3) ...
}
```
The `t=0` is dead (overwritten). Flow deletes it. cse sees it (invalidates t==5). Then `t = save` — cse records t == save. But does cse know save == 5? save was assigned t (==5) before. So cse might propagate save==5 to t. Hmm.

What if `save` is assigned in a way cse can't track? Like `save = t + 0`? folds. Or `save = (s16)a1`? real computation.

Hmm.

Alternatively, put the dead set of t on the fall-through path but AFTER the check? No, the check is what needs invalidating.

Actually, cse's invalidation: the forward scan processes insns in order. When it hits a SET of t, it deletes the t equivalence. So a set of t before the check invalidates. But the set must not change the check's value. The only way is if the set's value equals the old value (an identity), which is forbidden/folded.

Hmm. UNLESS the set is to a value that flow proves equal... no.

OK, what about a set of a DIFFERENT register that cse thinks aliases t? No.

Let me reconsider. Maybe the fold is done by jump.c's `thread_jumps`, not cse. If so, a different lever applies. Let me check which pass folds it by looking at the dumps. The .cse2 dump (after cse2) should show whether the fold happened. Let me compare the .cse2 of orig (with launder) and c1.

Actually, the target (orig) has the launder; the fold didn't happen. c1 (no launder) folds. Let me look at the .cse2 dump for c1's case 5 block to see if the fold happened by cse2.

Let me grep the .cse2 dump for the case 5 region. The branch structure in the RTL: `if_then_else (eq (reg16) (const 3))` etc.

Hmm, let me just check the .jump2 or .cse2 dumps. Actually, let me look at the .rtl (pre-cse) and .cse2 (post-cse) for c1 to see where the fold happens.

Let me grep the c1 .cse2 dump for the relevant branches.

This is getting deep again. Let me consider the time: ~09:05, started this item ~08:55. So ~10 min. I have time.

Let me test v7/v8 first (empirical), then investigate.

Actually, let me reconsider: maybe the fold is by the C front-end's `fold` in the `if (t != 3)` — no.

Let me look at the .cse2 dump for c1 around the case 5 branches. The labels: sel_054, sel_094. In the RTL, the branch conditions are `(eq (reg:SI 16) (const_int 3))` etc. Let me grep for `const_int 3` and `const_int 5` in the c1 .cse2 dump near the function.

Let me do it.
