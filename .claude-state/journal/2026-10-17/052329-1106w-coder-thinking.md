---
ts: 2026-10-17T11:23:29.479Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
Still plenty of time left, so I'll jot progress notes and keep working. I need to trace cse1's path for the a1 variant more carefully—since pe's uses were already replaced in cse1 and stable, the remaining issue is isolated to cse2, where I need to ensure the class containing (plus pd 4) stays correctly identified as const(sym+4).

I'm considering the ways this could happen without extra final code: either a live SET whose source is (plus pd 4) gets deleted after cse2's rewrites, or there's a SET with that same source whose destination gets used for something real later, like pe = pd + 2 serving as a loop pointer. I want to check the target code for any later register still holding the address of D_80115120, searching for an addiu instruction referencing offset 0x5120.
