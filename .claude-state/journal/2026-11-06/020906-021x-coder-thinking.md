---
ts: 2026-11-06T09:09:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mKJtR9e4TdnnHgQugWPK
---
So recs_for should return 136+ recs. Why did the wrapped call return empty? Perhaps tryinc.py imports delever_search from a stale location? sys.path.insert(0, tools). ds.recs_for orig is correct. But maybe delever_search.main() re-execs? Or `_score_file` uses `recs_for(tu, by_src, inc)` where `inc` may be from `dl.includers()` — fine.

Wait, maybe the wrapper `rot` gets called with different args: recs_for(tu, by_src, inc) positional. Yes.

Hmm, but the traceback line 10 in rot: `r[k % len(r):]`. Maybe r is not empty but a non-list? If r is None? Then len(None) TypeError. Empty list -> ZeroDivision. So orig returned [].

Could ds.recs_for in tryinc be from a *different module instance* (imported twice via different paths: "delever_search" vs tools.delever_search)? tryinc inserts tools path then imports delever_search — one instance.

Wait: `orig = ds.recs_for` captured before... then `ds.recs_for = rot`. Then `ds.main()` runs. Inside main, does it call `_score_file` which references global `recs_for`? Yes, module global -> rot. So rot called with (tu, by_src, inc) from the real load. Unless main uses `a.try_` with tu being... print in rot.

Let me quickly make a debug copy under my shard dir? I can't modify shared helpers, but I can copy tryinc.py into my shard and add prints. Let me instead run with a wrapper in -c.
