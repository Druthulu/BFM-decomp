---
ts: 2026-11-07T02:28:51.725Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: b6e7e01f-d886-48ec-8b0e-667e64e27bd9
---
I'm now seeing that the bwrap failures no longer count since 3.30.7, so my earlier claim was wrong and the first bug is moot. That leaves only the false refusal on '../' paths, plus a read guard on large files that I don't think is a bug. For the '../' case I'll write a short writeup, and first I need an example command, so I'll search the runs log for '../'.
