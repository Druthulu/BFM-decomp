---
ts: 2026-10-17T09:13:28.596Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm wondering whether s8 should be hoisted into a local pointer variable pointing to D_80126B58, mirroring the "lever" pattern mentioned around line 1251, since gcc would naturally hoist that address out of the loop as a loop-invariant.

For the negation case, I'm considering trying a different form for the subtraction—writing it as an addition of a negated term so gcc emits a negu followed by multiply instead of folding it into a subu.
