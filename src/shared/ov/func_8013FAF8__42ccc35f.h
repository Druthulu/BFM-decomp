/* func_8013FAF8 — shared body (overlay slot 0x80128158, h_exact 42ccc35f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013FAF8(s16 arg0, s16 arg1) {

    extern Hw4    D_8011516A[];
    extern Rec20  D_800AE7B8[];
    extern Blk60  D_8017F4C4[];
    extern Blk20  D_8017F7C4[];
    extern Prim4  D_8017F8C4[];
    extern Prim4  D_8017F934[];
    extern Prim4 *D_8017FA28[];
    extern s32    D_8017FA48[];
    extern u8 D_8017FA68;
    u8 sp18[72];
    s32 sp60[2];
    s32 *ot;
    s16 i;
    s16 j;
    s32 flag;
    s32 addr;
    Prim4 *p;
    s32 r;
    s32 t;
    s16 *pp;
    s32 flag2;
    register s32 flag3 __asm__("$18");

    func_80140E6C();
    func_80140F00();
    ot = func_80140958((s32 *)D_801151D0, arg0, arg1);
    if (D_8011511A < 6) {
        ot = (s32 *)func_80141100((int)ot);
    }
    for (i = arg0; i < arg1; i++) {
        if (i == D_8011511A || i == 2 || i == 4) {
            flag = 0;
        } else {
            flag = 0xFF;
        }
        p = &D_8017F8C4[i];
        if (i != 5) {
            if (i == 2) {
                addr = ((s32 *)&D_8017FA68)[*(s16 *)&D_80115128];
            } else {
                addr = D_8017FA48[i];
            }
        } else {
            addr = func_8013FFD8(2, func_8014168C(2), sp60);
        }
        func_80024054(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_8017FA28[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && *(s16 *)&D_80115128 != 0) {
                p = D_8017F934;
            }
            flag2 = flag;
            for (;;) {
                r = func_8013FFD8(i, j++, sp60);
                if (r == 0) {
                    break;
                }
                if (r < 0) {
                    func_80024054(r, sp18);
                    t = 1;
                    if (i == 0 && (D_80078EC0 & 0x7F) == j) {
                        t = 0xB6;
                    }
                    if (flag2 != 0) {
                        sp60[0] += -0x282828;
                    }
                    ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, t, sp60[0]);
                }
                p++;
            }
        }
        func_8005A600((s32)ot, 0, 0, 0x15, 0);
        flag3 = flag;
        *ot = 0x2000000;
        *ot = (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFFFFFF) | 0x2000000;
        D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] =
            (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);
        ot = func_800D29F8(flag3,
                           func_800D27DC(flag3 != 0, ot + 10, &D_8017F4C4[i], 8, D_8011516A[i].x),
                           &D_8017F7C4[i], 2, D_8011516A[i].x);
    }
    pp = &D_8017FE3C;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &D_800AE7B8[*(u16 *)&D_800B9A02], 2);
    }
    if (*pp != 0 && D_8017FE3E != 0) {
        ot = func_8013AB54(ot, D_800AE7B8[*(u16 *)&D_800B9A02].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    D_801151D0 = (s32)ot;
}
