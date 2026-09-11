void func_80184EFC(s32 a0) {
    extern s32 D_80190A08;
    extern u16 D_80190810[];
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    register s32 tmp __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 ret;
    s32 sub;
    u16 nib;
    s32 p20;
    s32 val;
    s32 sub2;

    s0 = a0;
    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4((void *)s0);
        return;
    }

    func_8001C214(ret, 0);

    /* §164-29: ONE shared pseudo for the flags temp and the tag accumulator.
     * The WAR edge from `sh tmp` to the tag chain's first def is what pins the
     * whole D_80190A08|0x70000000 build BELOW the flags store (target leaves the
     * `lw 0x20(s0)` load-delay slot a real nop). Split temps let sched1 hoist
     * the tag chain into that slot. The $2 pin fixes the resulting
     * $v0>$v1>$a0 local-alloc rotation. */
    sub = *(s32 *)(s0 + 0x20);
    tmp = *(u16 *)(sub + 0x2C);
    tmp = tmp | 0x10;
    *(u16 *)(sub + 0x2C) = tmp;

    tmp = (s32)&D_80190A08;
    tmp = tmp | 0x10000000;
    tmp = tmp | 0x20000000;
    tmp = tmp | 0x40000000;
    *(s32 *)(s0 + 0x58) = tmp;
    if (*(s16 *)(s0 + 0x70) & 0x8000) {
        *(s16 *)(s0 + 0x34) = 1;
    }

    nib = *(u16 *)(s0 + 0x70) & 0xF;
    p20 = *(s32 *)(*(s32 *)(s0 + 0x64) + 0x20);
    val = *(u16 *)(p20 + 0x12) + *(u16 *)((u8 *)D_80190810 + nib * 12);
    val = val + 0xE00;
    sub2 = *(s32 *)(s0 + 0x20);
    *(u16 *)(sub2 + 0x12) = val;
    func_8012B2CC(s0);

    func_8012B178(s0, (s32)0xFFFC0000);

    *(s32 *)(s0 + 0x1C) = 0x20;
    *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
}
