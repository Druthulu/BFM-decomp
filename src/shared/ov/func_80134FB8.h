/* func_80134FB8 — shared body (overlay slot 0x80128158, h_exact ffd70f58). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80134FB8(s32 a0, s32 a1, s32 a2) {
    return *(s16*)(a0 + 0x0) * *(s16*)(a1 + 0x0)
         + *(s16*)(a0 + 0x2) * *(s16*)(a1 + 0x2)
         + *(s16*)(a0 + 0x4) * *(s16*)(a1 + 0x4)
         + a2;
}
