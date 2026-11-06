---
ts: 2026-10-22T21:41:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mLCcmIeXSncPpLQ1Cqz4
---
Item 3: func_8017F7CC (ov_SC02_005, 25 lines) — barrier at entry: `__asm__ __volatile__("" ::: "memory");`.

Body:
```
void func_8017F7CC(s32 param_1)
{
    extern M8_SC02_005_8017F7CC D_801E2DD8;
    ...
    S16_SC02_005_8017F7CC loc;
    s32 iVar2;

    __asm__ __volatile__("" ::: "memory");
    *(s16 *)&loc.a.raw[0] = 0;
    *(s16 *)&loc.a.raw[2] = -0x40;
    *(M8_SC02_005_8017F7CC *)&loc.b.raw[0] = D_801E2DD8;
    iVar2 = ((Unkstruct_8017F7CC *)param_1)->unk204 - 1;
    ...
```

Let me extract and score lever-free.
