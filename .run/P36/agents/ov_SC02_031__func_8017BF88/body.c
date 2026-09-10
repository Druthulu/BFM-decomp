void func_8017BF88(s32 a0) {
    extern u8 D_8018865C[];
    s16 sp10[4];
    s16 sp18[16];
    s32 s0;
    s32 s2;
    s32 s3;
    u16 r;
    s32 scale;
    s32 c;

    s2 = *(s32 *)(a0 + 0x34);
    s0 = func_800D21C4(a0, D_8018865C, 0x2A);
    if (s0 == 0) {
        ((void (*)(s32))func_80146C3C)(a0);
        return;
    }
    *(s32 *)(a0 + 0x20) = s0;
    *(s16 *)(s0 + 0x2A) = 0x1F0;
    s3 = *(s32 *)(s2 + 0x20) + 0x34;
    r = rand();
    if (*(s32 *)(a0 + 0x2C) == 0) {
        scale = 0x1000;
        sp10[0] = (r & 0xFF) + 0x240;
        *(s16 *)(s0 + 0x28) = 0x240;
        *(s16 *)(s0 + 0x18) = scale;
    } else {
        scale = 0x200;
        sp10[0] = ((r & 0xFF) << 2) + 0xD00;
        *(s16 *)(s0 + 0x28) = 0x244;
        *(s16 *)(s0 + 0x18) = 0x1800;
    }
    sp10[1] = ((r & 0x7F00) >> 5) + 0xE00;
    sp10[2] = 0;
    RotMatrixYXZ(sp10, sp18);
    func_80048EAC((void *)s3, sp18);
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = scale;
    ApplyMatrixSV(sp18, sp10, sp10);
    c = *(u16 *)(a0 + 0x2);
    *(s32 *)(a0 + 0x10) = sp10[0] << 8;
    *(s32 *)(a0 + 0x14) = sp10[1] << 8;
    *(s32 *)(a0 + 0x18) = sp10[2] << 8;
    *(s32 *)(a0 + 0x1C) = 0x20;
    c++;
    *(u16 *)(a0 + 0x2) = c;
}
