---
name: resume-means-resume-the-run
description: "Resume" after a rate limit or interruption means replaying the interrupted work so it finishes itself — the same run, the same agent, transcript and cache intact; never re-plan, re-target or re-route models on your own inference
metadata:
  type: feedback
  upstream: PA
---

When the developer says "resume" after an interruption, they mean: pick up exactly where the work stopped, with the paid context
intact — not re-plan it, not re-target it, not route it to a different model.

**Why:** rebuilding targets or re-routing on the agent's own inference wastes the context already paid for and changes the
experiment; a replay finishes itself. Fifteen interrupted agents were resumed this way in one session after a provider rate
limit, each continuing from its own transcript.

**How to apply:** an orchestrated workflow resumes by its run id; a subagent resumes by a message to the same agent — "continue
exactly where you left off; your files are intact" — same agent, same model, transcript retained. When subagents will outlive
the session, the checkpoint must say how a fresh session aggregates their output (the tool that reads their transcripts and the
paths). Agents write their deliverables early — the draft file first, the verdict last — so an agent lost to a limit still
leaves something to bank.
