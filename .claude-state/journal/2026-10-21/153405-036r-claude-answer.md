---
ts: 2026-10-21T21:34:05.288Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: d89abc90-a31d-4632-bbe5-c8d7fc87e5b9
usage: {input: 10, cacheRead: 387755, cacheWrite: 1732, output: 861}
---

PA3 has a new build of 3.30, the release that adds external coders. It brings these changes:

- **External coders, finished.** Coding can run on a cheaper model through OpenRouter, while experts, retrievers, the planner and I stay on Claude. They run at high effort unless you ask for another. An external coder is our own coder on your key, with the same rules. Its card shows the model and its steps. A run cut off by a restart picks up where it stopped. A failed run goes to an in-house coder by default, but your rule in this project holds MiniMax's failures for you instead.
- **The spend is visible.** Once the first external coder starts, the statusline shows `External · tokens · $ spent · $ left`. A free model like your MiniMax variant shows $0.
- **The band shows them as coders.** An external coder appears as `pa-coder T11 · c<n>` with its model and latest step. The session's token count includes what external coders read.
- **PA3 learns from each run.** A finished external coder's report lists the commands it was refused and other friction. The expert proposes fixes, and I'll ask you before anything is kept: an allow rule for this project, or a note that later coders get.
- **Cancelled tasks stay cancelled.** If you cancel a stopped task, or put it back in the queue, it's no longer restarted when work goes on. The loop starts the plan's next task instead.

The mod's own files changed in this update, and a setting changed that only takes effect after a restart. So please restart Claude Code. No task starts until then, and you'll pick up where you left off. That includes T11, which resumes with MiniMax doing the cracking. I sent the routing to its expert before the update.

Project Architect 3.30, a feature update (External coders), is installed.

**To load it: /exit, then claude --continue (not /clear)**
