---
ts: 2026-11-06T19:59:46.945Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: f7728ba2-0f99-4e40-9ad8-d097eb3453f5
usage: {input: 8, cacheRead: 189176, cacheWrite: 997, output: 583}
---

PA3 updated from 3.32.7 to 3.32.8. Here is what changed:

- **The savings figures were too high, and are now honest.** Each time an agent read PA3's journal of decisions, the ledger counted it as savings, although a plain Claude Code session has no journal. On a busy project that was about two thirds of a week's measured savings. Journal reads now count nothing, and a one-time repair removes the credits already booked. So the Session and Project lines will show lower savings figures. I'll tell you once the repair has run.
- **External coder rows keep their details.** A DeepSeek coder's statusline row sometimes lost its model name and token count. It's now named from the coder's brief itself.
- **One more `?/?` fix.** The Session line could still show `?/?` after a turn when only this session was spending. It now compares against the account's total taken at the same moment.

Project Architect 3.32.8, a hotfix (Honest savings, steadier statusline rows), is installed.

**To load it: /exit, then claude --continue (not /clear)**

The mod's own files changed, so nothing starts until you restart. T11 is already paused and idle, so the restart you planned loads it. After the restart, tell me when you want T11 to go on.
