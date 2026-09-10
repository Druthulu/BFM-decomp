s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;

    u16 *ac;
    s16 *b8;
    s16 *b4;
    s32 r;
    register s32 pos __asm__("$12");  // !FAKE: pin $12 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 a1v __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s16 var_v0_3;
    s32 temp_a1;
    s32 var_t0;
    s32 var_v1;
    s16 *b4b;
    u16 *p;

    __asm__ ("" : "=r"(a1v) : "0"(arg1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
    pos = arg2;
    if (!(a1v & 1)) {
        var_t0 = (s16) arg2 - (*(s16 **)&D_801909BC)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_801909C8)[1];
    } else {
        var_a3 = (*(s16 **)&D_801909C8)[1];
        var_v1 = (*(s16 **)&D_801909BC)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_801909C8);
    ac = (*(u16 **)&D_801909BC);
    b4 = D_801909C4;
    temp_a1 = -var_v1;
    r = (temp_a1 * b8[0]) / var_a3;
    b4[0] = ac[0] + r;
    b4[1] = ac[1] + var_t0;
    r = (temp_a1 * b8[2]) / var_a3;
    temp_v0 = ac[2] + r;
    b4[2] = temp_v0;
    temp_v1 = b4[0];
    if (temp_v1 < M2C_FIELD(((void *)arg0), s16 *, 4)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 6) < temp_v1) {
        return 0;
    }
    if (temp_v0 < M2C_FIELD(((void *)arg0), s16 *, 0xC)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 0xE) < temp_v0) {
        return 0;
    }
    if (arg1 & 0x8000) {
        p = (*(u16 **)&D_801909C0);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_801909C4;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
        var_v0_3 = pos + 2;
    } else {
        b4b = D_801909C4;
        D_801152AA = -0xFFF;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
        var_v0_3 = pos - 2;
    }
    b4b[1] = var_v0_3;
    __asm__ __volatile__("" :: "r"(pos));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B t3_tus1)
    (*(s16 *)D_80126720) = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 4) + M2C_FIELD(((void *)arg0), s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 8) + M2C_FIELD(((void *)arg0), s16 *, 0xA)) >> 1);
    D_80126724 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 0xC) + M2C_FIELD(((void *)arg0), s16 *, 0xE)) >> 1);
    return 1;
}
