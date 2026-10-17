---
ts: 2026-10-17T06:22:07.338Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
Since callers already pass three arguments through cast-calls, I just need to update the function definition and declaration to take three s32 parameters instead of two—no caller edits required since 80180FA4 is def-only.

Checking 8018107C (SC07_007), it's also def-only with a body change but unchanged signature, and 8017EC90 is a K&R duplicate.

So I'm splitting batch 2 into caller-edit cases like 80187038, 801811A8, 80185AC0, and several cascading ones including 80157D20 which has a heavy cascade through func_80149CB4, versus def-only cases like 80180FA4, 8018107C, and 8017EC90. I'll defer 80157D20 to batch 3 since it's the most complex cascade, and once the background work finishes I'll move on to the batch 2 caller edits.
