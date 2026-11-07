---
ts: 2026-11-06T20:10:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TO3rWowIu9XA7YPJu0ns
---
The loop with 28 real insns is our case-2 loop (Loop from 60 to 149). It has insn 136: regno 97 (life 1) move-insn savings 1 not desirable — that's the -146 constant (`li v0,-146`)? And reg 96 moved (probably the symbol addr or 5?). Wait, insn 136 is "possible biv, reg 97, const = -146" — that's the p++ or the -0x92 store... hmm -146 = -0x92. And the moved insn 96 = regno 90 (life 1) moved to 529.

Where's the -1024 constant? It's not listed as moved in this loop section! But the final code has li s4 hoisted. Hmm, maybe -1024 was hoisted by cse2 or another pass? Or the "moved to 529" is a different constant.

Wait, the -1024 store is in this loop. Let me check the .lreg dump for li s4. Actually the hoist decision might be from loop.c but the dump line for it is missing because the constant was already shared via cse? Let me grep the .cse dump around our function.

Alternatively, maybe the -1024 constant insn got hoisted by `loop` in the *second* loop pass dump (the .loop file contains two passes? there are multiple "Loop from" listings because the dump file accumulates per function per pass? The .loop dump has the function at 11144 and maybe again later for the second loop pass).

Actually gcc 2.7.2 runs loop once. But the dump file contains all functions in the TU. Line 11144 is our function's loop dump. Only one section. Hmm.

The "moved to 529" for insn 96 (regno 90) — insn 96 could be the `li 0x1C5` (453)? Let me map insn numbers. Let me look at the .loop dump's insn listing? The .loop file might include RTL dumps only in the .rtl file.

Better: check the .cse2 or .lreg dumps for -1024 in our function. Let me grep the .lreg dump (which shows reg allocation) around func_80180254.

Actually the simplest decisive check: the final `li s4,-1024` is in the preheader at 2124 (before the loop, after `move s3,zero`). In the loop dump, "moved to 529" for reg 90 at insn 96 — maybe insn 96 IS the li -1024 and reg 90 is its pseudo, "life 1, savings 1" and it WAS moved (to 529). And insn 136 (reg 97, const -146) was "not desirable".

So the -1024 constant (reg 90) was hoisted because threshold*1*1 >= insn_count (28). threshold = (loop_has_call?1:2)*(1+n_non_fixed_regs). With a call in the loop, threshold = 1*(1+n). For hoist: (1+n)*1*1 >= 28 → n >= 27. n_non_fixed_regs without pin = 27? Then 28 >= 28 true → hoist. With pin, n=26 → 27 >= 28 false → no hoist. That fits perfectly!

So the mechanism: the pin (fix_register) decrements n_non_fixed_regs, lowering loop.c's hoist threshold by one, which prevents the -1024 hoist. Wall tag candidate: this is exactly "global-hardreg-reserve"-ish but the mechanism is loop.c threshold. Let me check the walls list: `loop-extra-iv`, `global-hardreg-reserve`... none matches "loop hoist threshold from fixed reg count". This would be a new tag: `loop-threshold-fixedreg` — "the pin's fix_register lowers n_non_fixed_regs by 1, dropping loop.c's hoist threshold so the -1024 stays in the loop".

But before declaring a wall, can real C prevent the hoist? Options:
- Increase insn_count of the loop: the condition is threshold*savings*lifetime >= insn_count. insn_count=28 here. If the loop had more than 28 real insns... threshold=28 (n=27), so 28>=28 hoists. If insn_count were 29, no hoist. But adding an insn changes the code. Not viable.
- Make the constant's insn "not desirable" via m->lifetime: if life=2, 28*1*2=56 >= 28 → still hoist. No.
- Prevent the constant from being a movable: make the -1024 value non-invariant. E.g., derive it from a loop-varying value in a semantically-real way. Hmm.

What about expressing the store so that the constant is combined with the load: e.g., `*(s16*)(*p + 0xA) = -0x400;` — same.

What about making the store's value come from an array/global read that the compiler can't prove invariant? e.g. `= -0x400` is a constant.

Real C idea: since target has `li v0,-1024; sh v0,10(v1)` where v1 = reload of *p, maybe write the store with a temp that's *also* used elsewhere so cse merges: e.g. `s32 m = -0x400; ... m` used once. Same.

Alternative: get the constant into a register that's already live (no hoist benefit) — the hoist is about instruction count.

Hmm, another angle: maybe we don't need to prevent the hoist; maybe we can make the loop's insn count >= 29 by real C that matches target? No—target is 28 too.

What if we make the loop contain a call that's NOT recognized as a call? no.

What about making the constant insn *conditional*: `m->cond`? A conditional invariant isn't hoisted unless... the code checks `!m->cond || (invariant... )`. If the constant's set is inside a conditional (e.g., `if (x) m = -0x400;`), then m->cond is set and the hoist requires more conditions. But adding a branch changes code.

What about hoisting it *ourselves* in a way that matches target? Target has it inside the loop; hoisting ourselves is the opposite.

What about making the constant store use a different constant that the target also has? No.

Hmm, but wait: maybe there's another real-C change that shifts the loop's insn_count above 28 *without changing the emitted instructions* — e.g., an extra insn that gets deleted later. Unlikely.

Alternatively, raise `threshold` down? We want threshold*savings*lifetime < insn_count, i.e., lower threshold. n_non_fixed_regs is compiler-global, not C-controllable (except pins). Hmm... unless: declaring a variable `register ... __asm__` is a pin (banned). What about using `-ffixed`? no.

What about increasing insn_count by making the loop body bigger in RTL but generating the same final code? E.g., a dead statement that flow deletes after loop.c — loop.c runs before flow's dead code elimination? Pass order: cse, loop, cse2, ... flow. Dead code elimination (`delete_dead_insns`?) happens in flow? A dead insn inside the loop would increase insn_count and be deleted later by flow (dead store elimination) — that's C0414-ish "dead-reset" but here it's a dead *insn*.

E.g., add a dead store inside the loop: `t = 0;` then `t` overwritten before use? That would add an insn to the loop body, increasing insn_count by 1 → 29 → no hoist; then flow/cse deletes the dead store → final code identical to target!

But careful: the dead store must not affect scheduling/regalloc, and must be removed by flow (`delete_dead_insns` in flow.c removes insns whose dest is dead and no side effects). A dead assignment to a local variable inside the loop: `s32 junk = 0;` as a statement in the loop body — a store to a pseudo with no use. flow's dead code elimination (`flow_analysis` + `delete_dead_insns`?) In gcc 2.7.2, `flow.c` has `delete_dead_insns` called from `flow_analysis`? Actually `life_analysis` computes; `delete_dead_insns` is called in `flow_analysis`? Let me check: in gcc 2.7.2, dead code elimination of dead stores happens in `flow.c` via `delete_dead_insns` called from `flow_analysis`? There's `-dS` (cfg). Hmm.

C0414 in the cookbook is "dead-reset cse-breaker" — used as a cse breaker. Here we'd use a dead insn to change loop.c's insn_count. But insn_count in loop.c is counted from the RTL *at loop.c time*, before flow. Does cse run before loop? Pass order: `cse` then `loop` then `cse2`... Actually gcc's toplevel: `rest_of_compilation`: jump_optimize, cse, loop_optimize, cse (2nd), ... then flow. Dead store elimination: in `flow.c` `life_analysis`... Actually `delete_dead_insns` is called from `flow_analysis`? Let me check gcc-2.7.2/flow.c for "dead".

But also cse (first, before loop) might delete a dead store? cse does `delete_trivially_dead_insns`? cse calls `delete_trivially_dead_insns (insns, max_reg_num ())` at the end? In gcc 2.7.2 cse.c, yes there's `delete_trivially_dead_insns` maybe. Let me check.

Alternatively, a dead insn that survives cse1 but is removed by flow after loop.c: e.g., a store to a local that's overwritten — flow's `delete_dead_insns` removes stores to dead pseudos.

But wait: the dead insn must be *inside the loop* at loop.c time and must not change scheduling at sched time (removed before sched1? sched1 runs after flow? Pass order in 2.7.2: ... loop, cse2, life, combine, sched, local-alloc, global-alloc, ... flow is between? Let me get the pass order: `rest_of_compilation` in toplevel.c: jump_optimize(1), cse, loop_optimize, cse, jump_optimize(2), flow_analysis (life), combine, ... Hmm actually `flow_analysis` runs after cse2 and before combine: `life_analysis` computes regs; dead code elimination `delete_dead_insns` runs there. sched (sched1) runs after combine, before local-alloc. So a dead insn removed in flow (before combine) is gone before sched1. 

But would cse1 remove it before loop? cse1 does not delete dead stores in general; it may if a store is redundant. A store to a fresh local `junk = 0` where junk is never read: cse1's `delete_trivially_dead_insns`? Let me check.

Actually easier: just try it. Add `{ s32 junk; junk = 0; }` inside the loop body and see if score drops to 0. But we must be careful: the dead store may alter reg allocation even if deleted... if deleted before flow, no.

Hmm, but insn_count counts *real* insns in the loop (28). Adding a dead store makes 29. threshold = 28 → 28 >= 29 false → no hoist. Then the dead store is deleted → final 28 insns. 

But is the dead store deleted by flow? A store to a local variable that is never used: flow's `delete_dead_insns` deletes insns setting a register that is dead, if the insn is not a call/volatile. Yes.

But there's a risk: `delete_trivially_dead_insns` in cse (runs before loop) might delete it. Let me check cse.c.

Let me just test empirically: variant vD with a dead store in the loop.

Where to put it: inside the while body. Something plausible: at the top of the loop, `s32 z = 0;`? Declaration inside a block after statements is fine in gcc (not C89-pure but gcc allows). Actually gcc 2.7.2 with default is C89-ish; declarations must be at block start. We can declare `z` at function top and assign `z = 0;` inside the loop.

But careful: assigning a constant to a local that is never used — will it be deleted? Yes, dead store.

Alternatively use a dead reset of an existing variable like `off`? That changes semantics of off. Use a new var.

Hmm, but the brief: "Lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." A dead store to increase insn_count is a real-C move (C0414 dead-reset family). It's not a launder/barrier/pin. It should be acceptable as long as it's real C and the score is 0. But "no new lever of any kind" — hmm. A dead store that gets eliminated and only serves to perturb a pass is arguably a "dead-reset cse-breaker" which the MOVES+ explicitly endorses (C0414 cracked 3 launders). So fine.

Let me try.

Variant vD: add `z = 0;` inside the loop. Declare `s32 z;` at top. Place it where? It must be inside the loop body at loop.c time. Put it right after `*p = v0;`? Or at the end. The position affects insn_count only (count of real insns in the loop). Let's put it at the loop head or right before the call.

Wait, but if placed before the call, the store might be moved/deleted. Let's try a couple positions.

Actually, better idea: use a dead *load*? A dead store is simplest.

Let me create vD with `z = 0;` just before `p++;` maybe. And vE with `z = 0;` after the call.

Also I should consider that the dead store changes `insn_count` by 1 → 29 → no hoist. But loop.c also counts insns in the loop; the dead store is inside. Good.

Let me test.
