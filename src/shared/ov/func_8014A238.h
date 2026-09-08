/* func_8014A238 — shared body (overlay slot 0x80128158, h_exact 01dbf78c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern s32 func_8014C2B0(void *a0, void *a1, s32 a2);
extern u8 D_801202A0[];
s32 func_8014A238(s32 arg0) {
    u32 i;
    Entry8014A238 *p;
    for (i = 0; i < 0x60; i++) {
        p = &((Entry8014A238 *)D_801202A0)[i];
        if ((p->f_0 != 0) && (p->f_AA != 0) &&
            (func_8014C278(arg0, (s32)p, 0x30) != 0) &&
            (func_8014C2B0((void *)arg0, (void *)p, 0x200) != 0)) {
            return (s32)p;
        }
    }
    return 0;
}
