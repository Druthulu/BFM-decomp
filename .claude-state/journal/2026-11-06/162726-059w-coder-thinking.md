---
ts: 2026-11-06T23:27:26.342Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a9d567e322a9bc10c
model: claude-opus-5-5
effort: medium
turnId: 7b1ff7f4-97be-400b-8730-ea952456489e
---
The uncovered count is zero, and the lying=3 and unbacked=1 results are already there before my changes, so they aren't mine to fix. The tracked .run files churning around is also old, and I didn't touch them, so I'll leave them out of this commit. I just need to work out where the restruct ledger lives and whether it's tracked, then check git status for config/ and ledger-style files so the commit holds only the src and TSV changes.

Casts are clean with zero uncovered in every form; the remaining rc 1 comes from lying=3 and one unbacked CAST_NONSTRUCT, both pre-existing. I'm now checking which tracked non-.run files changed, such as any restruct ledger.
