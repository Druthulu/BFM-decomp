s32 func_80185578(s32 arg0, s32 arg1) {
    extern u8 D_801BD0C4[];
    extern s32 D_801BD2FC[];
    extern u8 D_800D3918[];
    extern void func_80187414(s32 a0, void *a1, void *a2, s32 a3);
    extern void func_801873B0(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern void func_8001C924(s32 a0, void *a1);
    u8 buf[8];
    s16 y = arg1;
    s32 res;
    s16 state;
    s32 flags;

    state = *(u16 *)(arg0 + 0x70) & 0xF;
    flags = *(u32 *)(arg0 + 0xE0);
    if (flags & 4) {
        return 0;
    }
    switch (state) {
    case 0:
        if (flags & 1) {
            func_80187414(arg0, D_801BD0C4, buf, 0xC);
            res = ((s32 (*)(s32, void *, s32, s32, s32, s32))func_801873B0)(arg0, buf, 0x27F, (s16)arg1, 0, 0);
            *(s32 *)(arg0 + 0xD0) = res;
            *(u32 *)(arg0 + 0xE0) &= ~1;
            if (res != 0) {
                *(u16 *)(arg0 + 0xEE) = *(u16 *)(res + 0x36);
            }
        }
        /* fallthrough */
    case 1:
    case 2:
    case 3:
        func_80187414(arg0, D_800D3918, buf, 0xB);
        res = ((s32 (*)(s32, void *, s32, s32, s32, s32))func_801873B0)(arg0, buf, 0x27F, (s16)(y | (state + 1)), 0, 0);
        *(s32 *)(arg0 + 0xCC) = res;
        *(u32 *)(arg0 + 0xE0) |= 4;
        func_8001C924(*(s32 *)(arg0 + 0x20), (void *)D_801BD2FC[state]);
        if (res != 0) {
            *(u16 *)(arg0 + 0xEC) = *(u16 *)(res + 0x36);
        }
        break;
    default:
        return 1;
    }
    return 1;
}
