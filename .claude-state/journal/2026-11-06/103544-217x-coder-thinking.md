---
ts: 2026-11-06T17:35:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EdT0t1smBhLUMSXrvle6
---
Time 10.1 min. All 7, including the inverted-arms variant (jump opt normalizes it).

Let me now check the global.c dump to understand "preferences" — copy or normal. If it's a copy preference, maybe I can break the copy by changing the store/copy structure.

Let me grep global.c for "preferences".
