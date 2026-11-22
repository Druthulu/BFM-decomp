/* func_8013E22C — shared body (overlay slot 0x80128158, h_exact 16e22033). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void Square12(s32 *a0, s32 *a1);
s32 func_8013E22C(VecA *a0, Vec3s *a1) {
    s32 d[3];
    s32 sq[3];
    d[0] = a0->unk0.v0.unk2 - a1->x;
    d[1] = a0->unk0.v0.unk6 - a1->y;
    d[2] = a0->unk0.v0.unkA - a1->z;
    Square12(d, sq);
    return sq[0] + sq[1] + sq[2];
}
