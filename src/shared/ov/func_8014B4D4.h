/* func_8014B4D4 — shared body (overlay slot 0x80128158, h_exact 54bfb72a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80166244();
extern s32 D_80078E98;
void func_8014B4D4(void *a0) {
    *(u16 *)((s32)a0 + 0x1C8) = 0;
    D_80078E98 = 0x80000000;
    func_80166244();
}
