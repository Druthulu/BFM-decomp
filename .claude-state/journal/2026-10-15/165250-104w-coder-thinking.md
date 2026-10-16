---
ts: 2026-10-15T22:52:50.431Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I need to figure out how the census tier/lhash rule actually works—what distinguishes tier 1 from tier 2—so I should check type_census.py for how duplicate rows and tiers get computed. I'm noticing that Ramp388C's tier-1 class now includes three new T3 defs that are identical to it, which means those should become residual TYPE-CAN entries.

There's also a separate wrinkle: two new defs are identical to each other within the same batch, which might indicate a different tier. The tier distinction likely hinges on whether field names match too, since the new defs have auto-generated names like unk0 while Ramp388C may use similar unk-style naming already—I should grep to confirm.
