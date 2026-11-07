---
ts: 2026-11-06T07:24:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZGUJNPYhqRQUm8EcakKU
---
I'll write a scratch script under G24 that prints target and mine. But it needs the recipe for the TU. Simpler: use objdump on baseline object. Let me find the baseline path via oracle. Write a small script:

```python
import sys, subprocess, pathlib
sys.path.insert(0, "tools")
import delever as dl, delever_oracle as oracle, masked_diff as md
recs = dl.recipe(...)? 
```

Hmm, how does --try get recs? Let me look at main for --try.
