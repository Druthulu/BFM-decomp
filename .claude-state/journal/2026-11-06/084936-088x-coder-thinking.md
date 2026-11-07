---
ts: 2026-11-06T15:49:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aLXYt5x6qxuu9tVHL1NZ
---
No change (4). Let me check the diff of va1 to confirm it's still the la position.

Think about how to force the la early. The target's la a0 is at insn 1-2, before the callee-save spills. sched2 picks by LUID (lowest LUID first). The first statement's set has the lowest LUID. But combine deletes it unless it's used.

Alternative: use arg *before* the call in a way that requires its value. E.g., pass arg to another function? adds code.

What about using arg in the loop (e.g. `func_80052E38(arg)` is the only use). Hmm.

What if we make the call argument not a copy of arg but a *direct* use of arg in the call? The call `func_80052E38(arg)` requires a0 = arg. If arg's value is opaque, the move is needed.

Plain C to make arg opaque: a function call result! E.g. `arg = &D_800AF648;` — no.

Wait, what if we set arg from the *function pointer*? no.

Hmm, let me reconsider: maybe the target source had `arg = &D_800AF648;` and the la was needed because of combine's substitution. A plain-C alternative: use arg in a *comparison* or a statement that forces its value: e.g. `if (arg == 0) ...`? adds branch.

What about `*(volatile u8 *)arg;`? That's a load (adds insn).

What about passing arg at its *real arity* (C0505 R19: "a call passed at its REAL arity (the extra arg costs 0 bytes — jump2 deletes the no-op copy)")? If func_80052E38 actually takes more args... but we don't know.

Hmm, let me look at how the *twin* function or other functions in this TU handle the same prologue idiom. The comment C mentions "Same idiom, banked: src/800.c:3826-3832" — let me look at that.
