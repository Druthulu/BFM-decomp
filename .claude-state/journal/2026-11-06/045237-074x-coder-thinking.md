---
ts: 2026-11-06T11:52:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_byMLiELjBWiXsx9znHor
---
Key: `elt->in_struct = (MEM_IN_STRUCT_P (inner_dest) || inner_dest != SET_DEST)`. The store's mem is `MEM_IN_STRUCT_P` if the store was through a struct field.

Then for a load, cse checks `elt->in_struct` vs the load's `MEM_IN_STRUCT_P`? Let me look at the load handling / `lookup` and the check. Search for "in_struct" in cse.c.
