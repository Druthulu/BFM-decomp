---
ts: 2026-11-06T08:34:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6N9mdb47B5pbTLjskjlb
---
I'll write a small script under my shard dir `tgt.py` that prints target and/or mine listing for a TU/fn. But maybe simpler: write a script that takes item dir and prints both listings side by side. Let me write `dumpboth.py` in .run/P40/T11/G25/.

Actually dt.sh already gives the diff positions. But for reasoning I want full target listing. Let me write a script:

```python
import sys, pathlib, json
REPO=pathlib.Path('/home/musashi/bfm-decomp')
sys.path.insert(0,str(REPO/'tools'))
import delever_oracle as oracle, masked_diff as md
tu, fn = sys.argv[1], sys.argv[2]
# find obj for tu: need recipe. delever_search has recs_for(tu)
import delever_search as ds
recs=ds.recs_for(tu)
base=oracle.baseline_path(recs[0]['obj'])
ins=md.insns_from_object(str(base), fn)
for i,x in enumerate(ins): print(i, x['mnem'])
```

Need ds.recs_for signature. grep.
