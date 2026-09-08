/* func_80149210 — shared body (overlay slot 0x80128158, h_exact 6eedcb4a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80149210(s32 a0, s32 a1) {
    *(s32 *)((s32)a0 + 0x1E4) = a1 | (a1 << 16);
    *(s16 *)((s32)a0 + 0x1E4) = a1;
    *(s16 *)((s32)a0 + 0x1E6) = a1;
}
