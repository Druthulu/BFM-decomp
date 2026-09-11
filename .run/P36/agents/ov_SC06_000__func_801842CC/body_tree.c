void func_801842CC(s32 arg0)
{
    s32 s0;
    for (s0 = 0; s0 < 0x49; s0 += 0x18) {
        s32 a1 = func_80132EF4(arg0, 0x22);
        if (a1 == 0)
            continue;
        {
            s32 v0;
            register s32 v1 __asm__("v1");  // !FAKE: pin v1 — NEEDED DIFFERS (P36 rung B tus7)
            register s32 a0 __asm__("a0");  // !FAKE: pin a0 — NEEDED DIFFERS (P36 rung B tus7)
            v0 = *(u16 *)(arg0 + 0x84);
            a0 = *(u16 *)(a1 + 0xE);
            v0 &= 0x4;
            v1 = v0 * 2;
            __asm__("":"=r"(v1):"0"(v1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus7)
            v1 = v1 + v0;
            v1 = s0 + v1;
            v1 = v1 - 0x2A;
            v0 = *(u16 *)(a1 + 0x6);
            a0 += 0x28;
            *(u16 *)(a1 + 0xE) = a0;
            v0 -= v1;
            *(u16 *)(a1 + 0x6) = v0;
            v0 = *(u16 *)(a1 + 0xA);
            v1 = v1 << 16;
            v0 -= 0x20;
            *(u16 *)(a1 + 0xA) = v0;
            v0 = v1 >> 16;
            if (v0 >= 0) {
                v0 = v0 << 7;
            } else {
                v0 = v0 << 7;
                v0 = -v0;
            }
            v0 += 0x1000;
            *(u16 *)(a1 + 0x34) = v0;
            *(s32 *)(a1 + 0x14) = 0xFFFE0000;
            *(s32 *)(a1 + 0x18) = 0x30000;
        }
    }
}
