# How we work — bfm-decomp

<!-- The card: standing facts for every agent. Never appended to; the cap is
     card.max_chars in .claude/pa.json (default 7000), enforced by the archive.
     Each role prints its slice with `tools/card.py slice <role>`.
     Written at install (interview) and edited in the same task as whatever changed it (H7). -->

## Project <!-- roles: expert coder router planner review critic discuss auditor curator -->
bfm-decomp. Constitution `PROJECT_CONTEXT.md`; roadmap `GENERATION_PLAN.md`;
rules `rules/INDEX.md`; techniques `cookbook/INDEX.md`; ops detail `docs/ops/INDEX.md`.

## Developer <!-- roles: router planner review discuss auditor curator -->
Who: <!-- TODO DEVELOPER_NAME: no source found -->. Experience: <!-- TODO DEVELOPER_EXPERIENCE: no source found -->. Domain: <!-- TODO DEVELOPER_DOMAIN: no source found -->.
Preferences: recommendations, not questions. Plain-English recaps at phase end. A notification
whenever anything waits on them. Autonomy: <!-- TODO AUTONOMY_POSTURE: no source found -->. Notification channel: <!-- TODO NOTIFY_CHANNEL: no source found -->.
The developer pushes; agents never do. They ratify rules at the next planner session.
- drew-working-preferences: Drew's working style on BFM-decomp — autonomous-within-phases, ultracode effort, accepts recommended options, wants WSL/tooling decisions surfaced plainly

## Rhythm <!-- roles: router planner review discuss auditor curator -->
autonomous  <!-- autonomous: the router runs the phase end to end, stopping only at the two gates.
                  review: tasks marked `review: yes` end the turn with REVIEW.md and wait. -->
Gates: plan approval (planner session) and the milestone (verified by the closer expert).

## Tools <!-- roles: expert coder router planner review critic discuss auditor curator -->
PY = /usr/bin/python3

| Name | Command | Purpose |
|---|---|---|
| launch | `PY tools/launch.py --seed-only` | the pa-session's state detector; writes `.run/seed.md`; never typed by the developer |
| plan_edit | `PY tools/plan_edit.py` | the only writer of `PHASE_PLAN.md` (status, Changes, add/reopen) |
| status | `PY tools/status.py` | `.run/status.json` for the statusline; INBOX consume; waiting flags |
| task_log | `PY tools/task_log.py` | lint and finish a task summary (`Verified:` required) |
| research_add | `PY tools/research_add.py` | allocate a report id, write the index line |
| rules_add | `PY tools/rules_add.py` | add, supersede, promote, retire a rule |
| skill_add | `PY tools/skill_add.py` | turn a `workflow:` gotcha into `.claude/skills/<name>/SKILL.md` |
| cookbook_add | `bash tools/cookbook_add.sh` | add a cookbook entry and its index line |
| phaseend_index | `PY tools/phaseend_index.py` | assemble, lint and archive a PhaseEnd |
| genend_index | `PY tools/genend_index.py` | assemble and lint a GenerationEnd |
| commit_task | `bash tools/commit_task.sh` | the only commit path; explicit paths, no trailers, never pushes; auto-stages phase-ends/current/{tasks,logs,research,discussions,RECAP.md,TASK_PROGRESS.md}, but leaves reply-drafting discussion records unstaged and refuses messages mentioning a drafted/posted reply; citing an issue for a fix is fine (R120) |
| type_census casts | `PY tools/type_census.py --check-casts [--residue]` | cast-and-lying gate; `--residue`: raw P/I/X/M pass only if ledgered RESIDUAL(<cause>) per site; writes residue_census |
| run | `bash tools/run.sh` | any command that may print >40 lines; `--bg` / `--wait` for long compute |
| Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not | `Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not` | Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not |

## Skills <!-- roles: expert planner -->
<!-- one line per captured workflow; the SKILL.md is the canonical text -->
- <!-- TODO SKILL_NAME: no source found --> — <what it automates, when to invoke it>
- restruct-cycle-watch — Launch, find, wake on and stop a detached restruct_cycle.sh without racing inflight.json
- retire-doc-consumers — Grep and repoint tools, Makefile and docs that read a doc being retired, in the same task
- commit-task-autostage — Commit logs and research deliberately; force-add ignored tracked paths before commit_task.sh
- tools-edit-kit-corpus — After any tools/ edit: make kit-corpus, tool_dictionary row for new files, then make tools-health
- d1-snapshot — D1 readability snapshot: census to newest P dir, snapshot, timeline, progress --readme

## Paths <!-- roles: expert coder router planner review critic discuss auditor curator -->
- Oracles (the ground truth X3 names): <!-- TODO ORACLES: no source found -->
- Data: docs/decision-log.md
- Generated (never hand-edited, H1): <!-- TODO GENERATED_PATHS: no source found -->
- Hand-edited: <!-- TODO HAND_EDITED_PATHS: no source found -->
- Scratch: `.run/` (gitignored; never the system temp)

## Build / run / test <!-- roles: expert coder router planner review critic discuss auditor curator -->
- Build: `make`
- Run: `<!-- TODO RUN_COMMAND: no source found -->`
- Test / the gate: `make test` — green means <!-- TODO GREEN_MEANS: no source found -->
- Modes: <!-- TODO TEST_MODES: no source found -->
Long gates go through `tools/run.sh` with a raised timeout, never a poll loop.

## Conventions & house style <!-- roles: expert coder router planner review critic discuss auditor curator -->
- - **Document disabled logic.** When disabling or commenting out any logic based on evidence, leave a structured comment:
<!-- project-specific only; the general house style is in the project-architect skill -->

## Environment <!-- roles: expert coder router planner review critic discuss auditor curator -->
- OS / shells: Linux / bash
- Python: /usr/bin/python3 (3.12.3)
- Pins: <!-- TODO PINS_SUMMARY: no source found --> — detail in `docs/ops/INDEX.md`
- Harness gotchas that bite here: <!-- TODO HARNESS_GOTCHAS: no source found -->

## Docs map <!-- roles: expert coder router planner review critic discuss auditor curator -->
- `docs/ops/INDEX.md` — setup, env, pins, per-topic ops notes
- `cookbook/INDEX.md` — techniques, grep by tag
- `rules/INDEX.md` — full rule texts
- `phase-ends/TASK_INDEX.md`, `phase-ends/RESEARCH_INDEX.md` — what was done and what was learned
- `docs/research-archive/` — migrated legacy reports
- `docs/retired/` — everything moved out of the load order
