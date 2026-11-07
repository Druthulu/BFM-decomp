---
ts: 2026-11-06T11:21:27.293Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a0b3b0b95decb7d18
model: claude-opus-5-5
effort: medium
turnId: 82a3dfed-296f-42cc-9272-9ebcd74b0bb0
---
I'm seeing 11 uncovered P sites, but the restruct sweep using `--only` with function names returned zero rows. The brief suggests passing segment names instead, while a gotcha note says function names are what it accepts, so I'm wondering if the ledger already has residue rows that explain the empty result. I need to find out which sites are uncovered, and check-casts may be able to list them.

I'm still trying to tell which sites are the uncovered ones, so I'll check the log for a flag that prints them.
