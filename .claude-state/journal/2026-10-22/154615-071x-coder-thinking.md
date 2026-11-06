---
ts: 2026-10-22T21:46:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_u2vXqDbN9rA9qoPs5rzj
---
The `loc` reference remains at line 4255 (`loc.b.raw[0]` in the second store?) — my replacement of ST should have removed it... Ah, e1 replaced ST but the body has another `loc` use? Let me look: the function uses `loc.b.raw[0]` in two places: `*(M8...)&loc.b.raw[0] = D_801E2DD8;` (in ST) and later `*(M8_SC02_005_8017F7CC *)&D_801E4C50 = *(M8_SC02_005_8017F7CC *)&loc.b.raw[0];` inside the if. Yes! There's a second use of loc.b.

Let me fix e1: replace the later read with `((u8 *)loc16 + 8)`.

Let me do it.
