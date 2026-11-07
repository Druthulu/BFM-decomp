---
ts: 2026-11-06T21:32:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SxO9rytIdaXuYsC0wsWh
---
recs_for returns 141 recs (not 136; the includers map has 136 but by_src may have multiple recipes per TU). So why did tryinc.py get len 0?

Ah — I bet the issue is that tryinc.py's `rot` is called, but `orig(*a, **kw)` returns the list, and then it does `r[k % len(r):] + r[:k % len(r)]`. That's fine for len>0. The ZeroDivisionError means len(r)==0. 

Wait, maybe `rot` is called with different arguments than I think. `delever_search._score_file` calls `recs_for(tu, by_src, inc)` — 3 positional args. But maybe `main()` also calls recs_for elsewhere with 1 arg? Let me check line 504: `scorer = Scorer(tu, fn, recs_for(tu, by_src, inc), tag, inflight)` — that's for --run, not --try. For --try, only _score_file.

Hmm, but tryinc.py's rot: `def rot(*a, **kw): r = orig(*a, **kw); if r: print(...); return r[k % len(r):] + r[:k % len(r)]`. If r is empty, the `if r:` is false, so it skips the print, then `r[k % len(r)]` → ZeroDivisionError. So r is empty in that call.

But my direct test shows 141. The difference: tryinc.py is run as a script, and it does `sys.argv = [...]` then `import delever_search as ds`. Maybe the import happens with a different sys.path/cwd, causing `dl.includers()` to use a different RUN dir or cache. But `dl.includers()` uses REPO paths.

Wait — tryinc.py does `sys.path.insert(0, "/home/musashi/bfm-decomp/tools")` AFTER `sys.argv = ...`, then `import delever_search`. That should be the same module.

Hmm, but maybe the `--try` path calls recs_for with `tu` = the header, but the monkeypatch wraps `ds.recs_for`, while `_score_file` uses the name `recs_for` resolved in the module globals — which IS patched. 

Let me just run tryinc.py again and capture the full traceback.
