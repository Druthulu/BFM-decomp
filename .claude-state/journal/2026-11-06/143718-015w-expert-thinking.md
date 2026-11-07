---
ts: 2026-11-06T21:37:18.359Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: af5fe0128a7f156b5
model: claude-opus-5-5
effort: medium
turnId: bae90ace-8209-48c9-ab28-4c042901c4f3
---
I'm setting up the RM3 brief while the W49x and W50x runs finish. The RM3 items are already partially banked, so the goal is to strip out the kinds that are being kept. I'll use a fresh copy of the W50x brief as the base instead of the G08b one that retry_shard.py would use, and I need to remember that retry_shard also removes rows from results.ts.

I'm going to write a small scratch script that copies the directories by hand, so the existing results aren't touched. Removing the PARTIAL rows from G23 would be harmless since those are already banked, but I'd rather leave the history alone.

W50 came back clean with one match and three walls, each over 30 tries. While W49x and W50x run, I'm building RM3 to retry the seven banked partials that had fewer than 30 tries.
