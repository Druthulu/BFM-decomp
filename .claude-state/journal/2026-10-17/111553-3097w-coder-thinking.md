---
ts: 2026-10-17T17:15:53.270Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm tracing why c3 picks up c in v0, then checking the register ordering for p1 and the second pointer — it seems like v1 holds p1 first, then arg0 gets reused and reloaded via a0, which means arg0 can't be assigned to a1 for this to work. I'm puzzled why in my version arg0 ended up in v0 instead of a0.

Local-alloc normally handles pseudos confined to a single basic block, but arg0 gets set twice, so I'm wondering if that disqualifies it from local allocation and forces a different hard register. I'm considering restructuring the source so p1 loads first into v1, then arg0 writes to unkFC, then arg0 reloads — trying to see if that ordering naturally produces the a0/v0/v1 split, and I should check the dump scripts to confirm how the original example was structured.
