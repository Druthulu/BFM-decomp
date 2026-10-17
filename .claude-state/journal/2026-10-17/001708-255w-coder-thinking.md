---
ts: 2026-10-17T06:17:08.339Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
The non-header definitions already use the converted signature with void pointer and s32 parameters, so only the header bodies need updating since headers have conflicting declarations across the five including TUs. I should check how func_80149CB4 calls func_80157D20 in one of those includer binaries to confirm the actual calling convention.
