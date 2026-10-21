# commit_task.sh: auto-staging and message rules

Moved from the card's Tools row (2026-10-21) to make room.

- `bash tools/commit_task.sh` auto-stages `phase-ends/current/{tasks,logs,research,discussions,RECAP.md,TASK_PROGRESS.md}`.
- It leaves reply-drafting discussion records unstaged and refuses messages mentioning a drafted/posted reply.
- Citing an issue for a fix in the message is fine (R120).
- Ignored-but-tracked paths: see the `commit-task-autostage` skill.
