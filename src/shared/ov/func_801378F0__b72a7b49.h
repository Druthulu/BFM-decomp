/* func_801378F0 — shared body (overlay slot 0x80128158, h_exact b72a7b49). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801378F0(void) {

    extern u8 D_80127520[];
    extern u8 aD801269F0[] __asm__("D_801269F0"); /* §37 alias: TU canon is `extern int D_801269F0` */
    extern u8 D_80126A28[];
    extern u8 D_8017F078[];
    s32 i;
    s32 si;
    s32 di;
    u8 *p;

    func_80016714(D_80127520, 0xBFC);
    i = 0;
    si = 0;
    p = aD801269F0;
    di = 0;
    do {
        func_80016714(p, 0x4C);
        *(u16 *)&D_80126A28[di]     = *(u16 *)&D_8017F078[si];
        *(u16 *)&D_80126A28[di + 2] = *(u16 *)&D_8017F078[si + 2];
        *(u16 *)&D_80126A28[di + 4] = *(u16 *)&D_8017F078[si + 4];
        *(u16 *)&D_80126A28[di + 6] = *(u16 *)&D_8017F078[si + 6];
        p += 0x4C;
        i += 1;
        si += 8;
        di += 0x4C;
    } while (i < 3);
    func_8013A860();
}
