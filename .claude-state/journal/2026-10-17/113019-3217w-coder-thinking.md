---
ts: 2026-10-17T17:30:19.594Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm trying to figure out why the compare still reads a1 even with the copy in the else branch - it seems like some pass hoisted the move before the branch, setting a1=v0 on one path and a1=0 on the fallthrough, which looks like it could be jump threading rather than CSE.

Actually, I'm reconsidering this as an if-conversion pattern from gcc 2.7's jump.c, where "if (x) a=0 else a=b" gets rewritten to "a=b; if (x) a=0" by jump_optimize. Then cse2 would see the copy sitting before the compare and merge it with the canonical mode, so I need to check the actual dumps to see whether the rewrite happened in .cse or .cse2.
