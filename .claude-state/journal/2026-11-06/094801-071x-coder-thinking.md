---
ts: 2026-11-06T16:48:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VEHlwiaxkmfYd9uNEa4N
---
Still 6 `s32 m =` left? My regex didn't match all (the ones with different spacing, e.g. double space before func). And the score is the same 106. Let me check what the remaining ones are and whether the replacement worked for the 9 laundered ones. The remaining 6 are the non-laundered ones. The laundered ones (9) were replaced. But the score stayed 106 — so inlining didn't help.

Hmm. So the hoisting isn't about the local m; it's the symbol address constant being cse'd across calls.

Let me dump the RTL for win.c to see exactly where the constants become registers. Maybe the culprit is cse's handling of `(symbol_ref)` in a call argument: the argument is a constant, and cse may hoist it? Actually, GCC's cse doesn't hoist constants across blocks. But the *register allocator* may keep a constant in a register if it's "expensive" (2 insns: lui+addiu). global.c/local-alloc may decide to keep it.

Wait, but target doesn't. So in target's RTL the constants were NOT merged into shared pseudos. What merges them? cse: two `(symbol_ref D_8018E2DC)` constants in different blocks are equivalent; cse's constant table records them and may reuse a pseudo. Actually, cse for constants: `hash_rtx` on a CONST/SYMBOL_REF... In cse.c, constants are entered into the table with a pseudo? Let me look at how cse handles constant addresses. There's `find_best_addr` and the "constant" handling.

Alternatively the merge could be done by *combine* or by the tree optimizer (fold) — no.

Let me dump and see. I'll dump win.c (no asm) and orig (asm) and compare the RTL around the calls. This will show where the address constants are.

Actually, maybe better to look at the .cse2/.cse dumps for the presence of symbol_ref in registers.

Let me set up the dumptu for win.c (p4-like scratch). Use --keep then copy the TU.
