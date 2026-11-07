---
ts: 2026-11-06T16:50:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pOzMkD2UVxQrQ9nJ45Jc
---
Same as win: cse keeps the symbol in a pseudo (line 389 `(set (reg/v:SI 86) (symbol_ref ...))`). The `reg/v` pseudo is created by the C front end for the cast expression? Actually `reg/v` = a pseudo for a variable. Hmm, where does a variable come from in the inlined expression? The `(void *)(s32)D_8018E2DC` — the front end may create a temp.

Let me look at the .rtl (before cse) to see how the argument is expanded.

Actually, more productive: let me look at how the target's original likely expressed this. The target materializes the symbol per call. In GCC 2.7.2, passing a symbol address as an argument would normally create a pseudo (reg) set to the symbol_ref, then the call uses the reg. cse then merges pseudos with equal constants. To prevent merging, the constant must not be recorded in cse's table — e.g. if the value is used only in one block and the table is invalidated.

Wait — cse's constant table: `qty_const` records that a register has a known constant value. When the same constant appears again, cse may reuse the register. But at a CALL, the register holding the constant is a *call-clobbered* reg (a1 = $5). cse can't reuse a call-clobbered register across a call. So cse would create a NEW pseudo for the constant after each call. But in our dump, pseudo 86 is a `reg/v` (variable) — it's the same pseudo reused across calls, meaning the front end/expand created ONE pseudo for the variable m, not cse.

So the merging happens at the *tree/expand* level: `s32 m = (s32)D_8018E2DC;` — the variable m is a single pseudo in the function, assigned at each site. But we inlined the expression in x1! Yet the dump still shows reg/v 86. That's because my regex missed one site (line 4895 has `s32 m`). The reg/v 86 might be that one leftover. But the score is identical (106) either way, so the leftover isn't the cause.

Let me look at the x1b RTL (before cse) around the first call to see whether the argument is a constant or a pseudo.
