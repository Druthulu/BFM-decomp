---
ts: 2026-10-22T05:38:28.682Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a0c764ccd9460c76a
model: claude-opus-5-5[1m]
effort: medium
turnId: e277b03d-1802-4b61-a547-40ce3917ea33
---
This stale-scratch-file issue is really just a variant of the existing stale-drafts entry already covered in the cookbook, so it's more of a note for coders than a genuinely new technique. The four walls aren't techniques themselves since no move actually cracked them, but they're worth recording as named compiler walls in the final TSV.

I should add a note about orig.c staleness and the judge-learned rules, plus append the new tags (global-copy-pref, global-hardreg-reserve, loop-extra-iv, greg-lo-reg-count) to walls.txt. The remaining briefs — RM1, RM2, G14, G15, and the queue — need a correction line added instructing regeneration of orig.c from current src at item start, along with the judge/PERMISSIONS and REMINDER lines, so I'll check which already have the reminder before patching the rest with sed. I also need to run held_add for minimax G08b, confirm the judge refused cleanly, then log everything to T11.md, the progress file, and TASK_PROGRESS.md before committing.
