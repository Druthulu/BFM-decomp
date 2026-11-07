---
ts: 2026-11-06T09:08:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4hnCz7Qegypz0nQOgyP0
---
oracle is a different module — delever_search imports `import delever as dl` and `import oracle` maybe from tools dir; in my -c, sys.path has tools so oracle resolves... it says no recipes_by_src. Maybe delever_search imports oracle from a different package or has `oracle = ...`. Let me grep the imports.
