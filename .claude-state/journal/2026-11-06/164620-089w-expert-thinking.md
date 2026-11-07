---
ts: 2026-11-06T23:46:20.730Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: af5fe0128a7f156b5
model: claude-opus-5-5
effort: medium
turnId: 19e977d9-6c9c-432b-9d19-289a2d5a8d1f
---
I'm going through the parked.tsv rows that mix instruction with other kinds, like the 80181EBC barrier, launder and pin entries. The instruction rows fall under the parked "instruction rows" family, so the whole function is parked. The done-when condition is that those families are not attempted and their rows are recorded with their wall cause, which for instruction rows is no-c-spelling per the seed tags. I'm still working out how to handle the other kinds in those functions.

I'm weighing what wall cause to record for the other kinds in those instruction-parked functions, since they were never attempted. My current read is that the instruction lever blocks the whole body anyway, so I'm leaning toward `wall:no-c-spelling` for those rows, but I still need to check that tag exists in walls.txt and whether the 8015444C file-scope barrier needs a different treatment.

I'm going to check the top-level asm line in that file to see whether it actually pins output order between functions and static data, rather than guessing a tag for it.
