---
ts: 2026-11-07T01:09:24.130Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: abc89313538ecd9f4
model: claude-opus-5-5
effort: medium
turnId: a89d5fed-8a51-4ace-950d-5a651e76b176
through: 2026-11-07T00:54:15.635Z
usage: {input: 4, cacheRead: 104920, cacheWrite: 765, output: 279}
---

topic: DeepSeek learning mode in T11
idea: -
finding: A `$(...)` command substitution inside an argument (for example `sed -n "$(grep -n ... | cut ...),...p"`) matches no allow rule and is denied, which counts as friction. The cure is to run `grep -n` first, then `sed -n` with literal line numbers.
  evidence: T11 RM4/P1 denial 2026-11-06; DeepSeek model note 4; undo `pa_ext.py set --drop-model-note openrouter-deepseek/deepseek 4`
headline: DeepSeek note 4: no $(...) substitution inside arguments; grep first, then sed with literal lines
