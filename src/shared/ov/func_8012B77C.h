/* func_8012B77C — shared body (overlay slot 0x80128158, h_exact 5c649b51). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */
s32 func_8012B77C(s32 out, s32 from, s32 to) {
    Ang2_8012B77C_8012B77C t;
    s32 dx, dy, dz;
    s32 ang;
    s32 r1, r2;
    dz = *(s16 *)(to + 0xA) - *(s16 *)(from + 0xA);
    dx = *(s16 *)(to + 0x2) - *(s16 *)(from + 0x2);
    dy = *(s16 *)(to + 0x6) - *(s16 *)(from + 0x6);
    ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;
    t.hi = ang;
    r1 = func_80047948(ang);
    r2 = func_8004787C(ang);
    dz = (dz * r1 + dx * r2) >> 12;
    t.lo = ratan2(dy, -dz);
    *(Ang2_8012B77C_8012B77C *)out = t;
    return out;
}
