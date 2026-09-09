/* func_801343C4 — shared body (overlay slot 0x80128158, h_exact b50a7edb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{
    extern s32 func_80133AB0(s16 flag, s16 x, s16 y, s32 arg3);
    extern s16 * D_8017F808;
    extern s16 * D_8017F80C;
    extern u16 D_8018E6F8;
    extern u16 D_8018E6F4;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_8017F808;
    d94 = D_8018E6E8;
    pb0 = D_8017F80C;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_8018E6F8 = 0;
    D_8018E6F4 = 0;
    if (((int (*)(int, s16, s16, int))func_80133AB0)(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_8017F80C;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_8018E6F8;
        return 1;
    }

    pacs = D_8017F808;
    pb0s = D_8017F80C;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (((int (*)(int, s16, s16, int))func_80133AB0)(sangle, b0, pb0s[2], D_8018E6E8)) {
        goto setdst;
    }
    return 0;
}
