---
name: commit-task-autostage
description: Commit logs and research deliberately; force-add ignored tracked paths before commit_task.sh
---

# Committing alongside commit_task.sh's auto-stage

Captured 2026-09-30 from .run/P38/phaseend/sk_commit.md#Workflow.

## When to use
committing while coder runs or reports are pending

## Steps
- `tools/commit_task.sh` auto-stages everything pending under `phase-ends/current/{tasks,logs,research,discussions}`;
  whatever runs next sweeps another run's logs or a new research report into its commit (P38 T5.1: R3.38-002 rode in
  a coder commit; T5: a coder log rode in another's).
- Commit research and logs deliberately, in the commit that owns them, before the next coder commit runs.
- Gitignored-but-tracked paths (`.run/P3x/census`, `.run/P37/restruct/ledger.jsonl`) are refused: `git add -f` them
  first, then call commit_task.sh with the other paths.
- Messages: one line, at most 100 chars, no task id (the script prefixes it).
Origin: P38 T1, T5, T5.1, T10 summaries.
