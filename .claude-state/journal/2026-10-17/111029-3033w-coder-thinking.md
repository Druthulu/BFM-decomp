---
ts: 2026-10-17T17:10:29.010Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm wondering if the same address-commoning trick could apply to func_80180728's p0/p1 parameters, reassigning p1 after the first call to see if it forces a similar pseudo-variable pattern as seen with the sp+40 address in 80180728.

That said, the loop barrier and j laundering variables still block full laundering regardless, so even if p0/p1 crack to PARTIAL, the overall WALL result won't change—it's just worth a quick two-try test for evidence given the modest time budget remaining.
