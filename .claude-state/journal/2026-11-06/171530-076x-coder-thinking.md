---
ts: 2026-11-07T00:15:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lQkRROclAcuSF4XWyy7E
---
It's 17:15. Item 3 took only 5 minutes (17:10-17:15). 

Now item 4: func_80188790 header, 34 includers. Levers: pin tp $19 (s3) + launder on tp.

The function:
```c
void func_80188790(s32 a0) {
    s32 kind;
    register u16 *tp __asm__("$19");  // pin
    s32 s4;
    u8 *v1;
    s32 r0;
    s32 r2;
    s32 r3;
    s32 s1;
    s32 fE;
    r0 = rand();
    tp = (u16 *)&D_80126B58;
    __asm__ __volatile__("" : "=r"(tp) : "0"(tp));  // launder
    s4 = *(s32 *)(a0 + 0x1C);
    kind = (r0 & 1) ? 0xF : 0xE;
    v1 = func_8012913C(kind);
    if (v1 != 0) {
        r2 = rand();
        s1 = r2 - (r2 / 256) * 256;
        r3 = rand();
        fE = tp[7] + (r3 % 640) - 0x290;
        *(u16 *)(v1 + 0xE) = fE;
        if (s4 & 1) {
            *(u16 *)(v1 + 0x6) = s1 + 0x7A;
            *(u16 *)(v1 + 0xA) = tp[5] - 0xE0;
        } else {
            *(u16 *)(v1 + 0x6) = s1 - 0xF8;
            *(u16 *)(v1 + 0xA) = tp[5] - 0xC0;
        }
        *(u16 *)(v1 + 0x36) = tp[5] - 0x50;
    }
    if (func_8012BEE8(a0) == 1) {
        func_8012C218((void *)a0);
    }
}
```

Let me set up and get the baseline.
