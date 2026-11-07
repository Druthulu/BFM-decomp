---
ts: 2026-11-07T01:25:09.210Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a6113a6c423006329
model: claude-opus-5-5
effort: medium
turnId: b5ca22ff-b924-4947-95ef-cd25860f9a38
---
I'm noticing a second declaration that looks similar, so I'll check whether func_8014E5B4 is actually referenced anywhere. I also want to look at the other declarations. The `__asm__("")` on an extern that gets used would leave the symbol name empty, which would be a compile error, so I need to see where it's used.
