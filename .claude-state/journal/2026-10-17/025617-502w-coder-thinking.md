---
ts: 2026-10-17T08:56:17.737Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
That duplicated load and the sra appearing on both branches look like classic gcc delay-slot filling from reorg — stealing instructions from jump targets to fill branch delay slots rather than anything hand-written. That pattern strongly points to compiler-generated code.

The near-match at 800249F0 confirms this is from the same gcc-generated family. Looking at the frame layout and field offsets, I can map out the structure: it's processing primitives into packets, and the offset pattern (prims+4→packets+12, prims+8→packets+20, prims+12→packets+28) tells me prims is a 24-byte struct with a tag, three UV coordinates, vertex count, and three vertex indices, while packets matches the 32-byte POLY_FT3 structure (tag, rgb, three xy/uv pairs). The loop logic itself handles flag checking, clipping, and z-sorting before continuing to the next primitive.

Now I'm tracing the depth calculation branch - after storing the screen coordinates with stsxy3, it checks a global flag to decide between two paths: either store individual z-values and take the max of three (shifted right by 2) for otz, or use the average-based avsz3/stotz approach instead.

I'm then following how it loads texture coordinates and colors for the packet, and finally computing the ordering table slot address by shifting otz by the OT shift amount and adding it to the base ot pointer, masking out the high byte when linking into the table.

Now I'm hunting for where gte_ldrgb is called before the depth check, and double-checking the gte_stsz3 macro signature against the output registers, plus confirming what that negative-offset static array lookup with the 0x8000 bitmask is actually testing.
