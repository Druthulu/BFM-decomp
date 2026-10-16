---
ts: 2026-10-15T22:33:27.451Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: e38d62ab-3c00-4d8d-a7ba-8c504be79727
---
I'm tallying up row counts across the categories (225+18+5486+399+513+32), getting 6673, but the band total shows 6676 — leaving 3 rows unaccounted for that I need to track down.

Zero E1 folds stands out since E1 is gated at 50%. I'll run a quick scratch check against struct_map on a sample of 30 — 10 fold (only 18 exist, so I'll take 10), 10 residual, 10 define — before briefing c2.
