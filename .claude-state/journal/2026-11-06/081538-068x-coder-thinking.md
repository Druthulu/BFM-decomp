---
ts: 2026-11-06T15:15:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QiHt1PaGlDff2y71qYMk
---
Line 2372: `(jump_insn 492 491 478 ...)` — the branch's NEXT pointer is 478! And `(insn 478 492 494 ...)`. So after reorg, the order is: 492 (branch), 478 (andi in the delay slot), 494. So indeed reorg moved 478 into the delay slot.

And the dependency list of the branch: `(insn_list:REG_DEP_ANTI 478 ...)` — REG_DEP_ANTI on 478! The branch has an anti-dependency on 478, meaning 478's dest (a1) is read... no, ANTI = 478 writes something the branch reads? Actually REG_DEP_ANTI means "the branch's use happens before 478's set" — i.e., WAR: the branch reads a1? No, the branch reads a2/v0.

Hmm, but `insn_list:REG_DEP_ANTI 478` on the branch's dependency list means 478 must come after the branch (the branch's output/use is before 478's set). This is a WAR dependency: the branch (or something) reads a1, and 478 writes a1. What reads a1 before? Nothing obvious... unless reorg's `update_reg_dead_notes` / the delay slot machinery added it.

Actually the key: the branch has REG_DEP_ANTI 478 — this is because the andi's destination a1 is live at the branch? If a1 is live *after* the branch and the andi sets it, then moving the andi AFTER the branch... Hmm.

Anyway: reorg moved 478 into the delay slot. Why? Because `eligible_for_delay` allowed it. The resource check I traced should have blocked it via `set` accumulation... unless `insn_sets_resource_p(trial, &set, 1)` where `set` is cleared and rebuilt per branch but the branch's own `set` includes... Hmm.

Whatever the reason, the empirical fact: reorg steals the andi. To avoid it, the andi must not be in the same block before the branch, or must be ineligible.

New idea: make the andi *dependent on the branch's condition register* — no.

New idea: put the second set in the SAME block but AFTER the branch in RTL — i.e., in the fall-through, as the first insn. Then reorg's thread-copy would take it. Same result.

New idea: make the andi a *call-clobbering* insn? no.

New idea: give vol a second set that is a *memory load*, e.g. `vol = *(s32*)&vol;`? That's a load+store (2 insns).

Hmm. What about the second set being a `movhi`/`lui` pair? no.

Let me think about `eligible_for_delay` in mips.md.
