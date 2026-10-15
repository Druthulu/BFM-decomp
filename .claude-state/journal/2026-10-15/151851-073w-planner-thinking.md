---
ts: 2026-10-15T21:18:51.423Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab5a3773d37dd2401
model: claude-opus-5-5[1m]
effort: high
turnId: 5357bd4a-9af8-47c8-b7d6-78b8d0e3eabd
---
I need to spawn a retriever to investigate T3's new pieces in restruct.py — specifically how type_folds() loads config, how fold_type() and residue_cause work, and the implementation details of the --restamp, --write-types, and --audit-types flags.

I also need the layout audit output (conflicts, size, field count, negative offset), type_census.py's residue_census tnc computation and cause tracking, restruct_cycle.sh's loop structure, and audit_public.py's ledger record shapes and twin detection source data from struct_map.json. Given the breadth, I'll split this into two retrievers: one covering restruct/type_census mechanisation, the other covering ledger shapes, audit_public, and the zero-work exit logic, each capped around 25 calls.
