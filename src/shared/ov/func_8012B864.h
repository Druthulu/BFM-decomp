/* func_8012B864 — shared body (overlay slot 0x80128158, h_exact e576eec4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CB8;
extern s16 D_80126CB4;
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8012B864(s32 a0) {
    s32 dx = *(s16*)(a0 + 0xE) - D_80126CB8;
    s32 dy = D_80126CB4 - *(s16*)(a0 + 0x6);
    return (ratan2(dx, dy) - 0x400) & 0xFFF;
}
