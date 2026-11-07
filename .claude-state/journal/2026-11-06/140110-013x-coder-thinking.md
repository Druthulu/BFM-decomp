---
ts: 2026-11-06T21:01:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w2YnOtcK3ZDUQBtEnq3E
---
To dump my candidate, I need a TU. delever_search --try probably creates a scratch TU. Maybe it has a --keep option. The brief mentions `--keep` scratch is removed after use. Let me check delever_search.py options.

Actually, simpler: use the item's `tu` — the TU path is src/md_MAIN_034/md_MAIN_034.c which contains the current (pinned) function. To dump MY body I need to splice it. delever_search likely does that; maybe it supports `--dump` or leaves a temp. Let me look at delever_search.py briefly.
