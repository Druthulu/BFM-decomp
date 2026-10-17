---
ts: 2026-10-17T11:29:21.651Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I notice the target assigns x and y to separate registers, with y as a copy of x — x dies after the first case use and shares its register with the result, while y stays live through the other cases. My version instead collapsed them into a single pseudo, which is the key register-allocation difference I need to fix.

The question is why cse/copy-prop would merge x and y when y=x — cse canonicalizes to the oldest register and eliminates the copy entirely, so I need y to be something cse can't equate to x, like a parameter pseudo versus its copy, though that risks getting equated too unless cse's substitution rules don't apply there.

But cse operates on extended basic blocks, so if the y=x copy is in one block but its use is at a switch case label with multiple predecessors (fallthrough plus the jump), the equivalence is lost there and y stays live as its own register — that fits the free.c case where case 1-3 has multiple incoming edges. Still, that raises the question of why global allocation didn't just assign y and x different registers unless their live ranges overlap, which doesn't match what I'm seeing with one shared register.

I'm now wondering if local-alloc's optimize_reg_copy_1 is responsible — it replaces a copy's destination with the source when the source dies at that copy point, potentially applying even to global registers under -fexpensive-optimizations, which could explain the merge I'm seeing in the actual output.

Since x has a later use in case 0, that normally would block the copy from dying there, so I suspect the case-0 reference might have gotten rewritten too. I want to try several code variants: separate declarations for x and y, direct use of arg1 in case 0 with y only copied for cases 1-3, reordering the copy relative to state/flag computations, and declaring y as a 16-bit type instead.
