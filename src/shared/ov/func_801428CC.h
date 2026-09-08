/* func_801428CC — shared body (overlay slot 0x80128158, h_exact c6b01ebe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80142DB8(s32 *a0);
extern s32 func_80142D38(s32 *a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
void func_801428CC(s32 *a0) {
    if (func_80142DB8(a0) == 1) {
        func_80142BB4(a0, 1, 3);
    } else if (func_80142D38(a0) == 1) {
        func_80142BB4(a0, 0, 3);
    }
}
