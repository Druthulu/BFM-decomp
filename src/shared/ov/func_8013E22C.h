/* func_8013E22C — shared body (overlay slot 0x80128158, h_exact 16e22033). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void Square12(s32 *a0, s32 *a1);
s32 func_8013E22C(struct VecA *a0, struct VecB *a1) {
    s32 d[3];
    s32 sq[3];
    d[0] = a0->unk2 - a1->unk0;
    d[1] = a0->unk6 - a1->unk2;
    d[2] = a0->unkA - a1->unk4;
    Square12(d, sq);
    return sq[0] + sq[1] + sq[2];
}
