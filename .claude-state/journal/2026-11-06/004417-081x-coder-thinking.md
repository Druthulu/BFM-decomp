---
ts: 2026-11-06T07:44:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hvCUhQ2beTZj11U5WUgc
---
Row 0 is the root (depth None). Rows with parent=6 — 6 is probably the root's id. So all depth-1 moves are applied to the root (the lever-free body). Row 4: "R8 temp tmp0 @441" score 6. Row 5: "R7 block @441" score 6. Then depth-2 moves like "R12 width tmp0 u32->u16 @413" parent=5 → score 1.

So: apply R7 block @441, then R12 width tmp0 u32->u16 @413 → score 1. "tmp0" is a temp introduced by the block move? Hmm, "R7 block @441" wraps a statement in a block; "R12 width tmp0" changes a width of a temp named tmp0. The generator names generated temps tmp0.

The body line numbers: @441 etc. Our function body in the TU is around lines 370-440? Let me find func_800CB900's line range in src/md_MAIN_026. The body starts where? Let me grep.
