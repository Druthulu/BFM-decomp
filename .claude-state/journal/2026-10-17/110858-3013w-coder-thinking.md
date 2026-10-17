---
ts: 2026-10-17T17:08:58.493Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
Pinning seems difficult, so I'm considering other ways to block loop hoisting—maybe through register allocation hints or by checking whether the size variable's type (u8 vs s8 vs s16) affects how the constant gets promoted into a pseudo register, since that promotion is what's enabling the hoist in the first place.

Actually, I wonder if combine could produce the constant load after the loop runs, using an expression like `(j | 8) & 8` that depends on j so loop optimization won't hoist it as invariant, but combine later simplifies it to a plain constant 8. But this feels like exactly the kind of identity-launder trick the brief explicitly disallows, so I shouldn't rely on it.

Instead I'm leaning toward a genuine loop-invariant-hoist mechanism: loop.c's scan_loop pulls the constant assignment out of the loop body since it's set once and used in its block, leaving a PARTIAL:pin with a zero-score win. The nested do-while keepalive trick works too, since the brief permits do-while with a !FAKE comment, though I should compare it against simpler single-nesting alternatives before settling on this version. I'll go ahead and write win.c along with the notes and rows now.
