s32 func_80182358(s32 a0, u16 a1) {
    s16 sp10[4];
    s16 sp18[4];
    s16 sp20[4];
    s16 sp28[4];
    s16 pan;
    s16 vol;
    s32 v;
    s32 d;
    u16 *p;

    p = (u16 *)&D_80126B58;
    pan = 7;
    vol = 0x7F;
    sp10[0] = *(u16 *)(a0 + 0x6);
    sp10[1] = *(u16 *)(a0 + 0xA);
    sp10[2] = *(u16 *)(a0 + 0xE);
    ((void (*)(s16 *, s16 *))func_8012EFB8)(sp10, sp18);
    sp18[2] = 0;
    __asm__("" : "=r"(pan) : "0"(pan));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus8)

    v = sp18[0];
    if (v < 0) v = -v;
    if (v >= 0xA0) return 0;

    if (sp18[1] >= 0 ? sp18[1] >= 0x78 : -sp18[1] >= 0x78) return 0;

    pan += sp18[0] / 20;
    if (pan < 0) pan = 0;
    else if (pan >= 0x10) pan = 0xF;

    sp20[0] = p[3];
    sp20[1] = p[5];
    sp20[2] = p[7];
    ((void (*)(s16 *, s16 *))func_8012EFB8)(sp20, sp28);
    sp28[2] = 0;

    d = ((s32 (*)(s16 *, s16 *))func_800132BC)(sp18, sp28) - 0x100;
    if (d > 0) {
        vol -= (d * 127) / 25600;
        if (vol < 0) vol = 0;
    }
    func_8002D4C8(a1, (u16)(vol | ((pan << 8) | 0x3000)));
    return 1;
}
