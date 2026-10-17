---
ts: 2026-10-17T04:59:11.674Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abc404fb8a77f6873
model: claude-opus-5-5[1m]
effort: medium
turnId: ffb0e172-bea2-4dc0-ae04-98d6d34d67e0
---
Since none of the includers declare this as u8, the K&R declaration must be file-scope in each including TU, so I'm checking whether declaring it as `extern s32 func_80014CF8(s32 a0, s32 a1)` preserves the byte layout — the K&R call passes an s32 and an int literal 4, matching this s32 prototype.

But I'm second-guessing whether that counts as "lying" to the type checker versus the real `u8 (u32, u32)` definition. It might still be worth trying `extern u8 func_80014CF8(u32 a0, u32 a1)` instead, since gcc 2.7's calling convention for u8 returns doesn't assume zero-extension by the callee — the caller inserts its own masking on each use, which could fold together with the explicit `&0xFF` already in the K&R code and end up producing matching byte counts despite the type mismatch. This is cheap enough to just test directly.
