---
ts: 2026-10-17T09:54:44.737Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
effort: medium
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
Since common.h already has gte, I'll write a small Python script to replace a function in a file given its start and end lines with new text, editing from bottom to top of 800.c so line numbers stay valid. I'll craft the replacement text for each function manually, pulling signature and body from the draft.

For the externs, I need to deduplicate: D_8006388C and D_8006389C are referenced in two places with the same Tex_t type, so I should define that typedef once and reuse it rather than redeclaring separately. Header comment edits I'll handle separately with the Edit tool after the body swaps, and I'm naming replacements by their function's hex address, now working through func_8001E378 and func_800249F0's replacement regions.

For func_80025CBC and func_80026514, I'm introducing local typedefs for the texture, triangle, and face structures, naming them after each function's address, and reconciling existing externs like D_800AF630 and D_80063884 so the types stay consistent. I'm settling on a `u8 *` return type for func_80026514 since the real struct type isn't defined yet at the declaration point, which is fine since callers just cast the result anyway.

I decide to keep the K&R-empty parameter list on the extern declaration but change its return type to `u8 *`, which makes the caller's existing function-pointer cast a no-op while preserving the exact same bytes. For func_800268D0, I'm reusing the same texture entry typedef and D_8006388C extern, adding GT4 and Face4 typedefs, and confirming D_80063888 already exists as u32. Then for func_80027058 I'm checking whether binding two different C declarations to the same underlying asm symbol causes any conflict.

For func_80027200 I'm defining function-specific typedefs for the frame data, draw mode, and source structures, briefly weighing whether to share the draw-mode typedef across multiple functions but deciding to keep one per function for simplicity, even with the minor duplication—then moving on to actually writing the script.

I've confirmed no typedef collisions, but I'll still suffix each draft's scratch typedefs per-function since Src_t/DM_t differ across drafts sharing 800.c, and convert the two K&R-empty externs to `extern u8 *f();` since callers already cast calls the same way. Next I'll write the range-replace helper and replacement texts.
