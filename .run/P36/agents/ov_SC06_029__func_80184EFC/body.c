void func_80184EFC(s32 a0) {
    extern s32 D_80190A08;
    extern u16 D_80190810[];
    s32 ret;
    s32 p20;

    ret = func_8012C1B8();
    *(s32 *)(a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C214(ret, 0);

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
    /* P36 S104 e22: the tag is ONE expression (each `|` a fresh single-set pseudo, so sched1's birthing boost,
     * sched.c:2469-2544, keeps the chain after the flags store) and the flags update is a plain `|=` — the old
     * shared `tmp` (a two-death pseudo, refused by local-alloc.c:472) needed a $2 pin; the `s0 = a0` copy needed $16. */
    *(s32 *)(a0 + 0x58) = (s32)&D_80190A08 | 0x10000000 | 0x20000000 | 0x40000000;
    if (*(s16 *)(a0 + 0x70) & 0x8000) {
        *(s16 *)(a0 + 0x34) = 1;
    }

    p20 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x20);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(p20 + 0x12) + D_80190810[(*(u16 *)(a0 + 0x70) & 0xF) * 6] + 0xE00;
    func_8012B2CC(a0);

    func_8012B178(a0, (s32)0xFFFC0000);

    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x2) += 1;
}
