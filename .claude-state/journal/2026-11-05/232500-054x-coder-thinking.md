---
ts: 2026-11-06T06:25:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aaFj6b2l0vlVyXyK8tRJ
---
Now the codegen is very different: mine uses `div` (a real division!) instead of the magic multiply — meaning loop.c's strength reduction / the "div by const" expansion changed. Wait: mine has `div zero,v0,s4` where s4 = mod (a variable divisor). Target has `div zero,v0,s2` too — OK that's `rand() % mod`, a variable modulo. Fine.

The 102 vs 106 insns and the frame -72 vs -80: mine now needs fewer callee-saved regs (s7 missing). The target saves s7 = arg0.

So the goto conversion changed too much. Mine: `move s6,a0` (arg0 in s6) vs target `move s7,a0`.

Hmm, the goto version dropped 4 insns and changed the whole register allocation. The differences in the loop body order are substantial.

Let me reconsider. Maybe a better approach: keep the for loops (loop notes) but block just the hoisting. Since the hoisting (s5 array base, s8 magic) is what we want to avoid.

Wait — hold on. Why does the *target* (with the levers) not hoist? Because of the launder asm? The launder is `__asm__ ("" : "=r"(tmp) : "0"(tmp));` — an asm insn in the loop. In loop.c, `move_movables`/`strength_reduce` may bail when the loop contains an asm? Hmm, but the *pin* is also there.

Actually! I recall: in gcc, an `asm` in the loop makes `loop_optimize` skip some optimizations because `loop_has_volatile`... no, that's for volatile.

Hmm, but actually the launder asm has an output operand — it's a "set" of tmp from tmp. loop.c's move_movables could hoist it... but its operand is in a hard reg? No.

Let me think about the s5 hoist (array base). loop.c's strength reduction creates a new register. There's a check `loop.c: if (loop_has_call) ...`? Actually there IS: gcc's loop.c refuses to hoist/strength-reduce when the loop contains a `setjmp` or... Let me grep loop.c for "asm".

Actually — simpler hypothesis: with the asm present, `loop_optimize` finds `NOTE_INSN_LOOP_BEG`... no.

Let me test empirically: take win.c (for loops, no levers) = w1.c, and add back ONLY the launder asm; see if the hoisting disappears. That tells me whether the launder (an asm insn) is what blocks loop.c. If yes, I need a plain-C equivalent that blocks loop.c the same way.

But actually, the more direct question: which lever blocks the hoist — the pin or the launder? The pin is `register s32 tmp __asm__("$2")` (a hard-reg variable). A hard-reg variable in the loop means `tmp` is a hard reg, and loop.c... hmm, the launder asm and the pin are related: the launder's operand is tmp which is a hard-reg var.

Let me test: w2.c = for loops + launder asm restored (no pins). w3.c = for loops + pins restored (no launder).

Wait, but orig (both) scores 0. So one of them blocks it. Let me test.

Actually, time is a factor. Let me be strategic: the goal is score 0 with no levers. The target's shape: no hoisting, plain index addressing, magic per iteration.

What plain-C construct blocks loop.c's strength_reduce and move_movables? Known: `goto` loops (no LOOP notes) — but that changed too much (102 vs 106).

Hmm, but wait: with goto loops, the target's *other* loop optimizations are also gone: e.g., the target has `lhu $2,34($sp)` before `sra $21,$20,31`... those are just sched.

The goto version's problem might not be the loop shape per se but that I introduced `{ }` blocks and the code differs. Let me look at the goto diff more: mine 102 insns vs target 106. Mine's frame is 72 vs 80 (one fewer saved reg). The target saves 8 callee-saved ($16-$23) and mine saves 7.

Hmm, actually here's a thought: in the goto version, `u = D_8018E894[i]` is still there and loop.c didn't run... so why fewer regs? Because without loop.c, some invariants are computed inside the loop, needing fewer registers? But the target (with for loops and levers) uses 8.

So the target shape is NOT simply "no loop.c". Something else.

Let me check what loop.c did in the target. In the target, is there any hoisting? Looking at the target asm: the outer loop computes `sll $2,$19,2` before L201 and in the delay slot; `lw $2,D_8018E894($2)`. That's plain indexed access — no GIV. And the magic constant is inside the inner loop.

Hmm, so loop.c in the target did... nothing? Let me check whether loop.c even ran: does the target's .loop dump show the function with LOOP notes? Let me check the .loop dump section for func_801834A4 — if it has NOTE_INSN_LOOP_BEG, loop.c saw it.

Actually, maybe the key: `D_8018E894` is declared `extern s32 D_8018E894[];` INSIDE the function. A symbol array. loop.c's strength reduction needs `find_mem_givs`. 

Wait, but in MY win.c (lever-free, for loops), it DID strength-reduce (s5 pointer increment). So loop.c runs and reduces.

Difference between mine and the target: the levers. So one of the levers blocks loop.c. Most likely the launder asm: gcc's loop.c has this in `strength_reduce` or `move_movables`:

Let me grep loop.c for "asm".
