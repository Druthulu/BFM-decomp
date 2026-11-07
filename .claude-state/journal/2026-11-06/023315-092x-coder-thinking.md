---
ts: 2026-11-06T09:33:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L720CqGwyg42eU8UKNZV
---
Item 1: 180 scored tries, best 19. WALL. Good, well over 30 tries.

Time check: item 1 started around 02:00? Let me record dates. I'll check date at item boundaries.

Now item 2: generate variants. Target ~14 lever-free. Let me build a generator with real-C moves: decl order, res/flg order, t2 widths, goto shapes, if shapes, && folds.

Item 2's body is bigger. Let me write a generator with:
- decl order variants (6)
- tail shapes (res=0 then if; flg then if/else; if/else; ternary) (5)
- t2 as u32/s32 (2)
- goto/if shapes (2)
That's 120.

Actually let me simplify: focus on the tail (res/flg) since that's the crux, plus decl order. 6 decl × 6 tails = 36.

Tails:
T1: res = 0; flg = D_801F84AC; if (flg != 0) res = &D;
T2: flg = D_801F84AC; res = 0; if (flg != 0) res = &D;
T3: flg = D_801F84AC; if (flg != 0) res = &D; else res = 0;
T4: if (D_801F84AC != 0) res = &D; else res = 0;
T5: res = 0; if (D_801F84AC != 0) res = &D;
T6: res = (s32*)&D; if (D_801F84AC == 0) res = 0;
T7: flg = D_801F84AC; res = flg ? (s32*)&D : 0;

Also the tail needs res live — without the keepalive it's dead. So all these will be ~14 (res dropped). Hmm, that means the tail doesn't matter; the score will be the same 14. Unless res is kept alive somehow.

So for item 2, the lever-free score is determined by "res dead" → 14. Variants of the tail won't change it. The decl order etc. might change 71 insns slightly.

Hmm, so 30 tries on item 2 will all be ~14. Fine — that's the wall evidence.

But wait: maybe I should double-check whether some real-C use of res can match. What if res is used as a *pointer* in a real statement that costs nothing? E.g., `*a0 = ...`? no a0.

OK. Let me generate 36 variants for item 2 and score.

Actually, since all lever-free variants are ~14, maybe I can save time: generate 36, score, record best. Let me do it.

Item 3: 30+ variants of the constants/decl order. The lever-free score 56; maybe some permutation gets closer. Worth trying because the constants' order might naturally match if we reorder declarations (global-alloc priority order depends on allocno order = pseudo number = decl order for exact ties). Actually priorities differ by refs, so decl order only breaks ties. Hmm. But the *allocno order* for equal priority is by regno (decl order). c80, cFF, cDF, mlo: refs c80=13, cFF=13, cDF=9?, mlo=5. Ties: c80 vs cFF (13 each) — tie broken by pseudo number (decl order). Target has c80=a3 (earlier reg) and cFF=t0. Mine has c80=a2, cFF=a3. So the tie-break/order matters! If I reorder the declarations (c80 after cFF), maybe cFF gets a2 and c80 a3... but target has c80 in a3, which is *after* a2. In mine c80 got a2 (the first). So in target c80 is NOT first — mlo (a2) is. So the tie-break between c80 and cFF: target c80=a3, cFF=t0 → c80 before cFF in reg order. Mine c80=a2, cFF=a3 → also c80 before cFF. The difference is just mlo jumping to the front in target (keepalive).

So without the keepalive, mlo can't get a2. Unless... we boost mlo's refs with real C: e.g. reuse mlo in the source as `& mlo` in 4 places (already) — what if we write the mask expression as `& (mlo & 0xFFFFFF)`? folds. Or use mlo for the c80 stores? No, c80 is 0x80.

What if we *lower* c80/cFF refs: c80 is stored 12 times (4 packets × 3). Could we write the stores as a loop? That changes structure.

OK item 3 wall.

Item 4: 30+ variants of loop shape/e pointer. Best 8.
Item 5: 30+ variants. Best 1.

Let me generate and score these efficiently. Total ~150 more compiles ≈ 2 min. Plus generation.

Let me write the item 2 generator.
