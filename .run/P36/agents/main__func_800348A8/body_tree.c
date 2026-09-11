s32 func_800348A8(u32 arg0) {
    u16 *p;
    u16 *q;
    s32 i;
    u32 lo;
    u32 hi;
    s32 five;

    p = D_800A46E8;
    i = 0;
    five = 5;
    lo = arg0 & 0xFFFF;
    hi = arg0 >> 16;
    q = p + 3;
    do {
        __asm__ ("" :: "r"(i), "r"(i));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
        if (p[0] == five && q[-1] == lo) {
            if (hi == 0 || q[0] == hi) {
                return i + 1;
            }
        }
        i++;
        q += 0x2A;
        p += 0x2A;
    } while (i < 8);
    return 0;
}
