---
ts: 2026-10-17T16:30:44.367Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm noticing j=0 being set late shortens j's live range, which raises its priority and lets it allocate earlier—in q6 j took a2 instead of the target t0, and pb now looks fine. I want to pull up q6's allocation table to compare priorities against the target.
