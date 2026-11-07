---
ts: 2026-11-06T12:13:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_u0tbgXbIK8CqxrbTo6lw
---
OK: `--keep` prints candidate object path. But scratch dirs must be removed after use ("`--keep` scratch is removed after use"). Fine.

Let me write a dump helper that: takes obj path and fn, prints "idx mnem" for a range. And for target: get recipe obj → baseline_path. Let me write dump.py:

```python
import sys, pathlib
sys.path.insert(0, "tools")
import masked_diff as md
import delever_oracle as oracle
import delever as dl
```

Hmm, importing tools modules from a script under .run — need sys.path. Simpler: use `md.insns_from_object`. For target object, I need the recipe. I can just pass the object path as an arg; find it via a one-time python call.

Let me get the object path for src/800.c: use oracle.load_recipes + recipes_by_src. One-off script.
