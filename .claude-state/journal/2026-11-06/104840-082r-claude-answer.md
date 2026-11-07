---
ts: 2026-11-06T17:48:40.332Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: 452ea738-9510-4407-be28-9ecba2b403f6
usage: {input: 8, cacheRead: 168679, cacheWrite: 1832, output: 743}
---

PA3 updated from 3.32.4 to 3.32.7. Here is what changed:

- **External coders hand off on time (3.32.7).** OpenRouter sends a reply's token counts only at its end, so PA3 thought DeepSeek coders had used zero tokens while they ran. Because of that, they never got the "save your progress and hand off" request at the 350k-token context limit. Some ran far past it, and one ran until its model refused the prompt as too long. They now get that request on time, like in-house coders. The statusline also shows each external coder's context, and its tokens and spend move while it runs.
- **No more red rows for launches PA3 turned away (3.32.7).** A coder refused at launch for learning mode, a full lane or a duplicate no longer leaves a red row on the statusline. It never ran.
- **No more `?/?` on the Session line (3.32.6).** A tiny rounding difference made a session look bigger than its account. The line now shows the real numbers.
- **Updates that can't get stuck (3.32.5).** A slow download now finishes in the background instead of being dropped after 8 seconds. That was probably why the update check failed at the last session start on WSL. If an update ever fails, I'll say so with the one command to run. A release you skip with "Not now" is offered again every 8 hours.

Project Architect 3.32.7, a hotfix (External coders count their tokens and hand off on time), is installed.

**To load it: /exit, then claude --continue (not /clear)**

The mod's own files changed, so nothing starts until you restart. T11 is paused and idle, so you can restart now. After the restart, tell me when you want T11 to go on.
