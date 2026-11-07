---
ts: 2026-11-06T11:46:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UkxWnzQtVNN5JMGX5W3K
---
All 30 — wait, these are all 119 ins and score 30, not 28. Why? Because I changed the source: in this template the tag2 load is placed BEFORE x += w_ ... same as before. Hmm, d000 scored 28 with 120 ins. The difference: d000's emit put `tag2 = 0xE1000200;` BEFORE the ot store. In gen3's BODY_HEAD, I have `tag2 = 0xE1000200;` before the ot store too. Let me check... yes:
```
    *(u32 *)p = (tag2 & mFF) | (...);
    tag2 = 0xE1000200;
    ((Unkstruct...)->unk3FFC = ... | pmask;
```
Same as d000 (const before). Hmm, but d000 had 120 ins vs these 119.

Difference: gen3's decl block has `s32 otp; u8 *p; register mFF; s32 vx, vy; u32 pmask; register tag2` — same as d000's HEAD? d000's HEAD from gen2:
```
    s32 otp;
    u8 *p;
    register u32 mFF ...
    s32 vx, vy;
    u32 pmask;
    register u32 tag2 ...
```
Same. Hmm, and the body identical? gen2's G2 has tag2 load first, then x += w_... yes.

Wait, e000 should equal d000. Unless gen3's BODY_HEAD differs subtly: I wrote `tag2 = *(u32 *)p;` after the vx/vy stores — yes. d000 also.

Hmm, but e000 has 119 ins vs d000 120. Odd. Let me diff e000 and d000.

Oh! I see: in gen3 BODY_HEAD I put `pmask = (u32)p & 0xFFFFFF;` then the tag store, then tag2 const, then ot store. Same.

Wait, maybe the difference is the extern decl comment or something. Let me diff.
