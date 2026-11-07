---
ts: 2026-11-06T22:57:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CY8TA6pbxLZ8zvNdKe8j
---
dump_conflicts is called AFTER prune_preferences and BEFORE allocation. So the preferences shown are post-prune.

prune_preferences: for each allocno (from least to most important), it removes prefs that conflict (line 860: `AND_COMPL_HARD_REG_SET(hard_reg_preferences[allocno], temp)` where temp includes conflicts). And it computes regs_someone_prefers.

So r78's v0 preference might be removed because v0 conflicts with r78 (r99 = $v0). And the a1 preference remains.

But where does the a1 come from in the first place? expand_preferences merges. Hmm.

Let me look at the r78 (iVar4) merge chain more carefully with the post-local-alloc RTL:
- insn 90: `(set r78 (minus r76 r80))` with REG_DEAD r80. r78 and r80 don't conflict → merge r78's prefs with r80's. r80 (t) has prefs? At insn 88: `(set r80 (plus r77 4096))` — set_preference(r80, plus) → no. So r80 has no prefs unless merged from elsewhere.
- insn 100: `(set r78 (minus r76 r80))` REG_DEAD r76, r80 → merge.

Hmm, so no a1.

Wait, maybe the preference comes from the *div* insn after all: single_set on a parallel. Let me check single_set's behavior: it returns the SET if there's exactly one SET (ignoring CLOBBERs). The divmodsi4 parallel has TWO sets (div and mod) → single_set returns 0. So skipped.

Hmm.

Unless the divmodsi4 pattern's second set (mod) is eliminated by dead-code (REG_UNUSED), leaving a single_set? The REG_UNUSED note on the mod (r103) — combine/flow might delete the mod set, leaving only the div. Then single_set returns the div set! And the REG_DEAD r74 (d) would be a dying src → merge r78 (q) with r74 (d). r74 prefers a1! So q (r78... wait, in w0, q = r79) gets a1. And then iVar4 (r78) merges with q? Hmm, in w0, q = r79 and iVar4 = r78. The div sets r79 from r78 and r74. If single_set, dest r79, dying r78 and r74 → merge r79 with r78 and r74. r74 prefers a1 → r79 and r78 get a1!

YES! That's it. The div (after flow deletes the unused mod set) becomes a single_set `(set q (div iVar4 d))` with REG_DEAD iVar4 and d. expand_preferences merges q, iVar4, and d's preferences → iVar4 gets d's a1 preference!

And in the TARGET (pinned), d is a hard reg ($s0), not an allocno → reg_allocno[$s0] < 0 → the merge with d is skipped → iVar4 has no a1 preference → gets $v1. 

So the root cause is confirmed: `d = arg1` gives d an a1 preference, and the div's expand_preferences propagates it to iVar4/q.

To fix: prevent d from having the a1 preference. That requires d not to be set from $a1. 

How can d get arg1 without a copy from $a1? If arg1 is used directly (w4), the parameter pseudo has no a1 preference (no set insn)... but w4 showed r77 prefers a1. Hmm, maybe in w4 the div propagates from something else. Let me check w4's d (r73 = arg1 parameter) — does it prefer a1? The w4 greg didn't list a preference for 73. But r77 prefers a1. Hmm, so in w4 the a1 comes from elsewhere. Maybe the parameter's `reg_preferences` are set from the incoming hard reg by `global_conflicts`'s block-live setup? Hmm.

Wait, in w4, maybe there's still a copy: `(set r73 (reg $a1))` at entry for the parameter. Let me check the w4 lreg insn 4.

Actually, in w4's alloc table, r73 (9 refs/27) is the divisor. If there's an insn `(set r73 (reg $a1))`, then r73 prefers a1 → the div propagates to iVar4. Let me check.

Let me look at w4's lreg insn 4.
