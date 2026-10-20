---
ts: 2026-10-17T18:51:14.276Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm rewriting this decompiled function into cleaner C with properly named variables instead of register-based names.

Still refining the array indexing...

I see this is register-named m2c output reusing a single `v0` throughout. I'll produce a natural-C rewrite using array indexing with distinct temporaries, plus a version of the original that just splits the reused `v0`.
