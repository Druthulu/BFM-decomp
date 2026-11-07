---
ts: 2026-11-06T23:44:30.271Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ad2f5b165a7f6e91c
model: claude-haiku-5-5
effort: medium
turnId: e4f74c0e-cf1a-45a1-8c3a-3307ee420397
---
I'm checking the family-80188C04 rows in parked.tsv: four are named, at SC03_089 through SC03_092. The T11.md note says the other seven members have no singleton row, and they aren't identified in the scope logs.

I'm noting that the 7 remaining family members aren't in the scope logs, so I'll report them as not found. I'm also setting aside the Q2 rows (80181EBC, 80189240, and the rest), since those are instruction or barrier rows rather than family members. Next I want to check the file-level comment near line 880 of ov_MAIN_012 for any macro that might explain the blank 8015444C rows.

Next I'm searching the ov_MAIN_012 file for `#define` lines or barrier markers, limited to the first ten matches, to see whether a macro explains the blank 8015444C rows.
