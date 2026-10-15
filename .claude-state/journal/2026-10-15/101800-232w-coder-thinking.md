---
ts: 2026-10-15T16:18:00.513Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
I need to verify the "only newly backed entries" claim—s_macro_rows actually appends entries for all K sites it can back, including ones already backed, which contradicts the docstring. I should filter the result to keep only entries for sites that were unbacked before this call, matching on line/offset/class identity.
