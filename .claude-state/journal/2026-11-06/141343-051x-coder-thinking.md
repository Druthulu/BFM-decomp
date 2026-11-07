---
ts: 2026-11-06T21:13:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Mo8H7rVbELDlUZeHWDdm
---
All 30 variants score ≥1; none reach 0. This confirms the wall. Best lever-free = 1 (w2). Tries: w1,w2,w3,w4 + t01..t30 = 34 scored tries. Wall tag: expand-void-return (or flow-unused-result). The mechanism: `rv = (s32)a0` is dead in a void function; expand/flow delete it; keeping it needs the $2 pin (row kind) + asm (row kind). Tag `expand-void-return` fits best (the target's exit value is a return value the void expansion drops). Alternatively `flow-unused-result`. The walls.txt has both. The src comment says flow deletes it; expand drops void return. The target's move is the dead set. Let me pick `flow-unused-result` — "flow deletes results the target computes but never uses". Actually the move is deleted by flow. But the deeper reason is the void return. Hmm. The wall tag should describe the mechanism. The evidence: "lever-free body emits 42/43 ins; only the dead move v0,s0 missing; flow deletes the dead set in a void fn; pin+asm (row kinds) are the only way to keep it." Tag: flow-unused-result. But `expand-void-return` is also apt. moves.md uses both. Let me use `flow-unused-result` since flow is the pass that deletes it (verified: w2 = 42 ins, the move gone).

Wait, but is it flow or expand? Let me verify with a dump: does the RTL before flow contain the move, and after flow it's gone? I could dump w2. But the src comment says "DELETED by flow". And the wall defs: "flow-unused-result | flow | flow deletes results the target computes but never uses". That matches exactly. Use it.

Actually, let me double check by dumping w2 and checking the .flow dump. Quick. But I've already got strong evidence (the src comment + score). Let me do a quick dump to be rigorous — it's cheap and the brief says "read dumps when unsure".

Let me dump w2 and check whether the move exists pre-flow and is gone post-flow.

Actually, time budget. I've spent maybe 12 min on item 2. Let me do the dump quickly.

For item 2, the TU is src/ov_SC05_002/ov_SC05_002_jr_8017BEBC.c (also large). I need a minimal TU with the struct Unkstruct_80126B58 and CAST_WIDTH. Let me check what's needed: `CAST_WIDTH(s32, a1, 0xE0)`, `Unkstruct_80126B58`, `func_8012B77C`. These are in engine headers. A minimal TU with common.h + engine_prelude.h might define them. Let me try.

Let me build min_w2.c for item 2.
