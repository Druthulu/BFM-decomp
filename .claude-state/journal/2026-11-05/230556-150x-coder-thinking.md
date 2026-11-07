---
ts: 2026-11-06T06:05:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wkOibposyYSjxbLEXN6R
---
Item 4 done (WALL, ~14 min wall clock — hmm, below 20 but 72 tries). Let me move on to item 5.

Item 5: func_8017EF9C in src/ov_SC03_013/ov_SC03_013_jr_8017C730.c:3690.

The def:
```c
void func_8017EF9C(void *a0) {
    s32 loc[5];
    register s32 s0 __asm__("$16");  // pin $16
    s0 = (s32)a0;
    ((Unkstruct_800B5CB8 *)s0)->unk20 = ((s32 (*)(void))func_8012C1B8)();
    if (((Unkstruct_800B5CB8 *)s0)->unk20 == 0) {
        func_8012CAE4((s32 *)s0);
        return;
    }
    func_8001C2C4(((Unkstruct_800B5CB8 *)s0)->unk20);
    {
        register s32 v1 __asm__("$3");  // pin $3
        s32 v0;
        v1 = D_80184CA8[((Unkstruct_800B5CB8 *)s0)->unk70];
        ((Unkstruct_800B5CB8 *)s0)->unkFE = (v1 & 0xF000) >> 12;
        ((Unkstruct_800B5CB8 *)s0)->unk100 = v1 & 0xF;
        v0 = ((Unkstruct_800B5CB8 *)s0)->unk20;
        ((Unkstruct_800B5CB8 *)v0)->unk12 = v1 & 0xFF0;
        v1 = ((Unkstruct_800B5CB8 *)s0)->unk100;
        if (v1 == 2) {
            ((Unkstruct_800B5CB8 *)*(s32 *)(s0 + 0x20))->unk10 = 0x400;
        }
    }
    func_8012B2CC(s0);
    loc[1] = 0;
    loc[0] = 0;
    loc[2] = D_80184D0C[((Unkstruct_800B5CB8 *)s0)->unk100];
    func_8012B14C(s0, (s32)&loc[0]);
    {
        s32 v0, v1;
        s32 pa0;
        __asm__("" : "=r"(pa0) : "0"(s0));  // launder
        v1 = (s32)&D_80184CCC[0];
        v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;
        v0 |= 0x40000000;
        *(s32 *)(pa0 + 0x58) = v0;
        *(s32 *)(pa0 + 0x1C) = *(s16 *)(pa0 + 0x70);
        func_8012AD50((void *)pa0);
    }
}
```

Two pins ($16 s0, $3 v1) and one launder (pa0).

Let me set up: copy orig, baseline, naive lever-free.

Note: the launder `pa0 = s0` is a plain copy — removing it makes pa0 = s0 (same variable). Then the code uses s0 directly. The launder probably prevents cse from merging pa0 with s0 (which would change the register allocation: s0 is $16 pinned, pa0 would be... hmm).

Let me test.
