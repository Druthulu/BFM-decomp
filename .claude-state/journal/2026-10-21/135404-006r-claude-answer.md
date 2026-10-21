---
ts: 2026-10-21T19:54:04.441Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 347c80a9-cb0f-4d61-9ea9-11388d81f921
usage: {input: 16, cacheRead: 640910, cacheWrite: 84444, output: 4713}
---

T11 stays stopped. Nothing restarts until you say so.

**The update.** The PA3 release that adds external coders already looks installed: it's the newest commit, 682d3e76af. If you meant a newer release, the mod will offer it in its own picker. If you meant a status update on the work, here's where T11 was when it paused on the 17th:
- **Committed:** 78 functions cracked, in two batches, both 218/218 byte-identical.
- **Not started:** 27 batches, 246 functions. 14 of those batches are routed Haiku-first.
- **Haiku's walls:** 18 functions Haiku couldn't crack still need their Opus retry.

**Your setup worked.** I ran the check, and all three configs connect:

| Config | Model | Check |
|---|---|---|
| openrouter-deepseek | deepseek | connected |
| openrouter-glm | glm | connected |
| openrouter-qwen | qwen3 | connected |

None of them is set up for this project yet. There's no default coder, no lanes and no escalation rule, so nothing uses them until we decide.

**How these differ from what T11 tried.** T11's "external lane" was a custom script, `.run/P40/T11/ext/lane.py`. It made the model draft a function through the API in one go. DeepSeek ran 9 of its 28 functions that way, cracked none, and spent $0.21. The new external coders are different. Each is our own coder agent with the full toolset (it can read, edit, compile, compare the bytes and try again), just running on DeepSeek, GLM or Qwen. That's a much fairer test than the old lane gave them. Their tokens cost cash on your OpenRouter keys, not subscription usage.

**What PA3's own tests found:**
- **DeepSeek V4.1 Flash:** the recommended model. It's the cheapest, and max effort helps on hard work.
- **GLM 5.3 Flash:** about 3 times DeepSeek's price. Most of its hardest attempts ran out of time, its hosts were unreliable, and it needs max effort even on easy tasks.
- **Qwen 3.8 Flash:** passed nearly everything it finished, but at 6 to 11 times DeepSeek's price per task, because its only host barely caches.

**My recommendation: a small bake-off inside T11.** T11 is a good test bed. Every function is independent, the byte check decides whether a crack is right, and wrong code can't get in because every win goes through the same committer and the 218/218 check. Here's what I'd do:
- **One batch each.** DeepSeek, GLM and Qwen each get one of the unstarted Haiku-first batches, about 8 to 10 functions each, at max effort. That compares them with Haiku's 57% on functions of the same kind.
- **Walls go to Opus.** Anything an external coder can't crack goes to an Opus retry, the same rule Haiku's walls follow. Escalation is set to in-house.
- **Everything else stays as it is.** Haiku-first for the other batches, and Opus for the large functions and those with more than one kind of lever.
- **The old lane retires.** Its 9 results stay in the comparison table.
- **The summary compares them.** T11's summary gets a row per model: crack rate, minutes and dollars per crack.

Then we'd decide on real numbers whether one of them takes over the cracking work in later phases.

Three things to settle:
- **Your 4-coder cap.** Do external coders count toward it, or run on top of it? They don't spend subscription usage, but they do add compile load on this machine. Also, disk space was about 6 GB the last time I checked.
- **A credit limit on each key.** Please confirm each key has one, plus a guardrail at openrouter.ai that allows only the recommended host. Without the guardrail, OpenRouter spreads requests over many hosts, some pricier and some serving lower-quality copies of the model.
- **T11's resume note.** On resume, the expert should read the note T11 committed when it paused (in 1a0eea2f4b). The mod has since overwritten that file with a thinner recovery note. I'll point the expert at the committed one.

Pick an option in the picker. Once you've chosen, I'll write the project settings and a three-line "External coders" section on the card. When you say go, I'll pass the routing to T11's expert as it resumes.
