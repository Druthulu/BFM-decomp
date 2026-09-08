/* func_801636D0 — shared body (overlay slot 0x80128158, h_exact 176fa9de). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern u16 D_80126B18[];
extern s32 D_80115200;
void func_801636D0(s32 a0, s32 a1) {
    u32 i;
    s32 v;
    u16 *p;
    s32 *q;
    i = 0;
    v = a1 & 0x7FFF;
    p = D_80126B18;
    q = &D_80115200;
    do {
        if (*q & 1) {
            func_8014AD30(a0, p, 0, v & 0xFFFF);
        }
        p += 4;
        i++;
        q += 1;
    } while (i < 3);
}
