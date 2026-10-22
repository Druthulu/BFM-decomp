---
ts: 2026-10-21T23:34:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Cf2QqMm4wwyZqKk90LOI
---
Now let me look at each remaining item's source file. All are `launder` kind.

Items:
2. func_80180D54__ov_SC01_080_jr_8017AE2C — src/ov_SC01_080/ov_SC01_080_jr_8017AE2C.c, func_80180D54, launder, 66 lines
3. func_801815D4__ov_SC01_080_jr_8017AE2C — same file, func_801815D4, launder, 40
4. func_8018483C__ov_SC02_000_jr_8018173C — src/ov_SC02_000/..., func_8018483C, launder, 77
5. func_8017DA30__ov_SC02_004_jr_8017AE2C — src/ov_SC02_004/..., func_8017DA30, launder, 34
6. func_80184828__ov_SC02_005_jr_80181D30 — src/ov_SC02_005/..., func_80184828, launder, 61
7. func_8017D81C__ov_SC02_021_jr_8017C294 — src/ov_SC02_021/..., func_8017D81C, launder, 72

Let me look at the source functions. First, find the function in the source file.

Let me set up a helper to view. Let me start with item 2: func_80180D54 in src/ov_SC01_080/ov_SC01_080_jr_8017AE2C.c.

Also I need to understand the kinds: the "launder" kind refers to `__asm__ __volatile__("" : "=r"(x) : "0"(x))` launders. Let me check the "kinds" file per item dir to see.

Let me look at all source files.
