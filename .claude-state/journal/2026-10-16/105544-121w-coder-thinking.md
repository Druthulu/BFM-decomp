---
ts: 2026-10-16T16:55:44.318Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
Since lift_types handles that case, I'm planning to write a custom TSV with component rows and lhash-based ids, then dry-run a fold against all ids to check for refusals. I want to check how main's fold branch validates the TSV lhash input before relying on it.
