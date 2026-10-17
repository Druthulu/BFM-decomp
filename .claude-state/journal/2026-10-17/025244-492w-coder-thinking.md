---
ts: 2026-10-17T08:52:44.397Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I'm trying to verify the claim that the original splat assembly marks this as a handwritten function, looking at the GTE opcodes involved—RTPT, gte_stflg, and NCLIP—to see if they match known patterns.

The remaining calls like stsxy3, avsz3, stotz, and nccs line up closely with PsyQ's inline GTE macros, especially the cfc2/nop/sw pattern used in gte_stflg. The stack layout, hoisted constants, and loop-invariant address computation all suggest compiler-generated code rather than hand-written assembly, though the register allocation order (t6, t7, t3, t2, t1...) still needs more thought to confirm it matches gcc's typical allocation priorities.

Mapping this into C terms, I'm reconstructing a per-face loop over a face structure: pulling vertex indices from offsets within the face data, computing vertex pointers into the verts array, then calling gte_ldv3, gte_rtpt, and gte_stflg to transform and project the triangle, followed by a flag check that likely gates whether the clipping/normal code path continues.

I notice t1 is actually a strength-reduced induction variable separate from a3, initialized to a3+4 and incremented by 20 each iteration, so the offset arithmetic on it (like -17(t1) or -1(t1)) maps back to specific byte fields in the original prim struct, such as the rgb code byte or tag byte after the pointer advances.

Then I'm looking at the OT (ordering table) insertion logic: it computes the OT entry for the current prim using otz shifted and scaled, then performs the classic linked-list style primitive insertion — splicing the new prim into the OT bucket by rewriting the tag field with the old head pointer and updating the OT head to point to the new prim, before advancing prim by 5 words.

There's also a secondary condition checking a shadow/dither flag that, if set, inserts an extra sprite primitive into a separate OT bucket (tag 0x01000000) and advances prim by 2 more words. The outer loop decrements count and advances both pointers by 16 bytes each iteration, structured as a do-while from GCC's typical loop rotation around the initial skip-if-zero check.

Other macros to check include gte_ldrgb, gte_ldv0, gte_nccs, and gte_strgb — I want to verify their exact register loading patterns against ldv3 and stflg.
