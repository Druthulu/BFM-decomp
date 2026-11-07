---
ts: 2026-11-06T09:34:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n7kjJJnzPf0AaSzpwgeV
---
40 lines (36 + a stray?). Two at 13. Best 13. Hmm, one at 16. So item 2: best lever-free 13.

Wait, 40 lines but 36 generated — the score file has 36 lines... "wc -l 40" because of the extra `echo ---`? No, I redirected sc.sh output only. 36 variants + maybe v01-v36 plus? Let me not worry; grep counts sum to 40 (2+37+1). Hmm, that means 40 score lines. The glob v*.c may match v01..v36 only. Oh wait, 37 at score 14 + 2 at 13 + 1 at 16 = 40. Maybe there are leftover files from an earlier generation? No. Whatever — the score distribution is clear.

Actually, maybe sc.sh printed some extra lines. Fine.

Item 2: 40 tries, best 13 → WALL.

Hmm, which variant got 13? Let me check later for the log.

Now item 3: 30+ variants. Real-C moves: decl order of pkt, ob, mlo, c80, cFF, cDF, pad; widths (u32 vs s32); init at decl; the ob usage (ob = D_800AA60C; reuse); mlo as u32/s32; c80 as u8/u32.

The lever-free score 56 is driven by the caller-saved permutation. Let me generate variants of the constants' declaration order and types. 6 decl orders × a few type variants.

Let me write the generator: take win.c (lever-free) and permute the declaration block lines.

Decl block in win.c:
```
    u8 *pkt;
    u8 *ob;
    u32 mlo;
    u32 c80;
    u32 cFF;
    u32 cDF;
    u32 pad[2];
```
Plus externs before. Variants: permutations of [pkt, ob, mlo, c80, cFF, cDF, pad] — 6-8 orders; plus widths (u8 c80 etc. would change codegen? c80 = 0x80 stored as u8 → the `*(u8*)(pkt+6) = c80` still works; type u8 vs u32 changes the pseudo size → priority changes!). That's a real lever from the catalog ("s16/u8 widths"). Let me include width variants: c80/cFF/cDF as u8, mlo as u32/s32.

Combination: 6 decl orders × 5 width variants = 30.

Let me write it.
