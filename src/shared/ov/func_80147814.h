/* func_80147814 — shared body (overlay slot 0x80128158, h_exact 61479027). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80147814(s32 a0, s32 a1) {
    s32 v0 = *(s32*)(a0 + 0x34) + a1;
    *(s32*)(a0 + 0x34) = v0;
    if (a1 < 0) {
        if (v0 < (s32)0xFFE10000) {
            *(s32*)(a0 + 0x34) = (s32)0xFFE10000;
            return;
        }
    }
    if (a1 > 0) {
        if ((s32)0x1F0000 < *(s32*)(a0 + 0x34)) {
            *(s32*)(a0 + 0x34) = 0x1F0000;
        }
    }
}
