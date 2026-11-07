---
ts: 2026-11-06T05:22:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AAwLjd0NdHVm5pIqU0gr
---
This is about volatile refs, not dead stores. The actual dead-store removal for memory is in `cse.c`'s cse_insn: it records stores to memory and can delete an earlier store if the same memory is overwritten. Let me look for "invalidate" / "delete" in cse_insn around stores.

Actually — maybe the removal isn't a "dead store" at all! Maybe the compiler *merged* the stores: `b[0]=t; ... b[0]=u88;` — cse could replace the second store's value... no.

Hmm, wait. Let me recount. Mine has 42 insns vs target 45. The diff showed mine[21:26] vs target[21:29] — mine has 5 insns, target has 8. The target's extra 3 insns are `sh v1,24`, `sh v0,28`, and one more. So yes, 3 stores removed.

Maybe it's `combine` merging the two stores? No, they're to the same location with different values.

Let me find it in cse.c: search for "store" and "delete" or the `sets[i].dest_hash` logic. In cse_insn, for each set with a MEM dest, it checks `sets[i].dest_hash` and if the same memory was stored earlier and not used, it can delete the earlier insn. There's a function `cse_insn` with:

```
	  /* If this is a store into memory, ... */
```

Let me grep for "sets\[i\].dest" and "MEM".
