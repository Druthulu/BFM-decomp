---
ts: 2026-10-22T00:21:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fc9f39fX1B99UOCCkZy3
---
Same pattern. The fix: replace the store's mask with `pv &= 0xFF000000;` before the store, and remove the launder.

Note the second store here uses a struct field: `((Unkstruct_80181CF4_2 *)ot)->unk40 = (...).unk40 & 0xFF000000) | ((u32)p & 0xFFFFFF);` (slightly different from item 5's pointer form).

Let me do the same: orig.c = lines 5249-5340; then cand: split the first store's mask with `&=`.

Let me create the files.
