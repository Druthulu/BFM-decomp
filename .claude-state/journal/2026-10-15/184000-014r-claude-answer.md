---
ts: 2026-10-16T00:40:00.605Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d6aebf-6350-4daa-876d-9c2a38cf16a3
usage: {input: 10, cacheRead: 392957, cacheWrite: 1843, output: 565}
---

PA3 3.28.6 is installed, and it's a set of small fixes to how updates behave:
- **Installs while paused:** a chosen update can now install while a task is paused and no agent is working. It no longer waits for the task to end.
- **Clearer restart messages:** the status line reads "installing, please wait" until the install has really finished. After a restart I'll say plainly that the new version is loaded, so an old restart line doesn't look like a loop.
- **No double installs:** I now hear only the new version and its title, so I can't start a second install beside the mod's.
- **Windows:** background steps no longer open empty console windows.

**To load it: /exit, then `claude --continue` (not /clear).**

The restart also applies a changed setting and loads the new mod and agents, and you'll pick up where you left off. T3 is at its clean pause point (batch 3 committed), and nothing starts until you're back and say go.
