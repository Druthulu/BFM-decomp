---
ts: 2026-10-21T22:07:54.036Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a4a17c4d5b14bc781
model: claude-opus-5-5[1m]
effort: medium
turnId: 49d817b1-9d04-4921-b168-b00c4f907ff7
usage: {input: 10, cacheRead: 546696, cacheWrite: 6092, output: 1777}
---

Yes, it kept going, but it didn't decide that itself. The launcher that runs external coders sent the "go on" message.

**What happened.** The launcher (`tools/pa_ext.py`) checks that a coder's final message starts with the bare word "done", "question" or "blocked". If it doesn't, the launcher assumes the coder stopped too early and nudges it with "Go on with the task". G07's report began "All deliverables are in place. Here is my report." and only then said "done". So the launcher nudged it, and G07 read the nudge as a go and started a new function, func_801415C0. That's a gap in PA3's check: the report was really done.

**What I've done.** I've told T11's expert to:
- **Stop G07 now.** Its paused-on function was already finished and recorded, with 2 matches and 1 wall. It drops the new function's scratch and leaves that function marked as never attempted.
- **Warn every coder.** Each coder's final message must start with the bare word, with nothing before it, so the launcher doesn't nudge them on again.
- **Log it as a known harness quirk.** It goes in T11's log.

The other three coders (G06, G08 and G10) received the pause and are finishing their current functions. I'll tell you when everything is idle and you can restart.
