---
ts: 2026-10-15T22:05:45.299Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I'm working out the definition for a site "sitting on a base" of a canonical type: checking whether at least 90% of a site's MEMBER entries tied to its base norm share one majority type, then seeing if at least 50% of a type's TNC sites satisfy that condition.

For E2, I need to track down where global declarations are canonically typed (non-pointer object or array) in src/ or include/, so I'm checking whether an existing census tool like type_census already tracks this, and searching for how `globals_at` is populated.
