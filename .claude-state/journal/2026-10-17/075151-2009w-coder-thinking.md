---
ts: 2026-10-17T13:51:51.653Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm wondering whether the register holding s0 being stable rules out natural rematerialization here, unless it's happening through inline assembly. It makes me think about whether the original source called something like Psy-Q's SetRotMatrix, which could explain why the compiler emits two jals and reloads the matrix address this way.

I'm sketching a possible pattern where a pointer variable gets reused -- assigned to the matrix address, passed to one function, then reassigned to a different value before being passed to the next function that reloads the original address, which could force the needed cse invalidation naturally.
