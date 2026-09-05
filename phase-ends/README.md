# phase-ends/ — the living record

- `PhaseEnd_Phase[N].md` — written at each phase boundary (format defined in `PROJECT_CONTEXT.md`). Append-only history: build log, deviations, commit message, rules added, changelog. Never deleted.
- `CURRENT_PHASE.md` — the in-phase autonomous log: approved phase plan, per-task checkboxes, current task pointer, blockers. Created at phase start, updated after every task, absorbed into the PhaseEnd file and deleted at phase close. This is the crash/compaction recovery point.
- `DIGEST.md` — the session-start digest: every phase's synopsis + every rule in full + the corrections to PROJECT_CONTEXT.md; appended at every PhaseEnd (P7). 
- `logs/Phase<N>.md` — the archived in-phase worklogs (R19): NOT in the load order; consult on demand only.
- Sessions read `PROJECT_CONTEXT.md`, then `DIGEST.md`, then the THREE most recent `PhaseEnd_*.md` in numeric order, then `CURRENT_PHASE.md` (if present), and replay its 🛑 SESSION CHECKPOINT block verbatim into the chat — every session (R64 candidate, 2026-09-05; ≈100k tokens + the checkpoint).
