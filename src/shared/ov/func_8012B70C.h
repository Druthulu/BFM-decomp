/* func_8012B70C — shared body (overlay slot 0x80128158, h_exact 8e7aeefd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8012B70C(s16 *a0, s16 *a1) {
    s16 ax = a0[2];
    s16 bx = a1[2];
    s16 by = a1[0];
    s16 ay = a0[0];
    return (ratan2(ax - bx, by - ay) - 0x400) & 0xFFF;
}
