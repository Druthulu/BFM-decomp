---
ts: 2026-10-22T04:22:28.257Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: b6fd9291-e22c-4524-a74d-40b055853631
usage: {input: 8, cacheRead: 278774, cacheWrite: 2465, output: 1553}
---

T11 is starting fresh with a new expert, using one MiniMax coder at first.

The new expert has these instructions:
- **It starts from the committed resume note** (d37317858e) and each batch's handoff.
- **It runs one external coder at first,** on one paused batch of 5 functions or fewer. PA3 3.30.1 would hold a model new to the project to one coder at a time anyway, until one of its runs comes back clean.
- **The judge rules on commands no allow rule covers.** PA3's judge runs on Opus with auto mode's rules. It decides each such command once, and the project remembers the decision. The expert won't pre-approve anything to get around it, so we'll see the judge make real decisions.
- **It reviews that coder's report before spawning anything else.** It looks at:
  - which commands were refused or judged;
  - the friction the coder hit;
  - what worked.

  Then it fixes its next brief, writes notes for later external coders and adds new crack moves to the cookbook. Each note comes to you as a one-line FYI with its undo, and nothing waits on you.
- **Then it scales up,** to the usual 4 MiniMax coders, resuming the remaining batches from their handoffs.

The rest of the routing hasn't changed:
- An in-house Opus coder banks the wins every 6 to 8 finished batches.
- Walls and failed runs go on your held list.
- func_8012EF34 and func_8012EF70 are still waiting on your ruling.
- Every coder is reminded to begin its final message with the bare word "done", so the launcher doesn't nudge it into another function.

I've released the talk hold too. If the mod refuses either release, I'll tell you.
