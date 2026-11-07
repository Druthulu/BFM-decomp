---
ts: 2026-11-06T06:02:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AnMIIY8ZTIBVyPuBkMe6
---
Wait — this removes dirs like `ov_MAIN_012__func_80150170` but the matching condition `'__' + f + '__' in name` also matches `ov_SC01_000__func_80150170`? No: `'__func_80150170__'` is not in `ov_SC01_000__func_80150170` (no trailing __). The first condition `name.endswith('__func_80150170')` matches. Good.

But careful: could this match another function like `func_80150170__func_80150170`? That's a G21x item dir, not in engine/score. Fine.

Also `func_80175820` endswith matches `ov_SC01_000__func_80175820`. Good. And `func_80180D38` endswith matches `ov_SC04_018__func_80180D38`. Good.

Hmm, but the delever_search score dir might be keyed `<tu>__<fn>` where tu is `ov_MAIN_012`. Yes.

Let me run it.
