---
ts: 2026-10-22T04:41:09.734Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: e7747ee9-48a1-4284-a5ea-2e5ea273be56
usage: {input: 6, cacheRead: 218792, cacheWrite: 1228, output: 901}
---

I'd expect somewhat better results, but not a big jump. The judge removes friction, not the hard part.

**What the judge and this release fix:**
- **Refused commands.** Before, a command outside the allow rules was simply refused. The coder then wasted turns finding a workaround or did without the tool. Now the judge rules once and the project remembers. In this run alone it has already allowed `objdump` and the scoring script.
- **Runs that die.** Batch G06 failed with "Prompt is too long". MiniMax now saves its progress and hands off to a fresh coder at 350k tokens, so a run like that is no longer lost.
- **Lessons carrying over.** After each run, the expert now corrects its next brief and writes notes for later coders. So later MiniMax coders start knowing what the earlier ones learned.

Together these should mean fewer failed runs and more of each run spent actually trying spellings.

**What they don't fix.** Cracking a singleton comes down to reasoning about how gcc 2.7.2 picks registers and merges copies, then guessing which spelling tips it. In MiniMax's first session, its 10 walls fell on the same compiler behaviours as Haiku's: merged copies and ties in register choice. That points to the model's reasoning, or to real walls, not missing tools. Its clean crack rate was 37%, against Haiku's 57% and Opus's 50 to 60%.

My guess is a few points better, maybe into the 40s, mostly from fewer wasted or failed runs. The comparison also won't be clean. The batches left now include functions earlier coders already tried and failed, so they're harder on average. The expert's report after this first coder will show how much friction the judge removed. Its crack rate over the next few batches will tell us the rest.
