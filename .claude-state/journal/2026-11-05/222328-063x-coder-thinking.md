---
ts: 2026-11-06T05:23:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sosCLb7ngongB0TgVPwy
---
Wait, I made an error in the body: I dropped the `s32 acc`/`t` lines from the block. Let me fix gen3 to include them exactly. Let me rewrite the block:

```
    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x18) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x20) - t) >> 2);
    }
```
I wrote only the last line inside the block, plus a bogus `s32 acc = ...` after? Let me just rewrite the file properly.
