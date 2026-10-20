---
ts: 2026-10-17T17:33:11.208Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm tracing how local-alloc assigns registers to the mlo/mhi constants, since the swap means mlo now maps to t4 and mhi to t2 — checking whether allocation priority, based on reference counts and lifetime, explains why they got flipped.
