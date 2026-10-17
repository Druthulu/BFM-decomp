---
ts: 2026-10-17T13:46:05.621Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm puzzling over why s0 still holds a value across the call — maybe gcc's old MIPS codegen forces the symbol address into a pseudo register that then persists through CSE or loop hoisting, since the instruction ordering in dw0 differs with a scheduled store.

Could it be that the do-while(0) boundary gets collapsed by the constant-condition fold before CSE even runs, or that a dead label gets stripped by jump optimization, erasing what I thought was a basic-block boundary? I should check how s0 and s1 are actually used in the target's prologue and whether other callee-saved registers are available.
