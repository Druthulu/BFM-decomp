---
ts: 2026-11-06T11:39:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8ADx3hhvwE6Je0LrzRb7
---
Let me write v2: v0 with the middle group wrapped in do-while.

The middle group in v0:
```
    tag2 = *(u32 *)p;
    x += w_;
    ...
    *(u32 *)p = (tag2 & mFF) | (...);
```
Wrap that in do{}while(0).

v3: wrap only
```
    tag2 = 0xE1000200;
    ((Unkstruct_80015B6C *)otp)->unk3FFC = ... | pmask;
```

Let me write both files. Actually to save time, maybe use a single file with all variants? No, dt.sh takes one body.

Write v2.
