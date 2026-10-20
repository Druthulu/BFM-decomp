---
ts: 2026-10-20T00:43:18.294Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: fe32491d-66e9-49a3-a426-75f4e7e37c97
usage: {input: 8, cacheRead: 217839, cacheWrite: 5233, output: 709}
---

PA3 has been updated from 3.29 to 3.29.4. This bundles four small fixes:

- **Pauses you ask for stay paused.** A pause now survives a restart. After the restart, I'll tell you the work was paused on your request and ask whether to resume, and nothing starts again on its own. Also, at a session start nothing runs until the update check has answered, including a task the last session cut off, like T11.
- **The status line shows update checks.** At a session start it reads "checking for updates…". While an update installs it says so, and then it tells you to restart until you do.
- **The cleanup offer comes later, as a picker.** The one-time `.run/` cleanup is offered with a picker after the update check and any restart it needs, and the picker explains why it's recommended. Nothing is deleted until you approve my list.
- **You run the cleanup's deletion yourself.** Once you approve the list, I write the deletion as a script and check that it removes nothing outside `.run/`. Then I give you one `!` command to run.

This update also changed a setting that only takes effect after a restart, so please restart Claude Code. T11 stays held until then, and no work starts.

Project Architect 3.29.4, a hotfix (The .run/ cleanup hands you a verified command), is installed.

**To load it: /exit, then claude --continue (not /clear)**
