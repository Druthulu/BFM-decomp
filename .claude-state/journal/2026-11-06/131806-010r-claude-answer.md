---
ts: 2026-11-06T20:18:06.944Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: 5fe35b08-6a5f-470d-a22c-4948eb9280be
usage: {input: 8, cacheRead: 294346, cacheWrite: 2461, output: 1303}
---

It's both. DeepSeek is back in learning mode, and the cracking queue is nearly finished anyway.

**Learning mode is back.** W48x, the last coder before the restart, read one big file whole and got a read-guard block. That one block counts as friction, so DeepSeek is limited to one coder again. Apart from that, the judge refused nothing in W48x or the four runs before it:

| Run | Judge allowed / refused | Friction |
|---|---|---|
| O05x | 218 / 0 | 2 whole reads of big files, 7 sandbox failures |
| W47 | 84 / 0 | 4 sandbox failures |
| W47x | 60 / 0 | 2 sandbox failures |
| W48 | 140 / 0 | 3 sandbox failures |
| W48x | 98 / 0 | 1 whole read of a big file |

DeepSeek stopped writing to `/tmp` after its second note. What's left is two things:
- **Whole reads of big files.** The standing note already says to outline a big file first and read it by line range, and DeepSeek still slips now and then.
- **Sandbox failures.** The sandbox (bwrap) fails a command, which then works when it's re-run. That points to the WSL sandbox, not DeepSeek, so no note to the coders would fix it. If it counts as friction, it could keep any external model in learning mode. I'd report it to PA3 as a bug.

**Little work is left.** The expert's plan for this attempt is 4 batches, W49 and three more, then the RM3 retries of earlier walls. So even out of learning mode, T11 could use at most about 4 coders at once now. One lane costs us maybe a few hours, not days. W49 already cracked its first function.

**My recommendation.** Leave it as it is. A new note for the big-file reads probably wouldn't stop the slips, and adding one would count as friction too. If you want, I'll write up the sandbox-failure question for PA3 with the evidence above, and you can file it with `/pa-bugreport`.

I've released the talk hold.
