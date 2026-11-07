---
ts: 2026-11-06T21:32:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a0EhMVa3a8IP6DsTeV2L
---
So `_score_file` calls recs_for(tu, by_src, inc) and uses recs[0]. tryinc.py's rot wraps recs_for and rotates by k. If recs is non-empty (as dt.sh proves), rot should work. The ZeroDivisionError suggests len(r)==0 when called from tryinc.

Ah — I see: tryinc.py's `rot` is called with `*a, **kw`. delever_search calls `recs_for(tu, by_src, inc)` positionally: a = (tu, by_src, inc). orig(*a) works. Then `print(f"... {len(r)}")` and `return r[k % len(r):] + r[:k % len(r)]`. If len(r)>0, fine.

But the error traceback shows `~~^~~~~~~~` and ZeroDivisionError: integer modulo by zero at `r[k % len(r)]`. So len(r)==0.

Unless... the header path passed to tryinc is wrong. I passed `$D/tu` as argv[2] (the header). Let me check: tryinc.py `sys.argv = ["delever_search.py", "--try"] + sys.argv[2:5] + ["--body"]`. So sys.argv[2:5] = [argv[2], argv[3], argv[4]] = [tu, fn, body]. I invoked: `tryinc.py $k $D/tu $D/fn $D/orig.c`. So argv[1]=k, argv[2]=$D/tu, argv[3]=$D/fn, argv[4]=$D/orig.c. Then sys.argv = ["delever_search.py","--try", tu, fn, body, "--body"]. Good.

But `$D/tu` contains `src/shared/ov/func_8012B8E4.h` (a path), and `$D/fn` contains `func_8012B8E4`. The `tu` arg passed to recs_for is the string "src/shared/ov/func_8012B8E4.h" (from cat of the tu file). Good.

Hmm, but wait: in tryinc.py, `orig = ds.recs_for` is captured at import time, then `ds.recs_for = rot`. But `_score_file` calls `recs_for(...)` — is it the module-global `recs_for` or a local reference? In Python, `_score_file` references the module-global `recs_for`, which is patched by `ds.recs_for = rot`. So rot is called. Good.

So why len 0? Maybe delever_search's main() runs `_score_file` in a subprocess or the `recs_for` used is a different one? Or maybe tryinc's `ds.main()` re-imports the module? Unlikely.

Wait, the traceback `~~^~~~~~~~` is from `k % len(r)`. Let me actually run tryinc with a print to debug. But maybe the issue is that `recs_for` is called with a DIFFERENT header path: dt.sh passes `$(cat $d/tu)` = "src/shared/ov/func_8012B8E4.h". tryinc passes the same. Hmm.

Actually, maybe the `inc` cache is keyed differently and the header's includers list is empty because `includers()` returns transitive includers but the header is included via a relative path that resolves differently. But dt.sh worked, so recs_for(header) was non-empty in that run. The difference: dt.sh runs `delever_search.py --try ...` as a subprocess with cwd=/home/musashi/bfm-decomp. tryinc.py is run from the project root too (I ran it as `.run/P40/T10/tryinc.py` from the project root). Hmm.

Wait — maybe tryinc.py's `rot` is called MULTIPLE times, and the first call has a non-empty list but a later call (with a different tu) has empty. Let me look: recs_for is also called elsewhere? In _score_file only once. But `main()` might call other things. Actually `--try` calls `_score_file` once. But the monkeypatch affects ALL recs_for calls, including any during module init? No.

Hmm, let me just run tryinc.py with a debug print. Actually, let me write a small script to print the includer count for the header using dl.includers() and recs_for.

Let me do that.
