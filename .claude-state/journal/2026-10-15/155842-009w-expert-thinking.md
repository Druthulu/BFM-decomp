---
ts: 2026-10-15T21:58:42.955Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I notice struct_map still references 800D3888 even though it's already folded, and there are type conflicts at 800D3888 and 80126B58 — but conflicts alone are common in real structs, so naively applying "conflicts → TYPE-UNION" would mislabel most large types. I need to be more careful about when TYPE-UNION actually applies versus just conflicting widths at a single offset.

Let me check how T2 actually handled its 16 residuals by pulling those rows from type_folds.tsv — comparing conflict counts, size hints, field layouts, and negative offsets against the actions taken will help me calibrate the rule properly.
