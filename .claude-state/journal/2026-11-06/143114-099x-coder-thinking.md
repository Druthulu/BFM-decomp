---
ts: 2026-11-06T21:31:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AssZIdghESb3EwZkVn3T
---
recs_for(tu, by_src, inc): if tu ends with ".h", returns [r for t_ in inc.get(tu, []) for r in by_src.get(t_, [])]. So `inc` maps the header to its includer TUs, and `by_src` maps each TU to its recs. If inc.get(header) is empty, the includer list is empty.

Where does `inc` come from? Let me find how it's built (maybe from config/dedup.us.yaml or a scan). Let me grep for `inc =` and `by_src =`.
