---
ts: 2026-11-06T09:57:34.670Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: e3aaae0c-c495-48a2-ad9a-66b74b0664e9
through: 2026-11-06T09:42:10.492Z
usage: {input: 4, cacheRead: 76885, cacheWrite: 661, output: 427}
---

topic: DeepSeek learning mode in T11
idea: -
refinement: T11's expert added DeepSeek model note 2 (2026-11-06) after G24x and G26 both wrote to /tmp despite their briefs. The developer was told, with its undo.
finding: DeepSeek keeps writing scratch files to /tmp, such as objdump listings and sort temp files, even when the brief forbids it. Each write is a judge refusal and re-arms learning mode, so it is DeepSeek's recurring blocker to leaving learning mode. The cure is the shard folder .run/P40/T11/<shard>/ or `<(...)` process substitution.
  evidence: DeepSeek model note 2, 2026-11-06, from T11.cG24x and T11.cG26; undo `pa_ext.py set --drop-model-note openrouter-deepseek/deepseek 2`
headline: DeepSeek's /tmp writes (G24x, G26) keep re-arming learning mode; model note 2 added
