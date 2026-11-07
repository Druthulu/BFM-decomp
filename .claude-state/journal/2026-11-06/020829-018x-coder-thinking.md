---
ts: 2026-11-06T09:08:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fPxLA8qvC7m4CjoDIDqs
---
dt.sh works for headers using recs[0] (first includer). But tryinc.py's rotation uses recs_for -> by_src; my earlier direct call passed ds.recs_for but `recs_for` in module uses by_src passed to it. In tryinc.py, orig = ds.recs_for, and it's called as recs_for(tu, by_src, inc) inside _score_file with real args, so r should be 136 non-empty if by_src has recipes for those includer srcs. But ZeroDivision means r empty at that point? Wait, tryinc.py modifies ds.recs_for, but _score_file calls the module-global recs_for... yes it does. Hmm, ZeroDivisionError at `r[k % len(r)]` means r empty. Maybe the print was skipped? Actually error traceback shows the rot function. So r was empty -> by_src.get(t_) empty for all 136 includers? But dt.sh works — dt.sh calls delever_search directly without tryinc, and _score_file exits if not recs. It worked, so recs non-empty there.

Wait — in tryinc.py, `sys.argv = [...]` then `import delever_search as ds`; then `orig = ds.recs_for`. But maybe delever_search uses `from ... import recs_for`? No. Hmm, but the ZeroDivision could be on `len(r)` where r is a list... k % len(r) with len 0. So r empty.

Difference: tryinc sets sys.argv = ["delever_search.py","--try"] + sys.argv[2:5] + ["--body"]. sys.argv[2:5] = [header, fn, body]. So args: --try header fn body --body. Same as dt.sh. Hmm.

Unless ds.recs_for is not the function called; maybe _score_file is invoked through a different code path with the wrapper... Let me just test with k=0 directly and add debug. Actually the error might be that `recs_for` is called with tu = rec? No.

Let me run tryinc.py 0 with the original win and see if it also fails.
