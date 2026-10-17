---
ts: 2026-10-17T06:47:35.977Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: 3752e07b-4737-417a-943d-26bcb99c8520
---
While I wait, I'm sketching plan for the next batch of functions, including figuring out how to handle the aliased function 8018094C, since the body heads regex needs a callee pattern that doesn't quite match its signature—trying to find a workaround via a signature-based approach.

I'm digging into why the alias head regex fails for 8018094C: the stored alias text uses `func_8018094C_bank` while the regex looks for `func_8018094C` as a whole word, so it never matches and the body edit bails out. That means rung D can't patch alias-defined functions directly, so I'm considering whether a `--unalias` option exists to convert the alias into a plain definition first, though that feels like a separate class of change outside the current scope. For now I'm leaning toward flagging 8018094C as blocked—alias-defined via an asm label, requiring unalias before body edits can work—but I want to check if `--unalias` is cheap to try first.
