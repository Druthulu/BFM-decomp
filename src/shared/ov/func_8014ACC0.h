/* func_8014ACC0 — shared body (overlay slot 0x80128158, h_exact 018e2b51). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014ACC0(s32 a0, s32 a1) {
    s16 v0;
    v0 = *(u16 *)((s32)a0 + 0x1C8) - a1;
    *(s16 *)((s32)a0 + 0x1C8) = v0;
    if (v0 < 0) {
        *(s16 *)((s32)a0 + 0x1C8) = 0;
    }
}
