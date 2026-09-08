/* func_8014A3E0 — shared body (overlay slot 0x80128158, h_exact 2b0c6f41). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_801152B0;
extern s16 D_801152B4;
s32 func_8014A3E0(struct S_8014A3E0 *a0) {
    s32 sp[4];
    sp[0] = a0->h12 * D_801152B0;
    sp[2] = a0->h1A * D_801152B4;
    if (sp[0] >= 0 && sp[2] >= 0) {
        return 1;
    }
    *(s16 *)((char *)a0 + 0x6) = a0->h88;
    *(s16 *)((char *)a0 + 0xA) = a0->h8A;
    *(s16 *)((char *)a0 + 0xE) = a0->h8C;
    return 0;
}
