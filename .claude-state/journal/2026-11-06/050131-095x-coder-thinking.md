---
ts: 2026-11-06T12:01:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NQcFyaxzABzVP8efmmjA
---
Best lever-free = 46 (g_initdecl: `Blk20 blk = D_800AE620;` at decl, 78 insns — but that's 78 vs 94, way fewer, probably because the second copy also... no, g removed only the first copy and init at decl; 78 insns means something got optimized).

Hmm, 78 insns vs 94: the init-at-decl version has 16 fewer insns — suspicious. Maybe the compiler copied the struct differently (e.g. memcpy call?) or the second copy got merged... Whatever, score 46.

So lever-free best = 46. Hmm, but v2 = 61, g = 46.

Tries item 3: v0,v1 (2), p1,p2 (2), p2a-d (4), gen6 (9), v2 (1), gen7 (10) = 28. Need 2+ more. Let me run 4 more lever-free variants to cross 30: e.g. g_initdecl + copy_top, g + vec s16, g + ang first, and a "blk = D_800AE620" with the second copy replaced by reusing the first (i.e., remove the second copy entirely — that's a semantic change? No: the second copy re-reads D_800AE620 which may have changed? No calls between that write to D_800AE620? There are calls (RotMatrixZ etc.) which could modify D_800AE620. So the second copy is needed semantically. But the target does re-read. Removing it would be a semantic change — not allowed.

Let me do 4 more: g_initdecl variants (vec s16, ang first, copy second top, blk decl order).

Then record WALL with best 46, tag: hmm. What's the wall tag for item 3? The mechanism: without the launder, cse/regalloc folds the constant struct address into each load (8×lui+addiu) — 16 extra insns. That's a new tag: `cse-const-addr` exists (cse folds or substitutes a constant/absolute address the target keeps base-relative). Yes! `cse-const-addr` fits perfectly.

Wait, but for the lever-free body the score is 46 (not just the 16 insns). The dominant mechanism is cse substituting the constant address. Tag: cse-const-addr.

But hmm — for the PARTIAL option (barriers gone, launders kept = 8), the remaining issue is the address hoist (sched1-birth-order). Not 0.

Let me do the last 4 tries and finalize.

Actually, wait. Let me reconsider g_initdecl (46, 78 insns). 78 insns is 16 fewer than target — the struct copy at declaration might have been optimized into something else (maybe gcc reused the stack layout and avoided the copy?). Since the score is 46, it's not a match.

Hmm, one more idea for the lever-free MATCH: use the struct copy + a real second read. Since the target's copy is 8 lw + 8 sw, `blk = D_800AE620;` should produce it. v2 got 97 insns (3 more than target). g got 78 (16 fewer) — inconsistent. Let me check g's diff quickly? It might be that with init-at-decl, gcc copied via a different path (e.g. the struct is in .bss and blk is on the stack, maybe it used lwl/lwr?). 78 = 94-16: exactly the 16 address-materialization insns missing... no wait, fewer insns = better.

Hmm, 78 insns means the function got smaller than the target. If the struct copy was optimized to fewer insns (e.g., 8 lw + 8 sw = 16 insns; can't be fewer unless it used... hmm).

Let me not chase it. Let me finalize item 3 as WALL best 46.

Actually, hold on. Let me quickly check the g_initdecl diff to make sure it's not something bogus (like the function returning early). Score 46 COUNT means same-ish structure. 78 vs 94 insns — 16 fewer. Suspicious: maybe with init-at-decl, the compiler placed `blk` in .bss? No, it's a local.

Could the second `blk = D_800AE620;` have been removed by the compiler? No, there are calls between.

Let me look at the diff head.
