---
ts: 2026-10-17T06:20:47.279Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
Looking at 8017EC90 (SC03_007), I notice the K&R function declares params a0 and a1 which are then read via pins at the same register positions — meaning the pin is just duplicating an existing parameter, so the fix is to use a0/a1 directly instead of the pin reads.

Going through the remaining cases: 8017DC50, 8017DE00, 80186CE0, 8018BCD4, 8018893C, 801854DC, 80183130, 80182424, 801857A4, and the four 80175AB8 instances are all written-first so they classify as SCRATCH. That leaves three unresolved traces — 8018094C, 8017E3F0, and 8012E688 — which I still need to check individually.
