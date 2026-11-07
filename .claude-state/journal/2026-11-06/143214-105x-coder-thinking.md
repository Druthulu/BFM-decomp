---
ts: 2026-11-06T21:32:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8NluiN4IAmx3F5ADovPM
---
includers map has 136 entries. So recs_for should return non-empty (as long as by_src has recipes for those TUs). The ZeroDivisionError must be because `by_src.get(t_)` is empty for the rotated TU? No, recs_for builds the whole list.

Wait — `recs_for(tu, by_src, inc)` returns `[r for t_ in inc.get(tu, []) for r in by_src.get(t_, [])]`. If by_src has no recipes for the includers (e.g., recipes list changed), it's empty. But dt.sh worked → by_src had at least one. Unless dt.sh's --try used a DIFFERENT tu string. Let me check: dt.sh does `$(cat $d/tu)` where $d/tu = "src/shared/ov/func_8012B8E4.h". Same.

Hmm, let me test recs_for directly.
