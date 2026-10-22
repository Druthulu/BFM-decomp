---
ts: 2026-10-21T23:57:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FeRsCclvDTsLYNkoLTRk
---
Not the right spot. I'm burning context. Let me stop the gcc source dive and make a decision.

DECISION for func_8018483C: I'll record a WALL. But before that, let me try the mode-changing copy idea quickly since it's cheap and I have a concrete hypothesis:

v12:
```
    u8 *pb = (u8 *)&D_800B99DC;
    p = (u16 *)pb;
```
Hmm, that's the same as before (pointer→pointer, no mode change).

Mode-changing: `s32 ib = (s32)pb;` — the address as an integer.

Let me test v12:
```
    s32 ib;
    u16 *pb = &D_800B99DC;
    ib = (s32)pb;
    p = (u16 *)ib;
```
If gcc folds (s32)pb to a constant, the reloc is lost and the diff will show it. Let me just test — the diff will tell me.

Hmm, but this adds a local (ib) which changes the allocation. Risky but let me try. Actually, let me try the SIMPLEST mode-changing copy that doesn't add a variable:

p = (u16 *)(s32)&D_800B99DC;   — hmm, the cast chain: &D_800B99DC → s32 → u16*. If gcc folds the whole thing to the address, nothing changes (score 5). If it doesn't fold, we get a mode-changing copy.

Let me test that (v12). It's 1 call. If it gives a different score, I'll see the mechanism.

Actually, hmm: (s32) of a pointer in gcc's front end: the C front end's convert.c would build a NOP_EXPR or a CONVERT_EXPR. Then fold-const's fold_convert would handle CONVERT_EXPR of an ADDR_EXPR. Let me just test.

Let me do it.
