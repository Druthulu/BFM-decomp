---
ts: 2026-10-15T22:16:39.620Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I'm weighing two readings of "declared as canonical type C": a strict single-declared-type interpretation yields just 1 global, while an exactly-one-canonical-among-many-TU-local-types rule yields 20. Both are deterministic, so I need to decide which interpretation the brief actually intends.

I'll go with the exactly-one-canonical rule — any declaration as C counts, and ambiguity only arises when more than one canonical type is declared for the same global. I need to update the tree-facts logic to track the full set of declared types per global rather than a single type, then have the band-decision step filter that set down to canonical types and check for uniqueness. I should also update the self-test to use a global with multiple declared types (one canonical, one not) to properly exercise this new logic.

I'll switch E2 to key off the unique canonical type among a global's declarations rather than requiring a single declared type tree-wide, since globals with multiple canonical types won't get an anchor.
