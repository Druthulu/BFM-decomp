---
ts: 2026-10-17T12:51:05.226Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
Looking at g2 line 76, the loop obscures the l variable but the field offsets expand as expected, folding the same way as t1's case—so only the constant-spelled f2 style actually matches. The target address at 5E94 lines up with &L[0].r, consistent with f2's approach where D_800A5E94 serves as the base register while the others get rebased, suggesting the original source held a pointer there.

I'm also considering whether f2's second base re-set could be meaningful rather than redundant, but I've already argued that's not possible, so I'll skip that variant. Instead I want to test f2 with the second re-set removed (n_sets reduced to 1) to isolate the scheduling contribution—quick to check via c17_f3.
