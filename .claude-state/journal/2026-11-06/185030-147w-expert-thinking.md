---
ts: 2026-11-07T01:50:30.918Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: bb4945f0-6e6b-4817-89f1-359e076476b0
---
I'm settling on how to draw the uncovered series: since it's now zero, a percentage of the first measurement won't work, so it should be an absolute line at zero. I'd plot it on the same y axis as the four-form share, so that it sits next to the raw figure and the gap is visible: uncovered on the floor while raw debt remains.

I'm weighing how to present the uncovered series in the legend, since it reads 0 and that alone could look like the debt is gone. I'd spell out that it's zero by the ledger, with the raw count above it still showing what's left.

I'm going to make the edits myself, since it's small. First I'll check how to pair the residue census with its sibling type census, using mtimes to confirm it's fresh.

Uncovered now gets its own column in readability_progress.py, drawn on the four-form raw series' base in timeline.py; it sits at 0, so the legend says so in words.
