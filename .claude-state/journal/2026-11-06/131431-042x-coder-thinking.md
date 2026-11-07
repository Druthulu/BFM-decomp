---
ts: 2026-11-06T20:14:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fjJ8azVGkUlvfzv4QpYW
---
insn_count is now 29, yet "Insn 100: regno 90 (life 1) moved to 533" — still moved! So the threshold must be ≥ 29, meaning n_non_fixed_regs is higher than I thought: threshold = 1*(1+n) ≥ 29 → n ≥ 28. So lever-free n_non_fixed_regs = 28, threshold = 29, and with the pin n = 27 → threshold 28. So hoist iff insn_count ≤ 28 (lever-free) or ≤ 27 (pinned). Since insn_count=28 in target, pinned threshold 28 → 28>=28 would hoist... but it didn't!

Hmm wait: with the pin, threshold = 1*(1+27) = 28, insn_count 28 → 28 >= 28 true → hoist. But target didn't hoist. So maybe with the pin n=27 → threshold 28 and hoist should happen. Contradiction. Unless the pinned version's insn_count is different, or loop_has_call... or the pinned version has a different `lifetime`/`savings`.

Let me dump the *orig* (pinned) version's loop dump to see the actual values. That's decisive.

Let me splice orig.c (identical to src) — that's the TU itself. Run cc1 dumps on the src TU directly.
