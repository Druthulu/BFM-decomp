---
ts: 2026-11-06T17:19:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tmUDvUIL1P8Eb6051gPW
---
Still t7 even with only 6 uses (m2). And the first 6 ands (with the inline 0xFFFFFF) presumably use a different constant register that matches? Interesting: i4's score is 21 with only the second half differing. So the inline 0xFFFFFF in the first half was materialized in t6?! Let me see: if the first-half inline constant got t6, the diff would show only the second half (6 ands) mismatched = 6-7. But it's 21.

Hmm, the diff tail shows the last 6 ands mismatched (175-201). What about the first 6 (insns ~146-170)? They're not in the diff, so they match (using t6?). Wait, if the inline constant (used in the first half) is in t6, then the first 6 ands match the target (t6), and the second-half mask (m2) is in t7 → mismatched. That gives ~6 ands + maybe the mask materialization = fewer than 21? The score is a masked diff count including shifts.

Let me see the full diff for i4.
