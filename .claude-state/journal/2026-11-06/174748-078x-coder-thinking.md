---
ts: 2026-11-07T00:47:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gt6zrKOcE2TZeuLotd0A
---
The target's initial RTL: insn 53 = `(set (reg/v:SI 2 v0) (mem D_801B7A84))` — the load into the hard reg v0 (pin). Then the asm 55, then the stores 58..67, then 70 (reg 78 = li 1), 72 (store D_801B7988), 75 (addiu reg 79), 77 (store D_801B7A84).

So the target's RTL order matches mine except for the asm and the pinned reg. The addiu (75) is at the end in both.

So in the target, the pin forces v0 for the load. And the const pseudo 78 is local-alloc'd into v1 (since v0 is taken).

Lever-free, the const wins v0.

So the question is how real C gets the load into v0. Options:
(a) Make val's qty priority ≥ the const's.
(b) Make the const not use v0 for another reason (e.g., it's in a different class or has a copy preference).

For (a): val's life is long (53→75), so its priority is low. Unless... 

Hmm wait, actually: what is `qty_n_refs` for val? It's the number of REGs in the qty (refs). val is used twice (def + use). The const: def + use = 2. Same.

What about qty_size? Both SImode = 4.

So val: 8/(75-53=22) = 0.36; const: 8/(72-70=2) = 4. Const wins.

For (a) we'd need val's life ≤ 2 or refs much higher.

Hmm, BUT: what if the load's value and the addiu are in *different basic blocks*? Then local-alloc allocates per block; the value would be global. Hmm.

Alternative (b): make the const pseudo prefer v1 via a copy preference. E.g., if the constant 1 comes from a `li` that's a copy of another value already in v1? 

Hmm, what about making the const store use `$v1` implicitly by tying: e.g., `D_801B7988 = func_returning_1()`? no.

What about making the constant store a *copy from a variable that lives in v1*? 

Hmm, hold on. What about the ORDER of the load vs the const in the RTL: if the const's li (insn 70) were born BEFORE the load (53), then... the const's life would be longer only if its use is still at 72. If the li is at, say, insn 40 and used at 72, life = 32 → priority 0.25 < val's 0.36 → val wins!

So: make the `li 1` be born early in the RTL (before the load) but stored late. How? Write the source as:

```
s32 one = 1;        /* born early */
...
D_801B7988 = one;   /* late */
```
The `one = 1` assignment at the top of the case block emits a `li` there... but wait, if `one` is a constant with one use, gcc's cse/combine might propagate the constant into the store and delete the early li (REG_EQUIV). Then the li is born late again.

Hmm, but if it survives as a `li` at the top, we'd get the same 71 insns (the li moved earlier). That's exactly what we want — as long as the RTL order change doesn't alter the final schedule badly.

But the target's li is at position 8410 (right after the load). If the li is born early (before the stores) but sched1 schedules it... The target's li is right after the load, before the stores. So having the li born early is compatible!

Let me try: declare `s32 one = 1;` at the top of the case block, then `D_801B7988 = one;` at the end. Risk: the compiler folds it back.

Alternatively, make the constant 1 come from an expression that can't be folded, e.g. `D_801B7988 = (D_801B7A84, 1);` no.

Let's try the `one` variable.

Another idea: what if the const is 1 and it's stored via a variable that also holds something else...

Let me also try the reverse: make val's use adjacent (the `val = D_801B7A84 + 1` idea) — that changes the RTL order (addiu right after the load), which sched1 may then move to the end. Let me test both.

Also: what if we use `val` twice: `D_801B7A84 = val + 1;` plus a dead use? Dead code would be deleted.

Let me write these variants:
- w40: `val = D_801B7A84 + 1;` after the calls; `D_801B7A84 = val;` at the end (with the do-while around the stores).
- w41: same but no do-while (plain).
- w42: `s32 one = 1;` at decl, `D_801B7988 = one;` at the end, do-while around the stores.
- w43: w42 without the do-while.
- w44: w40 + `one` variant.

Let me write them.
