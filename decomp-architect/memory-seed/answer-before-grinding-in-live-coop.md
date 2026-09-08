---
name: answer-before-grinding-in-live-coop
description: In a live co-op session (the person at the emulator or the controls, pacing on the agent's replies) END THE TURN with the answer they are waiting on before starting long autonomous work — only the final message of a turn is guaranteed to be seen
metadata:
  type: feedback
  upstream: PA
---

During a live interactive loop — the developer at the emulator, waiting on the agent's read of each step — text placed between
tool calls is not reliably displayed. From the developer's side the agent "never spoke again" after the step they had been asked
for, and they sat idle at a game-over screen while the agent ground builds for an hour.

**Why:** the harness guarantees only the FINAL message of a turn is seen. In co-op mode the person's time is the scarce
resource, and they pace themselves on the replies.

**How to apply:** when the person reports a step done, the very next thing they get is a turn-ending reply — the result of
their step and what to do next, or an explicit "your part is done, you can close X". Only after that turn ends does long
autonomous work start. When the interactive phase ends, say so unambiguously as a final message, not buried mid-stream. Announce
long grinds with their expected duration before starting them, and never leave a question from the person unanswered across
one.
