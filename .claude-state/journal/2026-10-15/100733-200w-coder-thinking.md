---
ts: 2026-10-15T16:07:33.205Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a39b699a467f2c7b2
model: claude-opus-5-5[1m]
effort: medium
turnId: 222ded7f-48dd-426b-b712-eaf41c6db60b
---
I'm wondering if the latest row backing a macro site is actually a residue or restamp row whose verdict falls outside BACKED_S_VERDICTS, which could explain the mismatched NO-SITE counts between resim, ov, and md.

I need to pin down the 7 sites rather than guess. Writing a debug script that reimports type_census feels too slow at 190 seconds, so I should instead trace how macro_sites gets populated and track down where check_casts_verdict is actually invoked.
