---
ts: 2026-11-06T21:46:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vA834G68CKWXslEAnniM
---
I'll write a scratch script `dis.py` under my shard dir:

```python
import sys, pathlib
sys.path.insert(0, "/home/musashi/bfm-decomp/tools")
import delever_oracle as oracle, masked_diff as md
tu, fn, body = sys.argv[1:4]
# find the baseline obj for fn
...
```
How to get the primary record? `oracle` has recs_for? delever_search uses `ds.recs_for`. Let me look at oracle's API: `oracle.baseline_path(obj)` and records. Simpler: use `md.insns_from_object` after finding the obj path from the record.

Let me check delever_oracle for a function listing recipes / obj.
