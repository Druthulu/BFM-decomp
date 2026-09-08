/* func_8014C3A4 — shared body (overlay slot 0x80128158, h_exact 1e2e5203). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3) {
    return func_8014C43C(a0, a1, a2, a3, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12));
}
