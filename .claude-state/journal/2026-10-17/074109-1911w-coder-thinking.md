---
ts: 2026-10-17T13:41:09.770Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
Looking at expand_divmod, the issue traces to t1 being a copy of op0, which holds the rand return value in $v0. Global allocation forces t1 into $v0 too, which pushes the rand result into $v1 instead. The target uses $16 (s0) for t1 likely because t is live across the second call to rand(), making it a callee-saved register candidate rather than a volatile one.

Without the pin, t would land in some other s-register already occupied by a0, i, pick, or obj, so I need to look more closely at the diff to see how the divmod temporaries interact there.
