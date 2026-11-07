---
ts: 2026-11-06T22:42:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_okAja2oiMRFXxHCmMMDf
---
There's a `--explain TU FN` mode with `--path` moves. That's useful: it reads one body's residual and suggests moves. Let me try `--explain` on our function (with the TU header) to see the residual and the move families. The `--try --body` already prints the diff. `--explain` might name the moves. Let me run it on w0.

Also `--path` with move names. Let me check what moves it suggests.

Actually, let me first run `--explain src/shared/ov/func_8012B8E4.h func_8012B8E4` to see the analysis.
