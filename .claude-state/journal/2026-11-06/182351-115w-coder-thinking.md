---
ts: 2026-11-07T01:23:51.295Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a6113a6c423006329
model: claude-opus-5-5
effort: medium
turnId: b5ca22ff-b924-4947-95ef-cd25860f9a38
---
The header declares this function with an asm label and K&R-style parameters, while the translation unit redeclares it earlier with an `__asm__("")`. I'm weighing whether to drop the decl at line 1574, since the redeclaration at 1576 uses `int a4` against the K&R definition, and it may be needed for argument promotion. I'll check lines 1570–1580 and where the header gets included.
