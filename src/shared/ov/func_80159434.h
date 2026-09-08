/* func_80159434 — shared body (overlay slot 0x80128158, h_exact e278b8df). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80159434(s32 a0, s32 a1) {
    s32 a2 = *(s32 *)((s32)a0 + 0x20);
    u16 v1 = *(u16 *)((s32)a0 + 0x23A);
    u16 v0 = *(u16 *)((s32)a2 + 0x10);
    *(u16 *)((s32)a2 + 0x10) = (v0 - v1) & 0xFFF;
    return (*(s32 *)((s32)a0 + 0x238) += a1);
}
