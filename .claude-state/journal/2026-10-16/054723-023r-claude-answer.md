---
ts: 2026-10-16T11:47:23.693Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aede67d56d4362411
model: claude-opus-5-5[1m]
effort: medium
turnId: 5f33e801-261d-4ea0-8c35-8bdc8ca8f1d7
usage: {input: 12, cacheRead: 165865, cacheWrite: 1351, output: 703}
---

The update makes one change to the status line. In a 3.2 session, the model line used to show the context figure, which was always `0/1M` because the main session never calls a model. It now shows the session's total work instead, for example `4.3M/∞`. That number counts every token that went into the contexts of Claude and all its agents, each one once, and the starting prompt that agents of the same type share is counted only once.

The mod's own files changed too, so the new mod and agents load only when Claude Code restarts. No task starts until then. You'll pick up where you left off, and I'll go through T4's question with you then.

Project Architect 3.28.7, a hotfix (The model line shows the session's work), is installed.

**To load it: /exit, then claude --continue (not /clear)**
