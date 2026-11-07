---
ts: 2026-11-06T09:16:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_onbQSxzIZS9k4Wkgz3aS
---
Same swap. The allocation gives v0 to the load temp (flg) and v1 to res. Target gives v0 to res and v1 to flg.

Why? In the target (with pin), res is a hard-reg $2 pseudo. flg is a normal pseudo. The target shows flg in v1 and res in v0. So with the pin, res=$2 fixed, flg gets v1 (because v0 is taken by the hard reg). In lever-free, both compete; local-alloc gives v0 to... flg.

So to match lever-free, res must win v0. Local-alloc order: let me look at local-alloc.c to understand allocation order. In GCC 2.7.2 local-alloc.c, `local_alloc` processes basic blocks; for each block it allocates quantities in order of... `qty_cmp`? Actually in local-alloc.c, the allocation is done by `alloc_qty` on qty numbers sorted by `qty_n_refs` or by size? Let me check.
