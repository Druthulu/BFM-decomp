---
ts: 2026-11-06T04:53:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cikwVsQNuUALzUgdKS1R
---
--keep didn't print because tryinc sets argv explicitly and drops extra args? tryinc: `sys.argv = ["delever_search.py", "--try"] + sys.argv[2:5] + ["--body"]` — it drops args beyond 5. So --keep is ignored. I'll run delever_search directly with the includer's TU recipe? The `--try TU FN FILE --body` where TU is the includer file. For a header, the recipe is the first includer. Just use the includer path as TU directly: `--try src/ov_MAIN_012/ov_MAIN_012_jr_801380E0.c func_8013A2BC a1.c --body --keep`.

Let me do that.
