---
ts: 2026-10-17T11:49:34.733Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm recalling how struct-return functions handle the copy to v0 in the epilogue, trying to figure out whether that copy happens at a different point than a normal return value, similar to the comment's description.

For testing, I want to pick a struct layout that forces BLKmode under strict alignment rules—something like two 32-bit fields that would get DImode but falls back to BLKmode since the struct's alignment is lower than the mode's required alignment, which should trigger a memory-to-memory word copy rather than a register move.

I'm ruling out soft-float SFmode returns in v0 and considering whether a struct containing a single-element array would still get classified as BLKmode under the 2.7.2 stor-layout rules, since array type mode assignment depends on whether the size is known at that point.

I'm checking whether bitfields that don't cross a word boundary still let the record collapse to a scalar mode like SImode, and considering what happens for union types where the mode logic differs for qualified unions.

Testing a concrete case: a union containing an s32 and an s16 array ends up BLKmode because the array's alignment is weaker than SImode's, forcing the whole union to size 4, align 4, and BLKmode -- meaning it's returned via memory and copied with word-sized block moves. I'm trying to construct a minimal struct that similarly forces align-4 BLKmode without a plain SImode field.

I'm also considering how the unaligned case behaves differently -- align-2 struct copies wouldn't use lw directly but lwl/lwr or halfword loads, which doesn't match. And I need to check how the caller side handles a BLKmode return value, since gcc's expand_call may pass the destination address directly rather than copying afterward, which affects whether caller code matches regardless of this struct shape question.
