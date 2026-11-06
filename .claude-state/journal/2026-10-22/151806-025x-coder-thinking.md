---
ts: 2026-10-22T21:18:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_642M98sTSAfbsM1gAsXm
---
recs_for(tu, by_src, inc) with tu ending .h returns [r for t_ in inc.get(tu, []) ...] where inc maps... In delever_search main, how are `by_src` and `inc` built? Probably inc maps header path -> includer src list. Let me find where recs_for is called.
