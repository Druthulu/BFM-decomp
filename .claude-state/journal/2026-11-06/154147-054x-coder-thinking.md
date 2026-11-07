---
ts: 2026-11-06T22:41:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mAU4GYBOqiwtinHtPhGZ
---
Preferences are set by `set_preference(reg, prefreg)` during conflict scanning: for each insn, if a reg is used with a hard reg, it records a preference. So r78 preferring $a1 means r78 is used in an insn together with $a1.

Which insn? Hmm. `set_preference` is called in `mark_reg_...`? Let me look.

Actually, the preference could come from the *parameter* $a1 being used in the same insn as r78? No.

Hmm, wait: maybe the preference for r78 = a1 is from `expand_preferences` merging preferences across allocnos that are connected by copies. r78 (iVar4) is computed from r76 (u5) and r77 (u6). Hmm.

Let me look at the .greg dump again for w0: "78 preferences: 5" (a1). And r79? "79 preferences: 5" too. And r80 "preferences: 2" (v0).

In the target: r77 preferences: 17 (s1), r80 preferences: 2 (v0), r78 none, r79 none, r76 none.

So in w0, r78 and r79 prefer $a1; in the target they don't. The difference is caused by... the pin changes the pseudo set. In w0, r74 (d) is a global allocno; the copy `d = arg1` (r74 = $a1 copy) creates a preference for $a1 on r74. Then `expand_preferences` merges preferences between allocnos connected by copies: r74 (d) and r76/r78/r79? d is used in the div with r78 (iVar4) and r79 (q) — but that's not a copy. Hmm.

Actually, `expand_preferences` propagates preferences through *copies* (REG_NO_CONFLICT blocks / copy insns). d = arg1 is a copy; the preference a1 is on d. Then... hmm.

Wait, maybe the preference for a1 on r78/r79 comes from the *hard reg $a1's* usage. Let me look at set_preference: it's called for each reg in an insn with hard reg operands. If an insn uses both r78 and $a1... The div insn `div r79, r78, d` — no hard reg.

Hmm, let me look at the actual code that records preferences.
