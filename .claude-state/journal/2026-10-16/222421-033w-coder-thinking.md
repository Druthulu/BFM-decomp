---
ts: 2026-10-17T04:24:21.038Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
Since callers live in the same translation unit as the definition, I'm thinking I can just prepare a fully edited copy of that TU in scratch space and pass it as the body/with argument together, rather than handling def and callers separately.

I should double check whether these functions have duplicate copies elsewhere at the same address -- grep only turned up this one file, but I want to also verify the line 1941 reference from the comment and scan for every occurrence within the file.
