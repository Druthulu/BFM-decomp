---
ts: 2026-11-06T09:42:10.492Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: f76e3a4e-a75b-43dc-a844-ba748271ff91
usage: {input: 4, cacheRead: 76562, cacheWrite: 323, output: 228}
---

FYI: T11's expert added a second note for every DeepSeek coder, in every project. G24x and G26 still wrote scratch files to `/tmp` despite their briefs, and each time that was a judge refusal that kept DeepSeek in learning mode. The note says to use the batch's own `.run/P40/T11/<shard>/` folder or `<(...)` process substitution instead. To undo it, run `/usr/bin/python3 tools/pa_ext.py set --drop-model-note openrouter-deepseek/deepseek 2`.
