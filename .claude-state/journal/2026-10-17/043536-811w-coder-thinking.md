---
ts: 2026-10-17T10:35:36.345Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
Those earlier goto tests were against an older body before the c29/c48 plain-C move changes, so I should rerun the goto inner loop test against the current body_free which includes those updates. Let me set up a workdir and helper script for this.
