---
ts: 2026-11-06T22:53:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yBx6DEDXASFPsKLn9EQI
---
Only set_preference. So the preferences must come from set_preference calls. For r77 to prefer a1, some insn must set r77 from a hard reg... but there's none.

UNLESS the "77" in the greg dump is NOT the lreg r77. Wait — the greg dump is generated after global-alloc. Let me check `dump_global_regs` — it prints `allocno_order` and the allocnos. The numbers are allocno indices? No, the .greg dump prints "N regs to allocate: 78 80 79 74 77 76" — those are register numbers (regno). And "N preferences: M" — M is a hard reg number.

Hmm, but maybe the preferences line is printed from `hard_reg_preferences[allocno]`, and allocno numbering differs from regno? The dump prints regno, so the mapping should be direct.

Wait, maybe the issue is that set_preference is called during global_conflicts, which scans the RTL. In the RTL, maybe there's a `(set (reg/v:SI 77) (reg:SI 5 a1))` that I missed because the grep pattern didn't match (e.g., the set is inside a parallel or a different format).

Let me grep the w6 lreg function for "reg/v:SI 77" with all occurrences.
