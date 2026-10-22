---
ts: 2026-10-22T12:56:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IVtg8eEd55PJcksV1y3l
---
This is deep. Let me look at the earlier part where `src_const` is computed for a set — the key part:

```c
	      /* If this insn is a set of a pseudo to a constant, ... */
```

Let me look for where src_const is set (around line 6600-6700) to see the condition on the number of sets.

Let me search for "src_const =" in cse.c within the block-processing function.
