---
ts: 2026-10-22T05:47:22.113Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a933331c6d154adc4
model: claude-opus-5-5[1m]
effort: medium
turnId: d25270b4-e42b-432f-9435-484b642c2966
---
Looking at G07's results, there are 5 MATCH rows, but two of them—func_8012EF34 and func_8012EF70—need to be excluded from the bank brief. I should check whether the bank_swap/bank_rows tooling supports exclusions directly, or if it's simpler to just tell the coder to exclude those two functions for now.

Instead of moving those rows out to a side file, the cleanest approach is to edit G07/results.tsv and change the result field for those two rows to `HELD-DECL`, since bank tools only act on MATCH/PARTIAL entries and should skip anything else. I need to double-check how bank_rows actually processes these statuses to confirm that's safe.
