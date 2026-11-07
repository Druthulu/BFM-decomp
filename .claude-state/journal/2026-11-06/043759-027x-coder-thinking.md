---
ts: 2026-11-06T11:37:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XdBv85rL4P5BQ2qYZxgh
---
All 6. The copy is always merged. Let me think about what prevents the merge: the launder. What real C forces a value to stay in a hard register? Nothing.

But wait — maybe a different real-C structure creates a *live range split*: the value is live across the switch; if we force it to be used after a call in a different way... 

The target: value computed in a1, then the switch. In the 0x41 arm there's an indirect call (clobbers a1). So the value must be in a callee-saved reg before that call — hence `move s1,a1` placed in the delay slot of the beq to the 0x53 arm. But wait: the 0x41 arm doesn't use the value at all. So why does the value need to be in s1 at all before the call? Because after the call... no, the 0x41 arm returns.

Hmm, so the copy is placed in the delay slot of `beq v1,v0 (0x53)` — i.e., on the path to the 0x53 arm. The value must be in s1 (callee-saved) for the 0x53 arm because... the 0x53 arm also calls ratan2! The value sVar3 is live across the ratan2 call at the end. So sVar3 must be callee-saved (s1). And the original tmp is in a1 (pinned), copied to s1 before the call. The copy is hoisted into the delay slot.

Without the pin, the compiler just uses s1 throughout. The pin is what makes a1 hold the value until the copy point.

So: the copy exists only because of the $5 pin. With the pin present but the launder removed, the compiler computes directly into s1 (dropping tmp). Interesting — so the pin alone is dropped.

Wait, that means with no launder, the pinned hard-reg variable tmp gets eliminated: the value is computed directly into sVar3's reg. Why? Because `tmp` is a hard-reg variable whose value is only copied out; cse/regmove decides to compute into the destination.

What if tmp has a *second* use that forces it? E.g., if tmp were used in the case 0x41 arm... but that adds code.

Hmm, what if we use tmp's value in the condition of the switch? Like `switch (bVar1 + (tmp & 0))`? folds.

What about `switch (bVar1)` where we first do `sVar3 = tmp;` and then `if (tmp == -1) return -1;`? adds a compare.

The target's delay-slot copy: is it possible the original C had the copy in a place that naturally yields that? The launder `asm("=r"(tmp):"0"(tmp))` sits BEFORE `sVar3 = tmp;` and before `bVar1 = ...`. It forces tmp to be materialized.

What real C forces materialization of a value? Using it in a context that can't be folded: e.g., storing it to a global, or passing to a call. A *store to a global* would produce a sw — extra code.

But what about a store that flow deletes? C0414 "dead-reset cse-breaker". Hmm, a dead store: `tmp = tmp;`? no.

OK, maybe the answer: this item is a WALL with tag combine-copy-merge (or global-hardreg-reserve), best 6. But I need 30 scored tries. I've done: v1 (23), v2 (0, but keeps launder), v3 (6), v4 (6), a1,a2,a3,a4(err),a5,a6. That's ~9 scored tries. Need 30.

Hmm wait — v2 scores 0 and removes the barrier but keeps the launder. That's PARTIAL:launder. Actually PARTIAL means "win.c scores 0 keeping only those levers". So v2 = PARTIAL:launder. But we want MATCH.

Actually — hold on. Maybe I can remove the launder differently: the launder's *purpose* is to keep the copy. What if I replace the launder with a different real-C construct that is itself... hmm, what about using the pinned variable in an `if` that's provably false but not folded? 

Alternatively: what if `sVar3` is a *pointer-derived* value? 

Let me think about the actual optimization: with `tmp` pinned to a1 and `sVar3 = tmp`, why does the compiler compute into s1 directly? Because sVar3 is the only real user, and the copy is a "move" that regmove/cse optimizes. What if there's an intervening insn between the definition of tmp and the copy? E.g., the bVar1 load. Target order: `andi a1,v0,0xfff; lbu v1,169(s0); li v0,83; beq...` — the lbu happens after. In source, `bVar1 = *(u8*)(p+0xA9);` comes after `sVar3 = tmp;`. The launder is before sVar3=tmp.

If I move the bVar1 load BEFORE `sVar3 = tmp`, maybe the copy survives? Let me try: reorder so that `bVar1 = ...` precedes `sVar3 = tmp`.

Also try: put `sVar3 = tmp;` after the switch? no.

Let me try more variants:
- b1: move bVar1 load before sVar3=tmp.
- b2: `s32 sVar3 = tmp;` plus a use of tmp in the bVar1 expression? e.g. `bVar1 = *(u8*)(p + 0xA9 + (tmp & 0));` folds.
- b3: make tmp's declaration `s32 tmp;` then `tmp = expr; sVar3 = tmp;` (separate statement).
- b4: declare tmp and sVar3 both and do `sVar3 = tmp = expr;` chained assignment? That's a copy chain.
- b5: `sVar3 = tmp;` twice.
- b6: use `if (tmp < 0) tmp = -tmp;`? changes.

Let me try b1, b3, b4, b5.

Also, thinking about it more: maybe the copy can be forced by making the value live across the switch in a1 because sVar3's live range is split by the case-0x41 indirect call. In the target, the copy is in the beq delay slot. What if the C uses the value *in the switch discriminant*? no.

Let me just try.
