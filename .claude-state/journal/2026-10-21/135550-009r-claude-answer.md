---
ts: 2026-10-21T19:55:50.567Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 752be26a-640e-4595-a769-e4bf8bd6db83
usage: {input: 16, cacheRead: 727648, cacheWrite: 6794, output: 3641}
---

DeepSeek only it is. The project settings are written and committed, and T11 is still stopped.

**The settings.** I committed these as 104338531e:
- **DeepSeek only.** `openrouter-deepseek` is the only backend in use, with up to 4 coders at once. GLM and Qwen stay set up on this machine but aren't used here.
- **Max effort.** PA3's tests found max cracks about one more task in ten on the hardest work.
- **Failures go to in-house coders.** If a DeepSeek run dies, for example on a host error, an in-house coder takes it over.
- **Default coder unchanged.** Tasks that don't name a coder still use in-house ones, so only T11's routing changes.
- **No more reminder.** The session-start reminder about external coders is off.

**The card** (`HOW_WE_WORK.md`) has a new "External coders" section. It says T11's Haiku-first batches run on DeepSeek at max effort instead of Haiku, and the functions it can't crack get the Opus retry. To fit that under the card's size limit, I moved the long note about what the commit script auto-stages into `docs/ops/commit-task-autostage.md` and left a pointer. That commit also picked up the journal changes waiting in the tree, which is harmless.

**What the expert gets on resume:**
- **DeepSeek's batches.** The 14 unstarted Haiku-first batches (G05 to G25), about 120 functions, go to DeepSeek coders.
- **The Opus retries.** Functions DeepSeek can't crack get an Opus retry before they count as survivors. So do Haiku's 18 earlier walls.
- **Opus's batches.** The Opus batches (G22, G23, G26 to G31 and O01 to O05) stay on Opus.
- **The old lane retires.** The old script lane stops, and its 9 results stay in the comparison.
- **The summary.** It compares DeepSeek with Haiku's 57% and with Opus: crack rate, minutes per crack and dollars per crack.
- **The resume note.** The expert reads the note T11 committed when it paused (in 1a0eea2f4b), not the thinner recovery note the mod wrote over it.
- **Disk.** It keeps the existing disk rule and watches `df -h /`.

Two things only you can do:
- **The key.** Make sure the DeepSeek key has a credit limit and a guardrail at openrouter.ai that allows only the recommended host.
- **Disk space.** Free space was about 6 GB last time, and 4 DeepSeek coders compile on this machine just as Opus coders do.

Tell me when you want T11 to go on, and I'll resume it with these instructions.
