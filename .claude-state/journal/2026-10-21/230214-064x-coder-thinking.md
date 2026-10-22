---
ts: 2026-10-22T05:02:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PRFrM4dMKsyYRd0t4Ucg
---
Good, the TU is ov_MAIN_012 again. Let me write a generic mkdump script under G08b that works for any item in the shard (using the item's tu/fn and the ov_MAIN_012 TU source).

The header file name: the item's `tu` is `src/shared/ov/func_801536DC.h` → the copied header goes to <work>/shared/ov/func_801536DC.h, and the TU source is ov_MAIN_012_jr_801458E0.c (which includes ../shared/ov/func_801536DC.h presumably).

Let me write the genericscript.
