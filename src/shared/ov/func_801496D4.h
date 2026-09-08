/* func_801496D4 — shared body (overlay slot 0x80128158, h_exact a4d9cd33). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801496D4(void *a0) {
    s32 v0 = 0;
    if (*(s32 *)((s32)a0 + 0x178)) {
        return v0;
    }
    v0 = *(u16 *)((s32)a0 + 0xAC) & 0x40;
    if (v0) {
        v0 = 1;
    }
    return v0;
}
