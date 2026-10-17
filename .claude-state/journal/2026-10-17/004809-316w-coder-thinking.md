---
ts: 2026-10-17T06:48:09.789Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: 3752e07b-4737-417a-943d-26bcb99c8520
---
Now I'm moving to 80157D20/80151664, planning the batch 4 caller edits by hand after batch 3 finishes: converting func_8015410C's header to K&R style with a body that resets D_80127518 before cascading into func_80151664, plus updating its many extern declarations to the K&R interim form so callers can cast-call it.

I also need to handle func_8017D098's shared header, converting its no-arg body into one that passes through the s32 argument to func_80151664, while its existing decls across the SC02/SC04 files already match K&R. The 22 cast-call sites for func_80151664 stay as-is, and I'll convert the remaining decls and def head to K&R before running the signature pass per header.

For 80157D20, I'm similarly updating func_80149CB4's header and body to delegate to func_80157D20, converting its decls and the 72 void-style decls of func_80157D20 to K&R, then running the signature pass on each header -- though I need to double check how the scope works once func_80157D20's declaration inside func_80149CB4.h gets touched by that pass.

I'm now confirming that the header-run scope covers the five TUs that include it, and that func_80149CB4.h ends up at 136 occurrences needing a manual prototype fix afterward. For the other 131 non-header binaries, the delegation call still lines up fine with func_80157D20's real definition elsewhere, so the interim K&R conversion across roughly 2400 files for the three names should hold -- now waiting on b3 before continuing.
