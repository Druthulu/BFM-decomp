/* func_80150FD8 — shared body (overlay slot 0x80128158, h_exact b6fa8969). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_800B99DA;
void func_80150FD8(s32 a0) {
    if (D_800B99DA & 7) {
        func_80146994(0x34, a0, 0, 0);
    }
}
