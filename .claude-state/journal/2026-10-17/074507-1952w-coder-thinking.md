---
ts: 2026-10-17T13:45:07.274Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm puzzling over why these two function calls with the same address argument wouldn't be merged by the compiler, considering whether the functions might take no parameters or whether the address refers to an array element instead.

Thinking about how gcc 2.7 handles constant address arguments: with -G0, symbol addresses are legitimate constants that get loaded directly into the hard a0 register rather than through a pseudo. Since a0 gets clobbered by the call, cse can't establish equivalence between the two calls, so maybe a direct call without the intermediate local variable would reproduce the exact rematerialization seen in the original code.
