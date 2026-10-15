# How we work — bfm-decomp

<!-- The card: standing facts for every agent. Never appended to; the cap is
     card.max_chars in .claude/pa.json (default 7000), enforced by the archive.
     Each role prints its slice with `tools/card.py slice <role>`.
     Written at install (interview) and edited in the same task as whatever changed it (H7). -->

## Project <!-- roles: claude expert coder planner review auditor curator -->
bfm-decomp. Constitution `PROJECT_CONTEXT.md`; roadmap `GENERATION_PLAN.md`;
rules `rules/INDEX.md`; techniques `cookbook/INDEX.md`; ops detail `docs/ops/INDEX.md`.

## Developer <!-- roles: claude planner review auditor curator -->
Who: Drew, solo developer; Claude does nearly all the work. Experience: cannot hand-read MIPS asm, so relies on
Claude to explain domain tools. Domain: Brave Fencer Musashi (SLUS-00726) matching decomp, now legible source.
Preferences: recommendations, not questions. Plain-English recaps at phase end. A notification
whenever anything waits on them. Autonomy: autonomous within phases; execute an approved plan without per-step asking. Notification: the harness toast.
The developer pushes; agents never do. They ratify rules at the next planner session.
- "Should we X?" asks for Claude's recommendation: answer it with the reason; record it as Claude's recommendation.
- Offered stop rules, he picks the strictest and amends it once the residue is bucketed: offer the buckets.
- A misconception in a request is corrected before any costly or hard-to-reverse step.
- A new tool or dependency: what it does, what ours already does, the delta. Environment needs stated plainly.
- Live co-op: end the turn with the answer he waits on before any long work; say plainly when his part is done.
- The agent cap is his live dial; the latest word binds from the next spawn.
- After a Ghidra MCP restart or program switch, ask him to run `/mcp` first (`docs/ops/mcp-reconnect-after-restart.md`).

## Rhythm <!-- roles: planner review auditor curator -->
autonomous  <!-- autonomous: the loop (the mod) runs the phase end to end, stopping
                  only at the two gates. review: tasks marked `review: yes` stop the queue with REVIEW.md. -->
Gates: plan approval (in the plan-mode view) and the milestone (confirmed by the
developer at the close question).

## Tools <!-- roles: expert coder planner review auditor curator -->
PY = /usr/bin/python3

| Name | Command | Purpose |
|---|---|---|
| launch | `PY tools/launch.py --state-json` | the state detector: the mod's read-only report; never typed by the developer |
| plan_edit | `PY tools/plan_edit.py` | the only writer of `PHASE_PLAN.md` (status, Changes, add/reopen) |
| status | `PY tools/status.py` | `.run/status.json` for the statusline; INBOX consume; waiting flags |
| task_log | `PY tools/task_log.py` | lint and finish a task summary |
| research_add | `PY tools/research_add.py` | allocate a report id, write the index line |
| rules_add | `PY tools/rules_add.py` | add, supersede, promote, retire a rule |
| skill_add | `PY tools/skill_add.py` | turn a `workflow:` gotcha into `.claude/skills/<name>/SKILL.md` |
| cookbook_add | `bash tools/cookbook_add.sh` | add a cookbook entry and its index line |
| phaseend_index | `PY tools/phaseend_index.py` | assemble and archive a PhaseEnd |
| genend_index | `PY tools/genend_index.py` | assemble a GenerationEnd |
| commit_task | `bash tools/commit_task.sh` | the only commit path; explicit paths, no trailers, never pushes; auto-stages phase-ends/current/{tasks,logs,research,discussions,RECAP.md,TASK_PROGRESS.md}, but leaves reply-drafting discussion records unstaged and refuses messages mentioning a drafted/posted reply; citing an issue for a fix is fine (R120) |
| type_census casts | `PY tools/type_census.py --check-casts [--residue]` | cast-and-lying gate; `--residue`: raw P/I/X/M pass only if ledgered RESIDUAL(<cause>) per site; writes residue_census |
| run | `bash tools/run.sh` | any command that may print >40 lines; `--bg` / `--wait` for long compute |
| every other tool | `docs/tool-index.md` | generated from `config/tool_dictionary.tsv`; read by need |

## Skills <!-- roles: expert planner -->
<!-- one line per captured workflow; the SKILL.md is the canonical text -->
- restruct-cycle-watch — Launch, find, wake on and stop a detached restruct_cycle.sh without racing inflight.json
- retire-doc-consumers — Grep and repoint tools, Makefile and docs that read a doc being retired, in the same task
- commit-task-autostage — Commit logs and research deliberately; force-add ignored tracked paths before commit_task.sh
- tools-edit-kit-corpus — After any tools/ edit: make kit-corpus, tool_dictionary row for new files, then make tools-health
- d1-snapshot — D1 readability snapshot: census to newest P dir, snapshot, timeline, progress --readme

## Paths <!-- roles: claude expert coder planner review auditor curator -->
- Oracles (the ground truth X3 names): the Ghidra database (static) and PCSX-Redux (runtime), G1
- Data: docs/decision-log.md
- Generated (never hand-edited, H1): `asm/`, `extracted/`, `assets/`, `build/`, `docs/tool-index.md`
- Hand-edited: `src/`, `include/`, `config/`, `tools/`, `docs/`
- Scratch: `.run/` (gitignored; never the system temp)

## Build / run / test <!-- roles: claude expert coder planner review auditor curator -->
- Build: `make`
- Gate (R22): `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `218 passed, 0 failed of 218`
- Per binary: `make check BINARY=<alias>` (pass `-j`); main only via `tools/gate_main.py`
Long gates go through `tools/run.sh` with a raised timeout, never a poll loop.

## Conventions & house style <!-- roles: claude expert coder planner review auditor curator -->
- One commit per task; the developer pushes; no co-author or Claude-Session trailer; no tags or releases at closes.
- Third-party tools (maspsx, asm-differ, m2c, decomp-permuter) are git submodules, never vendored.
<!-- project-specific only; the general house style is in the project-architect skill -->

## Environment <!-- roles: claude expert coder planner review auditor curator -->
- OS / shells: Linux / bash
- Python: /usr/bin/python3 (3.12.3)
- Pins: `docs/ops/version-pin-summary.md`; WSL disk capped at 75 GB (`docs/ops/wsl-disk-capped-75gb.md`)
- Harness gotchas: `make tools-health` runs in the foreground (the low-memory guard kills it in background)

## Docs map <!-- roles: expert coder planner review auditor curator -->
- `docs/ops/INDEX.md` — setup, env, pins, per-topic ops notes
- `cookbook/INDEX.md` — techniques, grep by tag
- `rules/INDEX.md` — full rule texts
- `phase-ends/TASK_INDEX.md`, `phase-ends/RESEARCH_INDEX.md` — what was done and what was learned
- `docs/research-archive/` — migrated legacy reports
- `docs/retired/` — everything moved out of the load order
