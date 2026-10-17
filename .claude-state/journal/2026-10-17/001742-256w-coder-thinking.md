---
ts: 2026-10-17T06:17:42.636Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm noticing func_80149CB4 just forwards both arguments into func_80157D20, but the declaration for that function across the codebase seems to only take a void parameter — which raises a question about how this actually compiles given the mismatched signature in the 136 translation units that include this header.

I need to work out whether func_80149CB4.h's declaration conflicts with the 131 definitions it would appear alongside — if `extern void func_80157D20(void)` sits in the same TU as a def taking two params, that's a hard error, so the header must be excluded from those overlay TUs entirely. For now I'll K&R the declaration in both the header and the 5 affected TUs, letting the two-param prototype get set by hand after the rung D pass makes everything consistent, and I need to verify whether func_80149CB4.h actually gets included anywhere alongside those 131 definitions.

The fix that matches all 141 binaries is updating func_80149CB4.h's call site to pass the two arguments rather than none, since the (void) decl currently causes callers to silently pass nothing when the real def expects two params. I'll handle that in batch 2 once the background check on func_80149CB4 references comes back.
