---
name: restruct-cycle-watch
description: Launch, find, wake on and stop a detached restruct_cycle.sh without racing inflight.json
---

# Watching a detached restruct cycle

Captured 2026-09-30 from .run/P38/phaseend/sk_cycle.md#Workflow.

## When to use
running or relaunching tools/restruct_cycle.sh

## Steps
- Launch detached (the form in the phase plan's Context): `setsid nohup bash -c '... tools/restruct_cycle.sh ...' > .run/P<N>/restruct/cycle_<x>.log 2>&1 &`.
- The log stays 0 bytes until the first batch line; an empty log is not a dead cycle.
- Before any relaunch, look for a live one: `pgrep -af '^bash tools/restruct_cycl[e].sh'`. An unanchored
  `pgrep -f` matches the calling shell's own `bash -c` line; a double launch races `inflight.json` (P38 T4).
- To wake on exit without polling: `tail --pid=<pid> -f /dev/null` as a background task; its completion re-invokes you.
- Stop with `kill -INT <pid>`, wait for the exit, only then `--restore` (R118).
- On a stop with final X != Y the cycle leaves edited files as restruct left them: revert unjudged files before R22.
Origin: P38 T4, T6 summaries.
