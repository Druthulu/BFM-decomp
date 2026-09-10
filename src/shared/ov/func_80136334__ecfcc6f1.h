/* func_80136334 — shared body (overlay slot 0x80128158, h_exact ecfcc6f1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC[];
    extern s16 D_80126722;
    extern s16 D_80126724;
    u16 a1v;
    s16 a2v;
    s32 n;
    s16 *b4;
    s32 d;
    s32 dx;
    s32 denom;
    s32 result;
    s32 frame_pad[2];
    (void)&frame_pad;
    a1v = arg1;
    a2v = arg2;

    if (!(a1v & 1)) {
        dx = a2v - (*(s16 **)&D_8017F808)[2];
        d = dx;
        denom = -(*(s16 **)&D_8017F814)[2];
    } else {
        denom = (*(s16 **)&D_8017F814)[2];
        d = (*(s16 **)&D_8017F808)[2] - a2v;
        dx = -d;
    }
    n = -d;
    {
        s16 *b8 = *(s16 **)&D_8017F814;
        u16 *ac = *(u16 **)&D_8017F808;
        b4 = D_8017F810;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_8017F80C;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_8017F810[2] = a2v + 2;
        D_801152AC[0] = 0xFFF;
    } else {
        D_801152AC[0] = -0xFFF;
        D_8017F810[2] = a2v - 2;
    }
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}
