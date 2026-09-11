void func_80037EA0(void)
{
    extern void func_8003D3B4(s32, s32);
    register u8 *p __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    s32 i;
    u32 mask;

    i = 0;
    mask = 0xFFF9FFFF;
    p = D_800C6E2E;
    do {
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= mask;
            p[0] = 0;
        }
        i++;
        p += 0x60;
    } while (i < 0x10);
}
