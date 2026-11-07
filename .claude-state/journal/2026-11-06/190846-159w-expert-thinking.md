---
ts: 2026-11-07T02:08:46.847Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: e0c8644d-6ef7-4f4d-ab7b-71dcf29b7e37
---
The --update left the ov_* row in place, which may be intentional, since fleet rows might be meant to stay. I'll read the manifest row around lines 515-540 and the verbatim_check update logic that touches ov_* to see which it is.
