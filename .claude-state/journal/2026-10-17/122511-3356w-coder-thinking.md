---
ts: 2026-10-17T18:25:11.797Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a11ed4236c71ce25b
model: claude-opus-5-5[1m]
effort: medium
turnId: 638017c5-5103-4585-b12e-50498d92977e
---
I'm noticing that many instruction losses come from register allocation choices—without the pin, v0 gets grabbed by the constant load before the call's return value and the "ok" pseudo can settle into it, causing the mismatch across its live range.

This looks similar to a wall seen in W04 func_80188680. I'm thinking through whether making the comparison constant local instead of global would help—maybe by restructuring so "ok" stays confined to one basic block, avoiding the branch structure that forces it to span blocks and become a global allocation target.

I'm also considering why local-alloc assigns v0 to the constant 14 before global-alloc gets to pick a register for "ok"—it seems to come down to allocation order preferences, with v0 being tried first among free registers, which pushes "ok" into v1 instead.

Maybe splitting into a local `r = func & 0xFF` and letting `ok` be set globally in each arm could work, since r and 14 die before ok is born. But that's the c7 variant which lost instructions due to jump threading folding the 0/1 check — I need to figure out why the counts differ, 58 versus 62.
