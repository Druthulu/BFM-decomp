---
ts: 2026-11-07T00:36:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XENJi0gyfEPyN2rjCIOF
---
WOW: w29 and w31 score 0 (OTHER = MATCH, byte-identical)!

w29:
```
    s32 *cam;
    ...
    cam = D_80126B78;
    CAST_WIDTH(u16, obj, 0x14) = CAST_WIDTH(u16, obj, 0x14) + (a0->unk2A - *(u16 *)((u8 *)cam + 0x12));
    cam = 0;
    a0->unk2A = *(u16 *)((u8 *)D_80126B78 + 0x12);
```

So the dead reset `cam = 0;` (C0414!) broke cse: the second set of cam kills the equivalence, so the second use re-loads D_80126B78 from the symbol. And the dead set is deleted by flow before sched1 → zero footprint. Exactly the C0414 move.

w31 is the same with `cam = (s32 *)obj;` (also a 2nd set).

Score 0 = MATCH. But wait — the kinds for this item = "barrier". I must ensure win.c has no barrier (no asm) — correct, w29 has no asm. 

But hold on: is `cam = 0;` a "launder"? The constraint says identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack. This isn't identity — it's a dead reset, a 2nd set, catalog C0414. Fine.

Also, does w29 keep the pins? There were none.

Now: MATCH means win.c scores 0 AND the row kinds are gone. Let me write win.c = w29 and verify with dt.sh. Then append the results row and moves line.

But careful: is score 0 on the TU's whole object? dt.sh compares the function only; the MATCH definition in the brief: "win.c scores 0" (score 0 = MATCH; compares with the function in build/). The bank judges the whole object, but the coder's job is the score-0 body. The brief says MATCH = win.c scores 0. Good.

However, I should double check that the dead reset is real and not removed in a way that changes... it scores 0, byte-identical. 

Now let me record: item 1 result MATCH, best 0, tries = count. Let me count tries: w1, w2, w3 (2 scores: w3 twice? I scored w3 twice — the same body; count distinct tries). Let me count distinct candidate bodies scored on this item: w1, w2, w3, then w10..w36 = 27 + 3 = 30. Plus orig.c baseline (not a try). So 30 tries. Good — and it's a MATCH anyway, no wall needed.

Time: started 17:24, now ~18:02 → 38 min. Over budget, but the item is cracked. Let me move fast.

Steps:
1. Write win.c = w29 content.
2. Score win.c (verify 0).
3. Append results row.
4. Append moves.md line.
5. notes.md.
6. Next item.

Let me copy w29 to win.c via cp (a command, fine). Then score.
