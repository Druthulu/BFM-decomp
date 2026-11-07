---
ts: 2026-11-06T05:12:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_O87Wg7vmdVHLsU0Z1NaP
---
Wait, CAST_SIGN(T,p,k) = (*(T *)((p) + (k))). So `CAST_SIGN(void *, (u8 *)p, 0x20)` = `(*(void **)((u8*)p + 0x20))`. Then `*(s16 *)(that + 0x12)`. In orig: `*(s16 *)(CAST_SIGN(void *, (u8 *)p, 0x20) + 0x12)`. That's `*(s16 *)((void*)+0x12)` — pointer arithmetic on void* is a GCC extension (byte offset). Fine.

I changed it to `*(s16 *)((u8 *)CAST_SIGN(...) + 0x12)` which is equivalent but different spelling. Better keep original spelling to avoid perturbing. Let me revert to the orig spelling.
