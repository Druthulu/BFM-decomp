---
ts: 2026-11-06T12:33:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t9dPdCys8lfKzf6cV7Bj
---
So `return ret` emits `v0 = ret` (a move) plus a `use v0`. The move can be coalesced away if ret is allocated v0.

Now, an important detail: `emit_insn (gen_rtx (USE, VOIDmode, return_reg))` — a USE of v0 at each return. That keeps v0 live at the return point.

Since global-alloc chose s0 in c1, the uninitialized entry live range forced a saved reg.

Let me check whether the live range really matters by another diagnostic: keep `return ret;` in the early spots but ALSO define ret at entry (`s32 ret = 0;`). Then the entry def is in... `li v0,0` at entry → but target has no such insn; it would also make ret live across calls → still s0 probably. Not useful.

Alternatively: make the early returns `return ret;` but place them AFTER the first arm def? Not possible; they're early.

So the "return 0" route costs 2 insns. But maybe gcc emits `li v0,0` → target has `nop` in the delay slots... In c2 we got 257 ins (target 261): +2 for the two `return 0` (li v0,0), and the diff showed `j ... li v0,10; li v0,42` insertions meaning target has extra insns elsewhere that mine lacks. Actually mine has 257, target 261, so mine is 4 short.

Hmm, wait. Maybe `return 0` in those spots is actually what the target does — but the target's asm has no li v0,0 there... unless the target's early return is at a place where v0 already holds 0? At 1a90: after `jal func_8012CAE4`, v0 = whatever. Hmm.

Let me look at the target's epilogue region 1e38-1e3c to see the return sequence.

Actually, let's look at what mine (c2) looks like at those early returns. If `return 0` emits `li v0,0` (1 insn) and target has none, the score difference is 2.

But actually maybe the target's C early return is `return ret;` with ret in v0 because the *pin* was the only way — and the whole point of this shard item is to find a lever-free route. So maybe the intended crack is different: restructure so that the early returns' value is dead. For instance, if the function's early return value is a pseudo that gcc assigns to v0 because its only use is at the return...

Hmm, what if we make ret a variable that IS assigned before those returns in the source, but the assignment folds to nothing? E.g. `ret = param_1;`? no, that's a move.

What if the early returns return the value of `func_8012C1B8()`? Look at the second early return: `ptr = func_8012C1B8(); ... if (ptr == 0) return ret;`. Hmm, at that point v0 = ptr = 0 (since the branch tests ptr==0). So `return 0` there might compile to `move v0,a0`? Actually a0 = ptr and it's known zero → gcc might emit `move v0,a0` or nothing? Target: `beqz a0,1e3c` — no insn at all! Because v0... hmm, at 1aa0 `move a0,v0` then beqz a0 → return. v0 already = 0. So the target's return there is value-free.

In c2 (return 0), what does mine emit? Let me check the diff: mine[20:22] region. Let me dump c2 asm and compare around there.

Actually, a cleverer idea: return the *same* pseudo but make it dead code... 

Alternative idea: since the target's early returns leave v0 untouched, maybe the target C returns a variable that gcc can prove is v0 already... 

Honest alternative: use a `s32 ret;` and early `return ret;` but make the pseudo's live range short by giving the early returns their own pseudo through a block-local declaration... 

Hmm! What about scoping: if the early `return ret;` is in a block where a *different* variable named ret shadows? No.

Let me try yet another approach: what if the whole function is restructured so ret's first assignment is at entry with the value 0 and the early returns use `ret`? Then `ret = 0` at entry: `li v0,0`? and live across the calls → s0. no.

OK let me look at the problem from the target's arm structure. Let me see the full target asm around the arms and the STORE to understand what C shape it is.
