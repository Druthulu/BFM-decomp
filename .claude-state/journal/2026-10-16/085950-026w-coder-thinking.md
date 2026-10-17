---
ts: 2026-10-16T14:59:50.369Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: adedfdbb8f5ba3d6e
model: claude-opus-5-5[1m]
effort: medium
turnId: 98d47979-61fa-4c5e-b7c5-243938910128
---
For define rows, I need to check each target type's usage count fleet-wide — if a type is referenced in zero bodies outside its own header definition, I should strip its def from the header and mark the row as TYPE-NO-MEMBER. I also need to verify the check-structs dead-names count stays at zero after pruning, confirming nothing orphaned slips past the Dead-kept bullets.

I'm weighing how to count "used in bodies": a token grep across src and include excluding the self-definition block seems safest, since deleting a type still referenced by another header struct would break compilation. The plan is to iterate the prune to a fixed point, since removing one definition can eliminate references that make other candidates eligible too. Before coding this up, I want to look at an actual define target's definition in struct_types.h to confirm the format.
