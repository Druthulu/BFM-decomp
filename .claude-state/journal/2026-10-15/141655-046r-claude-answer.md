---
ts: 2026-10-15T20:16:55.090Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 5333dee7-fba9-4745-bbb6-027ff97d7eab
usage: {input: 6, cacheRead: 199651, cacheWrite: 1344, output: 808}
---

The PA3 update you were waiting for has arrived. Please restart Claude Code now: one of its settings only takes effect after a restart, and the restart also loads the new mod.

What it changes, in plain terms:
- **Restarts no longer pause tasks.** If Claude Code restarts, updates or the terminal closes while a task runs, the task's expert picks up by itself at the next start, and I tell you in one line. Only your own Ctrl+C waits for your go. This should end T2's run of false stop notices.
- **Long jobs run detached.** A long command such as a restruct cycle runs as a tracked job. The agent hands back "waiting on job" and stops, and the mod wakes it when the job ends, instead of the agent sitting in a waiting tool call. Pending jobs survive a restart.
- **The talk hold is tighter.** Only your messages hold the queue while we talk, and the hold ends 15 minutes after you last spoke.
- **Idle agents are handled better.** Waiting agents are kept warm by pings sized to them. Nothing is sent to an agent whose cache has gone cold; a fresh agent of the same kind takes the message instead.
- **Agents at their context limit** finish and commit only working code, save any unfinished edit as a patch, and hand off cleanly.
- **Smaller fixes:**
  - installing a new phase plan keeps finished tasks finished;
  - the mod's own commits get five minutes instead of one, and a leftover git lock is cleared automatically;
  - a running session checks for new releases every 8 hours and asks you once per version whether to install after the current task.

After the restart, T2 should resume on its own. If it doesn't, tell me and I'll restart it fresh from its log. The restruct cycle that was running stays committed batch by batch.
