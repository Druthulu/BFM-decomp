void func_8017FEA0(s32 s1)
{

    extern u8 D_8019AE80;
    extern u8 D_8019AEB4;
    extern s32 D_8019AEF4[];
    extern u8 D_801AAAE0;
    extern Blk4_80181EDC_8017FEA0 D_801AAAE4;
    extern Blk4_80181EDC_8017FEA0 D_801A94BC;
    extern Blk4_80181EDC_8017FEA0 D_801A94C0;
    s32 v1;
    s32 a1ptr;
    s32 s2;

    if (func_8012C354(s1, (s32)&D_8019AE80) != 0) {
        s32 t0;
        s32 t1;

        t0 = 1;
        *(u8 *)(s1 + 0xC0) = t0;
        t0 = (s32)&D_8019AEB4;
        *(s32 *)(s1 + 0xBC) = t0;
        t0 = *(s32 *)(s1 + 0xC4);
        t1 = 0x14;
        *(u8 *)(s1 + 0x75) = t1;
        v1 = *(s16 *)(s1 + 0x70);
        *(s32 *)(s1 + 0xB4) = 0;
        *(u8 *)(s1 + 0xC1) = 0;
        t0 = t0 | 2;
        *(s32 *)(s1 + 0xC4) = t0;
        t0 = *(u16 *)(s1 + 0x72);
        t0 = t0 | 0x1000;
        *(u16 *)(s1 + 0x72) = t0;

        if ((func_80029178(D_8019AEF4[v1]) & 0xFF) != 0) {
            a1ptr = *(s32 *)(s1 + 0x20);
            *(u32 *)(a1ptr + 4) |= 0x80000000;
            *(s16 *)(s1 + 0xAE) = -1;
            func_80180294((void *)s1);
            *(u16 *)(s1 + 0x34) += 1;
        } else {
            *(s16 *)(s1 + 0xAE) = -4;
            s2 = func_8012C194();
            *(s32 *)(s1 + 0xCC) = s2;
            if (s2 != 0) {
                s32 s0 = (s32)&D_801AAAE0;
                func_8001CD9C(s2, (void *)s0);
                func_800233CC((void *)s0, 0x80);
                *(Blk4_80181EDC_8017FEA0 *)s0 = *(Blk4_80181EDC_8017FEA0 *)&D_801A94BC;
                *(Blk4_80181EDC_8017FEA0 *)&D_801AAAE4 = *(Blk4_80181EDC_8017FEA0 *)&D_801A94C0;
                *(s16 *)(s2 + 0x18) = 0x800;
                *(s16 *)(s2 + 0x1A) = 0x800;
                *(u32 *)(s2 + 4) |= 0x50000000;
            }
            func_801818DC();
            func_8012AD50((void *)s1);
        }
    }
}
