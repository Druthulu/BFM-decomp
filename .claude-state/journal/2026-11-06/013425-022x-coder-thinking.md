---
ts: 2026-11-06T08:34:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BgOJmdq95g8kNgzwYdqK
---
recs_for needs by_src, inc. In main they load a registry. Simpler: search build for the object corresponding to TU. There's probably a mapping in build/ from TU to object. Let me check what object name appears for the TU. Look at .run/P40/T11/bin/held_add.py maybe. Or grep for "by_src" construction.
