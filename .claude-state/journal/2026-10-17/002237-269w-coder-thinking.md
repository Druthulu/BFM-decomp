---
ts: 2026-10-17T06:22:37.609Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm checking which callers already pass arguments via casts versus void stubs that cascade — for 800CC024, func_800CBFE4 likely needs cascading through a0, while func_800CBF28 already passes p1 directly. For 800CD1A8, both callers already cast properly, so no caller edits are needed there.

Next I need to move on to the remaining overlays: SC02_005, SC05_008, SC06_006, SC06_025, SC04_018, and the shared one at 80151664.
