/* func_801787D4 — shared body (overlay slot 0x80128158, h_exact b406ba1f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern void func_80178840();
void func_801787D4(void) {
    u8 *p = D_801202A0;
    s32 i;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)(p + 0) != 0 && p[0xC0] != 0) {
            func_80178840(p);
        }
        p += 0x10C;
    }
}
