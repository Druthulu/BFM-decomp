/* func_8014C278 — shared body (overlay slot 0x80128158, h_exact 0d433e70). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80013328(s32 a0, s32 a1);
s32 func_8014C278(s32 a0, s32 a1, s32 a2) {
    return func_80013328(a0 + 4, a1 + 4) < (s32)(a2 & 0xFFFF);
}
