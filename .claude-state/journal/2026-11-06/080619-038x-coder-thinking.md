---
ts: 2026-11-06T15:06:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6Yy7F0VfIjfCBNz40gMK
---
Key condition: `reg_n_sets[REGNO(x)] == 1 || reg_last_set_label[reg] == label_tick`. So if the register has exactly ONE set in the whole function, combine knows its constant value regardless of labels! That's why splitting EBBs (do-while) doesn't help: s0 has one set before the loop (the init) — wait, s0 has sets in the loop too (`s0 = s0 + 1`). So reg_n_sets[s0] > 1. Hmm, then the second condition: reg_last_set_label == label_tick, i.e., no label crossed since the set.

`label_tick` increments at each label. So inserting a label between `s0 = 0` and `a0 = s0 << 10` invalidates the known value! A do-while(0) creates a label? Let me check: do-while(0) in gcc 2.7.2... `do { s0 = 0; } while (0)` — the loop is optimized? At -O2 with the loop being do-while(0), gcc may still generate a label and branch. C0535 says it splits cse1 EBB. But d4 scored 5 — meaning the code changed (extra label/branch?) but score 5.

Hmm, but maybe the right placement is: put a do-while(0) *around the shift* or between the init and the shift. d4 wrapped only the init. The label would be after the init (the loop's end label), which is between init and shift. Score 5 though. Let me look at d4's diff.

Actually maybe `get_last_value` (line 6894) is the path that folds, and it uses LOG_LINKS/REG_EQUAL notes.

Alternatively, cse's fold: cse.c's fold_rtx substitutes constants via `reg_equiv_constant` within the same basic block (equivalence classes per block), plus `reg_known_value`? Let me check cse's fold_rtx for constants: search "reg_equiv_constant".
