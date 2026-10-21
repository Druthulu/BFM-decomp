---
ts: 2026-10-21T23:25:30.957Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 1b614274-08b8-401f-a769-9fa017df1681
usage: {input: 8, cacheRead: 280960, cacheWrite: 2032, output: 848}
---

PA3 has another build of 3.30. This is the update for the external coders you were waiting on. On top of the build from earlier today, it adds:

- **External coders hand off before they run out of room.** They're now logged like in-house coders, reasoning included. At the same context size as in-house coders, 350k tokens, they save their progress and hand off to a fresh coder, instead of running until the model's own limit cuts them off.
- **The auditor reviews external runs.** After any phase in which external coders ran, the auditor goes over all their runs: which fixes worked, what still hurts, and how the project should use them.
- **Techniques reach the cookbook again.** Since PA3 3.2, the techniques that task summaries marked for the cookbook were never actually added. Now each expert adds what a coder learned as soon as that coder reports, before starting the next one. Once per project, a picker will offer a one-time task to add the lessons still sitting in older task summaries. This project has a lot of those, from T11's crack moves and earlier.

**On the timing of your restart.** T11 is still pausing: the four MiniMax coders are finishing their current functions and writing up their findings. If you restart before they finish, nothing is lost, because an external run cut off by a restart picks up where it stopped. Waiting is cleaner, though. I'll tell you when they've all handed back and the expert has committed its resume note. The pause holds across the restart, and afterwards I'll ask you whether to resume T11.

Project Architect 3.30, a feature update (External coders), is installed.

**To load it: /exit, then claude --continue (not /clear)**
