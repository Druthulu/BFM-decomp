---
ts: 2026-10-17T12:04:11.968Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I should check how match_one verifies things—it likely needs the full file with externs included. I'm thinking about how T9.c5 handled this by combining a prelude header with win.c, and I want to build a similar prelude by splicing the externs from the translation unit, following the pattern gen.sh used for 80141874.

Actually, the simplest approach is to just save the full spliced TU as full.c and run match_one on that directly, rather than constructing a separate prelude—I'll write bin/full.sh to do this.
