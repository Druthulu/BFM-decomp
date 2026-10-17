---
ts: 2026-10-17T04:23:44.222Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
The two md functions take their first argument in `$4` through a pinned register local. I'll give them a real `s32 a0` parameter, which puts the value in `$4` under the o32 ABI. That should match the original codegen, and I'll let restruct.py rung D judge it. func_8016BF50 then gets a single ANSI prototype so the shared-body extend stops conflicting. Every change goes through restruct.py so the oracle decides, and no hand edits get past it.
