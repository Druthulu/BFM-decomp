---
ts: 2026-10-17T11:48:17.345Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm worried the "tu" filename clashes with my setup's existing tu file, and that delever needs a recipe for TU in src. For signature changes, I think I should use match_one against the whole file rather than a snippet, since it compiles a standalone C file with includes -- so copying the TU into scratch with the declaration changed and the body spliced in might work.
