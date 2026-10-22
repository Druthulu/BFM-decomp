---
ts: 2026-10-22T05:44:05.388Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 83475903-b835-4d76-a704-2b2e5503f976
usage: {input: 8, cacheRead: 228358, cacheWrite: 1088, output: 489}
---

PA3 has a small fix release, 3.30.3, with two changes:

- **External coders show their context size.** An external coder's row on the statusline now ends with how much context it holds, for example "· 48k tokens", the way Claude Code shows its own subagents. Before, it said "expert waiting". A coder that has ended keeps its last figure. Its row in the bands above the text box no longer repeats its model name, since the statusline row already shows it.
- **No restart request after a manual update.** If you install an update by hand before starting Claude Code, I no longer ask you to restart, because that start has already loaded it.

The mod's own files changed in this update, so the new mod and agents load only when Claude Code starts again. You'll pick up where you left off. No task starts until then, and T11 stays paused. After the restart, I'll ask you whether to resume it.

Project Architect 3.30.3, a hotfix (External coders show their context; no needless restart), is installed.

**To load it: /exit, then claude --continue (not /clear)**
