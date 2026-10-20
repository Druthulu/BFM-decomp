---
ts: 2026-10-17T17:22:12.076Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: f6f16880-5909-45e9-bf11-6d0f21d55a4b
---
Opus uses about 20k tokens per function, lower than T10's 40k, finishing each in 4-5 minutes. At this pace, with 7 shards of 8 running 4 in parallel, roughly 73 are done in about 1.5 hours, leaving 323 that would take another 6-7 hours. Switching to Haiku wouldn't save much on tokens since Opus is already efficient there—the real savings would come from price instead.
