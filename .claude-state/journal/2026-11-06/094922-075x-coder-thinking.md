---
ts: 2026-11-06T16:49:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dpFctBCfevtDMozQJnvI
---
So CONST_COSTS for SYMBOL_REF = 2 insns (unless SYMBOL_REF_FLAG set → 1). cse's fold_rtx decides whether to use the constant or a register based on costs. For a symbol address (cost 2), cse may prefer keeping it in a register (a pseudo) because the register is "free" once allocated.

In cse.c there's logic around line 1359: "If this is a constant being set equivalent to a register..." and the "cheap constant" check. Let me look at where cse decides to make a pseudo for a constant. Search for "qty_const" and "COSTS_N_INSNS".

Actually, the key mechanism might be simpler: the *tree* or *expand* stage emits one `symbol_ref` pseudo per expression; cse merges them because the constant hash matches. To prevent merging, the expressions must be *different rtx*: e.g. one is `(symbol_ref "D_8018E2DC")` and another `(const (plus (symbol_ref) (const_int 0)))`. That's an identity address spelling — forbidden.

Hmm, but wait: maybe the original source used *different types* for the same symbol: e.g. `(void *)D_8018E2DC` (u8*) vs `(s32)D_8018E2DC` (int cast). The rtx for a cast of an address to int vs pointer might differ? After fold both become symbol_ref.

Let me look at the win.c cse dump vs the orig's cse dump to see whether the non-laundered group B also merged. In the target, group B materializes fresh too. So the original had *no* merging at all. The asm launders only cover group A and C (6 of 12 calls); groups B and D (6 calls) have no launder and yet target materializes fresh. So in the original, cse did NOT merge group B's constants with group A's. That means cse in the original didn't keep symbol constants in registers at all. Why would our win.c differ?

Look at win.c cse2: insn 153 creates reg/v:SI 86 = symbol_ref. That's a `reg/v` (variable) pseudo created by cse? Actually `reg/v` means a user variable pseudo from the tree/expand stage, not cse. Hmm, `(reg/v:SI 86)` with REG_EQUAL symbol_ref. This pseudo is the *variable* m (s32 m = ...). But we removed the launder; the local `m` remains in win.c (for the 6 non-laundered sites) and x1 inlined them.

In win.c, the laundered sites became `{ s32 m = (s32)D_8018E2DC; func(...); }` — so there are still locals m for those. The pseudo 86 is one such local.

For the laundered ones, after removing the asm, m is just a local assigned from the symbol; cse propagates the constant into the use and may keep it in a register.

Target's fresh materialization per call means in the original, each call's argument was a *constant expression* materialized at the call, not a variable. Inlining the expression (x1) should produce that... but x1 scored 106 too. Let me check x1's cse2: did the inlined version still merge? Let me dump x1.

Actually, maybe the merging is done by *global-alloc keeping the constant in a register*, and the pseudo comes from `expand` (the tree creates a temp for the cast?). Let me look at x1's cse2.
