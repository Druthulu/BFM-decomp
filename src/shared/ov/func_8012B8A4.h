/* func_8012B8A4 — shared body (overlay slot 0x80128158, h_exact f56e3f4e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern u16 D_80126B66;
extern u16 D_80126B5E;
s32 func_8012B8A4(s16 *a0) {
    s16 cx = a0[7];
    s16 dx = D_80126B66;
    s16 dy = D_80126B5E;
    s16 cy = a0[3];
    return (ratan2(cx - dx, dy - cy) - 0x400) & 0xFFF;
}
