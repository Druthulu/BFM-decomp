---
ts: 2026-10-21T20:10:36.332Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a85fab1bb63fed5f8
model: claude-opus-5-5[1m]
effort: medium
turnId: 2cc0d81c-76ad-44e8-9eae-9a5f63800494
---
I need a barrier so no coders run mid-bank: run waves of 4 shards, and after about two waves pause to let active ones finish before banking and resuming — matching the old design. External coders use Claude Code processes with pa-coder and no make, so I should check if the old external lane's pids are gone and drop the BANKING flag that was only tied to that lane, verifying the external set accordingly.

I'll check process status and then write the ext briefs, reusing the same text as brief_<S>.txt, with coder label T11.cG05 mapping to file .run/P40/ext/T11.cG05.md, since pa_ext run likely derives the label from the filename. I also need to create .run/P40/T11/held.tsv with columns for item, shard, model, result, wall, and evidence, populating it with the Haiku wall times from the G03/G04/G09/G17 results plus WH1 and DeepSeek's run 9, using the results.tsv format of dir, file, func, kinds, result, best, tries, wall, evidence.
