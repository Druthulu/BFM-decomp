/* func_8014E284 — shared body (overlay slot 0x80128158, h_exact 8425223e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);  /* canonical (engine_core.h:11555) */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80012A60(s32 a0, s32 a1);
s32 func_8014E284(s32 a0, s16 *arg1, s16 *arg2) {
    u16 *a1 = (u16 *)arg1;
    u16 *a2 = (u16 *)arg2;
    EntSC01077 *p;
    s16 dx;
    s16 dz;
    s16 ax;
    s16 az;
    s32 r1;
    s32 r2;
    dx = a2[0] - a1[0];
    dz = a2[2] - a1[2];
    if ((s16)(dx | dz) != 0) {
        for (p = (EntSC01077 *)D_801202A0; p < (EntSC01077 *)D_801202A0 + 96; p++) {
            if (p->f00 == 0) continue;
            if (p->f58 == 0) continue;
            if ((p->f5C & 0x1000) == 0) continue;
            /* §17a-1 fn-ptr cast: keep the canonical extern, call with the intended sig. */
            if (((s32 (*)(s32, s32, u16 *, u16 *))func_80135A4C)(p->f20, p->f58, a1, a2) == 0) continue;
            ax = p->f06 - *(u16 *)(a0 + 6);
            az = p->f0E - *(u16 *)(a0 + 0xE);
            r1 = (s16)ratan2(dz, dx);
            r2 = (s16)ratan2(az, ax);
            if ((s16)func_80012A60(r1, r2) < 0x400) {
                *(s32 *)(a0 + 0x170) = (s32)p;
                *(u16 *)(a0 + 6) = a2[0];
                *(u16 *)(a0 + 0xA) = a2[1] + 0x10;
                *(u16 *)(a0 + 0xE) = a2[2];
                return 1;
            }
        }
    }
    return 0;
}
