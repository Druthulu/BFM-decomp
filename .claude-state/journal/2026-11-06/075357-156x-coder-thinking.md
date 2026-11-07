---
ts: 2026-11-06T14:53:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xEJVC0x7xEpiDmXdReoz
---
Line 1483-1492: `simplify_relational_operation` — this folds a comparison to a constant. This is in jump_optimize. It's the `if_then_else` simplification that folds `bne t,3` given... hmm.

Actually, the optimization that folds `bne t,3` given t==5 is likely in the SECOND jump pass using `reg_last_set`/known values. But jump.c doesn't do value tracking across branches. Hmm.

Wait — maybe the fold is simpler: after reload, the register t ($16) is set to 5 somewhere? No, t is a runtime value.

Let me reconsider. The fold `bne t,3,L73` -> `j L73`: how does jump2 know t==5? 

OH. Maybe it's NOT a known-value fold. Maybe it's the "jump to next insn" optimization: the `bne t,3,L73` where L73 is the very next block? No.

Let me look at the target's structure: `bne t,5,L71; bne t,3,L73; sel_054: ...`. The `bne t,3,L73` jumps to sel_094 (L73). If it's not taken, fall through to sel_054. 

In mine: `bne t,5,L71; j L73` — wait, mine's jump2 shows `(jump_insn (label_ref N))` after the `bne t,5,L71`. Let me determine the target of that unconditional jump. If it goes to L73, then mine is `if (t!=5) L71; else L73` — the same as the target's `if (t!=5) L71; if (t!=3) L73` ONLY IF t!=3 is always true (t==5). So yes, it's a known-value fold.

But how does jump2 know t==5? Maybe via `reg_last_set` in jump.c? Let me search jump.c for "reg_last_set" or "known".

Actually, maybe the fold is done by `reorg.c` (the delayed-branch pass) or by the `dbr` pass, not jump2. The `jump2` dump might be after reorg. Let me check toplev.c for the jump2 dump.

Let me check the toplev.c around the post-reload passes.
