/* func_8017E404 — shared body (overlay slot 0x80128158, h_exact 7c41de81). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 ratan2(s32, s32);
extern void func_8012B0B4(SVEC *, s32, s32);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
s32 func_8017E404(s32 param_1, s32 param_2)
{
    register s32 p1 __asm__("$16") = param_1;
    register s32 p2 __asm__("$17") = param_2;
    SVEC in;
    SVEC out;
    SVEC buf;
    s32 d;
    s32 ang;
    u16 px, pz;
    s32 a0v;
    a0v = p1 + 4;
    __asm__ __volatile__("" : : "r"(p2), "r"(a0v));
    if (((s32 (*)(s32, s32))func_8012BC60)(a0v, p2 + 4) >= 0x1000) {
        return 0;
    }
    ang = ratan2((s32)*(s16 *)(p1 + 0xe) - (s32)*(s16 *)(p2 + 0xe),
                 (s32)*(s16 *)(p2 + 6) - (s32)*(s16 *)(p1 + 6));
    func_8012B0B4(&buf, (ang - 0x400) & 0xfff, 0x41);
    d = *(s32 *)&buf;
    px = *(u16 *)(p2 + 6);
    out.vx = px;
    out.vy = *(u16 *)(p2 + 0xa);
    pz = *(u16 *)(p2 + 0xe);
    out.vz = pz;
    out.vx = px + d;
    out.vz = pz + (d >> 16);
    in.vx = *(u16 *)(p1 + 0x3a);
    in.vy = *(u16 *)(p1 + 0x3e);
    in.vz = *(u16 *)(p1 + 0x42);
    if ((((s32 (*)(SVEC *, SVEC *, s32))func_8012CEB0)(&in, &out, 0) & 0x2000) == 0) {
        ((void (*)(s32))func_8012ADE4)(p1);
        return 1;
    }
    *(s16 *)(p1 + 6) = out.vx;
    *(s16 *)(p1 + 0xa) = out.vy;
    *(s16 *)(p1 + 0xe) = out.vz;
    return 1;
}
