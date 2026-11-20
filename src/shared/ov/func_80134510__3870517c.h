/* func_80134510 — shared body (overlay slot 0x80128158, h_exact 3870517c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80134510(s32 param) {
    extern s32 func_801345F8(s32);
    extern Foo_80134510_80134510 * D_8017F808;
    extern Foo_80134510_80134510 * D_8017F80C;
    extern Foo_80134510_80134510 * D_8017F810;
    extern u16 D_8018E6F8;


    s32 ret = 0;
    Foo_80134510_80134510 *b0 = D_8017F80C;
    Foo_80134510_80134510 *ac = D_8017F808;
    u16 t0 = (u16)((Foo_80134510_80134510 *)param)->vx;
    u16 t2, t4;

    ((Foo_80134510_80134510 *)param)->pad = 0;
    ac->vx = t0;
    b0->vx = t0;
    t2 = (u16)((Foo_80134510_80134510 *)param)->vy;
    ac->vy = t2 - 4;
    b0->vy = t2 + 0x2FC;
    t4 = (u16)((Foo_80134510_80134510 *)param)->vz;
    ac->vz = t4;
    b0->vz = t4;

    if (func_801345F8((*(s32*)&D_8018E6E8)) != 0) {
        s16 x;
        ((Foo_80134510_80134510 *)param)->vy = (u16)D_8017F810->vy - 2;
        x = D_8017F808->pad;
        if (x >= -3019) {
            if (x < -1400) {
                ret = 0x4000;
            } else {
                ret = 0x8000;
            }
        } else {
            ret = 0x2000;
        }
        D_8017F808->pad = D_8018E6F8;
    }
    return ret;
}
