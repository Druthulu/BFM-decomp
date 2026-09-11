void func_801834A4(s32 arg0) {

    extern s32 D_8018E894[];
    u16 pos[3];
    s32 i;
    s32 j;
    s32 u;
    s32 base;
    register s32 tmp __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 mod;
    s32 step;
    s32 obj;
    s32 half;
    register s32 hh __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 sign = 0;

    if ((D_800B99DA & 7) == 0) {
        pos[1] = 0;
        pos[2] = 0;
        for (i = 0; i < 6; i++) {
            u = D_8018E894[i];
            tmp = u * 0x600 + 0x2000;
            base = tmp;
            __asm__ ("" : "=r"(tmp) : "0"(tmp));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
            mod = (tmp << 16) >> 18;
            step = u * 6 + 0x12;
            half = step * 2;
            pos[0] = step;
            pos[1] -= 0x24;
            for (j = 0; j < 4; j++) {
                sign = half >> 31;
                obj = func_801850D8(1, (s16)(base + rand() % mod), 0, 0, pos, arg0,
                                    *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
                if (obj != 0) {
                    *(s32 *)(obj + 0x20) |= 0x800000;
                }
                hh = half;
                pos[0] -= hh / 3;
            }
        }
    }
}
