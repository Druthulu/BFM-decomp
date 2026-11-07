---
ts: 2026-11-06T12:01:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g1t2KBBtqecJYrk04uXi
---
g_initdecl is missing the first 16-insn copy entirely — because with `Blk20 blk = D_800AE620;` at decl, gcc apparently kept blk in .bss/D_800AE620? No — it seems the first copy vanished (maybe gcc treated `blk` as a copy of the global and used... hmm). Whatever, it's not a valid path.

OK. Item 3: WALL, best lever-free 46? But that body is arguably semantically dubious (missing the first copy). Hmm, wait: it's still correct C — `Blk20 blk = D_800AE620;` is a valid initializer. gcc just optimized it differently. Score 46.

Hmm, but for the WALL "best = lowest score of a lever-free body" — 46 it is (v2=61).

Let me do 4 more quick tries to reach 30, then finalize. I'll use g_initdecl variants.

Actually, let me reconsider one more time whether a PARTIAL:launder (p2=8) could be pushed to 0 with the right real-C move. The residual was:
1. address materialization hoisted above the obj/ent loads (2 insns moved).
2. missing nop.

Both are scheduling artifacts of removing the barriers. Hmm.

What if we keep ONE barrier (partial = "barrier" kept)? PARTIAL:barrier would require removing only the launder — p1 = 69 (bad). No.

What if we keep the barriers but remove the launders via the struct-copy? p1 with struct copy = ? That's a new try: barriers kept + struct copy (launders gone). Let me test — maybe 0! The struct copy could replace the launder's effect (keeping the address in a register) AND the barriers stay. Let me build it: take orig.c and replace both Blk20 blocks with `blk = D_800AE620;` (keeping the barriers), and keep the q launder blocks? The launders on q also must go for a launder-free body; but if we keep barriers only (PARTIAL:barrier), we must remove ALL launders including the q ones.

Let me construct: orig.c with:
- both Blk20 blocks → `blk = D_800AE620;`
- the q launder blocks → plain `RotMatrixZ(ang, &blk);` etc.
- barriers kept.

Score it. If 0 → PARTIAL:barrier (kinds kept: barrier). That's plausible because the barriers keep the address from hoisting, and the struct copy keeps the register.

Let me do that now.
