---
ts: 2026-11-06T20:50:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ERVNQhDBdL7JgHHLygaJ
---
Not our case.

This is getting deep. Let me step back and consider the practical question: is combine really the deleter, or is it `combine_instructions`'s final `try_combine` for i2=92, i3=101 where `dead_or_set_p(i3, 87)` returns TRUE because... `dead_or_set_p` checks if the register is dead after i3 (via REG_DEAD notes or a set). Hmm, in the .cse2 RTL, is there a REG_DEAD note on 87 somewhere? The first use insn 101 doesn't kill 87.

Hmm, wait — maybe the copy was combined with the *last* use first (combine goes forward, so no).

OK, let me look at the combine dump for insn 92's predecessors/successors more carefully: the dump shows `(note 92 90 94 "" NOTE_INSN_DELETED)`. And insn 101 uses 72. Let me check whether ALL uses use 72 or only some. Earlier grep for "reg/v:SI 87" in the combine section found nothing, so all uses use 72.

Hmm, maybe the copy was deleted by `combine`'s handling of `(set (reg) (reg))` where the dest is used once? No.

Wait — maybe it's not combine at all: maybe it's `jump_optimize(2)` (jump2), which runs after cse2 and before flow/combine. jump2 does cross-jumping and also `delete_unreferenced_labels`, `delete_noop_moves`! Yes — jump_optimize has `delete_noop_moves` which deletes `(set rA rB)` if... let me check. jump.c `delete_noop_moves`: "Delete insns that are no-ops, i.e. set a register to itself" — but also there's `mark_jump_label`... Actually jump_optimize has a `delete_noop_moves` that deletes `(set (reg) (reg))`? Let me check jump.c.

Hmm, but a copy `87 = 72` is not a no-op.

Let me check jump.c's `delete_noop_moves`.
