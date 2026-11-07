---
ts: 2026-11-07T02:08:41.973Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: e0c8644d-6ef7-4f4d-ab7b-71dcf29b7e37
---
The count dropped from 48 to 37, so 11 rows are gone, but one "ov_*" row may still be showing up as GONE. It could be a fleet-wide row where some copies are still verbatim, and strict mode still flags it. I'll check what verbatim_check's help says about that.
