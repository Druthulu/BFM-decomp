---
ts: 2026-10-17T12:34:43.099Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm checking whether mark_set_1 also triggers on CLOBBER, meaning a pseudo with both a clobber and a set would get n_sets=2 and become unknown to the scheduler, while CSE wouldn't be affected since it just folds the value after the clobber. Both the clobber-plus-set case and the subreg-set struct field case seem to need fixing.

Trying to trace how expand_assignment handles a struct field write into a register target — store_field calls store_bit_field, which for a full-width field just emits a plain move, so that path looks fine. Now I'm considering a union containing a pointer and a char array, wondering whether its layout picks SImode and whether that affects things.

I think the better test case is actually a local array of pointers rather than a struct — since arrays typically stay in memory, indexing into one and assigning should still go through a load/store rather than staying in a register, so I want to verify that behavior directly.

Let me just start experimenting with the DImode struct case first and see how the compiler lays it out.
