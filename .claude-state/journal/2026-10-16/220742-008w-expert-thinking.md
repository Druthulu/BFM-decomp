---
ts: 2026-10-17T04:07:42.313Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9a47c75f80e15358
model: claude-opus-5-5[1m]
effort: medium
turnId: 6772ecdd-9745-42a2-882f-578d1c390899
---
I need to re-verify state after the struct_types.h changes with the typedef aliases, re-running the residue and cast checks, classify.py, and check-structs. I'm wondering whether canon_types captures the new typedef aliases or if sites stamped with aliased names would slip through unrecognized.

I should check whether check-casts --residue recomputes residue_cause live versus just reading the stamped ledger value — if it's computed live and aliases dropped from canon_types, TNC could rise unexpectedly. I'll just run the full re-verification as one background chain script since the census takes a few minutes.

All the implementation work (sweeps, residue chain, prune, struct fixes, router scoping) is done. Since c2's typedef alias rewrite touched 557 defs after the chain ran, I'll re-run the full verification suite (check-residue x3, check-casts --residue, classify, check-structs) to confirm no sites regressed to TNC or drift.
