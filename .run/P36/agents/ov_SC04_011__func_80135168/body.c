int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §100); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801909BC;
    extern u8 D_801909C0;
    extern u8 D_801909C8;
    s16 *pb0;
    s16 *pac;
    s16 *pb8;
    u16 *pb4;
    u16 ax, bx, ay, by, az, bz;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801909C0);

    ax = p2[0]; pac = (*(s16 * *)&D_801909BC); pb0[0] = ax; bx = p1[0]; pb8 = (*(s16 * *)&D_801909C8); pac[0] = bx; pb8[0] = ax - bx;
    ay = p2[1]; pb0[1] = ay; by = p1[1]; pac[1] = by; pb8[1] = ay - by;
    az = p2[2]; pb0[2] = az; bz = p1[2]; pac[2] = bz; pb8[2] = az - bz;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801EDA30;
    ((H16 *)&D_801EDA40)->h = 0;
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
