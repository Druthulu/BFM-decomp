---
ts: 2026-11-06T05:00:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JzDeKzapTn4C0xwRNpzw
---
The dest (MEM) is inserted with `sets[i].src_elt` as its equivalent. `elt->in_memory = (GET_CODE(inner_dest)==MEM ...)`. A later load of the MEM looks up the hash and finds the entry; if the entry's `in_memory` is set (the entry itself contains a MEM?) it's skipped for replacement? Let me check lookup's use of in_memory. Search "in_memory".
