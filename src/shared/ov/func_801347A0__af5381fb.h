/* func_801347A0 — shared body (overlay slot 0x80128158, h_exact af5381fb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
    extern s16 * D_8017F80C;
    extern SVec_801347A0 * D_8017F808;
    extern SVec_801347A0 * D_8017F810;

    Elem_801347A0 *pElem;
    s32 val;
    register s32 iv __asm__("$4");
    s32 q;
    s32 dvsr;

    pElem = &((Elem_801347A0 *)arg2)[((S0_801347A0 *)arg1)->f2];
    val = ((s32 *)arg3)[((S0_801347A0 *)arg1)->f4];
    if (func_80134A28((s32)pElem, (s32)D_8017F80C, val) >= 0) {
        return 0;
    }
    iv = func_80134A28((s32)pElem, (s32)D_8017F808, val);
    if (iv < 0) {
        return 0;
    }
    iv = -iv;
    dvsr = pElem->f2 * 48;
    q = (iv * 48) / dvsr;
    D_8017F810->f0 = D_8017F808->f0;
    D_8017F810->f2 = D_8017F808->f2 + q;
    D_8017F810->f4 = D_8017F808->f4;
    if (func_80134A28((s32)&((Elem_801347A0 *)arg2)[((S0_801347A0 *)arg1)->f6], (s32)D_8017F810, ((s32 *)arg3)[((S0_801347A0 *)arg1)->f8]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem_801347A0 *)arg2)[((S0_801347A0 *)arg1)->fa], (s32)D_8017F810, ((s32 *)arg3)[((S0_801347A0 *)arg1)->fc]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem_801347A0 *)arg2)[((S0_801347A0 *)arg1)->fe], (s32)D_8017F810, ((s32 *)arg3)[((S0_801347A0 *)arg1)->f10]) < -0x2F00) {
        return 0;
    }
    if ((s16)arg0) {
        if (func_80134A28((s32)&((Elem_801347A0 *)arg2)[((S0_801347A0 *)arg1)->f12], (s32)D_8017F810, ((s32 *)arg3)[((S0_801347A0 *)arg1)->f14]) < -0x2F00) {
            return 0;
        }
    }
    if ((((S0_801347A0 *)arg1)->f0 & 0x300) != 0) {
        return 0;
    }
    D_8017F810->f0 = D_8017F808->f0;
    D_8017F810->f4 = D_8017F808->f4;
    (*(Elem_801347A0*)D_801152A8) = *pElem;
    D_8017F808->f6 = pElem->f2;
    return 1;
}
