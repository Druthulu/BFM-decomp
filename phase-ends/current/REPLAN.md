# REPLAN — Phase 3.40

Trigger: T2 returned `blocked` (63fc7e8bf6, work done and green) on the plan's own judgment clause: the projection shows TNC 0 does not fit the phase.
Question: how far 3.40 takes TYPE-NOT-CANONICAL (milestone says "with TYPE-NOT-CANONICAL gone").
Recommended (expert): approve the 95 % band (6,676 types, ~132.5k sites, ~10 h of sweep plus decision tooling) and leave the ~7k-site tail residual under a new single-use cause; TNC 0 is not worth thousands of one-site canonical structs.
Critic decision: needs-developer — milestone wording change; answered 2026-10-15.
Plan state: done T1 · T2 work done (blocked only on the judgment clause; mark done) · next T12 · queued T3-T11, T13, T14 · superseded none
Logs to consult: phase-ends/current/tasks/T2.md (lines 26-40: before/after, cost, projection, band policy, residual-type stamps), phase-ends/current/logs/T2.md
Developer decides:
1. 95 % band, tail under its own named cause, milestone amended — ~10 h sweep, decisions mechanised.
2. Literal TNC 0 — ~12.7k decision rows, ~8.7k new mostly one-site structs.
3. 80 % band — ~1.8k types, ~28k-site tail.
Recommended: option 1.

## Developer's decision (2026-10-15)
Option 1: "95% band: ~6.7k types, tail (~7k sites) stays residual under its own named cause; amend the milestone."
- Milestone: replace "with TYPE-NOT-CANONICAL gone … no TYPE-NOT-CANONICAL in its by-cause line (from 291,819)" by: TNC 0 for every type inside the 95 % band (6,676 types at the post-T2 census); the tail below the band covered by RESIDUAL rows under one new named cause (single-use / below-band, defined by a rule the tool applies, not by hand), its count stated; by-cause line otherwise free of TNC. The rest of the milestone unchanged (lever literal 0, lying 0, legacy-T7, check-structs, R22).
- T3 rewritten to the 95 % band with T2's mechanised policy (tasks/T2.md:39): define by default under the address name; residual by layout class (conflicts TYPE-UNION, size 0 TYPE-NO-LAYOUT, one field TYPE-SCALAR, negative offset TYPE-INTERIOR); folds only on detected E1/E2/E3 evidence; a one-time `--restamp` variant that also rewrites NO-EDIT stamps whose live cause is a residual row (~9.6k sites).
- Also carry (queued 2026-10-14 by Claude via plan_edit add-task, not yet in the plan): ledger backup at phase close after T13 — `tools/ledger_backup.py`: stripped gz copies (ROM-derived fields such as restruct `residual.pairs` objdump lines removed, found by a full scan) committed to `docs/ledgers/`, audit_public clean; full unstripped gz committed (never pushed) to a local clone of private `Druthulu/BFM-decomp-archive` at `../BFM-decomp-archive` under `ledgers/P<phase>/`; restore proven; wired per tools-edit-kit-corpus; docs/ops note + card pointer.
- Gotcha for T3+: the T2 re-draw cycle (LABEL_PREFIX=t2_r) stalled re-drawing the same 259 files with 0 conversions (rS10..rS20); a band sweep must shrink its drawable set or stop.
