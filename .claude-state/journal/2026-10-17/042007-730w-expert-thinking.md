---
ts: 2026-10-17T10:20:07.000Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a28afe298c346ad4e
model: claude-opus-5-5[1m]
effort: medium
turnId: 19fadc38-27f9-43cf-8450-c53af22fd50b
---
Removing the launder in func_8001BBBC causes a compile error, so it's actually needed—I'll mark that row as "removal does not compile (COMPILE-ERROR)". Now I need to hand-edit three rows for func_8001BBBC, func_80020F34, and ENGINE_SHB, which I'll do with a small python script.
