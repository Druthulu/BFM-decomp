---
ts: 2026-10-17T18:47:45.564Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
The GTE macros use inline asm that's already classified as "other" asm, not row-kind related since kinds is pin-only, so register $11/t3 clobbering there doesn't matter for this check.
