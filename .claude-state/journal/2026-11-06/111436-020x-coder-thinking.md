---
ts: 2026-11-06T18:14:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JgUl7nabmlHqOaOpC4B6
---
Key: `for (ins = born_index; ins < dead_index; ins++) IOR_HARD_REG_SET (used, regs_live_at[ins]);`

Note: born_index = 2*insn_number - 1, dead_index = ... For a value born at the load and dying at the store (the store in block d38), the range covers [2*load-1, 2*store+1). Hard reg a0 dies AT the load: regs_live_at is set after processing the insn (comment: "Set the registers live after INSN_NUMBER", both 2n and 2n+1). When the load is processed, reg_is_set(v1) born, then the REG_DEAD of a0 wipes it: `wipe_dead_reg` marks... `post_mark_life(regno, mode, 0, birth, death)`? Let's see wipe_dead_reg → mark_life with 0. In `mark_life`, regs_live_at is updated for a range. For a death at insn n, it presumably clears from 2n onward... but the IOR for the load insn happened after? Let me check ordering in block_alloc: it processes the insn, then IORs regs_live_at[2n] and [2n+1]. Death handling: `wipe_dead_reg(reg, output_p)` calls `post_mark_life (regno, mode, 0, birth, death)` where death = 2*n - output_p? Hmm.

Since a0 is dead after the load, regs_live_at[2n+1] would not include a0, but regs_live_at[2n] (before/at) does. The qty birth is 2n-1, so the loop `ins = 2n-1; ins < dead_index` includes 2n-1 and 2n — where a0 is still marked live at 2n. Hmm, then a0 would be used. Unless wipe_dead_reg marks from 2n (post_mark_life with birth = 2n) so regs_live_at[2n] is cleared too.

Let me check mark_life/post_mark_life quickly. Actually, the observed behavior says a0 is chosen, so a0 must be free over [2n-1, death). This is the "birth/death" mechanism: a register that dies in the same insn as the value is born is available, precisely because the value is born at 2n-1 (before the insn) but... Hmm, weird but empirical: it's chosen.

Rather than reverse-engineer fully, use empirical moves. What changes the choice? The `reg_alloc_order` — the order hard regs are tried. a0 is tried early; if free, chosen. To get $3 (v1), we need $3 free and a0 used (or a0 excluded by class). $3 is v1 which is a call-clobbered reg too.

What determines `used` set: fixed_reg_set (or call_used_reg_set if calls crossed) plus regs_live_at. Here no calls crossed for the load result (the function has no calls at all), so `qty_n_calls_crossed == 0` → used = fixed_reg_set. Fixed regs are $0, $1(at), $2? no... fixed_reg_set includes $0,$1, maybe $26-28, sp, fp, ra. So a0 is available.

reg_alloc_order for MIPS: let me check. In mips.h: REG_ALLOC_ORDER. Likely $2,$3,$4,...? Let me grep.
