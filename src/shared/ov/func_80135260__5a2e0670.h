/* func_80135260 — shared body (overlay slot 0x80128158, h_exact 5a2e0670). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3)
{
    /* BLOCK scope on purpose: this TU already declares D_8017F808/B0/B8 as `extern u8` inside
     * other function bodies (L2461-2463) and as `extern u16 *` inside others (L2587-2589).
     * A FILE-scope pointer decl here would make those inner `extern u8` decls conflicting-types.
     * The same reason keeps D_8018E6FC/D_8018E71C local (cf. the TU's own L3268-3270). */
    extern u16 *D_8017F808;
    extern u16 *D_8017F80C;
    extern u16 *D_8017F814;
    extern s32 D_8018E6FC;
    extern s32 D_8018E71C;

    u8 dead[56];
    s32 *p;
    s32 flag;
    s32 q;
    u16 *pa;
    u16 *pb;
    u16 *pc;
    u16 *pd;
    u16 *pe;
    u16 t;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, arg2, arg3)) {
    case 0:
        return 0;
    case 1:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        q = arg0 + 0x34;
        p = &D_8018E71C;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_8018E6FC;
        p = &D_8018E71C;
        flag = 1;
        break;
    }
    if (arg1 >= 0) {
        goto elsepath;
    }
    if (func_80135EB0(p, 0) != 0) {
        goto hit;
    }
    p = (s32 *)*p;
    if (p == 0) {
        return 0;
    }
loop:
    if (func_80135EB0(p, 0) == 0) {
        goto body;
    }
hit:
    func_80136A94(flag, arg0, (s32)arg3, q);
    return 1;
body:
    p = (s32 *)*p;
    if (p != 0) {
        goto loop;
    }
    return 0;
elsepath:
    pa = D_8017F80C;
    pb = D_8017F808;
    pc = D_8017F814;
    pc[0] = pa[0] - pb[0];
    pc[1] = pa[1] - pb[1];
    pc[2] = pa[2] - pb[2];
    if (func_80134A74(0, (s16)pb[0], (s16)pb[2], (int)p) != 0) {
        goto hit;
    }
    pd = D_8017F808;
    pe = D_8017F80C;
    t = pe[0];
    if (((pd[0] & 0xFF80) == (t & 0xFF80)) && ((pd[2] & 0xFF80) == (pe[2] & 0xFF80))) {
        return 0;
    }
    if (func_80134A74(0, (s16)t, (s16)pe[2], (int)p) != 0) {
        goto hit;
    }
    return 0;
}
