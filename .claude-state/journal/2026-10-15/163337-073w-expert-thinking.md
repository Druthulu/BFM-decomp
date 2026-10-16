---
ts: 2026-10-15T22:33:37.900Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: e38d62ab-3c00-4d8d-a7ba-8c504be79727
---
I'm noticing that MatEntry is declared locally in an overlay .c file rather than in the canon headers, which raises a question about whether it actually qualifies as a canon type despite the grep match. I need to double-check that each of the 18 targets truly resolves to a type defined in engine_types.h or struct_types.h rather than a local .c-file typedef.
