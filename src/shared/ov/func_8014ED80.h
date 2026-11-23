/* func_8014ED80 — shared body (overlay slot 0x80128158, h_exact fce3e1eb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
s32 func_8014ED80(SubED80 *a0) {
    s16 g1[3];
    s16 g2[3];
    if (a0->unk44.s & 0x80000) {
        return 0;
    }
    if (a0->unk1F8.s & 0x4000000) {
        return 0;
    }
    g1[0] = a0->unk88.u;
    g1[1] = a0->unk8A.u - 0x10;
    g1[2] = a0->unk8C.u;
    g2[0] = a0->unk4.i.hi.u;
    g2[1] = a0->unk8.i.hi.u - 0x10;
    g2[2] = a0->unkC.i.hi.u;
    func_8014EE14((s32)a0, g1, g2);
}
