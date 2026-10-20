---
ts: 2026-10-17T18:21:52.508Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa9b0e5d08de57697
model: claude-opus-5-5[1m]
effort: medium
turnId: e63830b2-df73-4dc7-aa47-f942d785c11a
---
I realize my regex is matching call sites too, since it doesn't require the match to start at the beginning of a line without leading whitespace. I need to anchor the pattern so indented lines like function calls don't get mistaken for declarations.
