/* func_80135888 — shared body (overlay slot 0x80128158, h_exact 4a3066ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80135888(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad_[8];
    register s32 m __asm__("$2");
    s32 sp;
    register s32 p1   __asm__("$17");
    register s32 mode __asm__("$18");
    register s32 p0   __asm__("$19");
    register s32 base __asm__("$20");
    register s32 p3   __asm__("$21");

    p0 = arg0;
    p1 = arg1;
    p3 = arg3;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, (s16 *)arg2, (s16 *)arg3)) {
    case 0:
        return 0;
    case 1:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 0;
        break;
    case 2:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 1;
        break;
    case 3:
        base = p0 + 0x34;
        sp = (s32)&D_8018E71C;
        mode = 0;
        break;
    case 4:
        base = (s32)&D_8018E6FC;
        sp = (s32)&D_8018E71C;
        mode = 1;
        break;
    }

    if (p1 < 0) {
        if (func_80135EB0(sp, 0) != 0) {
            func_80136A94(mode, p0, p3, base);
            return 1;
        }
        sp = *(s32 *)sp;
        __asm__ __volatile__("");
        while (sp != 0) {
            if (func_80135EB0(sp, 0) != 0) {
hit:
                func_80136A94(mode, p0, p3, base);
                return 1;
            }
            sp = *(s32 *)sp;
        }
        return 0;
    }
    {
        u16 *pb = (*(u16 * *)&D_8017F80C);
        u16 *pa = (*(u16 * *)&D_8017F808);
        s16 *pc = (*(s16 * *)&D_8017F814);
        pc[0] = pb[0] - pa[0];
        pc[1] = pb[1] - pa[1];
        pc[2] = pb[2] - pa[2];
        if (func_80134A74(0, (s16)pa[0], (s16)pa[2], sp) == 0) {
            return 0;
        }
    }
    goto hit;
}
