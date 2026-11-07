---
ts: 2026-11-06T15:53:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TnZK2115vEfTwTzI8b2o
---
vd1 (double set) still 4. vd2 (volatile pointer) worse. vd3 no change.

Hmm, double set didn't keep the set alive? Because cse still propagates the constant at each use (the value is known). So the la still at the copy.

Wait, but if there are two sets of the same constant, the first set's value is known; the copy still folds; the first set is dead (overwritten by the second before any use) → deleted. So yes.

What if the first set is used *before* the second? E.g.:
```
arg = &D_800AF648;
func_80052E38(arg);   <- use here
arg = &D_800AF648;    <- second set after
```
The second set is dead → deleted. Tested (vc6).

What if the second set is used: 
```
arg = &D_800AF648;
func_80052E38(arg);
arg = 0;
if (arg == 0) ...  <- real use? adds code
```

Hmm.

Let me reconsider the mechanism from the comment: "combine substitutes cse's REG_EQUAL constant into the call-site copy and deletes the first set (measured: identical bytes to the plain call)." So without the launder, the first set is deleted. To keep it, we need the set to have a REG_EQUAL that combine cannot substitute, or a second use.

What if the *value* is not a compile-time constant but still &D_800AF648? The only way is a runtime computation. E.g.:
```
arg = (u8 *)&D_800AF648;
```
vs
```
arg = (u8 *)((u32)&D_800AF648);
```
same.

What about using the address of an element of an array of unknown length? same.

What about `arg = D_800AF648 + 0;`? same.

What if we make `arg` point to a *local struct* whose address is runtime? no.

OK, I'm fairly convinced the `arg` launder is not removable by plain C for this shape. But wait — the moves line 69: "keepalive 2nd use blocks merge (best 4)" suggests even a keepalive only gets to 4 (which is our score). So this is a known wall family: combine-argcopy-sink.

Hmm, but the target here NEEDS the early la. The launder is the only way.

However — maybe the score 4 residual is only the la *position*, and the brief wants score 0. If I keep the `arg` launder, I'd have PARTIAL:launder (win.c scores 0 keeping the launder). But the brief says a win.c that keeps all row kinds is a WALL; keeping only some is PARTIAL.

Let me now also consider the 2-output launders: c3 (keeping arg launder, removing the 2-output) scored 39. So those are also load-bearing. If I can't crack either, the item is a WALL with best lever-free 43 (c1) or PARTIAL if I keep them.

Actually wait: the PARTIAL definition: "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c; a win.c that keeps all row kinds is a WALL". Here the row kind is "launder" only. If win.c keeps the arg launder but removes the 2-output launders, then kind "launder" is still present (kept) → PARTIAL:launder, and it must score 0. But c3 (arg launder kept, 2-output removed) scored 39, not 0. So keeping the arg launder and removing the 2-output ones is worse.

If I keep the 2-output launders and remove arg (c2) → score 4, not 0.

So neither partial is 0. The item would be a WALL with best lever-free = 43 (c1).

But hold on — maybe I can crack the 2-output launders with the `do-while`/`#line` trick, and then the arg one remains. Let me think about the 2-output launders first, since they're a cross-jump enabler.

The 2-output launder: `__asm__ ("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz));` with `#line 900 "p.c"` and `#line 901 "p.c"`. Purpose: "retires cse1's cross-call unification of the OT index / n<4 test; its two copies carry identical #line 900 so jump.c can cross-jump the POLY/LINE tails (ASM_OPERANDS rtx_equal_p compares file+line)".

Removing them: 344 ins (2 fewer) and score 39. The cross-jump merged the tails. So the launders PREVENT cross-jump? Wait, the comment says the launders' identical #line *allows* cross-jump. Without them, the tails differ in line numbers? Hmm, "its two copies carry identical #line 900 so jump.c can cross-jump the POLY/LINE tails (ASM_OPERANDS rtx_equal_p compares file+line)". 

Hmm, so the asm operands make the two tails' insns comparable; with the #line identical, cross-jump merges... but removing them gives 344 (fewer insns) meaning MORE merging. So the launders were preventing something else (cse unification of n<4 test).

Let me look at the c3 diff to understand. Actually, let me look at the score-39 diff for c3.
