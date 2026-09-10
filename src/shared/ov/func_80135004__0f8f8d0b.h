/* func_80135004 — shared body (overlay slot 0x80128158, h_exact 0f8f8d0b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80135004(s32 arg0, s32 p1, s32 p2)
{
    extern int func_80134A74(int, s16, s16, int);
    extern s16 * D_8017F80C;
    extern s16 * D_8017F808;
    extern u8 D_8017F814;
    extern s16 *D_8017F810;
    extern u16 D_8018E6F8;

    s16 *pb0;
    s16 *pac;
    s16 *pb8;
    u16 *pb4;
    u16 ax, bx, ay, by, az, bz;
    int id;
    int a1v, a2v;

    pb0 = D_8017F80C;

    ax = ((u16 *)p2)[0]; pac = D_8017F808; pb0[0] = ax; bx = ((u16 *)p1)[0]; pb8 = (*(s16 * *)&D_8017F814); pac[0] = bx; pb8[0] = ax - bx;
    ay = ((u16 *)p2)[1]; pb0[1] = ay; by = ((u16 *)p1)[1]; pac[1] = by; pb8[1] = ay - by;
    az = ((u16 *)p2)[2]; pb0[2] = az; bz = ((u16 *)p1)[2]; pac[2] = bz; pb8[2] = az - bz;

    id = ((int)arg0) & 0xFFFF;
    a1v = pac[0]; a2v = pac[2];
    D_8018E6F8 = 0;

    if (func_80134A74(id, a1v, a2v, D_8018E6E8)) {
    found:
        pb4 = (*(u16 * *)&D_8017F810);
        ((u16 *)p2)[0] = pb4[0];
        ((u16 *)p2)[1] = pb4[1];
        ((u16 *)p2)[2] = pb4[2];
        ((u16 *)p2)[3] = D_8018E6F8;
        return 1;
    }
    {
        u16 *qb;   /* D_8017F808 -> $a0 (reloaded) */
        int qa0;   /* D_8017F80C[0], kept in $a1 for the 2nd-call arg */
        u16 *qa;   /* D_8017F80C -> $a2 (reloaded) */
        qb = (u16 *)D_8017F808;
        qa = (u16 *)D_8017F80C;
        qa0 = qa[0];
        if (((qb[0] & 0xFF80) == (qa0 & 0xFF80)) &&
            ((qb[2] & 0xFF80) == (qa[2] & 0xFF80)))
            return 0;
        if (func_80134A74(id, (s16)qa0, (s16)qa[2], D_8018E6E8))
            goto found;
        return 0;
    }
}
