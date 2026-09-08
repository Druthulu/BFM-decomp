/* func_80172590 — shared body (overlay slot 0x80128158, h_exact 7d4c601d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80172590(u8 *a0) {
    s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x1;
    *(u32 *)((s32)a0 + 0x1F4) = v0;
    return v0;
}
