---
ts: 2026-11-06T18:43:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XyEvmIMFjUSXVxwQLpPT
---
All worse or 4. Time 11:43:16 → 13.3 min.

Let me reconsider whether there's any way to get the a1 materialization early. 

IDEA: What if the a1 materialization is *not* folded into the call arg because the call's a1 argument is not a direct copy — e.g., if the call is made through a *pointer* variable `fp`? Then the arg setup is the same.

IDEA: What if we pass `a1` as the *third* argument and `a2` as the second? That changes the register assignment (target has a1 = D_801A15AC in $5, a2 = D_801A15B4 in $6). Swapping would give different regs → no.

IDEA: What if the a1 value is used in the *branch condition* of the call's result? e.g., `if (func_8012D5E4(...) == 1 && a1)` — adds a test.

IDEA: What if the source declares a1 *before* a0 (decl order)? The pseudo creation order follows the RTL, not decls.

IDEA: The keepalive asm also had the effect of preventing combine from folding. What if we prevent the fold by making a1's value used in a way that combine can't fold but costs no insn — e.g., make a1 a *parameter-like* value passed to the function? no.

Hmm, hold on: what about the `if (func_8012D5E4(a0, a1, a2, a3) == 1)` — the call's return. What if the call is written with the a1 argument as `(s32)&D_801A15AC` directly (no variable)? Then the materialization is at the call arg — same.

OK, one more idea: what if the *first* call's second argument is also a1 (reused) but the second assignment to a1 is *before* the first call, and the first call uses a different variable? Then a1 is live across the first call — the target doesn't have that.

Let me try a fundamentally different structural idea: put the v0 chain in a *separate basic block* by using an `if` with a condition that's true but opaque? That adds a branch.

What about the store order and a do-while at the *end* (around the call)? e.g., do{}while(0) around the call+result? That might change the block end.

Let me look at what the C0535 cookbook says exactly (do{}while(0) splits cse1 EBB). The mechanism: cse1 treats an EBB (extended basic block) as a unit for constant propagation. Splitting it changes cse's behavior. Our issue is sched1, and w2 (do-while around the v0 chain) gave 9 — worse.

Hmm, what if the do-while wraps ONLY the a1 assignment? Then a1 is in its own block, before the v0 chain block:
```
a0 = s0;
do { a1 = (s32)&D_801A15AC; } while (0);  // !FAKE: do-while
v0 = ...
```
Then the a1 materialization is in block X, the v0 chain in block Y. The final asm: block X: move a0,s0; lui a1; addiu a1 (2 insns) then block Y. But the target has TWO moves a0,s0 before a1 (the second move is the call arg copy, which would be in block Y) → order: move, a1, move → wrong.

Unless the second move is in block X too (it's the call arg, at the end).

Hmm, what if the do-while wraps `a0 = s0; a1 = ...;`? Same.

What if it wraps `a0 = s0;` alone? Then block X: move a0,s0; block Y: a1, v0 chain... → order: move, then a1 early? In block Y, a1's materialization folds into the call arg and sched1 places it late. No.

What if the do-while wraps the *v0 chain through the stores* (w2, score 9)? The a1 is in block X with the pin move; block Y has the rest. The result was 9 — let me see what went wrong. Maybe the second move ended up in block Y at the end.

Let me check w2's diff to understand. Actually, let me test the do-while around just `a0 = s0; a1 = ...;` (block X) and see the score.

Actually — hold on! What if the do-while wraps the a1 assignment AND the v0 chain (i.e., splits BEFORE a1 and after the chain)? Then block X = [52 move], block Y = [55 a1, 58...]. In block Y, the a1 materialization could still be folded and scheduled late within Y.

What if we split AFTER the a1 assignment but BEFORE the second move? The second move (92, a0 = a0) is generated at the call — it's in block Y regardless.

Ugh.

Wait, actually, let me reconsider the second move. In the orig's RTL, insn 94 = `(set (reg:SI 4 a0) (reg/v:SI 4 a0))` — a self-copy. Why does it survive? Because a0 is the pinned variable and the call needs it in $4. This self-copy is deleted in some builds? In the orig's final asm, the two moves at 8014/8018 exist. Hmm, but wait: maybe the first move (8014, the delay slot) is insn 52 and the second (8018) is insn 94. Yes.

So to match, the final order must be: 52, 94, 55, 58... where 94 is the self-copy in block Y (scheduled at the top of block Y). If 55 is also in block Y, sched1 can put 94 before 55 (as it does now: 52, 92, 58... in w1 — wait, in w1 the order is 52, 92, 58, ... and 55 is folded into 94 later).

Hmm, in w1 the a1 materialization IS insn 94 (the call arg), and the self-copy is insn 92. The target order: 52, 92, then the a1 materialization. In w1: 52, 92, 58... So sched1 placed the a1 materialization (94) late.

What if the a1 materialization were a separate insn (not folded) — e.g., insn 55 (set 77 symbol) and 96 (set a1 77)? Then sched1 could schedule 55 early? It becomes ready when 96 is scheduled (late) unless there's a barrier.

So the barrier is essential.

Hmm, is there any non-lever C construct that makes sched1 keep an insn early? Looking at sched.c's `adjust_priority`: `if (birthing_insn_p (PATTERN (prev)))` — insns that "birth" a register get max_priority (a boost). birthing_insn_p: an insn that sets a register that is not... Let me look. If the a1 materialization were a "birthing insn", it'd get a priority boost and be scheduled early!

Let me read birthing_insn_p.
