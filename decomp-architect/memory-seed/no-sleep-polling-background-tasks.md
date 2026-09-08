---
name: no-sleep-polling-background-tasks
description: Never sleep-poll a running background task — the harness re-invokes the agent when it completes; one sanity check right after launch, then wait
metadata:
  type: feedback
  upstream: PA
---

When a background task is running (a backgrounded shell command, a long command the harness moved to the background, a
subagent), do not issue repeated "sleep, then read the log" calls to watch it. The harness re-invokes the agent with a
completion notification the moment the task finishes; polling buys nothing and burns tokens.

**Why:** the developer flagged it hard mid-session — the agent had sleep-polled a long sweep every couple of minutes ("stop
polling, we talked about this, you are wasting tokens"). The harness's own guidance says the same.

**How to apply:** launch, then stop and wait for the notification. At most one quick sanity check right after launch, to confirm
the task started without a systematic error (an empty log and no process is "never started", not "running"). If the developer
sends a message while it runs, answer that; do not invent poll turns. Reach for paced checking, with a delay matched to how fast
the state actually changes, only for external work the harness genuinely cannot track (a CI run, a remote queue).
