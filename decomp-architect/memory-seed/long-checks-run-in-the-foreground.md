---
name: long-checks-run-in-the-foreground
description: A long verification target run as a BACKGROUND task can be killed by the harness's low-memory guard during a transient spike; run it in the foreground with an explicit long timeout, log to a file, and check for orphaned workers afterwards
metadata:
  type: feedback
  upstream: PA
---

Long verification runs (the project's health target, a fleet rebuild) belong in the foreground with an explicit timeout, their
output redirected to a file with the exit code appended.

**Why:** the source project's health target, run as a background task, was killed twice in one session with "the system is
running low on memory" — both times inside a step whose worker fan-out is a transient memory spike, with tens of gigabytes free
seconds later. The same command in the foreground, with a fifteen-minute timeout, passed both times. The killed run also left a
tool's scratch file behind that must never be committed.

**How to apply:** `make <health-target> > <scratch>/<task>_health.log 2>&1; echo "EXIT=$?" >> …` in the foreground, never as a
background task; read the exit code, not the last line of output. While there, check the process table for orphaned workers
from earlier sessions and stop them by PID — never with a process-name pattern that appears in your own shell's command line,
which kills the calling shell.
