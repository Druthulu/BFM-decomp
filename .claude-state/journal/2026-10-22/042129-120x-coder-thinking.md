---
ts: 2026-10-22T10:21:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zwxNxIpVfvNnOnTnZRLm
---
v1 = launder removed (pins kept). v2 = x/y initialized at declaration.

Let me build the batch from v1.c.

Anchors in v1.c:
```
    s32 x;
    s32 y;
    register s32 z asm("a0");
...
    p = D_80192D28;
    s1 = 0;
    x = -0x680;
    y = -0xE80;
    z = -0x350;
    D_80192CF0 = 0x68;
```
Let me writethe variants.
