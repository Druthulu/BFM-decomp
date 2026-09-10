void func_8018431C(void *a0)
{
    extern s32 D_8019CAF4[];
    extern u8 D_8019CAE4[];
    extern u8 D_8019CA7C[];
    extern u8 D_8019CA7E[];
    extern u8 D_801C00F0[];

    s32 s2;
    s32 s1;
    u16 v0;
    s16 v1;
    s16 s0raw;

    s2 = (s32)a0;
    s1 = func_8012C194();
    if (s1 == 0) {
        func_8012CAE4((void *)s2);
        return;
    }

    v0 = *(u16 *)(s2 + 0x72);
    *(s32 *)(s2 + 0x20) = s1;
    v0 |= 0x1000;
    *(u16 *)(s2 + 0x72) = v0;
    v1 = *(s16 *)(s2 + 0x70);
    s0raw = v1;

    if ((v1 & 0x8000) != 0) {
        s32 idx;
        u8 *p;
        u16 b;

        idx = s0raw & 1;
        p = D_8019CAE4 + idx * 8;
        func_8001CB6C((u8 *)s1, D_8019CAF4[idx], *(s16 *)(p + 0), *(s16 *)(p + 2));
        b = *(u16 *)(p + 4);
        *(u16 *)(s1 + 0x10) = 0x400;
        *(u16 *)(s1 + 0x1A) = 0x2000;
        *(u16 *)(s1 + 0x18) = 0x2000;
        *(u8 *)(s1 + 0x27) = b;
    } else {
        register u8 *dptr __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)

        func_8001CF00(s1);
        dptr = D_801C00F0;
        *(u16 *)(s1 + 0x28) = 0x300;
        *(u16 *)(s1 + 0x2A) = 0x110;
        *(u8 *)(s1 + 0x27) = 0x78;
        *(u32 *)(s1 + 0x20) = (s32)dptr;
        *(u16 *)(s1 + 0x10) = 0x400;
        *(u16 *)(s1 + 0x1A) = 0x800;
        *(u16 *)(s1 + 0x18) = 0x800;

        if ((*(u16 *)(s2 + 0x70) & 3) == 0) {
            func_800233CC(dptr, 0x80);
        }

        {
            u16 flags = *(u16 *)(s2 + 0x70);
            if ((flags & 1) != 0) {
                *(u16 *)(D_8019CA7C + (flags & 3) * 12) = 0x10;
                *(u16 *)(s1 + 0x14) = 0x400;
                goto shared_tail;
            }
            *(u16 *)(D_8019CA7C + (flags & 3) * 12) = 0x20;
        }

        *(u32 *)(s1 + 4) |= 0x40000000;

        if ((*(u16 *)(s2 + 0x70) & 0x4000) != 0) {
            func_8002D4C8(0x701, 0);
        }
        if ((*(u16 *)(s2 + 0x70) & 0x2000) != 0) {
            s32 ret = func_800291B4(*(s16 *)(s2 + 0xFC));
            if ((ret & 0xFF) == 0) {
                *(u16 *)(s2 + 0x70) |= 0x4000;
            } else {
                *(u16 *)(s2 + 0x70) &= 0xDFFF;
            }
        }
        func_8012C658(0x1E1, (s16)(*(u16 *)(s2 + 0x70) | 1), s2);

    shared_tail:
        *(u16 *)(D_8019CA7E + ((*(u16 *)(s2 + 0x70)) & 3) * 12) = 0x20;
        if ((*(u16 *)(s2 + 0x70) & 0x4000) != 0) {
            *(u16 *)(s1 + 0x1A) = 0;
            *(u16 *)(s1 + 0x18) = 0;
        }
    }

    func_8012AD50((void *)s2);
}
