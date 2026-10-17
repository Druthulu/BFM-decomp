---
ts: 2026-10-17T17:08:32.098Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm puzzling over why r73 gets allocated to a1 even though it seems like it was allocated first — this must come down to how local register allocation picks free registers in priority order, possibly without a custom allocation order defined for mips in this gcc version.

Right, qty ordering follows birth order, so r73 as qty 0 goes first in allocation — meaning v0, v1, a0 must already be unavailable for some other reason. I'm now recalling that MIPS gcc 2.7 might define a custom REG_ALLOC_ORDER in mips.h that reorders which hard registers get tried first, which could explain why a1 was picked over v0/v1.

I'm starting to wonder if local-alloc's register allocation order isn't simply births-first — maybe qtys with suggested registers get processed before others, which would explain why r73 landed on a1 instead of following the strict numeric sequence. I should check whether anything else references v1 within that range before assuming it's actually free.
