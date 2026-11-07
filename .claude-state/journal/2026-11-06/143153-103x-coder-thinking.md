---
ts: 2026-11-06T21:31:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6jg0ej0o4OKl19AS7NkE
---
The --try for a header compiles ONE includer (rec["src"]) with the header shadowed. The score is against that includer's baseline. It doesn't verify all includers. The brief says MATCH requires score 0 on every includer, verified with tryinc.py k=0..n-1.

tryinc.py rotates the includer list; the ZeroDivisionError means recs_for returned empty. But dt.sh worked, so recs_for(header,...) inside delever_search --try returned at least one rec (since it printed a score). Wait — dt.sh calls delever_search --try with the header TU. The --try path uses `rec = recs[?]`? Let me see how --try picks the rec. Let me look above line 765.

The --try path: `recs = recs_for(tu, by_src, inc)`; then picks `rec = recs[?]`. If recs is non-empty, it works. So recs_for IS non-empty when called from delever_search. But tryinc.py's `rot` monkeypatches `ds.recs_for` and calls `orig(*a, **kw)` where `a` = the args passed by delever_search. delever_search calls `recs_for(tu, by_src, inc)`. So rot gets (tu, by_src, inc). orig returns the list. If non-empty, it rotates. But it printed ZeroDivisionError → len(r)==0.

Hmm, maybe the delever_search --try path calls recs_for with different args or the `inc` is empty in tryinc's context. Wait, tryinc.py inserts /home/musashi/bfm-decomp/tools into sys.path and imports delever_search as ds, then calls ds.main(). The main() builds by_src and inc itself. So the same as dt.sh. Why would recs_for return empty?

Wait — maybe delever_search's --try path does NOT call recs_for at all for a header; maybe it uses a different function to get the rec. Let me look at the --try code above 765.

Let me read 740-770.
