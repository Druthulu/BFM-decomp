---
ts: 2026-11-06T22:54:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eHlALe3B4PLKgZzl2Nj2
---
So r77 is only set by the minus insns. No set from a hard reg. Yet the greg dump says r77 prefers a1. 

Hmm, wait — maybe the greg dump's "77 preferences: 5" is from `hard_reg_full_preferences` which includes the propagated ones, and the propagation is via expand_preferences. Let me re-examine expand_preferences: it iterates insns and for each insn with a single_set whose dest is an allocno, it looks at REG_DEAD notes. At insn 90: `(set r77 (minus r76 r79))` with REG_DEAD r79. Condition: `!CONFLICT(r77_allocno, r79_allocno)` and `!CONFLICT(r79, r77)`. r77 and r79 conflict? "77 conflicts: 74 75 76 77 2 29 64 65 66" — no r79. "79 conflicts: 74 75 76 79 29" — no r77. So no conflict → merge r77's prefs with r79's.

r79 (t) = (plus r75 4096) at insn 88 (no REG_DEAD) and (plus r75 -4096) at insn 98 with REG_DEAD r75. At insn 98: dest r79, dying r75. r79 and r75 conflict? "79 conflicts: 74 75 76 79 29" — yes, 75 is in the list! So CONFLICT(r79, r75) → the merge is skipped. Hmm.

So r79 doesn't get r75's prefs.

Then r77's a1 comes from r79's prefs (v0, per the dump). Hmm, the dump says r79 prefers v0 and r77 prefers a1. So r77 didn't get v0 from r79.

Wait, maybe expand_preferences is called BEFORE the conflicts are fully computed? Let me check the order in global_alloc: global_conflicts() then expand_preferences() then prune_preferences(). Hmm, the conflict matrix is computed first.

Hmm, this doesn't add up. Let me look at the actual dump line format — maybe "77 preferences: 5" is printed from `hard_reg_copy_preferences` or something else. Let me look at dump_global_regs in global.c.
