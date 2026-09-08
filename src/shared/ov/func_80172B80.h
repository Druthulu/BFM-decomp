/* func_80172B80 — shared body (overlay slot 0x80128158, h_exact 6eafeaf2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801150F8;
extern void func_80147060(u8 *a0);
extern void func_80171A1C(u8 *a0);
extern void func_80172BC8(void *a0);
void func_80172B80(u8 *a0) {
    if (D_801150F8 == 0) {
        func_80147060(a0);
    }
    func_80171A1C(a0);
    func_80172BC8(a0);
}
