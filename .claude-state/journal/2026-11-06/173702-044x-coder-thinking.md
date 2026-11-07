---
ts: 2026-11-07T00:37:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bRRJ2FcazH1ekkcbTMBE
---
Item 2: kinds barrier,pin. Two levers: `register s32 val __asm__("$2")` (pin) and `__asm__ __volatile__("")` (barrier).

The body:
```
u16 sp10[3];
sp10[0..2] = ...;
func_8013B598(0, sp10);
switch (D_801B7A84) {
case 0:
    s32 *p;
    register s32 val __asm__("$2");
    func_8013C0F8((s32)&D_801A64C8);
    p = &D_801B7930;
    func_8017F53C((s32)p);
    val = D_801B7A84;
    __asm__ __volatile__("");
    D_801B7948 = 0;
    D_801B794C = 0;
    D_801B7950 = 0;
    *p = 0;
    D_801B7988 = 1;
    D_801B7A84 = val + 1;
    break;
...
```

Prior: sched1-birth-boost best 2, 13 tries + 1440 permutations.

Let me set up: extract orig.c, score baseline, then remove the levers and see the score.

Start time: 17:36.

Let me extract lines 7442-7477.
