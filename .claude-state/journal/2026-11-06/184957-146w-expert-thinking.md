---
ts: 2026-11-07T01:49:57.645Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: bb4945f0-6e6b-4817-89f1-359e076476b0
---
I'm checking which census the residue numbers should come from: the newest readability census is P39, but only P37 has residue data. I'm weighing whether the residue file should be paired with its type census by timestamp, and whether a stale residue file should blank the uncovered rows or stop the run.

I'm deciding whether a stale residue census should refuse the run or blank the uncovered rows, and I'll go with using the residue census only when a fresh type_census.json matches it, blanking with a stderr note otherwise. That still risks silent blanks, but I'll make sure the T12 row's residue data is fresh. Next I'm moving on to timeline.py lines 240 to 360.
