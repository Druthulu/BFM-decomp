---
ts: 2026-10-17T16:36:53.717Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing the join block stores the computed value right after the branch arms in the target, but in my version the scheduler hoists the constant load for 0x64808080 above that store, shifting its position relative to the target's instruction order.

The remaining mismatch is just the constant hoisting above the sh, and storing y later isn't an option. I'll try quick variants on k2 with pins kept, then combine with the keepalive fix.
