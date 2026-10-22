---
ts: 2026-10-21T23:37:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Y002lBLa3lp2ExlpREp9
---
Good. Now I understand: `--try` with `--body` splices the body into the TU, and for headers it shadows the header via an include dir, compiling the primary includer (recs[0]).

To sweep all includers, I need to rotate recs. tryinc.py does that by monkeypatching recs_for. My sweep.py "all" mode does that but subprocess-based (the monkeypatch doesn't affect the subprocess!). I need to run it in-process. Let me restructure: import delever_search and call its main with modified sys.argv, in-process.

tryinc.py does exactly this: `runpy`-style with sys.argv set and sys.exit(ds.main()). So I'll write my own that loops k in-process.

Let me rewrite sweep.py's "all" mode to call ds.main() in-process with monkeypatched recs_for.

Careful: ds.main() may sys.exit. Wrap in try/except SystemExit.

Also the "score" mode: subprocess is fine but slow-ish; in-process would be faster for sweeps. Let me make score mode in-process too, with output capture.

Let me rewrite.
