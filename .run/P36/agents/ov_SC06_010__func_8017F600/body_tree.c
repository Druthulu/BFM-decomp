void func_8017F600(s32 param_1) {

    extern s32 D_801151D4;

    u8 *s0 = (u8 *)param_1;
    u16 nv[4];
    s32 pad_[4];
    s32 g;
    s32 iv;
    s32 idx;
    s32 t1;
    s32 t2;
    s32 p;
    s32 q;
    u32 uVar1;

    g = D_801151D4;

    if (*(u16 *)s0 == 0) {
        return;
    }

    t1 = *(s16 *)(s0 + 6);
    t2 = *(s16 *)(s0 + 0xA);
    if (t1 * t1 + (t2 + 0x482) * (t2 + 0x482) > 0x1323F) {
        func_8012ADE4(param_1);
        *(s32 *)(s0 + 0x14) = 0;
    }

    idx = *(s32 *)(s0 + 0x1C) & 3;
    switch (idx) {
    case 0:
        iv = func_8012C588(0x281, (s32)s0);
        if (iv != 0) {
            *(s32 *)(iv + 0x1C) = 2;
            *(s16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
            *(s16 *)(iv + 0x16) = -((rand() & 0xF) + 0x10);
            *(s16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
        }
        break;
    case 1:
        break;
    case 2:
    case 3:
        iv = (s32)func_8012913C(0x23);
        if (iv != 0) {
            *(s16 *)(iv + 0x6) = *(u16 *)(s0 + 0x6) + (rand() & 0x3F) - 0x20;
            *(s16 *)(iv + 0xA) = *(u16 *)(s0 + 0xA) + (rand() & 0x3F) - 0x30;
            {
                s32 r = rand();
                s32 t = *(u16 *)(s0 + 0xE);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(s16 *)(iv + 0xE) = t + (r & 0x3F) - 0x20;
            }
            *(s16 *)(iv + 0x34) = (rand() & 0x17FF) + 0x800;
            nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(iv + 0x6);
            nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(iv + 0xA);
            nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(iv + 0xE);
            VectorNormalSS(nv, nv);
            *(s16 *)(iv + 0x6) = *(u16 *)(iv + 0x6) + ((s16)nv[0] >> 6);
            *(s16 *)(iv + 0xA) = *(u16 *)(iv + 0xA) + ((s16)nv[1] >> 6);
            *(s16 *)(iv + 0xE) = *(u16 *)(iv + 0xE) + ((s16)nv[2] >> 6);
        }
        break;
    }

    if (*(u16 *)s0 != 0) {
        p = *(s32 *)(s0 + 0xCC);
        *(u16 *)(p + 0x8) = *(u16 *)(s0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(s0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(s0 + 0xE);
        *(u16 *)(p + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10);
        *(u16 *)(p + 0x12) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + *(u16 *)(s0 + 0xFC);
        *(u16 *)(p + 0x14) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14);
        q = *(s32 *)(s0 + 0x20);
        if (*(s32 *)(q + 4) < 0) {
            register u32 val __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
            val = *(u32 *)(p + 4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus7)
            uVar1 = *(u32 *)(p + 4) & 0x7FFFFFFF;
        }
        *(u32 *)(p + 4) = uVar1;

        p = *(s32 *)(s0 + 0xD0);
        *(u16 *)(p + 0x8) = *(u16 *)(s0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(s0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(s0 + 0xE);
        *(u16 *)(p + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10);
        *(u16 *)(p + 0x12) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + *(u16 *)(s0 + 0xFE);
        *(u16 *)(p + 0x14) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14);
        q = *(s32 *)(s0 + 0x20);
        if (*(s32 *)(q + 4) < 0) {
            register u32 val __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
            val = *(u32 *)(p + 4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus7)
            uVar1 = *(u32 *)(p + 4) & 0x7FFFFFFF;
        }
        *(u32 *)(p + 4) = uVar1;
    }
}
