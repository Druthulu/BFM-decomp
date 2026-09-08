/* func_8014E048 — shared body (overlay slot 0x80128158, h_exact eab8167e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80012A60(s32 a0, s32 a1);
extern s32 ratan2(s32 a0, s32 a1);
extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */
extern s16 D_801152AC;
s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3)
{
    s32 dx;
    s32 dz;
    s32 w0;
    s32 w1;
    s32 t2;
    s32 p1;
    register s32 h __asm__("$4");   /* a0 — the b[0]-store copy temp (RC-4b) */
    register u16 *p3 __asm__("$7");   /* a3 — force the addu a3,a2 copy to materialize (RC-3) */
    u16 *psVar11;
    s32 sVar7;
    s16 sVar8;
    u32 uVar10;
    short a[3];
    short b[3];
    __asm__("addu %0,%1,$zero" : "=r"(p3) : "r"(param_3));
    w0 = p3[0];
    w1 = param_2[0];
    dx = w0 - w1;
    p1 = param_1;
    __asm__ __volatile__("" : : "r"(p1), "r"(param_2));
    w0 = p3[2];
    w1 = param_2[2];
    dz = w0 - w1;
    if ((short)(dx | dz) != 0) {
        h = dx;
        b[0] = (short)h;
        b[1] = p3[1] - param_2[1];
        t2 = p3[2] - param_2[2];
        b[2] = t2;
        b[0] = -(short)dx;
        b[2] = -t2;
        psVar11 = *(u16 **)(p1 + 0x170);
        if (*psVar11 != 0) {
            if ((psVar11[0x2e] & 0x1000U) != 0) {
                sVar8 = (s16)dz;
                if (*(s32 *)(psVar11 + 0x2c) != 0) {
                    if (((s32 (*)(s32, s32, u16 *))func_80135A4C)(*(s32 *)(psVar11 + 0x10), *(s32 *)(psVar11 + 0x2c), param_2) != 0) {
                        s32 ndz = psVar11[3] - *(u16 *)(p1 + 6);
                        s32 ndx = psVar11[7] - *(u16 *)(p1 + 0xe);
                        sVar7 = (s16)ratan2((s32)sVar8, (s32)(s16)dx);
                        sVar8 = (s16)ratan2((s32)(s16)ndx, (s32)(s16)ndz);
                        if ((s16)func_80012A60(sVar7, sVar8) < 0x400) {
                            a[0] = psVar11[3];
                            a[1] = psVar11[5];
                            a[2] = psVar11[7];
                            b[0] = a[0] + b[0];
                            b[1] = a[1] + b[1];
                            b[2] = a[2] + b[2];
                            uVar10 = ((s32 (*)(s32, void *, void *))func_80133784)(0, a, b);
                            if ((uVar10 == 0) || (((uVar10 & 0x2000) != 0) && ((*(u16 *)D_801152A8 | *(u16 *)&D_801152AC) == 0))) {
                                psVar11[3] = b[0];
                                psVar11[5] = b[1];
                                psVar11[7] = b[2];
                            } else {
                                *(u16 *)(p1 + 6) = *param_2;
                                *(u16 *)(p1 + 10) = param_2[1] + 0x10;
                                *(u16 *)(p1 + 0xe) = param_2[2];
                            }
                            return 1;
                        }
                    }
                }
            }
        }
    }
    *(s32 *)(p1 + 0x170) = 0;
    return 0;
}
