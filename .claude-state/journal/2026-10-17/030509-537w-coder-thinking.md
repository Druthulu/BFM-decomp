---
ts: 2026-10-17T09:05:09.458Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
This looks like the same GT4 analog but with a 24-byte face struct and a shifted offset layout for the vertex/normal indices — essentially a variant where field positions differ by a few bytes due to an extra field, but the spill pattern for register pressure stays the same.

Stack frame is 64 bytes with locals for rgb, flag, otz, and a spill slot, plus incoming args for count, shift, OT, and index. It handles both flat and gradient RGB cases, runs the perspective transform for all four vertices, checks a flag for clipping behavior, stores screen coordinates and computes average Z for the fourth vertex, then does the nclip and Z-sign rejection checks before computing per-vertex colors via normal-based lighting and loading UV coordinates for the fourth vertex.

Working through the UV texture coordinate offsets and register assignments for all four vertices, then the storage of U/V, CLUT, and texture page values into the quad polygon structure for a POLY_GT4 primitive.
