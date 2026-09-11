s32 func_800331D4(s32 arg0) {
    u16 *p;
    register s32 i __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    p = D_800A46E8;
    i = 0;
    do {
        if ((*p & 0x3F) == 1 && p[2] == (arg0 & 0xFFFF)) {
            if (((u32)arg0 >> 16) == 0 || ((u32)arg0 >> 16) == p[3]) {
                return i + 1;
            }
        }
        i += 1;
        p += 42;
    } while (i < 8);
    return 0;
}
