---
ts: 2026-10-15T22:15:53.509Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
E1 checks out structurally since only two band TNC sites have any MEMBER entry on the same base, which matches what's expected given how the restamp moves TNC sites with a drawn base. Now I'm looking at E2's 235 ambiguous cases, where the same symbol gets declared as different types across translation units (like s32 versus u8), and I want to figure out whether "ambiguous" should actually exclude canonical entries.

I'm refining the rule so that if the declaration set has exactly one canonical type among it, it should resolve as C rather than count as ambiguous, and only flag true ambiguity when two distinct canonical types appear. Now I need to check how many of the 235 would shift into the canonical bucket under this refined rule.
