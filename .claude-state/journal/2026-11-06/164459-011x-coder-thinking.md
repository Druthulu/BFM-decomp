---
ts: 2026-11-06T23:44:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SffVpO83JQB80YzLWNCl
---
Now let me build the lever-free versions. I'll write them as `win.c` per item.

Item 1 (func_800CFE60): remove pin `mode` and launder.

The pin: `register s32 mode __asm__("$19");` → `s32 mode;`
The launder: `__asm__("" : "=r"(q) : "0"(q));` → removed.

Note the launder is on q which is declared inside the if-block `s32 *q = &D_800C7C60;`. Removing launder leaves `s32 *q = &D_800C7C60; p = q; *p = val;`.

Let me create win.c for item 1.

Actually careful: the orig.c I copied starts at line 936 which is `s32 func_800CFE60(void) {`. Good, bare definition (the body file presumably just the function). Let me check how --body works: probably the file is the whole function def. Let me check delever_search.py briefly.
