s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    s32 a1v;
    register s32 a2v __asm__("$12");  // !FAKE: pin $12 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 n;
    s16 *b4;
    s32 d;
    s32 dx;
    s32 denom;
    s32 result;
    s32 frame_pad[2];
    (void)&frame_pad;
    __asm__("" : "=r"(a1v) : "0"(arg1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
    a2v = arg2;

    if (!(arg1 & 1)) {
        dx = (s16) arg2 - (*(s16 **)&D_801909BC)[2];
        d = dx;
        denom = -(*(s16 **)&D_801909C8)[2];
    } else {
        denom = (*(s16 **)&D_801909C8)[2];
        d = (*(s16 **)&D_801909BC)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        s16 *b8 = *(s16 **)&D_801909C8;
        u16 *ac = *(u16 **)&D_801909BC;
        b4 = D_801909C4;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_801909C0;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_801909C4[2] = a2v + 2;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_801909C4[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B t3_tus1)
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}
