/* func_8014A638 — shared body (overlay slot 0x80128158, h_exact cd1be7e1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014A638(s32 arg0) {
    s16 v;
    if (*(s32 *)((s32)arg0 + 0x44) & 0x10) {
        v = *(u16 *)((s32)arg0 + 0x188) - 4;
        *(s16 *)((s32)arg0 + 0x188) = v;
        if (v < 0) {
            *(s16 *)((s32)arg0 + 0x188) = 0;
        }
    }
}
