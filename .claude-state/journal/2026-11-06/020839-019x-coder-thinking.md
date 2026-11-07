---
ts: 2026-11-06T09:08:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XdlSSqqzk7DRJt3BqlPw
---
recs_for returns empty here but not under dt.sh. Perhaps delever_search's _score_file imports recs_for differently — check: maybe `recs_for` is rebound later or _score_file uses a local variable. Let me grep for "recs_for(" occurrences: lines 504, 660, 682, 752, 849. It calls global. Hmm.

Wait — maybe delever_search is loaded twice: tryinc inserts tools into sys.path and imports delever_search; but tools/delever_search.py may run main under `if __name__ == "__main__"`? It's imported as module and then `sys.exit(ds.main())`. Fine.

Could by_src be built via oracle.load_recipes() and in the wrapped call recs_for is called with inc.get(tu,[])... Let me debug by printing inside rot.
