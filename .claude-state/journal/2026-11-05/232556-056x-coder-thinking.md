---
ts: 2026-11-06T06:25:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pnU91TmQJgY9p5CLTg4C
---
Interesting! 
- w2 (launder kept, pins removed): 34.
- w3 (pins kept, launder removed): score 5, 106 insns = target count!

So the PINS are what block the loop.c hoisting (the hard-reg variable tmp blocks the strength reduction / move_movables). And the launder can be removed with a small residual (5).

So for a full MATCH I need to remove the pins too, which unblocks loop.c hoisting.

Wait, that's backwards from what I said: w3 has pins kept → no hoisting → 106 insns. w2 has pins removed, launder kept → 34. And win.c (both removed) → 41, 107 insns.

So: pins block loop.c. Removing them lets loop.c hoist. To get the target shape without pins, I need plain-C to prevent loop.c's hoisting.

Options:
1. goto loops (no LOOP notes) — tried, gave 102 insns, 44. Hmm, but that's *without* the pins; the shape was different.

Wait, why did goto give 102 insns while the target has 106? Because with the pins, the target has... hmm. Let me look at the w3 (score 5) diff to see what the launder removal costs. Then think about whether the goto version can be tuned.

Actually, let me reconsider: with pins kept + launder removed, score 5. The pins are the remaining lever. What do the pins do?
- They block loop.c (that's why the target's shape is un-hoisted).
- They put tmp and hh in $2.

If I can block loop.c in plain C, and get tmp/hh into $2 naturally, we get 0.

How to block loop.c's strength reduction in plain C? Ideas:
(a) A second set of the induction variable? no.
(b) Make the array access non-reducible: e.g., `u = D_8018E894[i]` — if the index expression isn't a simple biv (e.g., `D_8018E894[i + 0]`?), no.
(c) Put a construct in the loop that makes loop.c bail: e.g., a call to a function that could modify the array? `unknown_address_altered`? Hmm — `D_8018E894` is a global array; loop.c's `find_mem_givs` for a memory ref: if the address is `symbol + i*4`, it's a GIV.

Actually, what specifically does loop.c do with the hard-reg variable? A `register s32 tmp __asm__("$2")` makes tmp a hard reg — loop.c's `record_giv`/`move_movables` may bail because the pseudo is a hard reg? Hmm, in loop.c, `move_movables` skips insns that set a hard reg? There's a check "if (GET_CODE (SET_DEST (set)) == REG && REGNO >= FIRST_PSEUDO_REGISTER ..." etc.

Honestly the exact mechanism: the *pin* is a hard-register variable. In gcc, a hard-reg variable's assignments are real insns. In loop.c, `strength_reduce` is called only if `!loop_has_call`? No — there IS a call (rand, func_801850D8) in the loop! Let me check: strength_reduce's gate at the top.

Actually wait — line 3175: "loop doesn't contain a function call and the variable isn't volatile". And in strength_reduce there's a check `if (loop_has_call)` somewhere? Let me grep "loop_has_call".

The loop contains calls, so many loop.c opts are already disabled. Hmm, but mine DID strength-reduce the array base...

Let me look at the actual difference between mine and target in the .loop dump. Let me grep the .loop dump for the function and look for "giv"/"Reg" decisions. That'd tell the mechanism precisely.

But first — maybe there's a much simpler framing. Since the pins block loop.c, maybe what blocks it is the *asm insn* (launder) — no, w2 had the launder and still hoisted (34, but same insn count 106!). Hmm wait, w2: 106 insns = target count, but score 34. Let me check whether w2 hoisted. 106 insns matches the target. Hmm! So with the launder kept (pins removed), the insn count is right but the registers differ (score 34).

And w3 (pins kept, launder removed): 106 insns, score 5.

And win.c (both removed): 107 insns, score 41.

So the launder asm is what blocks the hoisting (w2: launder kept → no hoist → 106). And the pins block... hmm, w3 has pins and no launder → 106, no hoist?? That contradicts.

Wait: w3 = orig minus the launder line = pins kept, no launder → 106 insns, score 5.
w2 = orig minus pins = no pins, launder kept → 106 insns, score 34.
win = neither → 107 insns, score 41.

So EITHER lever alone blocks the hoist. Both together = no hoist (target). Neither = hoist (107).

Hmm, so each of them independently prevents loop.c's transformation. Interesting: the pin (hard-reg var) and the asm launder both break it.

Now the question: what plain-C construct breaks it?

Since either lever suffices, maybe the mechanism is: the launder asm is an insn whose pattern is an asm — loop.c's `move_movables` skips insns with side effects but still processes... Hmm, but why would it block the array GIV?

Alternatively the mechanism could be about `tmp`: with the launder, `tmp` is set twice (base = tmp, launder sets tmp, mod = ...). loop.c's move_movables might hoist `tmp = u*0x600+0x2000`... no, it depends on u.

Hmm, wait. Actually maybe the hoisting I see in win.c is not loop.c at all but **cse/global-alloc**! The address `&D_8018E894[i]` — with the loop, the address is `D_8018E894 + i*4`. In win.c, mine had `lui s5; addiu s5; ... lw v0,0(s5); addiu s5,s5,4` — a pointer increment = GIV strength reduction = loop.c.

OK. Let me directly check: is `loop.c` even enabled for this function? The .loop dump will show. Let me grep the target's .loop dump for func_801834A4 and look at what it says (e.g., "Loop from ... to ...", "giv").

Let me do that. It's the decisive evidence.
