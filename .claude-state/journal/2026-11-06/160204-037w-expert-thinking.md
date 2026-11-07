---
ts: 2026-11-06T23:02:04.772Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: af5fe0128a7f156b5
model: claude-opus-5-5
effort: medium
turnId: 963b5aac-9394-46c7-924a-9f682d9e0754
---
Most of the unwalled entries sit in the current B11 shards and will be walled by the bank, while the instruction rows and the func_80188C04 family are parked. That leaves the remaining pin, launder, barrier, and keepalive entries outside B11 that still need a list. I'll wait for the bank and recompute, and I still need to check what's in held.tsv and which walls came from older runs.

I'm still checking which walls came from older model runs and whether the held rows from earlier attempts are being applied by the bank. Once that's clear, the parked family and instruction rows will get their wall causes, and I need to look into the blank-name rows with an empty func field after the bank has run.

Of the 93 unwalled singleton rows, 27 are parked, along with the func_80188C04 family. I'll list the rest after the bank commits.
