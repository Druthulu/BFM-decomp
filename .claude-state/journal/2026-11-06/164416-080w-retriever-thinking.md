---
ts: 2026-11-06T23:44:16.822Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ad2f5b165a7f6e91c
model: claude-haiku-5-5
effort: medium
turnId: e4f74c0e-cf1a-45a1-8c3a-3307ee420397
---
I'm checking the SR3_ macro names against the 11-member family: one sits in ov_SC04_005 near func 8017BEBC, another in ov_SC03_092_jr_80181694.c. The names seem to encode the function they call, so the macro is probably the callee rather than the caller.

I still need the list of the 11 family members, so I'll grep lever_residue.tsv for them. I'll also check the 8015444C rows, where the barrier sits at file scope with a blank func. Then I want to pin down which lever and which macro are involved, starting with line 118 of lever_residue.tsv and the source around line 1590 of ov_MAIN_012. I've used six tool calls so far, so I have to be economical.
