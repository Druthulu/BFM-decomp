---
ts: 2026-11-06T22:46:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NSRjXogpfKxNSFBYnPmg
---
The div is a parallel → expand_preferences skips it (single_set = 0). So no merge there.

Hmm, so where does the a1 preference come from? Let me look at `set_preference` for insn 6 again: dest = r74, src = $a1. set_preference(r74, $a1): src_regno = 5 (hard), dest_regno = 74 (pseudo). The condition at line 1601: src < FIRST_PSEUDO and dest >= FIRST_PSEUDO and reg_allocno[dest] >= 0 → set hard_reg_preferences[allocno(r74)] |= 5. Yes, r74 gets a1.

Then expand_preferences propagates via REG_DEAD merges. For r77 (iVar4) to get a1, there must be a chain of merges from r74 to r77. The chain: r74's preference propagates to a set where r74 is a dying src. The div has REG_DEAD r74, but it's a parallel (single_set=0). Hmm. Any other insn with REG_DEAD r74? 

Hmm, wait — maybe expand_preferences runs on the RTL BEFORE the div is formed as a parallel? No, it runs in global_alloc after all the RTL is final.

Let me search for REG_DEAD r74 (reg/v:SI 74) in the lreg dump.
