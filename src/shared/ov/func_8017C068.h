/* func_8017C068 — shared body (overlay slot 0x80128158, h_exact e4701d13). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C068(void) {
    extern u8 D_801202A0[];
    extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);
    u8 *p;
    short i;
    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x6B) {
            if (*(s32 *)(p + 0xCC) != 0) {
                func_80016714(*(void **)(p + 0xCC), 0x38);
            }
            if (*(s32 *)(p + 0xD0) != 0) {
                func_80016714(*(void **)(p + 0xD0), 0x38);
            }
            func_8012C218(p);
            return;
        }
        p += 0x10C;
    }
}
