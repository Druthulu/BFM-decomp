/* func_8013E6AC — shared body (overlay slot 0x80128158, h_exact 55bb00e6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E6AC(void) {
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        s32 *ep;
        s32 *fp;
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_8017FE64;
        for (i = 0; i < 5; i++) {
            s32 *fa;
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_8017FE3C = 2;
        D_8017FE3E = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8017FE3E = 0;
        D_8017FE3C = 0;
        D_80115112 = 6;
    }
}
