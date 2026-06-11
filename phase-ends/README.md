# phase-ends/ — the living record

- `PhaseEnd_Phase[N].md` — written at each phase boundary (format defined in `PROJECT_CONTEXT.md`). Append-only history: build log, deviations, commit message, rules added, changelog. Never deleted.
- `CURRENT_PHASE.md` — the in-phase autonomous log: approved phase plan, per-task checkboxes, current task pointer, blockers. Created at phase start, updated after every task, absorbed into the PhaseEnd file and deleted at phase close. This is the crash/compaction recovery point.
- Sessions read `PROJECT_CONTEXT.md`, then every `PhaseEnd_*.md` in numeric order, then `CURRENT_PHASE.md` (if present) — in that order, every session.
