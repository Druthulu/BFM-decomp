---
ts: 2026-10-17T17:12:41.495Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm realizing my extractor incorrectly matched a call site rather than a function definition, so I need to tighten the regex to require the line to start without indentation, ensuring it only captures actual declarations.
