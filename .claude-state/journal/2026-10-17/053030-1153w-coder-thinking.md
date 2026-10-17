---
ts: 2026-10-17T11:30:30.204Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm trying to figure out register scheduling so the store to that global happens before the frame pointer load—likely need the fp load to depend on v0 so an anti-dependency forces the store first, rather than having the call result stored directly.

Also considering whether the compiler sees the store and the fp load as aliasing: since D_8011511C is a u16 and D_80182668 is a pointer array indexed by a different u16 global, the scheduler may treat them as non-conflicting since they're distinct symbols with known addresses. I think I need to look at the full diff to understand what's actually forcing the ordering.
