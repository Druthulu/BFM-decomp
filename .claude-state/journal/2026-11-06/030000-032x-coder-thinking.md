---
ts: 2026-11-06T10:00:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CAZAQ5EuE2NXQjKwNC9Y
---
All four baseline 0. Now I need lever-free versions.

Let me think about item 1 more. Since expand-void-return is the wall tag, but maybe there's a trick I'm missing: what if we keep the function `void` but make rv live by *returning it from an inner construct that GCC can't drop* — e.g., a `goto` into a block where rv is used? No, dead code is dead.

Actually — hmm! What about the **`return` in a function declared `void` but with a *non-void prototype visible at the point of the definition*? The callers' `extern void` declarations come later. What if the definition line says `s32` but the conflict... no.

What if we exploit that the callers are *after* the definition, and change the definition to s32 while the *callers'* declarations remain void → error. Tested: error.

Hmm, unless we can suppress the error... no levers allowed.

OK here's another thought experiment: the target is generated from a source where the function returns a value. The decomp's current source is void + pin. The "crack" would be to change the *callers'* declarations from void to s32 (allowed in general decomp work, but this brief forbids it). Actually, wait — let me re-read the constraint once more:

"no signature or decl change outside the body (callers stay as they are)"

Yes, forbidden.

So item 1 = WALL expand-void-return, best 15 (or can we improve best below 15? WALL best = lowest score of a lever-free body).

Can we lower the score below 15 by making *some* of the value-sets happen? For example, if the function is void but we write the tail so that v0 is set as a byproduct of a comparison in a way that matches some target instructions. Hmm, the target's `slt v0,a0,v1` at 43e8: that's the condition `a0 >= x` → `slt v0,a0,x; beqz`. That's already in mine? Mine ends at 43e8: jr ra. Wait mine's 43e8 is jr ra, and target's 43e8 is `slt v0,a0,v1`. Let me compare: mine had:

43c4 lui v1
43c8 lw v1
43cc slt v0,a1,a0
43d0 beqz v0,43e8
43d4 slt v0,v1,a1
43d8 beqz v0,43e4
43dc nop
43e0 addiu v1,v1,1440
43e4 addiu a1,a1,1440
43e8 jr ra
43ec nop

Target:
43c4 lui v1
43c8 lw v1
43cc slt v0,a1,a0
43d0 beqz v0,43e8
43d4 slt v0,v1,a1
43d8 beqz v0,43e4
43dc nop
43e0 addiu v1,v1,1440
43e4 addiu a1,a1,1440
43e8 slt v0,a0,v1
43ec beqz v0,43fc
43f0 slt v0,v1,a1
43f4 bnez v0,4404
43f8 subu a0,v1,a0
43fc j 4424
4400 li v0,-1
4404 slti v0,a0,16
4408 bnez v0,4424
440c sll v0,a0,0x1
4410 subu a0,a1,v1
4414 slti v0,a0,16
4418 bnez v0,4424
441c sll v0,a0,0x1
4420 li v0,31
4424 jr ra
4428 nop

So mine diverges exactly at 43e8: target continues the control flow; mine returns. The first 9 instructions match. Score 15 = 15 missing instructions (COUNT class).

Can we make the control flow continue in a void function? The control flow after 43e8 is: `if (a0 >= x) goto done;` — with rv dead, GCC sees the branch target = return, so it's `if (a0 >= x) return;` and the rest of the code is still reachable from the fallthrough... wait, but the rest (d = x - a0; if (d<16)...) leads only to `return;` too. GCC's jump opt: since every path after leads to return, it may collapse. Actually, mine jumped from 43e8 (after the if(y<a0) block) straight to jr ra — meaning GCC determined the whole rest is dead? No, the rest has branches `if (d < 16)` whose outcome doesn't matter (both paths return), so the comparisons are dead too → eliminated.

To keep the control flow, the branches must have observable effects. Without a return value, they don't.

Could we make them have side effects matching the target? No, target has no side effects.

Therefore 15 is the floor for a lever-free void body. So WALL expand-void-return with best 15.

Hmm, but hold on! Wait. What about `goto done` where `done:` has a statement that's a *call*? No.

OK, but before I settle, let me reconsider whether the constraint really forbids return-type change. Let me re-read the exact brief text: "CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added; write only under .run/P40/T11/G26x/ ...; no make, no git, no commit; no signature or decl change outside the body (callers stay as they are); no `register` vars, no `__asm__`; ..."

"no signature or decl change outside the body (callers stay as they are)". This is unambiguous: don't change the signature/declarations. The definition's return type is part of the signature. So no.

Hence WALL for items 1 and 2 at least. Item 2 target: let me confirm.

Actually, wait. For item 2, the function `func_80180AC4` sets `ret = 0` in one branch and `ret = 1` at the end. The target has li v0,0/1. Same expand-void-return.

Item 3: same (rv=0 in else).

Item 4: `f` is used in real code; the pin $3 steers f into v1. And the keepalive on i1 changes ref counts. This one may be crackable with real C (e.g., a do-while ref boost is a keepalive replacement... but do-while is allowed with the marker? "do{}while(0) only with `// !FAKE: do-while`" — that's allowed, and it's a real C construct that adds a reference). Hmm, but the keepalive here is `__asm__("" :: "r"(i1))` inside the loop to add a reference. A `do { } while (0)` wrapper around i1's use would add loop-weighted refs. That's the C0535 move.

But item 4's pin $3 on f: need to get f into v1 without a pin. Real C moves: change declaration order, temps, etc.

Let me now examine item 4's target and think.

But first, let me be efficient. The task: 4 items, each needs ≥30 tries if WALL. Let me be systematic.

Plan per item:
1. Item 1: WALL expand-void-return, best 15. Do ≥30 scored tries to satisfy the WALL requirement? "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 30 tries and 20 min. That's a lot of wall-clock. Hmm, 4 items × 20 min = 80 min minimum. That's the budget. OK.

Actually, maybe I can find cracks for items 1-3 by a different route I haven't considered. Let me think REALLY hard about expand-void-return.

GCC 2.7.2 expand_void_return... Let me read the source: tools/reference/gcc-2.7.2/stmt.c, function expand_return / expand_null_return. Let me grep.

Actually, a thought: what if the function is declared `void` but we make the value live via a **`return` in a nested block with an expression that has a side effect**? E.g. `return func();` — call side effect. Not matching.

What if we use a **computed goto**? no.

What about **`switch` on rv** at the end, where all cases do nothing? `switch (rv) { case -1: break; ... }` — GCC might keep the switch? It would compute rv for the switch condition — but if all arms are identical (empty), the switch is dead and removed. If arms differ in some observable way, extra code.

What about using rv in a **division by zero**? no.

OK here's a real possibility: make rv live by using it in the *condition of a branch that has different successors that both do nothing* — dead.

So no. expand-void-return is real.

Now, wait — is the target's v0 really a *return value*? Could it be that the original function had a **`goto` to a shared epilogue with a value computed** and the value is actually used by... no, jr ra with v0 = value = return.

Alternatively the original function might have been `s32` returning and the decomp's void is wrong. In that case the "crack" is impossible under this brief → WALL. That's consistent.

Let me now check item 4's target to see if it's crackable. Let me disassemble.

Let me get baseline object for item 4 via --keep.
