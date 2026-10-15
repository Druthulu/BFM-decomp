---
ts: 2026-10-15T21:23:48.398Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab5a3773d37dd2401
model: claude-opus-5-5[1m]
effort: high
turnId: 67c8c132-74af-44ca-a763-17f687dad756
---
I'm thinking through where a new type-decision classifier should live—rather than creating a separate tool, I'll propose adding it as a mode on restruct.py (like `--decide-band`) to keep things consolidated, while keeping in mind the rule that any tool change needs accompanying wiring and documentation.

For T3 verification, I'm laying out a chain of checks—structure census, restruct self-test, clean build, extraction and checking across all jobs, and a tools-health pass—noting the health check may run long, which the expert will need to account for.

For the T3 done-when criteria, I'm specifying that the band file needs to be frozen from the post-T2 residue census with exact columns and a header documenting its source commit, sort order, and cutoff, matching T2's projected totals. I'm also considering how determinism should be verified by rerunning the census on the same tree, and flagging a subtlety: since type definitions can affect field-canon unions and thus cluster hashes, a rerun after a header batch needs to confirm band names still resolve correctly.

I'm now deciding that after each header batch, any band names missing from struct_map should be zero, or the tool must re-key them by anchor address and document that behavior. I'm also specifying that a decision tool should apply T2's policy to every band type—writing fold rows with evidence, residual rows by layout class, or define rows—plus residual rows for every tail type, all tool-generated without manual edits, verified by a stratified spot check of 30 random decisions split across fold, residual, and define categories against struct_map facts. I'm also planning banded header batches committing definitions in stages (216, then 1,834, then 6,676 by rank) with full R22 checks at each stage, plus a restamp variant that rewrites NO-EDIT stamps for residual-caused rows, complete with its own self-test.

I'm also working out that restruct_cycle.sh should exit cleanly with code 0 and a "nothing drawable" message when a batch produces zero conversions, confirmed on a test set with no drawable sites. I need to verify that the verdict list in restruct.py explicitly names TYPE-BELOW-BAND, wire R127 into the tool dictionary and docs, confirm check-structs passes with zero duplicate definitions, and ensure dead names are tracked and allowed until T4/T5. The summary should record per-action and per-class counts, frozen totals, and the TYPE-BELOW-BAND rule as a binding constraint—this is a substantial task, but the context estimate seems manageable.

For T4, I'm updating the done-when criteria: every ov_* body with band-type sites gets re-swept via restruct_cycle.sh batches until the drawable set shrinks to zero and the cycle exits without redundant redraws, followed by per-segment residue passes with multiple forms and a restamp step that converts TNC stamps to live or TYPE-BELOW-BAND designations.

For the NO-EDIT variant, I need to run it once against the roughly 9.6k TYPE-NO-MEMBER sites, then check residue counts are zero everywhere—no ov site should retain a TNC stamp, band types should show zero TNC, and the tail gets stamped TYPE-BELOW-BAND. I should capture before/after summary counts including the TYPE-BELOW-BAND tally and NO-EDIT numbers, and since per-segment by-cause breakdowns aren't available, I'll rely on the whole check-casts output for verification instead.

For T5, the same structure applies plus fleet-wide checks: no TNC entries by cause, a TYPE-BELOW-BAND count that stays within the frozen tail site bound from the config header, and zero dead names remaining. I'm defining the verify step as a shell command that runs type_census.py with check-casts and residue flags, redirects to a log file, and greps to confirm no TYPE-NOT-CANONICAL entries exist—output size isn't a concern since it's redirected to file. T13's verification follows a similar pattern.
