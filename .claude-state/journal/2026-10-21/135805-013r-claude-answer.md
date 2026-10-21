---
ts: 2026-10-21T19:58:05.661Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: d67471cc-b91f-4422-8bc1-07a77916438f
usage: {input: 10, cacheRead: 460213, cacheWrite: 2223, output: 1658}
---

Got it: DeepSeek does the function cracking, and in-house coders do everything else. T11 is still stopped.

What I changed:
- **Project settings.** The default coder is back to in-house. DeepSeek stays set up at max effort, and nothing escalates by itself. Committed.
- **The card.** It now reads: function cracking runs only on DeepSeek at max effort, other coder work stays in-house, and nothing escalates to Opus or Haiku, so a failure waits for your OK.
- **The plan.** I've queued a second line for the plan's change log that replaces the one from a few minutes ago. Cracking coders, in T11 and any later crack wave, use DeepSeek. Everything else uses the in-house coder the task names: banking and the 218/218 check, tools, docs and restruct sweeps.

So when T11 resumes:
- **DeepSeek takes all 27 unstarted crack batches.** That includes the batches that were Haiku-first and the ones that were going to Opus. At most 4 run at once.
- **Banking stays in-house.** The coder that commits the wins and runs the 218/218 check stays on Opus, as before.
- **Walls are held.** Any function DeepSeek can't crack, or whose run fails, goes on a held list with its evidence. That includes Haiku's 18 earlier walls. Nothing gets retried on Opus until you decide.
- **Unchanged:** the old script lane retires, the expert reads T11's committed pause note, and the disk rule stays.

Tell me when you want T11 to go on, and I'll resume it with these instructions.
