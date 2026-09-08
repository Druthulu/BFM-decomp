/* func_801479BC — shared body (overlay slot 0x80128158, h_exact 3a20d067). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801479BC(s32 a0, s32 a1, s32 a2) {
    s32 v0 = *(s32*)(a0 + 0x28) + a1;
    *(s32*)(a0 + 0x28) = v0;
    if (a1 < 0) {
        if (!(-a2 < v0)) {
            *(s32*)(a0 + 0x28) = -a2;
            return;
        }
    }
    if (a1 > 0) {
        if (!(*(s32*)(a0 + 0x28) < a2)) {
            *(s32*)(a0 + 0x28) = a2;
        }
    }
}
