---
ts: 2026-10-17T08:59:43.841Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm comparing the register usage between my version and the reference at 80025CBC, checking whether the delay-slot move and subsequent addiu instructions line up correctly despite using slightly different register names.

There's also a subtle ordering question about when the sb store and the lw of otz happen relative to each other — the target schedules the store after the load, interleaving the tag computation with the code store, so I need to try reordering my source to match, perhaps setting d->code before the setlen assignment or vice versa.
