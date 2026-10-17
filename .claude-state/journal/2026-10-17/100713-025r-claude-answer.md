---
ts: 2026-10-17T16:07:13.556Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: ee7fbc65-97b8-4a8a-8e3c-c7327a9054ea
usage: {input: 16, cacheRead: 619084, cacheWrite: 7083, output: 2580}
---

None of the cracking is yours to do. "Hand cracking" here means Claude coders rewriting each function by hand in plain C, and that is all agent work.

**How much is left.** T11's wave covers 396 one-off functions: 394 still unattempted plus 2 copies of func_80136824. The expert has split them into 50 batches of about 8, so 4 coders work in parallel in scratch and a fifth commits the wins. The four first batches started a few minutes ago. If T10's rate of about 60% holds, about 240 of the 396 get cracked, and about 160 survive with their compiler wall recorded. After that, T20 only tags the roughly 864 rows that no wave touches. That is classification work, not cracking.

**The OpenRouter harness.** We have one: `tools/api_agent.py` gives an OpenRouter model the same tools a Claude coder gets, plus a compile-and-compare loop. We retired that lane in Phase 31 by choice, not because it was broken. The one measured comparison, on 2026-07-01, found two things:
- **Good drafts:** GLM 5.2 matched 10 of 18 hard functions at the function level, for about $1 in total.
- **Few usable:** only 3 of those 18 passed the full binary check. The function-level comparison it uses ignores which symbol a call or address points to, and the remaining failures were compiler walls that no drafting model can get past.

**Should you try external agents now?** Not inside the running wave. T11 already has 4 coders and one committer working through fixed batches against a shared build. Adding an outside lane mid-wave risks two writers on the same files, and it would muddy T11's numbers.

There's another catch. The harness was built for matching functions from assembly, not for removing levers, so it would need a small adapter. Its prompt and its oracle would have to score "lever-free and still byte-identical".

**The best time is right after T11.** Run a scratch-only bake-off on about 20 of the functions T11 couldn't crack. That's a fair, cheap test: a few dollars on the OpenRouter side, nothing committed, and the full binary check decides. If an outside model cracks what Opus couldn't, that's worth knowing before 3.41. If not, we've confirmed the walls are real.

I'm ready to add that as a small task after T11 if you agree. It needs your OpenRouter key in the environment, which only you can provide. Pick an option in the picker. The queue is moving.
