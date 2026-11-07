---
ts: 2026-11-06T16:56:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vH0VJ8jKdLI7i3Gi77ZT
---
local-alloc assigns registers in order of decreasing life length. The first quantity to allocate gets the "cheapest" free register? Let's look at find_free_reg and the ordering. The allocator tries the cheapest class first; then `qty_phys_reg[q] = -1` for those without suggestions, and later:

```
for (i = 0; i < next_qty; i++)
  {
    q = qty_order[i];
    ...
    if (qty_phys_reg[q] < 0)
      qty_phys_reg[q] = find_free_reg (qty_min_class[q], qty_mode[q], q, 0, 0, qty_birth[q], qty_death[q]);
  }
```
find_free_reg scans the allocatable registers in some order. Let me read find_free_reg.
