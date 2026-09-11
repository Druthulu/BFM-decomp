void func_8017EE80(s32 a0)
{
    s32 s4;
    s32 s3;
    register s32 s2 __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus7)
    s32 s1;
    s32 s0;
    s32 v0;
    s32 v1;
    u16 buf[10];

    s4 = a0;
    s3 = (s32)D_80188838[*(s16 *)(s4 + 0x70)];
    if (s3 == 0) {
        return;
    }
    s2 = s3 + 6;
    for (;;) {
        s1 = ((s32 (*)(void))func_8012C194)();
        if (s1 != 0) {
            v1 = 0;
            s0 = (s32)&D_801C8C64;
            while (v1 < 0x20) {
                if (*(s16 *)s0 == 0) {
                    break;
                }
                v1 += 1;
                s0 += 0x1C;
            }
            v0 = 0x20;
            if (v1 == v0) {
                goto next;
            }
            *(s32 *)(s0 + 0xC) = s1;
            func_8001CC3C(s1, 0, 0, 0);
            *(s32 *)(s1 + 0x20) = (s32)D_801886BC;
            *(u8 *)(s1 + 0x27) = 0x4C;
            *(u16 *)(s1 + 0x2C) = 0xC020;
            *(u16 *)(s1 + 0x1A) = 0x2000;
            *(u16 *)(s1 + 0x18) = 0x2000;
            *(u32 *)(s1 + 4) |= 0x50000000;
            func_80128EA8(s1, s0 + 0x14, (s32)D_801886C8);
            v0 = 1;
            *(u16 *)(s0 + 0x0) = v0;
            v0 = *(u16 *)s3;
            *(u16 *)(s0 + 0x4) = v0;
            v0 = *(u16 *)(s2 - 4);
            *(u16 *)(s0 + 0x6) = v0;
            v0 = *(u16 *)(s2 - 2);
            *(s32 *)(s0 + 0x10) = s4;
            *(u16 *)(s0 + 0x8) = v0;
            v0 = *(u16 *)s3;
            buf[0] = v0;
            v0 = *(u16 *)(s2 - 4);
            buf[1] = v0;
            v1 = *(u16 *)(s2 - 2);
            buf[2] = v1;
            v0 = 0x3DB;
            buf[3] = v0;
            buf[5] = 0;
            buf[4] = 0;
            *(u32 *)&buf[8] = 0;
            buf[7] = 0;
            v0 = 0x7FFF;
            buf[6] = v0;
            func_8012C51C(buf, s4);
        }
next:
        v1 = *(s16 *)s2;
        if (v1 == -1) {
            break;
        }
        s2 += 8;
        s3 += 8;
    }
}
