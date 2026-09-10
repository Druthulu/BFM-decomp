int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{
    extern u8 D_801909BC;
    extern u8 D_801909C0;
    extern u8 D_801909C8;
    s16 *pb0;
    s16 *pac;
    s16 *pb8;
    u16 *pb4;
    u16 a0, b0, a1, b1, a2, b2;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801909C0);

    a0 = p2[0]; pac = (*(s16 * *)&D_801909BC); pb0[0] = a0; b0 = p1[0]; pb8 = (*(s16 * *)&D_801909C8); pac[0] = b0; pb8[0] = a0 - b0;
    a1 = p2[1]; pb0[1] = a1; b1 = p1[1]; pac[1] = b1; pb8[1] = a1 - b1;
    a2 = p2[2]; pb0[2] = a2; b2 = p1[2]; pac[2] = b2; pb8[2] = a2 - b2;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801EDA30;
    D_801EDA40 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_801909C4);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801EDA40;
        return 1;
    }
    return 0;
}
