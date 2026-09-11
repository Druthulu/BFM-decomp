/* func_80177B5C — shared body (overlay slot 0x80128158, h_exact ef97c1ca). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s16 tbli;
s16 x;
s16 y;
{
    extern u8 D_80182A5C[];
    u32 *q;
    u32 v;
    u32 cl;
    u32 cs;
    u32 cl2;
    u32 tt2;
    u32 cs2;
    u32 ca;
    u32 mk1;
    u32 cc1;
    u32 flag;
    u32 n;
    u8 m;
    u16 t;
    s16 i;
    u32 col;
    u32 uv;
    u32 tt;
    u32 nv;
    u32 x1;
    u32 x2;
    u32 gg;
    s32 yt;
    u32 yl;
    u32 c;
    u16 bb;
    u32 c0;
    u32 w;

    mk1 = 0xFFFFFF;
    cc1 = 0x74808080;
    bb = bits;
    t = x + 0xE;
    flag = 0x1000000;
    i = 0;
    v = D_80182A5C[tbli];
    gg = ((u32)(p - 5)) & mk1;
    ca = 0x3000000;
    p[0] = gg | ca;
    x1 = (u16)(x - 3);
    x2 = (u16)(x + 5);
    p[1] = cc1;
    yt = y;
    c0 = yt + 1;
    c0 <<= 16;
    w = c0 | x1;
    __asm__("" : "=r"(w) : "0"(w)); // !FAKE: launder w — a second set of w stops sched1 launching the p[2] `or` at its store (birthing_insn_p, sched.c:2469), so it stays ahead of the cl chain and sched2's equal-priority tie (sched.c:2385) keeps that order; no plain spelling does (S103 c19) (P36 S103 c46 minimum-lever)
    c = v << 6;
    c |= 0x4016;
    cl = c << 16;
    p[2] = w;
    p[3] = cl | 0x1800;
    p += 5;
    p[0] = (((u32)(p - 5)) & mk1) | ca;
    p[1] = cc1;
    p[2] = c0 | x2;
    p[3] = cl | 0x1808;
    p += 5;
    q = p;
    yl = yt << 16;
    do {
        n = (u32)(bb << 16) >> 28;
        m = n;
        if (n != 0 || i == 2 || i == 0xFF) {
            flag = 0;
        }
        q[0] = (((u32)(q - 5)) & 0xFFFFFF) | 0x3000000;
        q[2] = (yl | t) | flag;
        col = 0x74808080;
        q[1] = col;
        nv = ((m * 8) + 8) | 0x4000;
        q[3] = cl | nv;
        q += 5;
        t += 8;
        i++;
        bb <<= 4;
    } while (i < 3);
    p = q;
    p[0] = (((u32)(p - 5)) & 0xFFFFFF) | 0x3000000;
    cs = y << 16;
    p[2] = cs | (u16)(x + 0x2A);
    cl2 = ((v << 6) | 0x4016) << 16;
    uv = tbli << 4;
    tt = uv | 0x1000;
    p[1] = col;
    p[3] = cl2 | tt;
    p += 5;
    p[0] = (((u32)(p - 5)) & 0xFFFFFF) | 0x3000000;
    cs2 = cs | (u16)(x + 0x32);
    tt2 = uv | 0x1008;
    p[1] = col;
    p[2] = cs2;
    p[3] = cl2 | tt2;
    p += 5;
    return p;
}
