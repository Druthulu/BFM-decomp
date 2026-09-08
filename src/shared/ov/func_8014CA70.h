/* func_8014CA70 — shared body (overlay slot 0x80128158, h_exact bbba14fb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
u16 func_8014CA70(s32 a0, s32 a1) {
    s32 base = *(s32 *)((s32)a0 + 0x78);
    return *(u16 *)((a1 << 1) + base + 0x14);
}
