---
ts: 2026-10-17T08:47:50.102Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
Plan: for each of the 13 targets, read its splat asm and sort it as compiler-shaped or hand-written by looking at the prologue, register order, delay slots and any $at/$k use. Compiler-shaped ones get a scratch C draft under .run/P40/T8/asmbody/, and I iterate match_one until it matches. Hand-written ones just get the evidence recorded. I only write scratch files because src/ is being edited concurrently.
