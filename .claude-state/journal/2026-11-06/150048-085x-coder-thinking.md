---
ts: 2026-11-06T22:00:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jo7g5vhmJWwT4OgFzEJG
---
Confirmed: dst u8 → lbu (wrong). But the allocation (v1) matches! So the integer-width change fixes allocation but breaks the load width.

So if I use `u8 *dst` (pointer, SImode), the load stays `lw` and the type is a pointer. Let me test. The uses `dst + 6` on a u8* are byte offsets (same). `*(u16*)(*(s32*)(dst+0x20)+0x10)` — dst+0x20 byte offset (same). So all insns identical, but dst is a pointer pseudo (SImode) — the allocation might differ from the s32 integer case? Unlikely (both SImode), but pointer-ness affects `reg_preferred_class`? No. It affects alias analysis (mem flags) → scheduling → lives → allocation. Worth a try.

Let me generate p variants and score.
