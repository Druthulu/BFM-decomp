---
ts: 2026-10-17T11:43:29.264Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm tracing why register k ends up with 13 references versus j's 11, thinking through how the copy at t3v and the loop depth weighting in reg_n_refs contribute to that count across the preheader and inner loop.

Computing j's priority at 0.44 versus k's 0.4459, k edges ahead narrowly — but if k's live range extends to 75 or more it ties with j, and since j's allocno number is lower it would win the tie. So the real question becomes whether I can nudge k's live length up by one or shift which variable t3v reads, though cse2 would likely just rewrite t3v back to k regardless.

Trying k with 13 references instead doesn't pan out — the live length requirement balloons to 88+. Testing whether making k live longer (by setting it before j in the preheader) flips the priority so j wins outright, but the instruction order in the preheader has k first, so I'd need the scheduler to reorder by priority for this to help.

I need to check whether the tree version's `t3v = m*4` statement and `k = m` actually reference k directly, so I'm looking at the tree source for that inner block.
