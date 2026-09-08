/* func_8014C59C — shared body (overlay slot 0x80128158, h_exact 60e5e4e3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 dx, s32 dy);
s32 func_8014C59C(void *a0, void *a1) {
    s32 dx = *(s16 *)((s32)a0 + 0x6) - *(s16 *)((s32)a1 + 0x6);
    s32 dy = *(s16 *)((s32)a0 + 0xE) - *(s16 *)((s32)a1 + 0xE);
    return ratan2(dx, dy) & 0xFFF;
}
