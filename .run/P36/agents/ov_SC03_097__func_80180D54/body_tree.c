s32 func_80180D54(void *a0, s32 a1) {
    s32 in[3];
    s32 out[3];
    s32 d;
    s16 e;
    register s32 ret __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    in[0] = *(s16 *)((s32)a0 + 6) - *(s16 *)&D_80126B5E;
    in[1] = 0;
    in[2] = *(s16 *)((s32)a0 + 0xE) - *(s16 *)&D_80126B66;
    Square0(in, out);

    d = D_80126B62 - *(u16 *)((s32)a0 + 0xA);
    e = d;
    if ((s16)d < 0) {
        e = -d;
    }

    ret = 0;
    if (out[0] + out[2] < (u16)a1 * (u16)a1) {
        ret = (s16)e < 4;
    }
    return ret;
}
