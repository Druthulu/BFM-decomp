---
ts: 2026-11-06T16:48:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RMQBarm2ZKd52T4WBWN8
---
Mine saves 9 regs (s0-s7 + ra), frame 136. Target saves 8 (s0-s6 + ra), frame 128.

Mine: m = *(a0+0x20)+0x34 in s0 ($16) and it's live across the two gte calls → s0 used for m. In target, m is in v0 (not callee-saved!) — target's prologue computes m in v0 and calls gte_SetRotMatrix/TransMatrix with it; since m dies before the next call? m is used in two consecutive calls; target keeps it in v0? Look at target: `lw v0,32(a0); addiu v0,v0,52; lw t4,0(v0)...` — that's gte_SetRotMatrix inlined? Actually gte_SetRotMatrix is a macro/inline in the target. Hmm, the target's first 20 instructions load the matrix and ctc2 — so gte_SetRotMatrix is inlined (it's a PSX SDK inline function). In mine, it's a `jal gte_SetRotMatrix` call! Different!

Wait, the source has `gte_SetRotMatrix(m); gte_SetTransMatrix(m);` — these are functions in the TU? In the target they're inlined (the body is the lw/ctc2 sequence). In my compile (no_fp), they're calls (`jal gte_SetRotMatrix`). That's a huge difference — but wait, my dump uses the whole TU with the same source... The target build also compiles the same TU. Why would mine call and the target inline?

OH. Because gte_SetRotMatrix in the target is a *macro* defined in a header that's included... but the .i I generated should be identical to the build's cpp output. Unless the build's cpp has different -D flags (e.g., -DGT... ) or the header's inline depends on __OPTIMIZE__?

Hold on: the target object's function starts with the inline gte sequence. My nopin.c compile via delever_search (the real recipe) scored 52 with 267 ins vs 265 — only 2 ins difference, and the diff didn't show a `jal gte_SetRotMatrix`. So the real scorer's compile DOES inline gte_SetRotMatrix. My d.sh dump shows calls — so my .i differs from the build's!

Ah, I see: my cpp used `-Isrc/shared -Isrc` extra includes; maybe the real build's include path finds a different `gte_*` header? Or my .i has different content because the TU includes "../shared/..." etc. Hmm.

Wait, more likely: the function is `func_8017E5D0(void *a0)` defined in the TU, and gte_SetRotMatrix is declared in the TU as a function... but the target inlines it. Let me grep the source for gte_SetRotMatrix.
