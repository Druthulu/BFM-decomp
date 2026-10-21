---
ts: 2026-10-21T19:59:19.120Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 5ec2485c-b326-40b3-a314-122c4e1956ce
usage: {input: 8, cacheRead: 353915, cacheWrite: 1147, output: 1465}
---

My recommendation is to keep banking on the in-house Opus coder, as T11 already does. It costs little, and it's the one step where a mistake hurts the whole wave.

**What banking is.** One coder takes the finished batches' wins and puts them into the real source tree. It rewrites the matching residue rows, re-runs the type census and the cast check, runs the full 218/218 build check and commits. So it's the single point where everyone's work meets the shared tree.

**Why Opus there:**
- **It's a small share of the tokens.** Batch 1's banker used about 78k tokens, against about 2.7M for the crack coders so far, so about 3%. Moving it to DeepSeek would save very little.
- **It's where an error costs most.** A bad crack only wastes one function's attempt. A bad bank can stall the wave: a broken merge, a wrongly rewritten residue row, or a commit that leaves the tree red. Batch 2 hit just such a snag. The census had to be re-run before the cast sweep after the function bodies were swapped, and an Opus coder caught it.
- **It's judgment work, not repetitive work.** That fits your rule: DeepSeek does the bulk per-function cracking, and in-house coders do the rest.

**One cheap improvement: bank less often.** Each bank pays for a full 218/218 run, about half an hour of machine time. With 27 batches left, I'd bank every 6 to 8 finished batches instead of every 4, so about 4 banks in all. That cuts the gate runs and the banker's tokens further. The risk is small, because every win sits in scratch, already byte-checked one function at a time, until it's banked.

There's also a middle option, if you want to see how DeepSeek copes: let it bank one batch while Opus does the rest, and compare. I wouldn't start there, though. Let's first see how it cracks.

If you agree, I'll add "bank every 6 to 8 batches" to T11's resume instructions. T11 is still stopped until you say go.
