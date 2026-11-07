---
ts: 2026-11-07T01:23:12.980Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a6113a6c423006329
model: claude-opus-5-5
effort: medium
turnId: b5ca22ff-b924-4947-95ef-cd25860f9a38
---
I'm checking whether the parked instruction functions cover all the remaining rows, including the empty functions in `md_MAIN_003` and `md_SC07_004`, and I'll verify that with a script once I've finished the full pass. Next I'm starting to compare the P1 win.c directories against orig.c.

I'm confirming the header rows are all WALL, so the header gotcha doesn't apply to any banked swaps. Next I'll bank the three P1 MATCH wins with bank_swap, then rewrite the TSV for all four shards and handle the family and instruction rows.

I'm banking the three P1 wins and running bank_rows across all four shards, then writing parked rows via a new park_rows.py. I'll also test deleting the dead `aF8014C4AC` declaration per TU, keeping it only if the build stays byte-identical.
