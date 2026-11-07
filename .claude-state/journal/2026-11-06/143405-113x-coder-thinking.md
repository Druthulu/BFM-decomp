---
ts: 2026-11-06T21:34:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tl4npAMOka0Gmh7gdYU1
---
Hmm, w4 (both do-whiles) score 38 — worse than w3 (21). The do-while on the cast changed something badly. w5 (only div do-while) = 21 (same as w3). w6 (only cast do-while) = 38.

Wait, w5 = 21 same as w3, so the div do-while didn't change the allocation. And w6 = 38 (cast do-while alone) — worse.

Let me reconsider. The func_8012BB3C case was similar but not identical. Let me look at that function's source to see its structure and what exactly cracked it. It's in src/shared/ov/func_8012BB3C.h? Let me find it. moves.md line 316: `keepalive,pin | func_8012BB3C | WALL lreg-qty-priority — C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor; residual extendhisi2 temp $v1 vs in-place $s0 (G27x)`.

Let me read src/shared/ov/func_8012BB3C.h (or wherever). This will show the exact structure and the attempted win.c. Let me find it.
