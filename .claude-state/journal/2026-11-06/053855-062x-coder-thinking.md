---
ts: 2026-11-06T12:38:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wTaXysgXskfJbPkyMbvv
---
So pseudo 73 = ret (`set (reg/v:SI 73) (const_int 7)`). And it's live at start (uninitialized). But I removed the early `return ret`... 

Oh! Look: `return 0` in c2 — I replaced the early returns. But maybe the early return in the ORIGINAL is `return ret;` and I replaced both. Let me check c2.c has `return 0;`. Yes I did.

Hmm, but "Registers live at start: 29 30 72 73". Maybe the lreg dump's "live at start" is computed differently, or maybe there's still an uninitialized use: `ret` is used at the STORE `unk2 = ret` — if the code can reach STORE without assigning ret? No: all paths to STORE assign ret. Hmm, but the compiler's flow might think... Actually: `goto STORE` from the arms; STORE is reached only via gotos and the fall-through at line 166 (ret assigned). So ret is always defined.

Wait — is the early `return 0` change actually in c2? Let me verify: yes I replaced 'func_8012CAE4((void *)param_1);\n        return ret;' with return 0 and the ptr==0 one.

Hmm, so why live at start? Let me check whether "live at start" is from the flow analysis at the *block* level, possibly listing regs live at the start of a block (the dump line says "Registers live at start:" for the function). Let me look at line 243 in that window.

Anyway, the conflict with v0 (2): insn 124 is `set (mem/s:SI (plus (reg 72) 216)) (reg:SI 2 v0)` — a store of v0 (the unkD8 = func_80143994(...) result) right after the `ret = 7` def at insn 127 (note order: 127 comes before 124 in the list). So at that point both 73 (ret) and v0 are live → conflict!

In the target, ret = v0, so the def `ret = 7` overwrites v0 AFTER the store of v0 to unkD8. Order: `li v0,7` comes after `sw v0,216(s1)`? Look at target:
```
1af8: lui v0,0
1afc: addiu v0,0
1b00: jal
1b04: sw v0,204(s1)     ← unkCC = &D_801EE880
1b08: sw v0,216(s1)     ← unkD8 = v0 (call result)
1b0c: j 1e38
1b10: li v0,7           ← ret = 7 in the j's delay slot
```
So in the target, `li v0,7` is in the jump's delay slot, after the v0 store. So v0 is dead after 1b08 → ret can take v0.

In mine, `li a0,7` at insn 127 is before the store of v0 at insn 124 — sched1 moved it? And ret's live range then overlaps v0's → conflict.

Wait, the conflict is computed on the RTL after sched1 (insns in order). If `li a0,7` (def of 73) comes BEFORE the `sw v0,216(s1)` (use of v0), then 73 is live across the v0 use → conflict → can't be v0.

So the fix: get the `ret = 7` def scheduled AFTER the unkD8 store, i.e. the target's order. Then ret wouldn't conflict with v0 and global-alloc could give it v0!

In C, the arm is:
```
((Unkstruct *)param_1)->unkCC = (s32)&D_801EE880;
((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32,s32))func_80143994)(param_1, 0x3000);
ret = 7;
goto STORE;
```
Source order: unkCC store, unkD8 = call, ret = 7. The target's asm has the call's result stored, then li v0,7 (in the delay slot of the j).

In mine, the order got swapped by sched1 (li a0,7 before the sw v0,216). Since ret was a0 (call-clobbered? a0 is used by the call... hmm).

So the C order is already right; the scheduler reordered because ret was in a different register. Chicken-and-egg: the allocator sees the RTL order produced by sched1, which depends on the registers... Actually sched1 runs BEFORE global-alloc (sched1 is before reload, and local-alloc before sched1?). Order: local-alloc → sched1? Actually the pass order in 2.7.2: jump, cse, ... local-alloc, then sched1? Let me recall: toplev.c: ... (local-alloc, sched1?) — in gcc 2.7.2: cse1, loop, cse2, jump2?, ... local_alloc, global_alloc, sched1?, sched2... Hmm, actually in 2.7.2: `local_alloc` then `global_alloc` then `sched` (sched1 is before reload, after global_alloc?) Let me check the pass order in toplev.c.

The order in gcc 2.7.2 toplev.c `rest_of_compilation`: ... (jump_optimize? ) cse, loop_optimize, cse2, jump_optimize(2)... then `local_alloc`, `global_alloc`, `sched` (sched1) — no wait, sched1 (-ds) is before reload; reload; sched2 (-dS).

I believe the order is: local-alloc, global-alloc, sched1, reload, sched2. If sched1 is after global-alloc, then the RTL order seen by global-alloc is pre-sched1. Then the conflict came from the pre-sched1 order — which is the source order: `ret = 7` after the call/store. Hmm, but then why the conflict?

Wait, look again at insn 127 vs 124: 127 is `set 73 = 7`, and 124 is `set mem = v0`. The lreg dump is post-local-alloc. Insn numbers 124 < 127 but the order in the list is 127 then 124. So the *sequence* is 120 (call?) → 127 (ret=7) → 124 (store v0) → 129 (jump). So the ret=7 def was emitted BEFORE the v0 store in the RTL — meaning the C order produced this: `ret = 7` before `unkD8 = call(...)`. 

Hmm, why? Because in the C:
```
((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32, s32))func_80143994)(param_1, 0x3000);
ret = 7;
```
The call is before. But gcc may hoist the `ret = 7` before the call's result store because the store is the call's return value assignment, which is emitted right after the call insn; the `ret = 7` is a separate insn after. So the order should be: call, store v0→unkD8, ret=7.

But the dump shows ret=7 BEFORE the store. That's because of `insn_list:REG_DEP_ANTI 120` — the scheduler/sched? No, this is pre-sched.

Ah, I bet this is the "delay slot" issue: the store to unkD8 uses v0 (the call result). The `ret = 7` was emitted before the store because... hmm, expand emits the store right after the call.

Unless the C is:
```
((Unkstruct *)param_1)->unkD8 = ((s32 (*)(s32, s32))func_80143994)(param_1, 0x3000);
ret = 7;
```
and expand emits: call; move temp = v0; sw temp, 216(s1); li 73,7. That's call, store, li. The dump shows li before the store.

Hmm, unless it's the *local-alloc* "reordering"? No.

Wait, maybe the insn order in the lreg dump is: `insn 120` (the call) → 127 → 124 → 129. But insn numbers suggest 124 was created before 127. GCC's emit order: the store `sw v0` at 124 was emitted... hmm, insn 124 has number < 127, so it was created earlier but reordered after? That happens with `emit_insn_before/after` or with the "delay slot filling"? No.

Actually there's a known gcc behavior: when a call returns a value that's stored, expand emits `(set (reg:SI 2) (call ...))` then the store. Here the store insn 124 is placed AFTER insn 127. That reordering is probably from the `reorder` in sched? Not pre-sched.

Hmm, maybe from `flow`/`jump` "insn 127 ... (insn_list:REG_DEP_ANTI 120)". REG_DEP_ANTI 120 means it has an anti-dependence on insn 120 (the call): it can't move before the call. That's sched1's marking? The lreg dump is before sched1... 

Whatever the mechanism, the important thing: ret's def is before the v0 use, causing a v0 conflict. If the C put `ret = 7` clearly after the store... it already does.

Hmm, wait. Maybe the actual C order in the target is different: maybe the target's C sets ret BEFORE the unkD8 store too, but with ret in v0 it doesn't matter.

Let me look at the target's asm again:
```
1af0: move a0,s1
1af4: li a1,12288
1af8: lui v0,0
1afc: addiu v0,0        ← &D_801EE880
1b00: jal func_80143994
1b04: sw v0,204(s1)     ← unkCC = v0  (delay slot!)
1b08: sw v0,216(s1)     ← unkD8 = v0
1b0c: j 1e38
1b10: li v0,7
```
Hmm interesting: `sw v0,204(s1)` in the jal's delay slot stores v0 BEFORE the call executes! v0 = &D_801EE880 at that point (the unkCC store), and then after the call v0 = the result, stored to unkD8. Wait, but the delay slot executes before the call → the unkCC store uses v0 = &D_801EE880. Correct.

So the C: `unkCC = (s32)&D_801EE880; unkD8 = func_80143994(...); ret = 7;`.

Now, for ret to be v0, the `li v0,7` must come after the last v0 use. In the target it's in the j's delay slot.

In mine: `li a0,7` before the `sw v0,216(s1)`. Hmm, that's because the store's v0 value... 

Wait, maybe in mine the order is: call → li a0,7 → sw v0,216 → j. That means gcc emitted ret=7 before the store. Let me look at the actual c2 asm to see. Let me dump c2's asm region.

Actually, this is the classic pattern where the *store of the call result* is emitted after the following statement's insns because the call result is stored via a temp... 

Let me just try a C variant: move `ret = 7;` BEFORE the unkD8 assignment in source:
```
unkCC = &D_801EE880;
ret = 7;
unkD8 = func_80143994(param_1, 0x3000);
goto STORE;
```
Then in the RTL, ret=7 comes before the call — ret live across the call → needs a saved reg. Bad.

Alternatively, the target's C might have the ret assignment where it is, and the RTL order issue is due to something else.

Hmm, let me look at the actual asm of c2 for the first arm.
