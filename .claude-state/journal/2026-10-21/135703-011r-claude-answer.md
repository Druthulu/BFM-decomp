---
ts: 2026-10-21T19:57:03.630Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 76c5624e-f6c9-423f-8b16-0d137f81ac00
usage: {input: 18, cacheRead: 888723, cacheWrite: 6478, output: 3512}
---

From now on every coder runs on DeepSeek, and nothing escalates to Opus or Haiku without your approval. T11 is still stopped.

What changed:
- **Project settings.** DeepSeek at max effort is now the default coder for every task, and escalation is empty. A failed run no longer hands off to an in-house coder by itself. Committed.
- **The card.** Its "External coders" section now reads: every coder runs on DeepSeek until you say otherwise, with no Opus or Haiku escalation, and failures wait for your OK.
- **The plan.** Every task in it still names opus55 as its coder, and the plan tool has no command to change that field. So I've queued a line in the plan's change log that overrides it for every task, including T11's banking coders. It takes effect at the next task boundary. When T11 resumes, I'll also hand its expert the same rule directly.

What T11's expert will do on resume:
- **All batches go to DeepSeek.** That's the 14 Haiku-first batches, the Opus batches (G22, G23, G26 to G31, O01 to O05) and the banking runs, at most 4 at once.
- **No Opus retries.** Every wall, or failed run, goes on a held list with its evidence. That includes Haiku's 18 earlier walls. The list waits for your decision, and those functions don't count as survivors until you rule on it.
- **The rest as before.** The old script lane retires, the expert reads T11's committed pause note (in 1a0eea2f4b), and the disk rule stays.

Two cautions:
- **Banking is the riskiest job to hand DeepSeek.** It's where the full 218/218 check runs and where the commits happen. A mistake there can't let wrong code in, because the check refuses it. But a stuck bank would stall the wave, and under your rule it would wait for you rather than fall back to Opus.
- **Your key's credit limit is now the real spending cap.** Every coder's tokens now cost cash on the DeepSeek key.

Tell me when you want T11 to go on, and I'll resume it with these instructions.
